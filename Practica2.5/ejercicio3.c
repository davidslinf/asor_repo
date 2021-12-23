#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char * argv[]) {

 struct addrinfo hints;
 memset(&hints, 0, sizeof(struct addrinfo));
 hints.ai_family = AF_UNSPEC;
 hints.ai_socktype = SOCK_DGRAM;

 struct addrinfo *res;
 int rc, sd;

 char buf[257];

 if(argc < 4) {
   perror("No hay suficientes argumentos\n");
   return -1;
 }

 rc = getaddrinfo(argv[1], argv[2], &hints, &res);

 sd = socket(res->ai_family, res->ai_socktype, 0);

 sendto(sd, argv[3], strlen(argv[3]), 0, res->ai_addr, res->ai_addrlen);

 ssize_t size  = recvfrom(sd, buf, 256, 0, res->ai_addr, &(res->ai_addrlen));
 buf[257] = '\0';

 printf("%s\n", buf);

 freeaddrinfo(res);

 close(sd);

 return 0;
}
