#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

void daemonize(){
	/*The working of a daemon is not too hard to understand but i had to do quite a bit of research
	to get the full details.
	Essentially, when our linux system boots up, there is a process usually called the init system
	which is the first to run. One of its core job is to begin the background daemon.
*/

	//In order to get this working, we will have to ffork child process

	/*The ini system that calls the program is actually our parent process, and therefore, we
	have to initiate 2 forks() to ensure that the ini system doesn't terminate prematurely. Now the
	working of the ini system is that when we createa  child process and kill the parent process,
	the init system is unaffected and it keeps running in th ebackground
*/


//create child process
	pid_t process1;

	process1 = fork();

	if(process1 == -1)
	{
		//fork failed
		exit(EXIT_FAILURE);
	}

	//0 is returned to the  child process and the process ID of the child is returned to hte parent
	if(process1 > 0){
		//since process ID of child is returned to parent we kill parent
		exit(EXIT_SUCCESS);
	}

	//child will be running, create a new session
}


int main(int argc, char ** argv){

	//stuff goes here
}
