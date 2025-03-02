#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>		//pid types
#include <sys/wait.h>		//wait function
#include <unistd.h>
#include <signal.h> 		//signal processing

/*CREATE CHILD
 * PRINT PID
 * PAUSE()
 * ON RETURN FROM PAUSE, EXIT CODE 5
 * PARENT WAIT FOR CHILD
 * WHEN DONE WAITING, PRINT CHILDPID=%D, EXITSTATUS=%D
 * DO NOT PRINT ANYTHING ELSE
 * CHILD HANDLES SIGINT KILL PROCESS
 */
 
void sigHandler(){};

int main() {
	
	//INSTANTIATE PID
	pid_t pid;
	
	//SET PID AND FORK
	pid = fork();
	
	//CHECK IF FORKED USING PID
	if(pid < 0) {
		perror("FORK FAILURE\n");
		exit(EXIT_FAILURE);
	}
	
	//CHILD PROCESS
	if(pid == 0) {															//CHECK IF THE CHILD OR PARENT
		signal(SIGINT, sigHandler);											//SIGNAL HANDLER INSTANTIATE
		pid = getpid();														//GET CALLER PID
		printf("%d\n", pid);	
		pause();															//WAIT FOR USER TO KILL CHILD
		exit(5);															//EXIT CODE 5
	}
	//PARENT PROCESS
	else {
		int status;															//STATUS OF CHILD
		signal(SIGINT, SIG_IGN);											//IGNORE ALL SIGNALS EXCEPT KILL
		waitpid(pid, &status, 0);											//WAIT FOR CHILD PID, STATUS OF CHILD, WAIT FOR CHILD TERMINATION
		printf("\nchildpid=%d,exitstatus=%d\n", pid, WEXITSTATUS(status));		//ON CHILD KILL, PRINT
	}
	
	return 0;
}
