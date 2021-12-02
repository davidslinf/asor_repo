#include <stdio.h>
#include <string.h>
#include <sys/typres.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argv, char** args) {

        if(argv < 2) {
                perror("Se necesita un argumento\n");
                return -1;
        }

        int fd = open("Tuberia", 0_WRONLY);

        if (fd == -1) {
                perror("Error al abrir la tuberia\n");
                return -1;
        }

        write(fd, arg[1], strlen(argv[1]) +1);
        close(fd);

        return 0;
}
