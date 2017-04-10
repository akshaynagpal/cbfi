## Instructions
gcc -shared -fPIC custom_lib.c -o custom_lib.so -ldl    
gcc helloworld.c -o helloworld    
LD_PRELOAD=$PWD/custom_lib.so ./helloworld     

