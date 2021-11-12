#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
//Esta funcion se encarga de mostrar la informacion de cada elemento del directorio por pantalla
//Devuelve true (1) en caso de ser un directorio y false (0) en caso contrario, asi solo se sumaran los tamanios en bytes de los ficheros
int printFile(const char *  name, struct stat buff) {
int printFile(const char * path, const char *  name, struct stat buff) {
    int result = 0;

    if(S_ISLNK(buff.st_mode)){ //Si el fichero es un enlace simbolico
      char * b = malloc(buff.st_size + 1);
      readlink(name, b,  buff.st_size);
      readlink(path, b,  buff.st_size);
      printf("%s->%s\n", name,b);
      free(b);
    }
    else if (S_ISDIR(buff.st_mode)){ //Si es un directorio
         printf("%s/\n", name);
         return 1;
         result = 1;
    }
    else if (access(name,X_OK) == 0) printf("%s*\n", name); //Solo necesitamos saber si se puede ejecutar, ya sabemos que existe de antemano
    else if (access(path,X_OK) == 0) printf("%s*\n", name); //Solo necesitamos saber si se puede ejecutar, ya sabemos que existe de antemano
    else printf("%s\n", name); //Si es un fichero regular u otro no especificado
    return 0;

    return result;
}


int main(int argc, char * argv[]) {
	if(argc == 2){
   DIR * directory = opendir(argv[1]);
   struct dirent * content;
   struct stat buff;
   long int byteSize = 0;
   int isDir;

    while((content = readdir(directory)) != NULL) {
       lstat(content->d_name, &buff);
       isDir = printFile(content->d_name,buff);
       char * fullpath = malloc(strlen(argv[1]) + strlen(content->d_name) + 2);
       strcpy(fullpath, argv[1]);
       strcat(fullpath, "/");
       strcat(fullpath, content->d_name);
       lstat(fullpath, &buff);
       isDir = printFile(fullpath,content->d_name,buff);
       free(fullpath);
       //si la funcion devuelve que no es un directorio sumamos el tamano de ese fichero
       if(isDir == 0) byteSize += buff.st_size;       
    }
	printf("Tamanio total en bytes: %li\n", byteSize);
    closedir(directory);
 }
 else {
  perror("Se debe introducir un directorio");
  return -1;
 } 
 return 0;
}