/**
 *
 * Include this file in source files for linking gcov_flush
 *
 * Use --coverage flag to compile executables with GCC
 *
 **/

void __gcov_flush(void);

void flush_gcov(){
	__gcov_flush();
}
