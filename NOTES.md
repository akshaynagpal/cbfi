# NOTES

## Architecture:
1. A gcc compiler like AFL that would instrument the code to find out read,write, malloc along with their line numbers.(TODO: find open source tool for this and use their code)    
2. Program wrapper
3. LibC Wrapper library - that woul return errors based on instrumented code.

## Process
- Instrument the code to call custom libc functions which are sys call wrappers.
- The program wrapper would use the instrumentation to run the different branches of the program and check coverage for each iteration.
- After every iteration see increase in coverage. (TODO: find open source tool that tells coverage percentage)  
- Converge at a point such that you could obtain a good coverage and give a text based simple report that summarizes faults injected and which lines of code are vulnerable.


---------------------------

Can use strace <path/to/executable> to find out what system calls are being called by the program.

Strace "strace -i <path/to/executable>" also prints that the instruction pointer of the code from where the syscall in invoked which will help us in getting the relative location of where the syscall is being invoked in the program and thus would be able to provide us information about which syscall is invoked(i.e. 1st, 2nd, 3rd etc.)
