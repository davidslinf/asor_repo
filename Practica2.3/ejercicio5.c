#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>

#define PATH_MAX 4096

int main(int argc, char** argv) {

        pid_t ProcesoID = getpid();
        pid_t PadreID = getppid();
        pid_t GrupoID = getpgid(0);
        pid_t SesionID = getsid(0);

        struct rlimit rlim;
        getrlimit(RLIMIT_NOFILE, &rlim);
        int MaxFicheros = rlim.rlim_max;

        char* DirActual = malloc(PATH_MAX);
        getcwd(DirActual, PATH_MAX);
        if(DirActual == NULL) perror("No hay suficiente espacio en el buffer para la ruta\n");

        printf("El PID es: %i\n", ProcesoID);
        printf("El PPID es: %i\n", PadreID);
        printf("El PGID es: %i\n", GrupoID);
        printf("El SID es: %i\n", SesionID);
        printf("El numero maximo de ficheros es: %i\n" , MaxFicheros);
        printf("El directorio de trabajo actual es: %s\n", DirActual);

        return 0;
}
