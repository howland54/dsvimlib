#ifndef INI_FILE_H
#define INI_FILE_H
/* this module is part of dsnav, a piece of software intended to communicate with n456, a linux based command processor
	that communicates with custom digital ranger boards

	the initial configuration of this software was developed on April 10, 2008, by Jonathan Howland 
	Woods Hole Oceanographic Institution
	Deep Submergence Laboratory

	508-289-2653
	jhowland@whoi.edu

*/

#include <stdio.h>

#define	MAX_CHARACTER_COUNT	128

#define BAD_INI_FILE_READ	-2000
#define	GOOD_INI_FILE_READ	 2000

#define	INI_FILE_FALSE		0
 
class IniFile
{
public:
	IniFile();
	
   int		openIni(const char *file_name);
   void     closeIni();
   int		readInt(const char *section, const char *attribute, int	default_int);
   int		readHexInt(const char *section, const char *attribute, int	default_int);
   double	readDouble(const char *section, const char *item, double	default_double);
   char     *readString(const char *section, const char *item, const char *default_string);
   void     setFD(FILE *fd);

private:
	FILE	*fd;
};


#endif
