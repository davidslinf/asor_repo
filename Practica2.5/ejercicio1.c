#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>

int main(int argc, char ** argv){

        struct addrinfo hints;
        struct addrinfo *result, *i;

        memset(&hints, 0, sizeof(struct addrinfo));
        hints.ai_flags = AI_PASSIVE;
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;
        int rc = getaddrinfo(argv[1], argv[2], &hints, &result);
        if(rc == -1){
                printf("Error en el addrinfo: %s\n", gai_strerror(rc));
                return -1;
        }

        for(i = result, i != 0, i = i->ai_next){
                char host[NI_MAXHOST];
                int rb = getnameinfo(i->ai_addr, i->ai_addrlen, host, NI_MAXHOST, NULL, 0, NI_NUMERICHOST);
                if(rb == -1){
                        perror("Error en el getnameinfo\n");
                        return -1;
                }
                 printf("%s\t%i\t%i\n", host, i->ai_family, i->ai_socktype);
        }
        
        freeaddrinfo(result);

        return 0;
}
