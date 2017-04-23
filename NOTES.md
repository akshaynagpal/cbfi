# NOTES

**04-23-2017**

Stdin and Stdout are by default buffered. Can be disabled stdbuf -i0 -o0 -e0.

-fno-builtin is the flag in gcc to disable printf converted to puts. GCC has mechasnism of builtin and which is not related to any optimizations disabled by -O0.

**04-09-2017**
<hr>

Might shift to using ltrace instead of strace.
ltrace gives trace of library calls made by the program
sltrace gives trace of system calls made by the program

Since we are writing library call wrappers. We would be essentially be failing library calls and not system calls. In such scenario, ltrace would give more info about library calls made by the program.

`ltrace -i <path/toexecutable>` would give lists of library calls along with the instruction pointer information of code which makes call to the library.

**03-25-2017**
<hr>

### Architecture
1. A gcc compiler like AFL that would instrument the code to find out read,write, malloc along with their line numbers.(TODO: find open source tool for this and use their code)    
2. Program wrapper
3. LibC Wrapper library - that woul return errors based on instrumented code.

### Process
- Instrument the code to call custom libc functions which are sys call wrappers.
- The program wrapper would use the instrumentation to run the different branches of the program and check coverage for each iteration.
- After every iteration see increase in coverage. (TODO: find open source tool that tells coverage percentage)  
- Converge at a point such that you could obtain a good coverage and give a text based simple report that summarizes faults injected and which lines of code are vulnerable.

**03-26-2017**
<hr>

### strace
Can use `strace <path/to/executable>` to find out what system calls are being called by the program.    

`strace -i <path/to/executable>` also prints that the instruction pointer of the code from where the syscall in invoked which will help us in getting the relative location of where the syscall is being invoked in the program and thus would be able to provide us information about which syscall is invoked(i.e. 1st, 2nd, 3rd etc.)

#### Example
1. hello world    
```
#include<stdio.h>

void main(){
    int x = 2;
    FILE *fp;
    fp=fopen("foo.txt","w+");
    fprintf(fp,"hello world");
    fclose(fp);
    printf("hello world");
}
```
`strace ./a.out` gives the following output:
<pre><code>
execve("./a.out", ["./a.out"], [/* 61 vars */]) = 0
brk(NULL)                               = 0x18b5000
access("/etc/ld.so.nohwcap", F_OK)      = -1 ENOENT (No such file or directory)
mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f757ea57000
access("/etc/ld.so.preload", R_OK)      = -1 ENOENT (No such file or directory)
open("/etc/ld.so.cache", O_RDONLY|O_CLOEXEC) = 3
fstat(3, {st_mode=S_IFREG|0644, st_size=88327, ...}) = 0
mmap(NULL, 88327, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7f757ea41000
close(3)                                = 0
access("/etc/ld.so.nohwcap", F_OK)      = -1 ENOENT (No such file or directory)
open("/lib/x86_64-linux-gnu/libc.so.6", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\3\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0P\t\2\0\0\0\0\0"..., 832) = 832
fstat(3, {st_mode=S_IFREG|0755, st_size=1864888, ...}) = 0
mmap(NULL, 3967488, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7f757e46b000
mprotect(0x7f757e62b000, 2093056, PROT_NONE) = 0
mmap(0x7f757e82a000, 24576, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1bf000) = 0x7f757e82a000
mmap(0x7f757e830000, 14848, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x7f757e830000
close(3)                                = 0
mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f757ea40000
mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f757ea3f000
mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f757ea3e000
arch_prctl(ARCH_SET_FS, 0x7f757ea3f700) = 0
mprotect(0x7f757e82a000, 16384, PROT_READ) = 0
mprotect(0x600000, 4096, PROT_READ)     = 0
mprotect(0x7f757ea59000, 4096, PROT_READ) = 0
munmap(0x7f757ea41000, 88327)           = 0
brk(NULL)                               = 0x18b5000
brk(0x18d6000)                          = 0x18d6000
<b>open("foo.txt", O_RDWR|O_CREAT|O_TRUNC, 0666) = 3</b>
fstat(3, {st_mode=S_IFREG|0664, st_size=0, ...}) = 0
<b>write(3, "hello world", 11)             = 11</b>
close(3)                                = 0
fstat(1, {st_mode=S_IFCHR|0620, st_rdev=makedev(136, 1), ...}) = 0
write(1, "hello world", 11hello world)             = 11
exit_group(11)                          = ?
+++ exited with 11 +++

```
