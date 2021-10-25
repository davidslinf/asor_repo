#include<stdio.h>
#include<errno.h>
#include<string.h>
#include <sys/types.h>
#include <unistd.h>

int setuid(uid_t uid);

int main() {
setuid(0);
 
 	if(errno != 0) {
		perror("Se produjo un error");
		char *strerror(int errnum);

 		return -1;
 	}  
	
	return 0;
}



