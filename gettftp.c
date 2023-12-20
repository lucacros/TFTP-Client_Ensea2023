#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h> //getaddrinfo
#include <netdb.h> //getaddrinfo
#include <netinet/in.h>
#include <unistd.h> // STDOUT_FILENO and STDIN_FILENO



//download a file from a source



int main (int argc, char*argv[]){
    char host[20], file[20];
    strcpy (host,argv[1]); //copy the adress into host
    strcpy (file,argv[2]); //copy the file's name into file
    
    printf("Host: %s\n",host);
    printf("File: %s\n",file);

///get the adress of the server


// Declare and initialize struct addrinfo hints with zeros
struct addrinfo hints;
//hints initialization
memset(&hints, 0, sizeof(struct addrinfo));
hints.ai_socktype = SOCK_DGRAM; // because it's UDP
hints.ai_family=AF_INET; //IPV4
hints.ai_protocol=IPPROTO_UDP;
hints.ai_flags=0;

struct addrinfo *res;

 
const char *service = "69"; 

// struct addrinfo {

// int ai_flags;
// socklen_t ai_addrlen;
// struct sockaddr *ai_addr;
// char *ai_canonname;
// struct addrinfo *ai_next;
// };

// call function getaddrinfo
//status creation
int status;
status = getaddrinfo(argv[1], service, &hints, &res);

//test error of getaddrinfo
if (status != 0) {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
        exit(EXIT_FAILURE);
    }

////Reserve a connection socket to the server 

//create and initialise the socket
int sock = socket(res->ai_family,res->ai_socktype, res->ai_protocol);
if (sock == -1) {
    perror("Error during socket creation");
    freeaddrinfo(res);
    exit(EXIT_FAILURE);
    }

////Read Request (RRQ)
int BUF_SIZE= 1500; // Maximum size for TFTP packet
// char buf[BUF_SIZE];
// memset(buf, 0, BUF_SIZE);


// buf[1] = 1; // Opcode to read is 1

// // add the file name
// strncpy(buf + 2, file, strlen(file));

// // add the mode ( read the file as it is)
// strncpy(buf + 2 + strlen(file) + 1, "octet", strlen("octet"));

char*cmd=malloc(BUF_SIZE);
cmd[0]=0;
cmd[1]=1;

char*filename = argv[2];
strcpy(&cmd[2], filename);
strcpy(&cmd[2+strlen(filename) + 1], "octet");

int size = (int)(2 + strlen(filename)+1+strlen("octet")+1);


////Send the Request to the server

// ssize_t sent_bytes = sendto(sock, buf, BUF_SIZE, 0,res->ai_addr,res->ai_addrlen);

// //ssize_t sent_bytes = sendto(sock, buf, BUF_SIZE, 0,
// //                          (struct sockaddr *)&addrinfo sizeof(addrinfo));

// if (sent_bytes == -1) {
//     perror("Error sending RRQ request");
//     close(sock);
//     freeaddrinfo(res);
//     exit(EXIT_FAILURE);
// }
// char response_buffer[516];  
// //ssize_t received_bytes = recvfrom(sock, response_buffer, sizeof(response_buffer), 0,
// //                                  (struct sockaddr *) &addrinfo, sizeof(addrinfo));

// ssize_t received_bytes = recvfrom(sock, response_buffer, sizeof(response_buffer), 0,
//                                   res->ai_addr, &(res->ai_addrlen));
// if (received_bytes == -1) {
//     perror("Error receiving response");
//     close(sock);
//     freeaddrinfo(res);
//     exit(EXIT_FAILURE);
// }

freeaddrinfo(res);
close(sock);
return 0;

}