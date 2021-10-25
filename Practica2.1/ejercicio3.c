#include<stdio.h>
#include<errno.h>
#include<string.h>


int main() {

	errno = 1;

	for(errno; errno < 256; errno++) {
		perror("Error");
		//char *strerror(int errnum = error);
	}
	
	return 0;
}
