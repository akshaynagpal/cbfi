Running the Python Wrapper:

To run the python wrapper:

(1) Make sure the custom library is compiled with proper flags

(2) Make sure that the test file is compiled with proper flags
-rdynamic, --coverage, -g

(3) Add mapping to python file
The python file has a libc_mapping dict that maps the user specified function name, to the libc fail mapping. Add the mapping for the functions you want to fail which are not already added.

(4) Create a config file for the test program. (Refer to sample-config.json)

(5) Run python script using:
python python-wrapper <configfilename>



Currently, I have still have to add code for duplicate permutations in python file and don't take any readings, but just copy individually the libc wrapper functions and see that our project is working overall.




If you face any issues:
There are some pprint lines commented in the python file, you can uncomment it to check what the run is performing.

Tip:
Don't waste much time if a particular function is not working and move on to next one.

