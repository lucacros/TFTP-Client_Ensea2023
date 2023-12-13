#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>


//download a file from a source



int main (int argc, char*argv[]){
    char host[20], file[20];
    strcpy (host,argv[1]); //copy the adress in the host
    strcpy (file,argv[2]); //copy the file's name in file
    
    printf("Host: %s\n",host);
    printf("File: %s\n",file);

////get adress of the server


// Declare and initialize struct addrinfo hints with zeros
struct addrinfo hints;
memset(&hints, 0, sizeof(struct addrinfo));
hints.ai_socktype = SOCK_DGRAM; // because it's UDP
hints.ai_family=AF_INET; //IPV4
hints.ai_protocol=IPPROTO_UDP;
struct addrinfo *res;

//replace node by 1069 and service by NULL
const char *node = "1069";  
const char *service = NULL; 

struct addrinfo {

int ai_flags;
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

////Reserve a connection socket to the server 

//create and initialise the socket
int sock = socket(res->ai_family,res->ai_socktype, res->ai_protocol);
if (sock == -1) {
    perror("Error during socket creation");
    exit(EXIT_FAILURE);
    }

////Read Request (RRQ)
int BUF_SIZE= 516; // Maximum size for TFTP packet
char buf[BUF_SIZE];
memset(buf, 0, BUF_SIZE);


buf[1] = 1; // Opcode to read is 1

// add the file name
strncpy(buf + 2, argv[1], strlen(argv[1]));

// add the mode ( read the file as it is)
strncpy(buf + 2 + strlen(argv[1]) + 1, "octet", strlen("octet"));

////Send the Request to the server

ssize_t sent_bytes = sendto(sock, buf, BUF_SIZE, 0,
                            (struct sockaddr *)&addrinfo sizeof(addrinfo));

if (sent_bytes == -1) {
    perror("Erreur lors de l'envoi de la requête RRQ");
    close(sock);
    exit(EXIT_FAILURE);
}
char response_buffer[516];  
ssize_t received_bytes = recvfrom(sock, response_buffer, sizeof(response_buffer), 0,
                                  (struct sockaddr *) &addrinfo, sizeof(addrinfo));

if (received_bytes == -1) {
    perror("Erreur lors de la réception de la réponse");
    close(sock);
    exit(EXIT_FAILURE);
}



}