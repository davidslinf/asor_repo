#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <time.h>
#include <sys/select.h>
#include <unistd.h>

int main(int argc, char ** argv){

        struct addrinfo hints;
        struct addrinfo *res;

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

        int rc2 = bind(sd, res->ai_addr, res->ai_addrlen);
        if(rc2 == -1){
                perror("Error en el bind\n");
                return -1;
        }

        freeaddrinfo(res);

        char buf[2];
        struct sockaddr_storage cliente;
        socklen_t clienteLen = sizeof(cliente);

        char host[NI_MAXHOST];
        char serv[NI_MAXSERV];

        fd_set set;
 
        while(buf[0] != 'q'){
                FD_ZERO(&set);
                FD_SET(0, &set);
                FD_SET(sd, &set);

                int rs = select(sd+1, &set, 0, 0, 0);
                if(rs == -1){
                        perror("Error en el select\n");
                        return -1;
                }

                ssize_t bytes;

                if(FD_ISSET(sd, &set)){
                        bytes = recvfrom(sd, buf, 2, 0, (struct sockaddr *) &cliente, &clienteLen);
                }
                else if(FD_ISSET(0, &set)){
                        bytes = read(0, buf, 2);
                }
                if(bytes == -1){
                        perror("Error en el recvfrom\n");
                        return -1;
                }
                if(bytes == 0){
                        printf("El cliente se ha desconectado\n");
                        buf[0] = 'q';
                }
                else buf[bytes] = '\0';

                if(FD_ISSET(sd, &set)){
                        int rc3 = getnameinfo((struct sockaddr *) &cliente, clienteLen, host,
                                NI_MAXHOST,serv, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);
                        if(rc3 == -1){
                                perror("Error en el getnameinfo\n");
                                return -1;
                        }

                        printf("Recibidos %i bytes de %s:%s\n", bytes, host, serv);
                }

                if(buf[0] == 't'){
                        time_t t = time(NULL);
                        char bufTime[256];
                        struct tm *locTime;
                        locTime = localtime(&t);
                        strftime(bufTime, 256, "%H:%M:%S %p", locTime);

                        if(FD_ISSET(sd, &set)){
                                ssize_t recibidos = sendto(sd, bufTime, strlen(bufTime), 0,
                                        (struct sockaddr *) &cliente, clienteLen);
                                if(recibidos == -1){
                                        perror("Error en el sendto\n");
                                        return -1;
                                }
                        }
                        else if(FD_ISSET(0, &set)){
                                printf("%s\n", bufTime);
                        }
                }
                 else if(buf[0] == 'd'){
                        time_t t = time(NULL);
                        char bufTime[256];
                        struct tm *locTime;
                        locTime = localtime(&t);
                        strftime(bufTime, 256, "%Y-%m-%d", locTime);

                        if(FD_ISSET(sd, &set)){
                                ssize_t recibidos = sendto(sd, bufTime, strlen(bufTime), 0,
                                        (struct sockaddr *) &cliente, clienteLen);
                                if(recibidos == -1){
                                        perror("Error en el sendto\n");
                                        return -1;
                                }
                        }
                        else if(FD_ISSET(0, &set)){
                                printf("%s\n", bufTime);
                        }
                }
                else if(buf[0] == 'q'){
                        printf("Saliendo...\n");

                }
                else{
                        printf("Comando no soportado\n");
                }
        }
        close(sd);
        return 0;
}


