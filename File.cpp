#include <iostream>
#include "8080emuCPP.h"
#include "gtuos.h"
#include <cstring>
#include <fstream>
#include "File.h"
#include <string>

#define MAXSIZE 100

using namespace std;


File::File(){
	//filename = " "; // setfilename ile degisecek
	fileCreation = 0;
	lastModify = 0;
	lastAccess = 0;
	filesize = 0;
}

char* File::getFileName(){
	return filename;
}


void File::setFileName(char file[MAXSIZE]){
    //cout << "file: " << file << endl;
    strcpy(filename, file);
    //cout << "File: " << filename << endl;
}

int File::getFileCreation(){
	return fileCreation;
}

void File::setFileCreation(int create){
	fileCreation = create;
}

int File::getLastModify(){
	return lastModify;
}

void File::setLastModify(int modify){
	lastModify = modify;
}

int File::getLastAccess(){
	return lastAccess;
}

void File::setLastAccess(int access){
	lastAccess = access;
}

size_t File::getFileSize(){
	return filesize;
}

void File::setFileSize(size_t size){
	filesize = size;
}

void File::printInfo(){
	cout << filename << "\t" << fileCreation << "\t" << lastModify << "\t" << lastAccess << "\t" << filesize << endl;
}
