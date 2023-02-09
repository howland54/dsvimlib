/* ----------------------------------------------------------------------

   Funcitons for imaging Interprocess Communication

   Modification History:
   DATE        AUTHOR   COMMENT
   11-Apr-2017  jch      creation
   ---------------------------------------------------------------------- */
#include <stdio.h>
#include <string.h>
#include "../include/global.h"

#include "../include/imageTalk.h"
thread_table_entry_t global_thread_table[MAX_NUMBER_OF_THREADS];

/* ----------------------------------------------------------------------

   imagetalk thread name to int

   returns -1 if name is not known

   Modification History:
   DATE         AUTHOR  COMMENT
   11-Apr-217  jch      creation

---------------------------------------------------------------------- */
int IMAGETALK_THREAD_NUM( char * name)
{

  int i;
  int thread_num = -1;
  
  for(i =0; i< MAX_NUMBER_OF_THREADS; i++)
    {
      if(global_thread_table[i].thread_name != NULL)
	if( 0 == strcasecmp(name, global_thread_table[i].thread_name))
	  {
	    thread_num = i;

	    i = MAX_NUMBER_OF_THREADS;
	  }
    }


  if(thread_num == -1)
    {
      printf("ERROR: IMAGETALK_THREAD_NUM unable to find thread \"%s\"\n", name);
      printf("\a\a\a\a\a");
    }

  return thread_num;
  
}


/* ----------------------------------------------------------------------

   imagetalk thread number int to string.

   Note that this lists all thread names, not just the ones
   that are loaded and run by rov.cpp in the thread table

   Modification History:
   DATE         AUTHOR  COMMENT
   11-Apr-217  jch      creation

---------------------------------------------------------------------- */
const char * IMAGETALK_THREAD_NAME (int thread_num)
{

  static char errmsg[] = "UNKNOWN THREAD NUMBER";
  const char * name; 

  if( (thread_num >= 0) && (thread_num < MAX_NUMBER_OF_THREADS))
    name = global_thread_table[thread_num].thread_name;
  else
    name = errmsg;

  return name;

}



/* ----------------------------------------------------------------------

   imagetalk message type int to string

   Modification History:
   DATE         AUTHOR  COMMENT
   11-Apr-217  jch      creation

---------------------------------------------------------------------- */
const char * IMAGETALK_MESSAGE_NAME (int num)
{

  const char *name;

#define make_entry(flag) case flag : name = #flag; break

  switch (num)
    {
      /* ---------    SYSTEM STATUS MESSAGES TYPES ----------*/
      make_entry( HLP );
      make_entry( PNG );
      make_entry( SPI );
      make_entry( RST );
      make_entry( VER );
      make_entry( RTT );
      make_entry( RPT );
    default:
      name = "UNKOWN MESSAGE TYPE";
    }

  return name;

}










  
