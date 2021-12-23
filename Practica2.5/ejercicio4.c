#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/select.h>

int main(int argc, char * argv[]) {

 struct addrinfo hints;
 memset(&hints, 0, sizeof(struct addrinfo));
 hints.ai_family = AF_UNSPEC;
 hints.ai_socktype = SOCK_DGRAM;

 struct addrinfo *res;
 int rc, sd;
 struct sockaddr_storage addr;
 socklen_t addrlen;
 char buf[2];
 char host[NI_MAXHOST];
 char serv[NI_MAXSERV];

 time_t currTime;
 struct tm *currDate;
 char * s;
 const char * dateFormat = "%Y-%m-%d";
 const char * hourFormat = "%H:%M:%S %p";

 if(argc < 3){
   perror("Se necesitan 2 argumentos, la dirección y el puerto\n");
   return -1;
 }

 rc = getaddrinfo(argv[1], argv[2], &hints, &res);

 sd = socket(res->ai_family, res->ai_socktype, 0);

 bind(sd, res->ai_addr, res->ai_addrlen);

 fd_set read_fds;

 while(1) {
  addrlen = sizeof(addr);
  FD_ZERO(&read_fds);
  FD_SET(sd, &read_fds);
  FD_SET(0, &read_fds);

  select(sd+1, &read_fds, NULL, NULL, NULL);
  ssize_t size;

  if(FD_ISSET(sd, &read_fds)){
    size = recvfrom(sd, buf, 2, 0, (struct sockaddr *) &addr, &addrlen);
    buf[size] = '\0';
  }
  else if(FD_ISSET(0, &read_fds)){
    size  = read(0, buf, 2);
  }

  if(FD_ISSET(sd, &read_fds)){
    getnameinfo((struct sockaddr *) &addr, addrlen, host, NI_MAXHOST,
       serv, NI_MAXSERV, NI_NUMERICHOST|NI_NUMERICSERV);

    printf("%d bytes de %s:%s\n", size, host, serv);
  }
  else if(FD_ISSET(0, &read_fds)){
    printf("%d bytes de entrada estandar\n", size);
  }

  if(buf[0] == 'q'){
    printf("Saliendo...\n");
    freeaddrinfo(res);
    close(sd);
    exit(1);
  }
  else if(buf[0] == 'd') {
     currTime = time(NULL);
     currDate = localtime(&currTime);
     s = malloc(11);
     strftime(s, 11, dateFormat, currDate);
     
    if(FD_ISSET(0, &read_fds)){
       printf("%s\n", s);
     }
     else if(FD_ISSET(sd, &read_fds)){
       sendto(sd, s, 11, 0, (struct sockaddr *) &addr, addrlen);
     }
    
     memset(s,0,strlen(s));
     free(s);
  }
  else if(buf[0] == 't') {
     currTime = time(NULL);
     currDate = localtime(&currTime);
     s = malloc(12);
     strftime(s, 12, hourFormat, currDate);

     if(FD_ISSET(0, &read_fds)){
       printf("%s\n",  s);
     }
     else if(FD_ISSET(sd, &read_fds)){
       sendto(sd, s, 11, 0, (struct sockaddr *) &addr, addrlen);
     }

     memset(s,0,strlen(s));
     free(s);
  }
  else{
    printf("Comando %c no soportado\n", buf[0]);
  }
 }

 return 0;
}
