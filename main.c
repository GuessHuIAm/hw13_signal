#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

static void sighandler(int signo){
	if(signo == SIGINT){
		printf("Program exited due to SIGINT.\n");

		int file = open("exit.txt", O_CREAT | O_APPEND | O_RDWR, 0766);
		char m[] = "Exited due to SIGINT.\n";
		write(file, m, strlen(m));
		close(file);

		exit(0);
	}
	if(signo == SIGUSR1){
		printf("PID of parent process: %d\n", getpid());
	}
}

int main(){
	signal(SIGINT, sighandler);
	signal(SIGUSR1, sighandler);

	while(1){
		printf("PID of process: %d\n", getpid());
		sleep(1);
	}

	return 0;
}
