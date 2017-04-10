## Instructions for LD_PRELOAD
gcc -shared -fPIC custom_lib.c -o custom_lib.so -ldl    
gcc helloworld.c -o helloworld    
LD_PRELOAD=$PWD/custom_lib.so ./helloworld     

### Instructions for gcov
gcc -fprofile-arcs -ftest-coverage helloworld.c -o helloworld    
LD_PRELOAD=$PWD/custom_lib.so ./helloworld    
gcov -i helloworld.c    

This generates a file called helloworld.c.gcov which has the following output:

file:helloworld.c
function:3,1,main
lcount:3,1
lcount:4,1
lcount:5,1


The gcov is generated in the format 
file:source_file_name
function:line_number,execution_count,function_name
lcount:line number,execution_count
branch:line_number,branch_coverage_type

Source: https://gcc.gnu.org/onlinedocs/gcc/Invoking-Gcov.html#Invoking-Gcov

We can use this file to get number of lines executed and also more info using flags given at above source link.