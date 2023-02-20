#ifndef VIMCGLOBAL_INC
#define VIMCGLOBAL_INC

#include <pthread.h>

#define MAX_NUMBER_OF_THREADS 256
#define END_OF_THREAD_TABLE "END OF THREAD TABLE"

#define NUM_DOF  6

#define DOF_X     0
#define DOF_Y     1
#define DOF_Z     2
#define DOF_HDG   3
#define DOF_PITCH 4
#define DOF_ROLL  5

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
