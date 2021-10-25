#include<iostream>
#include <sys/types.h>
#include <unistd.h>


using namespace std;


int main(int argc, char **argv) {

        int result = setuid(0);

        if(result == -1) {

                cout << "No se ha podido establecer el id.";
                return -1;
        }

        else
        cout << "Nuevo id establecido.";

        return 0;
}
