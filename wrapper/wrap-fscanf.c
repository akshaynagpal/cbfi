/**
 *
 * fscanf wrapper
 *
 **/

// #include "wrapper.h"

// int __fscanf(FILE *stream, const char *format, ...)
// {
//     va_list arg;
//     int done;
//     char* fail_num = getenv("FSCANF_FAIL");
//     int error = 0; // set to -1 if call is to be failed
//     unsigned int *numbers = NULL; // filled by parse function
//     unsigned int i = 0, length = 0;    // size of numbers array of integers
//     int original = btrace_has_gcov();   // check if called by gcov

//     if (fail_num != NULL && original == 0){
//         ++global_counts.fscanf;
//         length = parse_fail_str(&numbers, fail_num);
//         // iterate over numbers array
//         for (i = 0; i < length; i++) {
//             if (numbers[i] == global_counts.fscanf) {
//                 error = -1;
//                 break;
//             }
//         }
//         free(numbers); // release memory
//         if (error == -1) {
//             errno = EBADF;  // stream out of memory
//             return EOF;   // some read error occurs 
//         }
//     }

//     va_start (arg, format);
//     done = __vfscanf(stream, format, arg);
//     va_end (arg);

//   return done;
// }
