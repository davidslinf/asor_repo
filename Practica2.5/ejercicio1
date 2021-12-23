#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>

int main(int argc, char** args) {

        struct addrinfo hints;
        memset(&hints, 0, sizeof(struct addrinfo));
        hints.ai_family = AF_UNSPEC;

        struct addrinfo *res, *act;
        char name[257];

        if(argc != 2) {
                perror("Se necesita pasar una direccion\n");
                return -1;
        }
        if(getaddrinfo(argv[1], NULL, &hints, &res) == 0) {
                for(act = res; act != NULL; act = act->ai_next ) {
                        getnameinfo(act->ai_addr, act->ai_addrlen, name, sizeof(name), NULL, $
                        printf("%s %i %i\n", name, act->ai_family, act->ai_socktype);
                }
        }
        else {
                perror("Error en getaddrinfo()\n");
                return -1;
        }

        freeaddrinfo(res);
        return 0;
}


