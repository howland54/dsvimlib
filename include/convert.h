/********
* file: convert.h
* date: 12Nov89
* vers: 1.00
* orig: Steve Gegg

   April 16 2001 LLW updated some trig constants

* include file for use in data processing and plotting routines
  contains miscellaneous conversion defines
********/

#ifndef _CONVERSIONS
#define _CONVERSIONS

#define CMS_INCH	2.54	/* cms/inch */
#define METERS_FOOT 	0.3048	/* meters/foot */
#define METERS_NMILE	1852.0	/* meters/nautical mile */
#define METERS_FATHOM	1.8288	/* meters/fathom (straight conversion) */
#define UMETERS_UFATHOM	1.8750	/* unc mtrs/unc fthm - accounts for */
#define PSI_BARS  0.68947529
#define DECIBARS_TO_PSI  1.4503774
				/* snd vel of 1500m/sec to 800fm/sec */

/* April 16 2001 LLW updated value here */
// #define PI            3.1415926535897932384626433832795              /* PI */
// #define TWO_PI               (2.0 * PI)              /* 2*PI */

/* April 16 2001 LLW updated value here */
#define RADIANS		(57.295779513082320876798154814105)	/* degrees/radian */
// #define RTOD         RADIANS
// #define DTOR         (1.0/RTOD)

#define SECS_HOUR 3600
#define DEG_TO_RADIANS(a)	(a/RADIANS)	/* degrees (a) to radians */
#define RAD_TO_DEGREES(a)	(a*RADIANS)	/* radians (a) to degrees */
#define DEGMIN_TO_DECDEG(a,b) ((a)+(b/60.0))	/* deg,min to decimal degrees */
#define DEGMIN_TO_SECS(a,b) ((a*3600.0)+(b*60.0))	/* deg,min to seconds */
#define MSEC_TO_KNOTS(a)	((a/METERS_NMILE)*SECS_HOUR)
#define KNOTS_TO_MSEC(a)	((a*METERS_NMILE)/SECS_HOUR)
#define FEET_TO_METERS(a)	(a * METERS_FOOT)

#define  PRESSURE_TO_DEPTH .9930   // decibars to meters, from unesco page


#define MPStoKTS     1.943844494
#define KTStoMPS     1.943844494
#define MMtoYDS      0.001093613
#define CMtoFATHOMS  0.00548066492
#define CMtoFEET     0.03280839895

#define NEWTS_PER_LB    (4.48)

#define DTOR   (0.01745329251994)
#define RTOD   (57.29577951308)

#define TWOPI  (6.28318530718)
#define TWO_PI (6.28318530718)
#define PI     (3.14159265359)

#define RAD_PER_SEC_TO_RPM   (60.0/TWOPI)
#define RPM_TO_RAD_PER_SEC   (TWOPI/60.0)

	/* coordinate translation */

	/* coordinate translation options */
#define XY_TO_LL		1
#define LL_TO_XY		2
#define LL_TO_LL		3

	/* coordinate system types */
#define GPS_COORDS_WGS84	1
#define GPS_COORDS_C1866	2
#define LORANC_COORDS		3
#define SURVEY_COORDS		4
#define TRANSIT_COORDS		5

	/* coordinate system type messages */
#define GPS_DATA_WGS84		"GPS, WGS'84 \n"
#define GPS_DATA_C1866		"GPS, Clarke 1866 \n"
#define LORC_DATA		"LORANC Data\n"
#define TRANSIT_DATA		"TRANSIT Satellite Data\n"
#define SURVEY_DATA		"SURVEYED Benchmark Data\n"


//#define inrange(a, b, c) (((a)>=(b)) && ((a)<=(c)))

#define ATTITUDE_TO_DEG ((i>=DOF_HDG) ? RTOD : 1.0)

#endif
