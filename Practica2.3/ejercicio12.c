#include <stdio.h>
#include <string.h>
#include <signal.h>

volatile static int numSigint = 0;
volatile static int numSigtstp = 0;

void manejador(int signal) {

        if(signal == SIGINT) numSigint++;
        else if(signal == SIGTSTP) numSigtstp++;

        return;
}

int main(int argc, char** argv) {

        struct sigaction act;
        act.sa_handler = manejador;

        sigemptyset(&act.sa_mask);
        sigaddset(&act.sa_mask, SIGINT);
        sigaddset(&act.sa_mask, SIGTSTP);
        act.sa_flags = SA_RESTART;

        sigaction(SIGINT, &act, NULL);
        sigaction(SIGTSTP, &act, NULL);

        sigset_t set;
        sigemptyset(&set);

        while(numSigint + numSigtstp < 10) {
                sigsuspend(&set);
        }
		printf("Se han recibido %i señales de tipo SIGINT\n", numSigint);
		printf("Se han recibido %i señales de tipo SITSTP\n", numSigtstp);

        return 0;
}
