#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

int main(int argc, char **argv){

        struct addrinfo hints;
        struct addrinfo *res;

        if(argc < 4){
                perror("Faltan argumentos\n");
                return -1;
        }
        memset(&hints, 0, sizeof(struct addrinfo));
        hints.ai_flags = AI_PASSIVE;
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_DGRAM;

        int rc = getaddrinfo(argv[1], argv[2], &hints, &res);
        if(rc == -1){
                printf("Error en el getaddrinfo: %s\n", gai_strerror(rc));
                return -1;
        }

        int sd = socket(res->ai_family, res->ai_socktype, 0);
        if(sd == -1){
                perror("Error en el socket\n");
                return -1;
        }
         ssize_t bytesEnv = sendto(sd, argv[3], strlen(argv[3]) + 1, 0, res->ai_addr, res->ai_addrlen);
        if(bytesEnv == -1){
                perror("Error en el sendto\n");
                return -1;
        }

        char buf[256];
        ssize_t bytesRec = recvfrom(sd, buf, 256, 0, res->ai_addr, &(res->ai_addrlen));
        if(bytesRec == -1){
                perror("Error en el recvfrom\n");
                return -1;
        }
        buf[bytesRec] = '\0';

        printf("%s\n", buf);

        freeaddrinfo(res);

        close(sd);

        return 0;
}
