#include<stdio.h>
#include<sys/utsname.h>
#include<string.h>

int main(int argc, char **argv) {


        struct utsname buf;

        printf("Nombre del SO:%s\n",buf.sysname);
        printf("Nombre del host:%s\n",buf.nodename);
        printf("Release del SO:%s\n",buf.release);
        printf("Version del SO:%s\n",buf.version);
        printf("Hardware:%s\n",buf.machine);
        printf("Nombre de dominio:%s\n",buf.__domainname);

        return 0;
}
