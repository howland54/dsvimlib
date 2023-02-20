/* ----------------------------------------------------------------------

   command id,s etc and enums for image application


   Modification History:
   DATE        AUTHOR   COMMENT
   11-Apr-217  jch      creation

   ---------------------------------------------------------------------- */
#ifndef IMAGETALK_INC
#define IMAGETALK_INC

// declare this a posix source
#define _POSIX_SOURCE 1

// set for LINUX compiles.  Comment this our for windows.
#define __LINUX__
// note that windows compiler will automatically define __WIN32__

// pthread header files
#include <pthread.h>
#include <limits.h>

#include <sys/socket.h>		/* for socket(), connect(), sendto(), and recvfrom() */
#include <arpa/inet.h>		/* for sockaddr_in and inet_addr() */
#include "global.h"
#include "time_util.h"

typedef struct 
{
  rov_time_t  startup_time;
} startup_t;

#define NO_PUBLISHING   0
#define PUBLISH_LEVEL_1 1
#define PUBLISH_LEVEL_2 2
#define PUBLISH_LEVEL_3 3
#define MAX_PUBLISH_LEVEL  4



#define PROGRAM_VERSION "V0.01"



#define ANY_THREAD                    0  /* used when thread doesnt matter--such as source in logging */
#define LOGGING_THREAD                1
#define STDERR_THREAD                 2
#define BUS_THREAD                    3
#define TIMER_THREAD                  4
#define CMD_THREAD                    5
#define LCM_RECEIVE_THREAD            6
#define MS_NIO_THREAD                 7
#define SENSOR_THREAD                 8
#define MS_THREAD                     9
#define NIO_INPUT_THREAD              10
#define MS_NET_THREAD                 11
#define MESOBOT_TRAJECTORY_THREAD     12
#define MESOBOT_THALLOC_THREAD        13
#define DSPLLIGHT_THREAD              14
#define STEREO_LOGGING_THREAD         15
#define CTD_THREAD                    16
#define FATHOMETER_THREAD             17
#define ALTIMETER_THREAD              18
#define GPS_THREAD                    19



#define BUS_THREAD_SUBTHREAD          20
#define MX_MAIN                       30
#define MX_MONITOR_THREAD             31
#define MX_LCM_RECEIVE_THREAD         32
#define MX_MAIN_THREAD                33


#define FLY_THREAD_BASE               100
#define LIGHT_THREAD_BASE             175
#define EPI_THREAD_BASE               150

#define NO_THREAD_FOUND               -1

#define NULL_THREAD_ADDRESS           255





/* ----------------------------------------------------------------------
   Message types defined for use in the "type" field of message headers.
   See protocol documentation for the different variable length data
   which accompany each message type.

   All (well, most) message types are either writes, reads, or statuses.

   Write:  Sets (writes) a parameter value in another process.
	   Write messages elicit no response.
   Read:   Requests the value (reads) of a parameter in another process.
	   Read messages always elicit a "status" message in response.
   Status: Message containing the response to the read request.
	   Status messages elicit no response.

  
   ---------------------------------------------------------------------- */

/* ---------    SYSTEM STATUS MESSAGES TYPES ----------*/
#define HLP             0			/* help.  responds with a SSS */
#define PNG             1			/* ping message         */
#define SPI             2			/* ping message response */
#define RST             3			/* RESET message        */
#define VER             4			/* VERBOSE message      */
#define RTT             5			/* read thread table, responds with a SSS */
#define RPT             6			/* read port table, responds with a SSS */
#define BYE             7        /* time to quit */
#define CAMERA_TRIGGER  8
#define WCG             9        /* write camera gain */
#define WCE             10       /* write camera exposure */
#define WCAG            11       /* write auto gain */
#define WBIN            12       /* set binning */
#define WCAE            13       /* write camera auto exposure */
#define CAMR            14       /* camera removal from bus */
#define CAMA            15       /* camera addition to bus */
#define CAMERA_QUERY    16       /* check some camera parameters */
#define SQT             17       /* start query timer--start asking the camera for parameters */
#define IMAGE_QUERY     18       /* see if we need to save an image */
#define MSPI            19       /* microstrain prompt */
#define MSD             20       /* microstrain data */
#define STILL           21       /* take a still picture */
#define START_REC       22       /* start recording */
#define STOP_REC        23       /* stop recording */
#define SAS             24       /* Status ascii string */
#define WAS             25       /* write ascii string */
#define START_LIVE_VIEW 26       /* start live view */
#define STOP_LIVE_VIEW  27       /* stop live view */
#define LIVE_VIEW_TIME  28       /* get a live view image */
#define SET_COMPRESSION 29       /* set the compression type */
#define LOG             30       /* write this ascii string to the log */
#define WFS             31       /* write fstop */
#define WISO            32       /* write the ISO */
#define WPUBV           33       /* write publish view images */
#define WZOOM           34       /* write lens zoom */
#define WSHUT           35       /* write shutter speed  (for Sony) */
#define WEXPM           36       /* write exposure mode (for Sony */
#define WFOCM           37       /* write focus mode (for Sony) */
#define WEXPC           38       /* write exposure compensation (for Sony) */
#define WASP            39       /* write aspect ratio (for Sony) */
#define WCOMP           40       /* write compression setting (for Sony) */
#define WDRIVE          41       /* write drive mode (for Sony) */
#define WPUB            42       /* write publish mode --publish lcm or not, what level */
#define WREP            43       /* write repeated still capture */
#define WRES            44       /* stop repeated still capture */
#define WFOCS           45       /* write focus step */
#define FOCUS_TIME      46       /* send focus command if necessary */
#define WFOCD           47       /* continuous focus */
#define NO_VALID_MSG    48       /* what it says */
#define WFOCP           49       /* write focus position */
#define FOCUSSET_TIME   50       /* check on status of setting focus position */
#define WRECQ           51       /* recording quality change */
#define WLL             52       /* write light level */
#define WLC             53       /* write light channel */
#define RLH             54       /* request light humidity */
#define RLT             55       /* request light temp */
#define RHEALTH         56       /* request health timer */
#define LCOM            57       /* do comms on lights */
#define WMMODE          58       /* do comms on lights */
#define WDECIMATION     59       /* write or rewrite decimation factor */
#define LOG_QUERY       60       /* duh */
/* added by DY */
#define CONTROL_TIMER 70
#define WRITE_VEHICLE_STATE 71
#define WRITE_GOAL_STATE 72
#define WRITE_DESIRED_STATE 73
#define WRITE_CONTROL_LAW1 74
#define WRITE_CONTROL_LAW6 75
#define WRITE_FORCE 76
#define WRITE_CONTROL_TIMER 77
#define WRITE_JOYSTICK1 78
#define WRITE_JOYSTICK6 79
#define WRITE_MBT_TARGET 80
#define WRITE_EMERGENCY 81
#define WRITE_MX_TIMER 82
#define WRITE_MX_TIMER1 83
#define WRITE_MX_TIMER2 84
#define WRITE_HEARTBEAT_TIMER 85
#define WRITE_MOTOR_STATUS 86
#define WRITE_MISSION_PARAMETERS 87
#define WRITE_PUMP_COMMAND 88
#define WRITE_MX_ACOMMS_TIMER 89
#define WRITE_DARK_LIGHT_CYCLE 90
#define WRITE_GOAL_OFFSET 91
#define WRITE_FLOWo 92
#define WRITE_HEARTBEAT_RECEIVE_TIME 93
#define WRITE_IRRADIANCE 94
#define WRITE_GOAL_IRRADIANCE 95
#define WRITE_DEPTH_FLOOR 96
#define WRITE_MX_EMERGENCY 97
#define WRITE_DEPTH_CEILING 98
#define WRITE_MISSION_STATUS 99 //added 2021/08/27
#define WRITE_BATTERY_PACK 100 //added 2021/08/30
#define  VERSION_MISMATCH     -900
#define  DT_SETTING_NOT_READY -901

typedef enum
{
  SRC_NONE,			/* 0 */
  SRC_NAV,			/* 1 */
  SRC_VEHICLE_ALTIMETER,	/* 2 */
  SRC_VEHICLE_CTD,	/* 3 */
  SRC_VESSEL_FATHOMETER,	/* 4 */
  SRC_VESSEL_GPS,			/* 5 */
  SRC_VEHICLE_MICROSTRAIN,			/* 6 */
}
data_source_t;

typedef struct
{
  double pos[NUM_DOF];		/* x, y, z, heading, roll, pitch */
  double vel[NUM_DOF];		/* Units: meters, radians, seconds */
  double acc[NUM_DOF];
  rov_time_t pos_time[NUM_DOF];	/* time original data was received */
  rov_time_t vel_time[NUM_DOF];	/* time original data was received */
  rov_time_t acc_time[NUM_DOF];	/* time original data was received */
  data_source_t pos_source[NUM_DOF];	/* source of data */
  data_source_t vel_source[NUM_DOF];	/* source of data */
  data_source_t acc_source[NUM_DOF];	/* source of data */
  int NFG;			/* Flag to indicate whether or not nav soln. is good, based on what
                   nav mode you are in and the number of good ranges returned */
}
vehicle_state_t;

/* ====================================================================== 
   functions
   =================================================================== */

extern const char * IMAGETALK_MESSAGE_NAME (int num);
extern const char * IMAGETALK_THREAD_NAME (int num);
extern int    IMAGE_THREAD_NUM( char * name);
#endif

/* ----------------------------------------------------------------------
      END OF FILE IMAGETALK.H
   ---------------------------------------------------------------------- */
