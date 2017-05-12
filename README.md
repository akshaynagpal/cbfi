# Coverage Based Fault Injection
Code coverage is one of the most important parameters         for achieving robust software testing and design, however        achieving the same is almost impossible given the        limitations in testing scenarios. One such scenario is        simulating environment faults for the application under       test. In this report we present a prototype implementation         of ​Coverage Based Fault Injection (CBFI)[7], to test        programs for errors caused due to faulty or malicious         underlying hardware, operating system and other related       components. In this approach CBFI[7] is implemented as        a coverage based fuzzer with ​dynamically linked library        that wraps around existing GNU libc calls and permutes         fault injections to fail a set of libc calls and test the            program robustness as well as susceptibility to       vulnerabilities due to unhandled exceptions or crashes at        runtime. Our work is inspired and extends the previous         work on fault injections, specifically that presented in        Vulnerability Testing of Software System Using Fault       Injection[1] and Libfaultinj[2]. 

Compiling wrapper:
(1) `cd wrapper/`
(2) `make clean all`

Compiling test programs:
(1) `cd tests/`
(2) `make clean all`

Running a test program:
`OPEN_FAIL=1,2 LD_PRELOAD=../wrapper/wraplib.so ./testprogram`

Running Python Fuzzer:
(1) `cd python-wrappper/`
(1) `Create a config file based on sample config JSON`
(2) `Run python python-wrapper.py configfilename`
(3) `Report would be generated on the same folder`
