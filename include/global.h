#ifndef VIMCGLOBAL_INC
#define VIMCGLOBAL_INC

#include <pthread.h>

#define MAX_NUMBER_OF_THREADS 256
#define END_OF_THREAD_TABLE "END OF THREAD TABLE"
typedef struct
{
  int thread_num;
  char *thread_name;
  void *(*thread_function) (void *);
  void *thread_launch_arg;
  int extra_arg_1;
  int extra_arg_2;
  int extra_arg_3;
  int extra_arg_4;
  pthread_t thread;
}
thread_table_entry_t;
#endif
