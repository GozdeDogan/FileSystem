#ifndef H_FILE
#define H_FILE

#include <string>
#include "8080emuCPP.h"
#include "memory.h"

#define MAXSIZE 100

using namespace std;


class File
{
	public:
		File();
		char *getFileName();
		void setFileName(char file[MAXSIZE]);
		int getFileCreation();
		void setFileCreation(int create);
		int getLastModify();
		void setLastModify(int modify);
		int getLastAccess();
		void setLastAccess(int access);
		size_t getFileSize();
		void setFileSize(size_t size);

		void printInfo();

	private:
		char filename[MAXSIZE];
		int fileCreation;
		int lastModify;
		int lastAccess;
		size_t filesize;
};


#endif
