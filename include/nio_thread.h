/* ----------------------------------------------------------------------

   nio thread for ROV control system

   Modification History:
   DATE         AUTHOR  COMMENT
   1-OCT-2001   jch      Created and writte from LLW's sio 
   15 FEB 2002  JCH      change for new messaging api
   2008-06-24    mvj    Added support for external task accounting.


---------------------------------------------------------------------- */
#ifndef NIO_PROCESS_INC
#define NIO_PROCESS_INC

// ----------------------------------------------------------------------
// DEBUG FLAG:  Uncomment this and recompile to get verbose debugging 
// ----------------------------------------------------------------------
//#define DEBUG_NIO
//#define DEBUG_CONFIG
// ----------------------------------------------------------------------

#define BUFFERMAX 512
#define MAX_NIO_DESTINATIONS  9

#define DEFAULT_TERMINATOR_STRING "\r"
#define MAX_PORT_NAME_LENGTH  256
//#define DEFAULT_TERMINATOR_CHAR '\r'
// dy munged this for sail 2/28/06
#define DEFAULT_TERMINATOR_CHAR 0X03
#define MAX_DESTINATION_STRING_LENGTH 256
#define ERRONEOUS_NIO_PORT  9999
#define ERRONEOUS_IP_ADDRESS  "ERROR_ADDRESS"



typedef struct
{
  int    	      thread_number;
  char   	     *ip_address;
  int                 socket_number;
  int                 to_socket_number;

  int    	      my_sock;   
  struct sockaddr_in  MyAddr;	/* Source Addr  */
  int                 to_sock;
  struct sockaddr_in  ToAddr;	/* Sendto Address */
  char   	      name_of_thing_this_nio_port_is_connected_to[512];
  int    	      n_of_destinations;
  int    	      auto_send_addresses[MAX_NIO_DESTINATIONS];
}
nio_port_table_entry_t;

// External task accounting data structure.
// 2008-06-24    mvj    Added.
#include "launch_timer.h" 
typedef struct {

  bool                    flag;
  char*                   complete_msg;
  unsigned int            outstanding;
  unsigned int            max_outstanding;

  launched_timer_data_t** timers; 
  double                  timeout;

} external_task_t;


typedef struct
{
  pthread_mutex_t         mutex;
  int                     nio_thread_num;
  nio_port_table_entry_t  my_nio_port_table_entry;
  int                     nio_port_fid;
  pthread_t               nio_rx_subthread;
  unsigned int            total_rx_chars;
  unsigned int            total_tx_chars;
  char                    inchars[MSG_DATA_LEN_MAX + 1];
  int                     inchar_index;

  external_task_t         ext_task; // 2008-06-24    mvj    Added.

}
nio_thread_t;

extern void *nio_thread (void *thread_num);
extern char *flyIniFile;

#endif
