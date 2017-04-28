from pygdbmi.gdbcontroller import GdbController
from pprint import pprint

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


# Start gdb process
gdbmi = GdbController(gdb_args=['../wrapper/hello','-nx','--quiet', '-interpreter=mi2'])

responses = gdb_read(gdb_controller=gdbmi)
pprint(responses)
print("\n\n")

gdbmi.write('br main', timeout_sec=100, read_response=False)
responses = gdb_read(gdb_controller=gdbmi)
pprint(responses)
print("\n\n")

gdbmi.write('run', timeout_sec=100, read_response=False)
responses = gdb_read(gdb_controller=gdbmi)
pprint(responses)
print("\n\n")

gdbmi.write('next', timeout_sec=100, read_response=False)
responses = gdb_read(gdb_controller=gdbmi)
pprint(responses)
print("\n\n")

gdbmi.write('next', timeout_sec=100, read_response=False)
responses = gdb_read(gdb_controller=gdbmi)
pprint(responses)
print("\n\n")

gdbmi.write('call flush_gcov()', timeout_sec=100, read_response=False)

response = gdbmi.write('next', timeout_sec=100, read_response=False)
responses = gdb_read(gdb_controller=gdbmi)
pprint(responses)
print("\n\n")

gdbmi.write('call flush_gcov()', timeout_sec=100, read_response=False)

gdbmi.exit()