#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>


/*
int spawn(char* program, char** arg_list){
	pid_t child_pid;
	//int child_pid;

	child_pid = fork();
	if (child_pid == 0)  //Fork returns 0 to the child, as the child is, supposed, created with no problem
						//this return wont happend. Run a test changing validations and print values and statements
		return child_pid;

	if (child_pid < 0) {
		printf("fork failed\n\n");
	    return 1;
	}
	else if(child_pid==0){
	    printf("child process successfully created!\n");   //This two sentences are printed and we see the child and parent pid
		printf("child_PID = %d,parent_PID = %d\n\n",getpid(), getppid());
	}
	else {
		//wait(NULL);
		//printf("parent process successfully created!\n");
		//printf("child_PID = %d, parent_PID = %d\n\n", getpid(), getppid());
		execvp(program, arg_list);
		printf("returning from execvp");
		abort();
	}
}

*/

void process_creation(int arg_v){
	int child;
	int status=0;
	int pid;
	int ppid;


	child = fork();

	if(child == -1){
		fprintf(stderr, "Fork() did not work as expected.\n");
		exit(EXIT_FAILURE);
	}
	else if(child == 0){ //All this is part of the child created by fork
		printf("This is child process\n");
		pid = getpid();
		ppid = getppid();
		printf("Child PID: %d, Parent PID: %d\n", pid, ppid);

		switch(arg_v){
			case 1:  //Date
				char* arg_list[] = {"date", NULL};
				execvp("date",arg_list);
				break;

			case 2: //Whoami
				char* arg_list2[] = {"whoami", NULL};
				execvp("whoami",arg_list);
				break;
			case 3: //Time
				char* arg_list3[] = {"uptime", "-p", NULL};
				execvp("uptime",arg_list);
				break;
			case 4:
				char* arg_list4[] = {"/home/encanis185/LinuxEmbebido/4.-MemoryLeak/src/leak.o", NULL};
				execv("/home/encanis185/LinuxEmbebido/4.-MemoryLeak/src/leak.o",arg_list);
				break;

			default:
				printf("Something wrong happend. process_creation()\n");
				exit(EXIT_FAILURE);

		}
	}
	else if(child > 0){ //Returning to parent process
	    waitpid(child, &status, WUNTRACED|WCONTINUED);
	    printf("This is parent process\n");
	    pid = getpid();
	    ppid = getppid();
	    printf("Child PID: %d, Parent PID: %d\n", pid, ppid);

	}

	return;
}

int check_args(char* arg_v){
	printf("Validating provided arg...\n");

	if (strcmp(arg_v, "fecha") == 0){
		return 1;
	}
	else if(strcmp(arg_v, "quiensoy") == 0){
		return 2;
	}
	else if(strcmp(arg_v, "tiempo") == 0){
		return 3;
	}
	else if(strcmp(arg_v, "personal") == 0){
		return 4;
	}
	else{
		printf("No valid argument was provided\n");
		return 0;
	}

}


int main (int argc, char *argv[]){
	//char* command = "ls";
	char* arg;
	int command = 0;

	if(!argc || argc > 2){
		printf("Error in provided arguments\n");
		exit(1);
	}
	else{
		arg = argv[1];
	}

	pid_t pid;
	pid = getpid();
	printf("Process ID before fork(): %d\n", pid);

	/*
	char* arg_list[] = {"ls",
			"-l",
			"/",
			NULL
	};
	*/
	command = check_args(arg);
	if(command==0){
		exit(1);
	}
	else{
		printf("Using Fork()\n");
		process_creation(command);
		//pid = fork();
	}


	//spawn("ls", arg_list);
	//printf("done with main program\n\n");
	return 0;
}
