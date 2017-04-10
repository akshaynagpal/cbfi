### fopen() libc wrapper
1. `gcc -shared -fPIC  wrap-fopen.c -o wrap-fopen.so -ldl`
2. `gcc -o hello hello.c`
3. `LD_PRELOAD=path/to/so/folder/wrap-fopen.so ./hello`
