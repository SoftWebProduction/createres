/*
 Copyright (c) 2013-2015 softWEB Production All Right Reserved, https://swp.pt
 This source is subject to the softWEB Production Licensing models.
 All other rights reserved.
 
 THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 PARTICULAR PURPOSE.
 
 
 Title:		Createres
 Version:	2.2.0
 Company:	softWEB Production
 Author:	Isaias Lourenco
 Copyright:	softWEB Production © Moerbius, 2015
 License:	MIT
 Website:	https://swp.pt
 
 
 
 BYTELOC        DATA        SIZE                EXPLANATION
 *******        ****        ****                ***********
 0              0           1 byte              (0 -> No compression 1 -> Compression) ** Not yet implemented **
 1-3            0           3 bytes             (Reserved fo future use)
 
 4-7            3           4 bytes             (Integer indicating that 3 files are stored in this resource)
 
 8-11           16          4 bytes             (Integer indicating that the first file is stored from the 16th byte onward)
 12-15          40          4 bytes             (Integer indicating that the second file is stored from the 40th byte onward)
 16-19          10056       4 bytes             (Integer indicating that the third file is stored from the 10056th byte onward)
 
 20-23          9           4 bytes             (Integer indicating that the first stored file contains 9 bytes of data)
 24-27          8           4 bytes             (Integer indicating that the first stored file's name is 8 characters in length)
 28-35          TEST.TXT    value of byte 20    (7 bytes, each encoding one character of the first stored file's filename)
 36-44          Testing12   value of byte 24    (9 bytes, containing the first stored file's data, which happens to be some text)
 
 45-48          10000       4 bytes             (Integer indicating that the second stored file contains 10000 bytes of data)
 49-52          9           4 bytes             (Integer indicating that the second stored file's name is 9 characters in length)
 53-61          TEST2.BMP   value of byte 49    (8 bytes, each encoding one character of the second stored file's filename)
 62-10061       ...         value of byte 45    (10000 bytes, representing the data stored within TEST2.BMP.  Data not shown!)
 
 10062-10065    20000       4 bytes             (Integer indicating that the third stored file contains 20000 bytes of data)
 10066-10069    9           4 bytes             (Integer indicating that the third stored file's name is 9 characters in length)
 10070-10078    TEST3.WAV   value of byte 10066 (8 bytes, each encoding one character of the third stored file's filename)
 10079-30078    ...         value of byte 10062 (20000 bytes, representing the data stored within TEST3.WAV.  Data not shown!)
 
 */

#ifndef __createres__Resource__
#define __createres__Resource__

#ifdef _MSC_VER
#include "VC/direntVC.h"
#include <io.h>
#include <direct.h>
#include <tchar.h>
#define MAXPATHLEN	MAX_PATH
#else
#include <dirent.h>
#include <sys/param.h>
#include <unistd.h>
#endif

#include <sys/stat.h>
#include <fcntl.h>
#include <cstring>
#include <cstdlib>

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

class Resource {
    
public:
    Resource();
    ~Resource();
    void pack(char *filename, char *path);
    char *unpack(char *resourcefilename, char *resourcename, int *filesize);
    int compress;       //Indicates either to use compression or not
    void listFiles(char *resourcename);
    
private:
    int getfilesize(char *filename);
    int countfiles(char *path);
    void packfile(char *filename, int fd);
    void findfiles(char *path, int fd);
    void showFiles(char *filename);
    int chartoint(char *value);
    
    int currentfile;	//This integer indicates what file we're currently adding to the resource.
    int currentloc;	    //This integer references the current write-location within the resource file
    int compresslloc;   //Location of the compression byte
    int numfilesloc;    //Location of the number of files byte
    int firstfileloc;   //Location of first file data
    
};

#endif /* defined(__createres__Resource__) */