#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
    pid_t pid;

    pid = fork();

    if (pid < 0 ) {
        fprintf(stderr, "Fork Failed");
        exit(-1);
    }
    else if( pid == 0) {
        execlp("/bin/ls","ls",NULL);
        printf("Hello"); ##Hello will never be executed since the exec call completely overides the program and calls ls 
#and nothing is returned by the exec call unless the exec results in an error 
    }
    else{
        wait(NULL);
        printf("Child Complete");
        exit(0);
    }
}

