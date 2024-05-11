//I will be modifying the below code to be more advanced
//that is i will be making it a system monitoring
//Daemon. The main purpose will be to continously
//monitor resources within the system such as CPU,
//memory, disk usage and network activity. I will also
//implemnt reak-time notificcations and logging
//helping those using the program to identify performace
//issue

//there is a library called libnotify
//will check what the library is

//Implementing a daemon to keep track of time passed


/*From what i have read within the example, a daemon
should actually be its own process and so in that
case we are going to create a child process that will
run the background
*/
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#ifndef ERROR
    #define ERROR -1
#endif
int init(void){
    pid_t childProcess,sessionID; //Hold child PID
    int8_t errorNumber;
    typedef char* string;
    string path = "/tmp/timeDaemon.txt";
    time_t t;

    childProcess = fork(); //creates a new process for
    //child


    //Using the docs, if fork() returns a negative value
    //the creation of a child process was unsuccessful
    if(childProcess < 0){
        errorNumber = errno;
        fprintf(stderr,"Error: %s\n",strerror(errorNumber));
        exit(ERROR);
    }

    //fork returns a 0 to the newly created child process
    //now what if we get something greater than 0,
    //then that is not what we want
    if(childProcess > 0){
        errorNumber = errno;
        fprintf(stderr,"Error: %s\n",strerror(errorNumber));
        exit(ERROR);
    }

    //create a process for the child process, since
    //the parent process has been terminated

    sessionID = setsid();
    if(sessionID < 0){
        errorNumber = errno;
        fprintf(stderr,"Error: %s\n",strerror(errorNumber));
        exit(ERROR);
    }

    //according to my research, it is good practice to
    //let the daemon run as root
    chdir("/");

    //next, we have to close the standard file descriptors for reuse
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    //what we will now do here is actually implement the daemon functionality
    for(int i=0; i<10; i++){
        //remember we ant to write the time and Date every 5 seconds to the file
        FILE *file = fopen(path,"a");
        if(file == NULL){
            errorNumber = errno;
            fprintf(stderr,"Error: %s\n",strerror(errorNumber));
            exit(ERROR);
        }
        //get the time and Date
        time(&t);
        fprintf(file,"Current Time and Date: %s", ctime(&t));
        //close the file
        fclose(file);
        sleep(2);
    }


}

int main(void){
    init();
}