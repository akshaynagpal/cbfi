/**
 *
 * printf() wrapper
 *
 **/

#include "wrapper.h"

typedef int (*orig_printf_type)(const char *format, ...);

int printf(const char *format, ...){
	// ... argument list
	char* fail_num = getenv("PRINTF_FAIL");
  int error = 0; // set to -1 if call is to be failed
  unsigned int *numbers = NULL; // filled by parse function
  unsigned int i = 0, length = 0;    // size of numbers array of integers
  int original = btrace_has_gcov();   // check if called by gcov
  
  // checking for inner calls to open function
  if (fail_num != NULL && original == 0){

      // increment count for failing attempt
      ++global_counts.printf;
      // allocate numbers and store parsed integers
      length = parse_fail_str(&numbers, fail_num);

      // iterate over numbers array
      for (i = 0; i < length; i++) {
          if (numbers[i] == global_counts.printf) {
              error = -1;
              break;
          }
      }
      free(numbers); // release memory
      if (error == -1) // check if call is to be failed
          return -1;
  }

	// original printf
  va_list arg;
	int done;
	va_start (arg, format);
  done = vfprintf (stdout,format, arg);
	va_end (arg);
	return done;
}