/* ----------------------------------------------------------------------

nio thread for ROV control system

Modification History:
DATE        AUTHOR COMMENT
1-OCT-2001  JCH     Created and written.
22-Jan-2002 JCH     make work with sending, not just receiving
15 feb 2002 JCH     change for new messaging api
26 apr 2002 JCH     make work for broadcast
19 Jul 2002 LLW     Revised to transmit as well as receive, presently supports
                    only one TX destination
23 SEP 2006 LLW     Print name of thread on init
2007-10-23 nio_thread will receive SAS in addition to WAS
2008-06-22    mvj   Added support for external task accounting, primarily
                    for use in fasttime mode, but enabled regardless by
          setting EXT_TASK=1 in the section of the .ini file
          specific to each NIO thread.

---------------------------------------------------------------------- */

/* standard ansi C header files */
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <fcntl.h>

/* posix header files */
#define  POSIX_SOURCE 1

#include <pthread.h>
#include <termios.h>
#include <unistd.h>


/* jason header files */
#include "../include/imageTalk.h"



#include "../include/msg_util.h"		/* utility functions for messaging */

#include "../include/IniFile.h"


#include "../include/nio_thread.h"		/* nio thread */
//#include "../include/config_file.h"

int read_ini_nio_process (IniFile *theIni, char *my_name, nio_thread_t * my_nio);
//#include "stderr.h"

//#include "launch_timer.h"       /* timers - used for external task timeout */

// 2008-06-30    mvj   Note - uncommenting this causes a seg fault.  
//                     Did not attempt to track down problem.
//#define DEBUG_NIO
extern thread_table_entry_t global_thread_table[MAX_NUMBER_OF_THREADS];

extern pthread_attr_t DEFAULT_ROV_THREAD_ATTR;
/* ----------------------------------------------------------------------

Function to open a network port.  

Returns -1 if unsuccesful, valid file id if successful 

Modification History:
DATE         AUTHOR  COMMENT
1-OCT-2001  JCH      Created and written.

---------------------------------------------------------------------- */

int open_network (nio_thread_t * nio)
{

   if ((nio->my_nio_port_table_entry.my_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
      {
         //stderr_printf("%s: ***Aborting UDP FROM Port: %s \n", IMAGETALK_THREAD_NAME(nio->nio_thread_num), nio->my_nio_port_table_entry.name_of_thing_this_nio_port_is_connected_to);
         return 0;
      }



   bzero(&(nio->my_nio_port_table_entry.MyAddr), sizeof (nio->my_nio_port_table_entry.MyAddr));	/* Zero out structure */


   nio->my_nio_port_table_entry.MyAddr.sin_family = AF_INET;	/* Internet address family */


   nio->my_nio_port_table_entry.MyAddr.sin_addr.s_addr = htonl(INADDR_ANY);	/* Server IP Address */

   nio->my_nio_port_table_entry.MyAddr.sin_port = htons(nio->my_nio_port_table_entry.socket_number);	/* Broadcast port */

   /* Bind to the broadcast port */
   if (bind (nio->my_nio_port_table_entry.my_sock,
             (struct sockaddr *) &(nio->my_nio_port_table_entry.MyAddr),
             sizeof (nio->my_nio_port_table_entry.MyAddr)) < 0)
      {
         //stderr_printf("%s: COULD NOT BIND to UDP Port: %s \n", IMAGETALK_THREAD_NAME(nio->nio_thread_num), nio->my_nio_port_table_entry.name_of_thing_this_nio_port_is_connected_to);
         return 0;
      }


   // now put in the port that we are going to talk to
   nio->my_nio_port_table_entry.to_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);;

   if (nio->my_nio_port_table_entry.to_sock < 0)
      {
         //stderr_printf ("%s: Could not create socket for UDP  TO Port: %s \n", IMAGETALK_THREAD_NAME(nio->nio_thread_num), nio->my_nio_port_table_entry.name_of_thing_this_nio_port_is_connected_to);
         return 0;
      }


   // add in broadcast capability


   int broadcastPermission = 1;
   if(setsockopt(nio->my_nio_port_table_entry.to_sock,
                 SOL_SOCKET, SO_BROADCAST,
                 (void *) &broadcastPermission,
                 sizeof(broadcastPermission)) < 0)
      {
         //stderr_printf ("%s: ***couldn't set broadcast on UDP : %s \n", IMAGETALK_THREAD_NAME(nio->nio_thread_num), nio->my_nio_port_table_entry.name_of_thing_this_nio_port_is_connected_to);
         return 0;
      }

   memset(&(nio->my_nio_port_table_entry.ToAddr), 0, sizeof (nio->my_nio_port_table_entry.ToAddr));	/* Zero out structure */


   nio->my_nio_port_table_entry.ToAddr.sin_family = AF_INET;	/* Internet address family */


   nio->my_nio_port_table_entry.ToAddr.sin_addr.s_addr = inet_addr (nio->my_nio_port_table_entry.ip_address);	/* Destination IP Address */



   if(INADDR_NONE == nio->my_nio_port_table_entry.ToAddr.sin_addr.s_addr)
      {
         //stderr_printf ("%s: ERROR Invalid IP Address %s\n",JASONTALK_THREAD_NAME(nio->nio_thread_num),nio->my_nio_port_table_entry.ip_address);
      }
   //else
   //stderr_printf ("%s: Valid IP Address %s is OK.\n",JASONTALK_THREAD_NAME(nio->nio_thread_num),nio->my_nio_port_table_entry.ip_address);



   nio->my_nio_port_table_entry.ToAddr.sin_port = htons(nio->my_nio_port_table_entry.to_socket_number);	/* Broadcast port */

#ifdef DEBUG_NIO
   stderr_printf ("%s: the sin_port is %d\n", JASONTALK_THREAD_NAME(nio->nio_thread_num), nio->my_nio_port_table_entry.to_socket_number);
#endif


   return 1;
}


/* ----------------------------------------------------------------------

Function to process incoming records 


Modification History:
DATE         AUTHOR  COMMENT
1-OCT-2001  JCH      Created and written.

---------------------------------------------------------------------- */

static void *
nio_rx_thread (void *arg)
{

   nio_thread_t *nio = (nio_thread_t *) arg;
   char big_buffer[BUFFERMAX];
   int rcv_size;
   nio = (nio_thread_t *) arg;
   struct sockaddr from_addr;
   unsigned int from_len;

   while (1)
      {

         if ((rcv_size = recvfrom (nio->my_nio_port_table_entry.my_sock, big_buffer, BUFFERMAX, 0, &from_addr, &from_len)) < 0)
            {
               fprintf (stderr, "error on recvfrom, socket from %s\n", nio->my_nio_port_table_entry.name_of_thing_this_nio_port_is_connected_to);
            }
         else
            {			// we got some good data

#ifdef DEBUG_NIO
               printf ("%s (thread %d) device %s  got %d characters\n", global_thread_table[nio->nio_thread_num].thread_name, nio->nio_thread_num,
                     nio->my_nio_port_table_entry.name_of_thing_this_nio_port_is_connected_to, rcv_size);
               printf(" the data: %s\n",big_buffer);
               fflush (stdout);
#endif
               // lock the data structure mutex so that we chan diddle with the data
               pthread_mutex_lock (&nio->mutex);
               // keep stats
               nio->total_tx_chars += rcv_size;
#ifdef DEBUG_NIO
               printf (" n of destinations for this data is % d \n ", nio->my_nio_port_table_entry.n_of_destinations);
#endif
               for (int i = 0; i < nio->my_nio_port_table_entry.n_of_destinations; i++)
                  {
                     msg_send( nio->my_nio_port_table_entry.auto_send_addresses[i], nio->nio_thread_num, SAS, rcv_size, big_buffer);
                  }




               pthread_mutex_unlock (&nio->mutex);
            }

      }

   return NULL;
}




/* ----------------------------------------------------------------------*/

//   NIO Thread

//   Modification History:
//   DATE         AUTHOR  COMMENT
//   1-OCT-2001  JCH      Created and written.

//----------------------------------------------------------------------*/
void * nio_thread (void *thread_num)
{

   nio_thread_t nio = { PTHREAD_MUTEX_INITIALIZER, -1};

   char *my_name;

   FILE *ini_fd;

   int status;
   msg_hdr_t hdr =  {0};
   unsigned char data[MSG_DATA_LEN_MAX] = {0};

   /* get my thread number */
   nio.nio_thread_num = (long int) thread_num;


   // now look into the process table and figure out what thread I am
   for (int i = 0; i < MAX_NUMBER_OF_THREADS; i++)
      {

         if (global_thread_table[i].thread_num == nio.nio_thread_num)
            {

               my_name = global_thread_table[i].thread_name;
               //#ifdef DEBUG_NIO
               //#endif
            }
      }
   if (!my_name)
      {
         //stderr_printf("%s: thread %d  not found in process table!\n", IMAGETALK_THREAD_NAME(nio.nio_thread_num), nio.nio_thread_num);
         fflush (stdout);
         fflush (stderr);
         // 2009/04/25 LLW do not abort on bad thread name
      }

   IniFile  *iniFile = new IniFile();
   int okINI = iniFile->openIni(flyIniFile);
   if(okINI)
      {
         status = read_ini_nio_process (iniFile, my_name, &nio);
      }


   if (status != 0)
      {
         fflush (stdout);
         fflush (stderr);
         // 2009/04/25 LLW do not abort on bad ini file status
      }



   // init the msg queue
   int msg_success = msg_queue_new(nio.nio_thread_num, my_name);

   if(msg_success != MSG_OK)
      {
         fprintf(stderr, "NIO THREAD: NIO thread for %s: %s\n",nio.my_nio_port_table_entry.name_of_thing_this_nio_port_is_connected_to,MSG_ERROR_CODE_NAME(msg_success) );
         fflush (stdout);
         fflush (stderr);

         // 2009/04/25 LLW
      }
   // wakeup message
   //#ifdef DEBUG_NIO
   //stderr_printf ("%s: (thread %d) initialized \n",  JASONTALK_THREAD_NAME(nio.nio_thread_num), nio.nio_thread_num);
   //stderr_printf ("%s: File %s compiled at %s on %s\n", JASONTALK_THREAD_NAME(nio.nio_thread_num),__FILE__, __TIME__, __DATE__);

   // #endif

   // ----------------------------------------------------------------------
   // open the network port
   // ----------------------------------------------------------------------
#ifdef DEBUG_NIO
   printf ("NIO THREAD: about to open port\n");
#endif
   nio.nio_port_fid = open_network (&nio);
#ifdef DEBUG_NIO
   printf ("NIO THREAD: got by open port, FID=%d\n",nio.nio_port_fid);
#endif

   // launch the thread to process incoming characters from the network port
   pthread_create (&nio.nio_rx_subthread, &DEFAULT_ROV_THREAD_ATTR, nio_rx_thread, (void *) (&nio));

   // loop forever
   while (1)
      {

         // wait forever on the input channel
#ifdef DEBUG_NIO
         printf ("NIO THREAD: NIO calling get_message.\n");
#endif
         int msg_get_success = msg_get(nio.nio_thread_num,&hdr, data, MSG_DATA_LEN_MAX);
         if(msg_get_success != MSG_OK)
            {
               fprintf(stderr, "NIO THREAD: nio thread--error on msg_get:  %s\n",MSG_ERROR_CODE_NAME(msg_get_success));
            }
         else
            {

#ifdef DEBUG_RECIEVED_MESSAGES
               // print on stderr
               printf ("NIO THREAD: NIO THREAD (thread %d)  got msg type %d from proc %d to proc %d, %d bytes data\n",
                       nio.nio_thread_num, hdr.type, hdr.from, hdr.to, hdr.length);
#endif
               // process new message
               switch (hdr.type)
                  {


                  case WAS:		// recieved a WAS (Write Serial String) Message
                  case SAS:		// 2007-10-23 nio_thread will receive SAS in addition to WAS

                     {
                        // send the characters to the port, keep stats
                        // note that WAS messages need NOT be null terminated
                        if (hdr.length > 0)
                           {

                              int bytes_sent;
                              // lock the mutex
                              pthread_mutex_lock (&nio.mutex);
                              // send the bytes

                              bytes_sent = sendto(nio.my_nio_port_table_entry.to_sock,
                                                  data,
                                                  hdr.length,
                                                  0,
                                                  (struct sockaddr *) (&(nio.my_nio_port_table_entry.ToAddr)),
                                                  sizeof (nio.my_nio_port_table_entry.ToAddr));

                              if (bytes_sent == hdr.length)
                                 {

                                    // keep stats
                                    nio.total_tx_chars += hdr.length;
                                 }
                              else
                                 {
                                    fprintf (stderr, "NIO THREAD: ERROR sending %d byte WAS to %s port %d - %d bytes sent.\n",
                                             hdr.length,
                                             nio.my_nio_port_table_entry.ip_address,
                                             nio.my_nio_port_table_entry.to_socket_number,
                                             bytes_sent
                                             );

                                    fprintf (stderr, "NIO THREAD: Data is: \"%*s\"\n", hdr.length, data);

                                 }

                              // unlock the mutex
                              pthread_mutex_unlock (&nio.mutex);
                           }

                        break;
                     }


                  case SPI:		// recieved a SPI (Status Ping) message
                     {
                        char msg[256];
                        sprintf (msg, "NIO THREAD: %s: (thread %d) is Alive!", global_thread_table[nio.nio_thread_num].thread_name, nio.nio_thread_num);
                        break;
                     }
                  case BYE:  // received a bye message--time to give up the ghost--or at least my socket
                     {

                        close(nio.my_nio_port_table_entry.my_sock);
                        return(NULL);


                        break;
                     }
                  default:		// recieved an unknown message type
                     {
                        printf ("NIO THREAD: %s: (thread %d) ERROR: RECIEVED UNKNOWN MESSAGE TYPE -" "got msg type %d from proc %d to proc %d, %d bytes data\n",
                                global_thread_table[nio.nio_thread_num].thread_name,
                              nio.nio_thread_num, hdr.type, hdr.from, hdr.to, hdr.length);
                        break;
                     }
                  }
            } // end else

      }


}

/* ----------------------------------------------------------------------

read_ini_nio_process

Modification History:
DATE         AUTHOR   COMMENT
1  OCT 2001  JCH  Created and written.
19 Jul 2002  LLW  Revised to transmit as well as receive, presently supports
only one TX destination
2008-06-22    mvj    Added option to manipulate task count for certain 
                     outgoing and incoming messages listed in ini file.
           This allows external processes to be included in the
           task count which is necessary for fasttime support.

---------------------------------------------------------------------- */

//#define DEBUG_CONFIG

int read_ini_nio_process (IniFile *theIni, char *my_name, nio_thread_t * my_nio)
{

   char destination_string[MAX_DESTINATION_STRING_LENGTH];
   char *new_destination;
   int   status;

   // read in the socket number
   my_nio->my_nio_port_table_entry.socket_number = theIni->readInt(my_name,  "PORT",ERRONEOUS_NIO_PORT );
   my_nio->my_nio_port_table_entry.ip_address = theIni->readString(my_name,"TO_IP_ADDRESS", ERRONEOUS_IP_ADDRESS);
   my_nio->my_nio_port_table_entry.to_socket_number = theIni->readInt(my_name,  "TO_PORT",       ERRONEOUS_NIO_PORT);



   status = (my_nio->my_nio_port_table_entry.socket_number  == ERRONEOUS_NIO_PORT) ||
         (0 == strcmp( my_nio->my_nio_port_table_entry.ip_address, "ERRONEOUS_IP_ADDRESS")) ||
         ( my_nio->my_nio_port_table_entry.to_socket_number == ERRONEOUS_NIO_PORT);

   // now read in the destinations for the nios
   if (0 == status)
      {

         sprintf(my_nio->my_nio_port_table_entry.name_of_thing_this_nio_port_is_connected_to,
                 "UDP port %d at IP Address %s",
                 my_nio->my_nio_port_table_entry.to_socket_number,
                 my_nio->my_nio_port_table_entry.ip_address
                 );

         for (int i = 0; i < MAX_NIO_DESTINATIONS; i++)
            {
               sprintf (destination_string, "destination_%d", i);
               new_destination = theIni->readString( my_name, destination_string, "NONE");

               if (strcmp(new_destination, "NONE"))
                  {			// this means there is a destination thread for this string
                     // now search through the global process table and look for the process name


                     for (int j = 0; j < MAX_NUMBER_OF_THREADS; j++)
                        {
                           if(global_thread_table[j].thread_name)
                              {

                                 if (0 == strcasecmp (global_thread_table[j].thread_name, new_destination))
                                    {
                                       my_nio->my_nio_port_table_entry.auto_send_addresses[my_nio->my_nio_port_table_entry.n_of_destinations++] = global_thread_table[j].thread_num;

                                       /*                                       stderr_printf("%s: %s added thread destination %d (%s) total=%d\n",
                                                     my_name,
                                                     my_name,
                                                     global_thread_table[j].thread_num,
                                                     global_thread_table[j].thread_name,
                                                     my_nio->my_nio_port_table_entry.n_of_destinations);
*/

                                       break;
                                    }
                              }

                        }
                  }

            }

      }
   return status;


}

