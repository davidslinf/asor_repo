#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

void atiende(int clisd, const char * host, const char * serv){

  char buf[257];
  ssize_t size;

  while((size = recv(clisd, buf, 256, 0)) > 0){
    send(clisd, buf, size, 0);
    buf[size] = '\0';
  }

  if(size == 0){
    printf("Conexión con %s:%s terminada\n", host,serv);
  }
  else{
    perror("Se ha producido un error al recibir datos\n");
  }
}

int main(int argc, char * argv[]) {

 struct addrinfo hints;
 memset(&hints, 0, sizeof(struct addrinfo));
 hints.ai_family = AF_UNSPEC;
 hints.ai_socktype = SOCK_STREAM;
 
 struct addrinfo *res;
 int rc, sd;
 struct sockaddr_storage addr;
 socklen_t addrlen;
 char host[NI_MAXHOST];
 char serv[NI_MAXSERV];

 int clisd;

 if(argc < 3){
   perror("Se necesitan 2 argumentos, la dirección y el puerto\n");
   return -1;
 }

 rc = getaddrinfo(argv[1], argv[2], &hints, &res);
 
 sd = socket(res->ai_family, res->ai_socktype, 0);

 bind(sd, res->ai_addr, res->ai_addrlen);
  
 freeaddrinfo(res);

 listen(sd, 5);

 while(1) {

  addrlen = sizeof(addr);
  clisd = accept(sd, (struct sockaddr *) &addr, &addrlen);

  pid_t pid = fork();

  switch(pid)
  {
     case -1:
      perror("Error al realizar fork()\n");
      close(clisd);
      return 1;
     case 0:
      getnameinfo((struct sockaddr *) &addr, addrlen, host, NI_MAXHOST,
                serv, NI_MAXSERV, NI_NUMERICHOST|NI_NUMERICSERV);

      printf("Conexión desde %s:%s y PID %d\n", host, serv, getpid());
      atiende(clisd,host,serv);
      return 0;
     default:
      close(clisd);
      break;
  }
 }
 close(sd);

 return 0;
}
