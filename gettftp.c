#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//download a file from a source



int main (int argc, char*argv[]){
    char host[20], file[20];
    strcpy (host,argv[1]); //copy the adress in the host
    strcpy (file,argv[2]); //copy the file's name in file
    
    printf("Host: %s\n",host);
    printf("File: %s\n",file);

}
