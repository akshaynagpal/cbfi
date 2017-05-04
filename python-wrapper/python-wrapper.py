from __future__ import division
from pygdbmi.gdbcontroller import GdbController
from pprint import pprint
import sys
import json
import subprocess
from collections import deque

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

def should_not_proceed(allexecutions, exec_string):
	"""last2_execs = allexecutions[-2:]

	if len(last2_execs) == 2 and exec_string == last2_execs[0] and exec_string == last2_execs[1]:
		return True
	else:
		return False"""
	last_exec = allexecutions[-2:]

	if exec_string in last_exec:
		return True
	#if len(last_exec) == 1 and exec_string == last_exec[0]:
	#	return True
	else:
		return False

def create_new_call_fail_dictionary(calls_failed, call, current_max_call):
	new_call_fail_dict = dict(calls_failed)
	if call in new_call_fail_dict:
		new_call_fail_dict[call].append(current_max_call)
	else:
		new_call_fail_dict[call] = [current_max_call]

	return new_call_fail_dict



def do_processing(executable, arguments, source_file_name, source_file_path, call_fail_dict):

	error_lineno = -1

	exec_args = arguments.split(" ")
	if len(exec_args) != 0:
		gdb_exec_args = ['-nx','--quiet', '-interpreter=mi2', '--args', executable] + exec_args
	else:
		gdb_exec_args = ['-nx','--quiet', '-interpreter=mi2', '--args', executable]


	#print gdb_exec_args

	gdbmi = GdbController(gdb_args=gdb_exec_args)

	responses = gdb_read(gdb_controller=gdbmi)

	gdbmi.write('set environment LD_PRELOAD={0}'.format(library), read_response=False)

	print "\n",call_fail_dict

	for call, fail_nums in call_fail_dict.iteritems():
		#We will be setting the environment variables for failing libc calls over here
		call_nums = ','.join(map(str, fail_nums))
		gdbmi.write('set environment {0}={1}'.format(call, call_nums), read_response=False)
		#print 'set environment {0}={1}'.format(call_to_fail, call_nums)

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
		#print "test"
		#pprint(responses)
		#print("\n\n")

		for response in responses:
			if response['message'] == 'stopped' \
				and response['payload']['reason'] == 'end-stepping-range' \
				and response['payload']['frame']['file'] == source_file_name:
				error_lineno = int(response['payload']['frame']['line'])
				#pprint(response)
			elif response['message'] == 'stopped' and response['payload']['reason'] == 'exited-signalled':
				break_outer = True
				abrupt = True
				#pprint(response)
			elif response['message'] =='stopped' and response['payload']['reason'] == 'exited-normally':
				break_outer = True
				#pprint(response)
			elif response['message'] =='stopped' and response['payload']['reason'] == 'exited':
				break_outer = True
				#pprint(response)


		
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

	return (exec_string, abrupt, error_lineno)

libc_mapping = {
	'FOPEN':'FOPEN_FAIL',
	'OPEN': 'OPEN_FAIL',
	'FGETC': 'FGETC_FAIL',
	'MALLOC': 'MALLOC_FAIL',
	'FPUTC':'FPUTC_FAIL'
}


if __name__ == "__main__":

	global library

	if len(sys.argv) < 2:
		print "Usage: python python-wrapper <config.json>"
		exit()

	configfilename = sys.argv[1]

	with open(configfilename,'r') as configfile:
		contents = configfile.read()

	config_json = json.loads(contents)

	if 'FAIL_CALLS' not in config_json \
		or 'SOURCE_FILE_PATH' not in config_json \
		or 'SOURCE_FILE_NAME' not in config_json \
		or 'ARGUMENTS' not in config_json \
		or 'LIBRARY_PATH' not in config_json \
		or 'EXECUTABLE' not in config_json :
		print "Incorrect format: Refer to sampleconfig.json for correct format"
		exit()

	# TODO: Write check in fail is in mapping
	fail_calls = config_json['FAIL_CALLS']
	calls_to_fail = []
	for call in fail_calls:
		calls_to_fail.append(libc_mapping[call])
	source_file_path = config_json['SOURCE_FILE_PATH']
	source_file_name = config_json['SOURCE_FILE_NAME']
	executable = config_json['EXECUTABLE']
	arguments = config_json['ARGUMENTS']
	library = config_json['LIBRARY_PATH']
	
	current_run = 1

	all_executions = list()

	error_lines = []

	queue = deque()

	for call_to_fail in calls_to_fail:
		call_num_to_fail = 0

		while True:

			call_num_to_fail += 1

			call_fail_dict = {		call_to_fail:[call_num_to_fail]		}

			exec_string, abrupt, error_lineno = do_processing(executable, arguments, \
				source_file_name, source_file_path, call_fail_dict)
			print "Coverage",exec_string

			if abrupt and error_lineno != -1:
				error_lines.append(error_lineno)
			if should_not_proceed(all_executions, exec_string):
				break
			elif not abrupt:
				lines = len(exec_string)
				zeroes = exec_string.count('0')
				coverage = (lines - zeroes) / lines
				print lines, zeroes, coverage
				queue.append(
					{
						'calls':{
							call_to_fail : [call_num_to_fail]
						},
						'coverage':coverage
					}
				)
				print "Added"

			all_executions.append(exec_string)

			current_run += 1

		del all_executions[:]	
		

	#print "\nQueue:",queue
	#print "\nCheck lines:", error_lines
	
	while len(queue) != 0:

		queue_item = queue.popleft()

		calls_failed = queue_item['calls']

		for call in calls_to_fail:

			if call in calls_failed.keys():
				current_max_call = calls_failed[call][-1]
			else:
				current_max_call = 0

			while True:
				current_max_call += 1

				new_call_fail_dict = create_new_call_fail_dictionary(calls_failed, call, current_max_call)

				exec_string, abrupt, error_lineno = do_processing(executable, arguments, source_file_name, source_file_path, new_call_fail_dict)

				print "Coverage",exec_string
			
				if abrupt and error_lineno != -1:
					error_lines.append(error_lineno)

				if should_not_proceed(all_executions, exec_string):
					break
				elif not abrupt:
					lines = len(exec_string)
					zeroes = exec_string.count('0')
					coverage = (lines - zeroes) / lines
					print lines, zeroes, coverage

					queue.append(
						{
							'calls':new_call_fail_dict,
							'coverage':coverage
						}
					)
					print "Added"

				all_executions.append(exec_string)

				current_run += 1

	print "Executions", current_run
	print "\nQueue:",queue
	print "\nCheck lines:", error_lines