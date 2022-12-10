#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <errno.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char **argv){
        struct addrinfo hints;
        struct addrinfo *result;
        char host[NI_MAXHOST];
        char serv[NI_MAXSERV];

        memset(&hints, 0, sizeof(struct addrinfo));

        hints.ai_flags = AI_PASSIVE;
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_DGRAM;

        int rc = getaddrinfo(argv[1], argv[2], &hints, &result);

        if(rc == -1){
                printf("Error en getaddrinfo: %s\n", gai_strerror(rc));
                return -1;
        }

        int sd = socket(result->ai_family, result->ai_socktype, 0);
        if(sd == -1){
                perror("Error en la creacion del socket\n");
                return -1;
        }

        int rc2 = bind(sd, result->ai_addr, result->ai_addrlen);

        if(rc2 == -1){
                perror("Error en el bind\n");
                return -1;
        }

        freeaddrinfo(result);

        char buf[2];
        struct sockaddr_storage cliente;
        socklen_t clienteLen = sizeof(cliente);
 
         while(buf[0] != 'q'){
                ssize_t bytes = recvfrom(sd, buf, 2, 0,
                        (struct sockaddr *) &cliente, &clienteLen);
                buf[bytes] = '\0';

                if(bytes == 0){
                        printf("El cliente se ha desconectado\n");
                        buf[0] = 'q';
                }

                int rc3 = getnameinfo((struct sockaddr *) &cliente, clienteLen, host, NI_MAXHOST,
                        serv, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);

                if(rc3 == -1){
                        perror("Error en el getnameinfo\n");
                        return -1;
                }

                printf("Recibi %i bytes de %s:%s\n", bytes, host, serv);

                if(buf[0] == 'd'){
                        time_t t;
                        struct tm *locTime;
                        char bufTime[256];
                        t = time(NULL);
                        locTime = localtime(&t);
                        strftime(bufTime, 256, "%Y-%m-%d", locTime);

                        int writesize = sendto(sd, bufTime, strlen(bufTime), 0,
                                (struct sockaddr *) &cliente,clienteLen);
                        if(writesize == -1){
                                perror("Error en el sendto\n");
                                return -1;
                        }

                }
                 else if(buf[0] == 't'){
                        time_t t;
                        struct tm *locTime;
                        char bufTime[256];
                        t = time(NULL);
                        locTime = localtime(&t);
                        strftime(bufTime, 256, "%r", locTime);

                        int writesize = sendto(sd, bufTime, strlen(bufTime), 0,
                                (struct sockaddr *) &cliente,clienteLen);
                        if(writesize == -1){
                                perror("Error en el sendto\n");
                                return -1;
                        }

                }

                else if(buf[0] == 'q'){
                        printf("Comando de finalizacion recibido\n");
                }
                else    printf("Comando no soportado\n");

        }

        close(sd);

        return 0;
}

                

