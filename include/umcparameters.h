#ifndef UMCPARAMETERS_H
#define UMCPARAMETERS_H

#define MAX_N_OF_FSTOPS 42
#define MAX_N_OF_SHUTTER_SPEEDS 55
#define MAX_N_OF_EXPOSURE_MODES 13
#define MAX_N_OF_FOCUS_MODES  3
#define MAX_N_OF_ISO  42
#define MAX_N_OF_EXP_C  33
#define MAX_N_OF_ASPECT_RATIO  3
#define MAX_N_OF_COMPRESSIONS 6
#define MAX_N_OF_DRIVEMODES 3
#define MAX_N_OF_LIVEVIEW_ENTRIES   10
#define MAX_N_OF_CAMERA_MODES 5
#define MAX_N_OF_IMAGE_SIZES  4
#define MAX_N_OF_MOVIE_FORMATS   3
#define MAX_N_OF_QUALITY_FORMATS 12

#define STILL_MODE   1
#define MOVIE_MODE   2

typedef struct
{
  char            fstop[5];
  unsigned int    fstopCode;
} fstopEntry_t;

typedef struct
{
   char           mode[5];
   unsigned short exposureModeCode;
   unsigned short validityCode;
} exposureModeEntry_t;

typedef struct
{
  char            shutter[7];
  unsigned int    shutterCode;
} shutterEntry_t;

typedef struct
{
  char            mode[7];
  unsigned int    focusCode;
} focusModeEntry_t;

typedef struct
{
  char            iso[7];
  unsigned int    isoCode;
} isoEntry_t;

typedef struct
{
  char            comp[7];
  unsigned short    compCode;
} exposureCompensationEntry_t;

typedef struct
{
  char               driveMode[12];
  unsigned short     driveModeCode;
} driveModeEntryEntry_t;


typedef struct
{
  char            ratio[5];
  unsigned char    ratioCode;
} aspectRatioEntry_t;

typedef struct
{
  char            compression[6];
  unsigned char   compressionCode;
} compressionEntry_t;

typedef struct
{
   char  operatingMode[18];
   unsigned char operatingModeCode;
} operatingModeEntry_t;

typedef struct
{
   char   framesPerSecond[4];

} liveViewEntryT;

typedef struct
{
   char   imageSize[4];
   unsigned char imageSizeCode;
} imageSizeEntry_t;

typedef struct
{
   char movieFormat[10];
   unsigned char movieFormatCode;
} movieFormatEntry_t;

typedef struct
{
   char  movieQuality[18];
   unsigned  short movieQualityCode;
} movieQualityEntry_t;

#define MIN_UMC_LIVE_VIEW_INTERVAL  0.03

static const operatingModeEntry_t operatingModeTable[] =
{
   {"Stand-by",0x01},
   {"Still",0x02},
   {"Movie",0x03},
   {"Contents-Transfer",0x04},
   {"END",0x99}
};

static const liveViewEntryT liveViewtable[] =
{
   "0",
   "1",
   "2",
   "3",
   "4",
   "5",
   "10",
   "15",
   "30",
   "END"
};
static const  shutterEntry_t shutterTable[] =
{
   {"30",0x012C000A},
   {"25",0x00FA000A},
   {"20",0x00C8000A},
   {"15",0x0096000A},
   {"13",0x0082000A},
   {"10",0x0064000A},
   {"8",0x0050000A},
   {"6",0x003C000A},
   {"5",0x0032000A},
   {"4",0x0028000A},
   {"3.2",0x0020000A},
   {"2.5",0x0019000A},
   {"2",0x0014000A},
   {"1.6",0x0010000A},
   {"1.3",0x000D000A},
   {"1",0x000A000A},
   {"0.8",0x0008000A},
   {"0.6",0x0006000A},
   {"0.5",0x0005000A},
   {"0.4",0x0004000A},
   {"1/3",0x00010003},
   {"1/4",0x00010004},
   {"1/5",0x00010005},
   {"1/6",0x00010006},
   {"1/8",0x00010008},
   {"1/10",0x0001000A},
   {"1/13",0x0001000D},
   {"1/15",0x0001000F},
   {"1/20",0x00010014},
   {"1/25",0x00010019},
   {"1/30",0x0001001E},
   {"1/40",0x00010028},
   {"1/50",0x00010032},
   {"1/60",0x0001003C},
   {"1/80",0x00010050},
   {"1/100",0x00010064},
   {"1/125",0x0001007D},
   {"1/160",0x000100A0},
   {"1/200",0x000100C8},
   {"1/250",0x000100FA},
   {"1/320",0x00010140},
   {"1/400",0x00010190},
   {"1/500",0x000101F4},
   {"1/640",0x00010280},
   {"1/800",0x000010320},
   {"1/1000",0x000103E8},
   {"1/1250",0x000104E2},
   {"1/1600",0x00010640},
   {"1/2000",0x000107D0},
   {"1/2500",0x000109C4},
   {"1/3200",0x00010C80},
   {"1/4000",0x00010FA0},
   {"1/5000",0x00011388},
   {"1/6400",0x00011900},
   {"1/8000",0x00011F40},
   {"END",0X00099999}
};

static const  fstopEntry_t fstopTable[] =
{
   {"1.0",0x0064},
   {"1.1",0x006E},
   {"1.3",0x0082},
   {"1.4",0x008C},
   {"1.6",0x00A0},
   {"1.7",0x00AA},
   {"1.8",0x00B4},
   {"2.0",0x00C8},
   {"2.2",0x00DC},
   {"2.5",0x00FA},
   {"2.8",0x0118},
   {"3.2",0x0140},
   {"3.5",0x015E},
   {"4.0",0x0190},
   {"4.5",0x01C2},
   {"5.0",0x01F4},
   {"5.6",0x0230},
   {"6.3",0x0276},
   {"7.1",0x02C6},
   {"8.0",0x0320},
   {"9.0",0x0384},
   {"10.0",0x03E8},
   {"11.0",0x044C},
   {"13.0",0x0514},
   {"14.0",0x0578},
   {"16.0",0x0640},
   {"18.0",0x0708},
   {"20.0",0x07D0},
   {"22.0",0x0898},
   {"25.0",0x09C4},
   {"29.0",0x0B54},
   {"32.0",0x0C80},
   {"36.0",0x0E10},
   {"40.0",0x0FA0},
   {"45.0",0x1194},
   {"51.0",0x13EC},
   {"57.0",0x1644},
   {"64.0",0x1900},
   {"72.0",0x1C20},
   {"81.0",0x1FA4},
   {"90.0",0x2328},
   {"END",0x9999}
};

static const isoEntry_t isoTable[] =
{
   {"50",0x00000032},
   {"64",0x00000040},
   {"80",0x00000050},
   {"100",0x00000064},
   {"125",0x0000007D},
   {"160",0x000000A0},
   {"200",0x000000C8},
   {"250",0x000000FA},
   {"320",0x00000140},
   {"400",0x00000190},
   {"500",0x000001F4},
   {"640",0x00000280},
   {"800",0x00000320},
   {"1000",0x000003E8},
   {"1250",0x000004E2},
   {"1600",0x00000640},
   {"2000",0x000007D0},
   {"2500",0x000009C4},
   {"3200",0x00000C80},
   {"4000",0x00000FA0},
   {"5000",0x00001388},
   {"6400",0x00001900},
   {"8000",0x00001F40},
   {"10000",0x00002710},
   {"12800",0x00003200},
   {"16000",0x00003E80},
   {"20000",0x00004E20},
   {"25600",0x00006400},
   {"32000",0x00007D00},
   {"40000",0x00009C40},
   {"51200",0x0000C800},
   {"64000",0x0000FA00},
   {"80000",0x00013880},
   {"102400",0x00019000},
   {"128000",0x0001F400},
   {"160000",0x00027100},
   {"204800",0x00032000},
   {"256000",0x0003E800},
   {"320000",0x0004E200},
   {"409600",0x00064000},
   {"AUTO",0x00FFFFFF},
   {"END",0x00999999}
};

static const exposureModeEntry_t exposureModeTable[] =
{
   {"M",0x0001,1},
   {"P",0x0002,1},
   {"A",0x0003,1},
   {"S",0x0004,1},
   {"IA",0x8000,1},
   {"SA",0x8001,1},
   {"MPA",0x8050,2},
   {"MAP",0x8051,2},
   {"MSP",0x8052,2},
   {"MME",0x8053,2},
   {"MIA",0x8054,2},
   {"MHP",0x8055,2},
   {"MHA",0x8056,2},
   {"END",0x9999,2}
};

static const aspectRatioEntry_t aspectRatioTable[] =
{
   {"3:2",0x01},
   {"16:9",0x02},
   {"END",0x09}
};

static const compressionEntry_t compressionTable[] =
{
   {"STD",0x02},
   {"FINE",0x03},
   {"XFINE",0x04},
   {"RAW",0x10},
   {"RAWJ",0x13},
   {"END",0x99}
};

static const  driveModeEntryEntry_t driveModeTable[] =
{
   {"NORMAL",0x0001},
   {"CONTINUOUS",0x8013},
   {"END",0x9999}
};

static const  exposureCompensationEntry_t exposureCompTable[] =
{
   {"-5.0",0xEC78},
   {"-4.7",0xEDA4},
   {"-4.3",0xEF34},
   {"-4.0",0xF060},
   {"-3.7",0XF18C},
   {"-3.3",0xF31C},
   {"-3.0",0xF448},
   {"-2.7",0xF574},
   {"-2.3",0xF704},
   {"-2.0",0xF830},
   {"-1.7",0xF95C},
   {"-1.3",0xFAEC},
   {"-1.0",0xFC18},
   {"-0.7",0xFD44},
   {"-0.3",0XFED4},
   {"0",0x0000},
   {"0.0",0x0000},
   {"0.3",0x012C},
   {"0.7",0x02BC},
   {"1.0",0x03E8},
   {"1.3",0x0514},
   {"1.7",0x06A4},
   {"2.0",0x07D0},
   {"2.3",0x08FC},
   {"2.7",0x0A8C},
   {"3.0",0x0BB8},
   {"3.3",0x0CE4},
   {"3.7",0x0E74},
   {"4.0",0x0FA0},
   {"4.3",0x10CC},
   {"4.7",0x125C},
   {"5.0",0x1388},
   {"END",0x9999}
};



static const focusModeEntry_t focusModeTable[] =
{
   {"M",0x0001},
   {"AF_S",0x0002},
   {"AF_C",0x8004},
   {"END",0x9999}
};

static const imageSizeEntry_t imageSizeTable[] =
{
   {"L",0x01},
   {"M",0x02},
   {"S",0x03},
   {"END",0x99}
};

static const movieFormatEntry_t movieFormatTable[] =
{
   {"XAVC_S_4K",0x08},
   {"XAVC_S_HD",0x09},
   {"END",0x99}
};

static const movieQualityEntry_t movieQualityTable[] =
{
   {"4K_30p_100Mbps",0x8100},
   {"4K_30p_60Mbps",0x8101},
   {"4K_24p_100Mbps",0x8102},
   {"4K_24p_60Mbps",0x8103},
   {"HD_60p_50Mbps",0x8200},
   {"HD_30p_50Mbps",0x8201},
   {"HD_24p_50Mbps",0x8202},
   {"HD_120p_100Mbps",0x8203},
   {"HD_120p_60Mbps",0x8204},
   {"HD_HFR30p_16Mbps",0x8283},
   {"HD_HFR24p_16Mbps",0x8284},
   {"END",0x9999}
};





#endif // UMCPARAMETERS_H
