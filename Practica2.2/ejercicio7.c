#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

int main(int argv, char **argc) {

	umask(027);

	int fd= open("Prueba.txt",O_CREAT|O_RDWR|O_TRUNC, 0645);

	if(fd==-1){
		perror("Error al abrir el fichero");
		return -1;
	}

	return 0;
}

