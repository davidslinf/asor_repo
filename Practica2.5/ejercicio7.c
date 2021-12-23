#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[]) {

 struct addrinfo hints;
 memset(&hints, 0, sizeof(struct addrinfo));
 hints.ai_family = AF_UNSPEC;
 hints.ai_socktype = SOCK_STREAM;

 struct addrinfo *res;
 int rc, sd;

 char buf[257];

 if(argc < 3){
   perror("Se necesitan 2 argumentos, la dirección y el puerto\n");
   return -1;
 }

 rc = getaddrinfo(argv[1], argv[2], &hints, &res);

 sd = socket(res->ai_family, res->ai_socktype, 0);

 connect(sd, (struct sockaddr *) res->ai_addr, res->ai_addrlen);

  
 ssize_t size;

  while(1){
   size = read(0, buf, 256);
   buf[size] = '\0';

   send(sd, buf, size, 0);

   if(buf[0] == 'Q' && size ==2) {
     break;
   }
   else {
     recv(sd, buf, size, 0);
     printf("%s", buf);
   }
  }

 freeaddrinfo(res);
 close(sd);

 return 0;
}
