#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdlib.h>

//Funcion que comprueba el tipo de fichero
const char * getType(mode_t mode) {
    if(S_ISLNK(mode)) return "Enlace simbolico";
    else if(S_ISREG(mode)) return "Fichero regular";
    else if (S_ISDIR(mode)) return "Directorio";
    else if (S_ISCHR(mode)) return "Dispositivo por caracteres";
    else if (S_ISBLK(mode)) return "Dispositivo por bloques";
    else if (S_ISFIFO(mode)) return "FIFO/Pipe";
    else return "Socket";
}

int main(int argc, char *argv[]) {
   if(argc == 2) {
      struct stat buff;
      stat(argv[1], &buff);
     
     //Para dar formato a la fecha
      const struct  tm *dt = localtime(&buff.st_atime);
      char * s = malloc(50);
      const char * format = "%Y-%m-%d %H:%M";
      strftime(s, 50, format, dt);
       
     
      printf("Major: %i  Minor: %i\n", major(buff.st_dev), minor(buff.st_dev)); 
      printf("Nodo-i: %li ", buff.st_ino);
      printf("Tipo de fichero: %s\n", getType(buff.st_mode));
      printf("Ultimo acceso: %s\n", s); 
      //st_mtime contiene la ultima fecha de modificacion del contenido del fichero o directorio mientras que st_ctime contiene la
      //ultima fecha de modificacion del contenido del inodo como por ejemplo un cambio de permisos.
   }
   else{
     perror("Solo se necesita 1 argumento.\n"); 
     return -1;  
   }
 
 return 0;
}
