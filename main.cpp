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
 
 */

#ifdef _MSC_VER
#include "VC/direntVC.h"
#include "VC/getopt.h"
#include <io.h>
#include <direct.h>
#include <tchar.h>
#define MAXPATHLEN	MAX_PATH
#else
#include <unistd.h>
#endif

#include <stdio.h>
#include <cstdlib>
#include <ctype.h>

#include "Resource.h"

#define VERSION "2.2.0"
#define ARGUMENTS "hr:f:u:cl"

void showList();
void unpack(char *filename);
void showHelp();


#ifdef _MSC_VER

wchar_t *resourcename;
wchar_t *folder;

int _tmain(int argc, TCHAR** argv) {
    //Disable -> warning C4996: 'abc': The POSIX name for this item is deprecated. Instead, use the ISO C++ conformant name: _abc. See online help for details.
#pragma warning (disable : 4996)
    
    wchar_t *arguments = _T(ARGUMENTS);
    
    
#else
    
    char *resourcename = NULL;
    char *folder = NULL;
    
    int main(int argc, char** argv) {
        const char *arguments = ARGUMENTS;
        
#endif
        // Our Resource Class
        Resource resources;
        
        int c;
        
        if(argc == 1)
            showHelp();
        
        c = getopt(argc, argv, arguments);
        
        while (c != -1)
        {
            switch (c)
            {
                case 'h':
                    showHelp();
                    break;
                case 'r':
                    resourcename = optarg;
                    break;
                case 'f':
                    folder = optarg;
                    break;
                case 'l':
                    showList();
                    break;
                case 'c':
                    //resources.compress = 1;
                    break;
                case 'u':
                    unpack(optarg);
                    break;
                case '?':
                    if (optopt == ':')
                        fprintf (stderr, "Option -%c requires an argument.\n", optopt);
                    else if (isprint(optopt))
                        fprintf(stderr, "Unknown option `-%c'.\n", optopt);
                    else
                        fprintf(stderr, "Unknown option character `\\x%x'.\n", optopt);
                    exit(1);
                default:
                    showHelp();
                    break;
            }
            
            c = getopt(argc, argv, arguments);
        }
        
#ifdef _MSC_VER
        
        char newfilename[255];
        char newpath[255];
        
        if(filename != NULL && path != NULL) {
            
            int i = 0;
            
            while(filename[i] != '\0')
            {
                newfilename[i] = (char)filename[i];
                ++i;
            }
            newfilename[i] = '\0';
            i = 0;
            
            while(path[i] != '\0')
            {
                newpath[i] = (char)path[i];
                ++i;
            }
            newpath[i] = '\0';
            
            resources.pack(newfilename, newpath);
#else
            if(resourcename != NULL && folder != NULL)
            {
                resources.pack(resourcename, folder);
#endif
                
            }
            
            for (int index = optind; index < argc; index++)
                printf("Non-option argument %s\n", argv[index]);
            
            return 0;
        }
        
        void unpack(char *filename) {
            int fd;
            int filesize;
            Resource resources;
            
            printf("Unpacking file: %s\n", filename);
            
            fd = open(filename, O_WRONLY | O_EXCL | O_CREAT, S_IRUSR);
            
            write(fd, resources.unpack(resourcename, filename, &filesize), filesize);
            
            close(fd);
            
            printf("Done!\n");
            
        }
        
        void showList() {
            
            if(resourcename != NULL) {
                
                Resource resources;
                
                resources.listFiles(resourcename);
            }
            else {
                printf("Must specify a resource filename.");
            }
        }
        
        void showHelp() {
            printf("\n");
            printf("Resource Packer %s\n", VERSION);
            printf("Copyright 2013 - 2015 by Moerbius\n\n");
            printf("Usage:\n");
            printf("createres <options>\n\n");
            printf("   -h                  This help\n");
            printf("   -r <resource name>  Resource file name\n");
            printf("   -f <folder name>    Folder containing the images or sounds to pack.\n");
            printf("   -u <file name>      File to unpack from resource.\n");
            //printf("   -c                  Compress the files. (NOT AVAILABLE YET)\n");
            printf("   -l                  Lists all files inside the resource.\n\n");
            printf("Example:\n");
            printf("   createres -r resources.dat -u image1.bmp\n");
            printf("   createres -r resources.dat -f DATA\n\n");
            
            exit(0);
        }