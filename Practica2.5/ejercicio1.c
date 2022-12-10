#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>

int main(int argc, char ** argv){

        struct addrinfo hints;
        struct addrinfo *result, *i;
        char host[NI_MAXHOST];
        char serv[NI_MAXSERV];


        memset(&hints, 0, sizeof(struct addrinfo));
        hints.ai_flags = AI_PASSIVE;
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;
        int rc = getaddrinfo(argv[1], argv[2], &hints, &result);
        if(rc == -1){
                perror("Error en el addrinfo: %s\n", gai_strerror(rc));
                return -1;
        }

        for(i = result, i != 0, i = i->ai_next){
                int rb = getnameinfo(i->ai_addr, i->ai_addrlen, host, NI_MAXHOST, serv, NI_MAXSERV,
                        NI_NUMERICHOST | NI_NUMERICSERV);
                if(rb == -1){
                        perror("Error en el getnameinfo\n");
                        return -1;
                }
        }
         printf("HOST: %s, SERV: %s\n", host, serv);

        freeaddrinfo(result);

        return 0;
}
