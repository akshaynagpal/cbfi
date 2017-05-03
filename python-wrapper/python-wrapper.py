from pygdbmi.gdbcontroller import GdbController
from pprint import pprint
import sys
import json
import subprocess

"""
Using pygdbmi.
Use pip install pygdbmi to run this script
"""

def gdb_read(gdb_controller,raise_error = False):
	list_of_gdb_messages = []

	while True:
		response = gdb_controller.get_gdb_response(raise_error_on_timeout=False)
		if len(response) == 0:
			break
		for msg in response:
			if msg['message'] is None or msg['payload'] is None:
				continue
			list_of_gdb_messages.append(msg)
	return list_of_gdb_messages

def get_linecount_string(out, source_file_name, abrupt):
	"""
	Currently assuming that all the lines of the C file would be at the
	top of the gcov data and the header file lines would be at the bottom.
	So we would be stopping when he encounter an .h file in the report
	"""
	process = False
	exec_count = ""
	for line in out:
		if 'file' in line and source_file_name in line:
			process = True
			continue
		elif process and 'lcount' in line:
			exec_count += line.split(',')[1]
		elif process and 'file' in line and '.h' in line:
			break
	return exec_count


libc_mapping = {
	'FOPEN':'FOPEN_FAIL'
}


if __name__ == "__main__":

	if len(sys.argv) < 2:
		print "Usage: python python-wrapper <config.json>"
		exit()

	configfilename = sys.argv[1]

	with open(configfilename,'rb+') as configfile:
		contents = configfile.read()

	config_json = json.loads(contents)

	if 'FAIL_CALL' not in config_json \
		or 'SOURCE_FILE_PATH' not in config_json \
		or 'SOURCE_FILE_NAME' not in config_json \
		or 'EXECUTABLE' not in config_json :
		print "Incorrect format: Refer to sampleconfig.json for correct format"
		exit()

	# TODO: Write check in fail is in mapping
	fail_call = config_json['FAIL_CALL']
	call_to_fail = libc_mapping[fail_call]
	source_file_path = config_json['SOURCE_FILE_PATH']
	source_file_name = config_json['SOURCE_FILE_NAME']
	executable = config_json['EXECUTABLE']
	call_num_to_fail = -1

	current_run = 1

	exec_set = set()
	error_lines = []

	while True:

		call_num_to_fail += 1

		gdbmi = GdbController(gdb_args=[executable,'-nx','--quiet', '-interpreter=mi2'])

		responses = gdb_read(gdb_controller=gdbmi)

		gdbmi.write('set environment LD_PRELOAD=../wrapper/wrap-fopen.so', read_response=False)

		"""
		We will be setting the environment variables for failing libc calls over here
		"""
		gdbmi.write('set environment {0}={1}'.format(call_to_fail, call_num_to_fail), read_response=False)

		gdbmi.write('br main', read_response=False)
		responses = gdb_read(gdb_controller=gdbmi)
		#pprint(responses)
		#print("\n\n")

		gdbmi.write('run', read_response=False)
		responses = gdb_read(gdb_controller=gdbmi)
		#pprint(responses)
		#print("\n\n")

		# The program execution stops here because break on main would have reached
		break_outer = False
		abrupt =False
		while(True):

			gdbmi.write('call __gcov_flush()', read_response=False)

			gdbmi.write('next', read_response=False)
			responses = gdb_read(gdb_controller=gdbmi)

			#pprint(responses)
			#print("\n\n")

			for response in responses:
				if response['message'] == 'stopped' \
					and response['payload']['reason'] == 'end-stepping-range' \
					and response['payload']['frame']['file'] == source_file_name:
					current_lineno = int(response['payload']['frame']['line'])

				elif response['message'] == 'stopped' and response['payload']['reason'] == 'exited-signalled':
					break_outer = True
					abrupt = True
				elif response['message'] =='stopped' and response['payload']['reason'] == 'exited-normally':
					break_outer = True

			
			if break_outer:
				gdbmi.write('call __gcov_flush()', read_response=False)
				break

		gdbmi.exit()

		process = subprocess.Popen(['gcov', '-i', source_file_path], stdout=subprocess.PIPE)
		out, err = process.communicate()
		
		with open('{0}.{1}'.format(source_file_name,'gcov'), 'r') as gcovfile:
			gcovdata = gcovfile.read().split('\n')

		#pprint(gcovdata)
		exec_string = get_linecount_string(gcovdata, source_file_name, abrupt)

		# Delete gcda file
		subprocess.call(['rm', '{0}.{1}'.format(source_file_path[:-2],'gcda')])

		# Delete gcov file
		subprocess.call(['rm', '{0}.{1}'.format(source_file_name,'gcov')])
		
		if abrupt:
			error_lines.append(current_lineno)

		if exec_string in exec_set:
			break
		else:
			exec_set.add(exec_string)

		current_run += 1