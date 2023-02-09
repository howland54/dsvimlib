/* ----------------------------------------------------------------------

   Convdata library for imaging

   Modification History:
   DATE        AUTHOR   COMMENT
   11-Apr-217  jch      creation


---------------------------------------------------------------------- */

#include "msg_util.h"
#ifndef A2B_THREAD_INC
#define A2B_THREAD_INC

// ----------------------------------------------------------------------
// DEBUG FLAG:  Uncomment this and recompile to get verbose debugging 
// ----------------------------------------------------------------------
#define DEBUG_A2B
// ----------------------------------------------------------------------
#define MAX_CMDSTRING_LEN 12
#include "imageTalk.h"

/* ----------------------------------------------------------------------
   data type to create a jasontalk message table
   ---------------------------------------------------------------------- */
typedef struct
{
  int msg_type;			// integer type of command
  const char *msg_cmd_name;		// ascii command string, e.g. WDO or PNG 
  msg_addr_t msg_default_destination;	// default thread address for this command
  const char *msg_help;		// help string for this command
  int msg_data_size;		// expected size of message data. -1 means variable. 
}
imagetalk_message_table_entry_t;


extern int ascii_to_binary (msg_hdr_t * in_hdr, char *in_data, msg_hdr_t * out_hdr, char *out_data);
extern int binary_to_ascii (msg_hdr_t * in_hdr, char *in_data, msg_hdr_t * out_hdr, char *out_data);

// this is an arrray of structures which is used by binary_to_ascii.
// each element of the array corresponds to a jasontalk command.
// the arrray is initilaized the first time binary_to_ascii is called
#define SORTED_IMAGETALK_LIST_SIZE (1+MSG_ADDRESS_MAX-MSG_ADDRESS_MIN)

extern imagetalk_message_table_entry_t sorted_imagetalk_list[SORTED_IMAGETALK_LIST_SIZE];

// here is the flag that is used to flag if the above array in initialized 
extern int sorted_imagetalk_list_initialized;

#endif
