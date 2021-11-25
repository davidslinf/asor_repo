/*      Cuando se acaba el padre antes que el hijo, el PPID del hijo pasa a ser 1 ya que es adoptado por Init()
        Cuando el hijo acaba antes que el padre este se queda en estado zombie ya que el padre no ha hecho wait()
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>

#define PATH_MAX 4096

void MostrarAtributos() {

        pid_t ProcesoID = getpid();
        pid_t PadreID = getppid();
        pid_t GrupoID = getpgid(0);
        pid_t SesionID = getsid(0);

        struct rlimit rlim;
        getrlimit(RLIMIT_NOFILE, &rlim);
        int MaxFicheros = rlim.rlim_max;

        char* DirActual = malloc(PATH_MAX);
        getcwd(DirActual, PATH_MAX);

        printf("El PID es: %i\n", ProcesoID);
        printf("El PPID es: %i\n", PadreID);
        printf("El PGID es: %i\n", GrupoID);
        printf("El SID es: %i\n", SesionID);
        printf("El numero maximo de ficheros es: %i\n" , MaxFicheros);
        if(DirActual == NULL) perror("No hay suficiente espacio en el buffer para la ruta\n");
        else printf("El directorio de trabajo actual es: %s\n", DirActual);
        
        free(DirActual);

        return;
}

int main(int argc, char** argv) {

        pid_t pid = fork();

        if(pid == -1){ //Error
                perror("Error en fork()\n");
                return -1;
        }
        else if(pid == 0){ //Hijo
                if(setsid() == -1){
                       perror("Error al crear la sesion\n");
                        return -1;
                }

                if(chdir("/tmp") == -1){
                        perror("Error al cambiar de directorio\n");
                        return -1;
                }

                MostrarAtributos();
        }
        else { //Padre
                //sleep(3)
                MostrarAtributos();
        }

        return 0;
}

