
/* ----------------------------------------------------------------------

   ascii_ito_binary() - imagetalk ascii to binary message

   binary_to_ascii() - binary message to jasontlk ascii

   Modified:
   
   Modification History:
   DATE        AUTHOR   COMMENT
   11-Apr-2017  jch      creation, derive from jason a2b

   ---------------------------------------------------------------------- */
/* standard ansi C header files */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../include/imageTalk.h"

#include "../include/macros.h"
#include "../include/imageA2b.h"
#include "../include/global.h"
#include "../include/convert.h"

#define SORTED_IMAGETALK_LIST_SIZE (1+MSG_ADDRESS_MAX-MSG_ADDRESS_MIN)
#define MAX_FORMAT_STRING_LENGTH  1024

// this is an arrray of structures which is used by binary_to_ascii.
// each element of the array corresponds to a jasontalk command.
// the arrray is initilaized the first time binary_to_ascii is called
imagetalk_message_table_entry_t sorted_imagetalk_list[SORTED_IMAGETALK_LIST_SIZE] =
{
   {
      0}
};

// here is the flag that is used to flag if the above array in initialized 
int sorted_imagetalk_list_initialized = 0;

// this is an un-ordered array of jasontalk commands
static const imagetalk_message_table_entry_t unsorted_imagetalk_list[] = {
   {PNG, "PING", 0,
    "PNG interrogates a thread to see if it is alive.   usage: \"PNG <thread number>\" example: \"PNG 0\"\n\r"},
   {SPI, "SPI", 0},
   {RST, "RST", 0},
   {VER, "VER", 0},
   {0, NULL, 0}
};


/* ----------------------------------------------------------------------

   ascii_to_binary() - imagetalk ascii to binary message


   ---------------------------------------------------------------------- */

int
ascii_to_binary (msg_hdr_t * in_hdr, char *in_data, msg_hdr_t * out_hdr, char *out_data)
{
   int i;
   int addr;
   char type[25];
   char command[16];

   // null terminate the incoming ascii string so scand will work
   in_data[in_hdr->length] = '\0';

   // Scan the global jasontalk list for the 3 character command name

   // should I really only use three characters?
   // probably not, but test this carefully!
   // doesnt work unless I scanf the command first

   int items = sscanf(in_data,"%s",&(command[0]));
   if(items != 1)
      {
         return(-1);
      }
   int clen = strlen(command);
   if(clen > MAX_CMDSTRING_LEN)
      {
         return(-1);
      }

   i = 0;
   while (unsorted_imagetalk_list[i].msg_cmd_name != NULL)
      {
         if (!strncasecmp (in_data, unsorted_imagetalk_list[i].msg_cmd_name, clen))

            {

               break;
            }
         else
            {
               i++;
            }
      }

   /* Couldn't Find it... Not valid Jasontalk      */
   if (unsorted_imagetalk_list[i].msg_cmd_name == NULL)
      {
//#ifdef DEBUG_A2B
         printf("ERROR %s Line %d MSG From %s To %s Type %s\nERROR Data: %s \n",
                __FILE__,
                __LINE__,
                IMAGETALK_THREAD_NAME(in_hdr->from),
                IMAGETALK_THREAD_NAME(in_hdr->to),
                IMAGETALK_THREAD_NAME(in_hdr->type),
                in_data);
//#endif
         return (-1);
      }

   /* Found it, so load the header with the correct command type and destination  */
   out_hdr->type = unsorted_imagetalk_list[i].msg_type;
   out_hdr->to = unsorted_imagetalk_list[i].msg_default_destination;
   out_hdr->from = in_hdr->to;
   out_hdr->length = 0;

//#ifdef DEBUG_A2B
         printf("MSG From %s To %s Type %s\nERROR Data: %s \n",
                __FILE__,
                __LINE__,
                IMAGETALK_THREAD_NAME(in_hdr->from),
                IMAGETALK_THREAD_NAME(in_hdr->to),
                IMAGETALK_THREAD_NAME(in_hdr->type),
                in_data);
//#endif

   // now process the specific message


   switch (unsorted_imagetalk_list[i].msg_type)
      {




      }


   return 0;

}


/* ----------------------------------------------------------------------

   binary_to_ascii() - binary message to jasontalk ascii


   ---------------------------------------------------------------------- */

int
binary_to_ascii (msg_hdr_t * in_hdr, char *in_data, msg_hdr_t * out_hdr, char *out_data)
{
   int i;
   int len = 0;

   // initialize the indexed list of jasontalk commands on first call

   if (!sorted_imagetalk_list_initialized)
      {
         // initialize the entire sorted list to default values
         for (i = 0; i < MSG_ADDRESS_MAX; i++)
            {
               sorted_imagetalk_list[i].msg_type = i;
               sorted_imagetalk_list[i].msg_cmd_name = "UNKNOWN MESSAGE TYPE ";
               sorted_imagetalk_list[i].msg_default_destination = 0;
            }

         // walk through the unsorted list, initializing the corresponding sorted entries as we go
         for (i = 0; i < (int) (sizeof (sorted_imagetalk_list) / sizeof (imagetalk_message_table_entry_t)); i++)
            {
               int sorted_list_index = sorted_imagetalk_list[i].msg_type;

               if ((sorted_list_index >= MSG_ADDRESS_MIN) && (sorted_list_index <= MSG_ADDRESS_MAX))
                  {
                     // ansii C lets us assign data structures
                     sorted_imagetalk_list[sorted_list_index] = unsorted_imagetalk_list[i];
                  }
            }

         // flag the sorted list as initialized
         sorted_imagetalk_list_initialized = 1;

      }

   // if the incoming message type is out of range then this message
   // type is illegal so return immediately with error status
   if (in_hdr->type > MSG_ADDRESS_MAX)
      {
         out_hdr->length = 0;
         return (-1);
      }

   //  load the outgoing message header with the correct command type and
   // return address. Caller must set destinatin address.
   out_hdr->type = PNG;
   out_hdr->from = in_hdr->to;
   out_hdr->length = 0;

   // create the beginning of the ascii string by sprintfing the ascii command
   // for this message type
   len = sprintf (&out_data[len], "%s", sorted_imagetalk_list[in_hdr->type].msg_cmd_name);

   // now process the specific message
   switch (in_hdr->type)
      {
      // ----------------------------------------
      // the following comands are not implemented
      // ----------------------------------------





      default:
         return (-1);
         //        { // this command not implemented so send an error message back to the sender
         //          len += sprintf(&out_data[len], " message recieved from %s (thread %d) with %d bytes data.",
         //                     global_thread_table[in_hdr->from].thread_name,
         //                     global_thread_table[in_hdr->from].thread_num,
         //                     in_hdr->length);
         //      break;
         //        }

      }				//switch


   out_hdr->length = len;

   return 0;

}





