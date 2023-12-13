#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>


//download a file from a source



int main (int argc, char*argv[]){
    char host[20], file[20];
    strcpy (host,argv[1]); //copy the adress in the host
    strcpy (file,argv[2]); //copy the file's name in file
    
    printf("Host: %s\n",host);
    printf("File: %s\n",file);

//get adress of the server


// Declare and initialize struct addrinfo hints with zeros
struct addrinfo hints;
memset(&hints, 0, sizeof(struct addrinfo));
hints.ai_socktype = SOCK_DGRAM; // because it's UDP
hints.ai_family=AF_INET; //IPV4
struct addrinfo *res;
//replace node by 1069 and service by NULL
const char *node = "1069";  
const char *service = NULL; 

struct addrinfo {

int ai_flags;
int ai_protocol;
socklen_t ai_addrlen;
struct sockaddr *ai_addr;
char *ai_canonname;
struct addrinfo *ai_next;
};

// call function getaddrinfo
int status;
status = getaddrinfo( node, service,&hints, &res);

//test error of getaddrinfo
if (status != 0) {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
        return 1;
    }


// res contain athe informations concerning adresses
//we need to parcour res to obtain the informations
int sock =socket( res->ai_family, 
res-> ai_socktype, res -> ai_protocol);


}