/*
 ============================================================================
 Name        : BusyBox.c
 Author      : encanis185
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>				//Errors
#include <linux/unistd.h>       /* for _syscallX macros/related stuff */
#include <linux/kernel.h>       /* for struct sysinfo */
#include <sys/sysinfo.h>		/*Uptime*/
#include <fcntl.h> 				//header file for file operations

//SLEEP
int isNumber(char number[]){

    for (int i = 0; number[i] != 0; i++) //Check if all the character in the array are digit
    {
        //if (number[i] > '9' || number[i] < '0')
        if (!isdigit(number[i]))
            return 0; //If one not digit char is found then return 0 / False
    }
    return 1; //There was just digits, so return true
}

void toSleep(char *argv){
	int seconds2sleep = 0;


	if(isNumber(argv) == 1){
		seconds2sleep = atoi(argv); //Cast the array to a int
		sleep(seconds2sleep);
		printf("We're back after %d seconds!\n", seconds2sleep);
	}
	else{
		printf("Argument is not a number\n");
	}

	return;
}

//END OF SLEEP

//MKDIR

int makedir(char* argv){
	char* path = argv;
	int status = 0;
	errno = 0;
	/* Create with read/write/search permissions for owner and group, and with read/search permissions for others.*/
	status = mkdir(path , S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    if (status == -1) {
        switch (errno) {
            case EACCES :
                printf("ERROR. The parent directory does not allow write\n");
                exit(EXIT_FAILURE);
            case EEXIST:
                printf("ERROR. Pathname already exists\n");
                exit(EXIT_FAILURE);
            case ENAMETOOLONG:
                printf("ERROR. Pathname is too long\n");
                exit(EXIT_FAILURE);
            default:
                perror("ERROR. mkdir\n");
                exit(EXIT_FAILURE);
        }
    }

    exit(EXIT_SUCCESS);

}

//END OF MKDIR

//UPTIME
struct t_time{
		int dd;
        int hh;
        int mm;
        int ss;
    };

static void converte(long segs, struct t_time *h)
{
    h->dd = (segs / 86400) % 24;
	h->hh = (segs / 3600) % 60;
    h->mm = (segs / 60) % 60;
    h->ss = segs % 60;
}

void getuptime(){
	struct sysinfo s_info; //This struct contains the up time as long int
	struct t_time tempo; //to manage the time info
	int status = sysinfo(&s_info);

	if(status != 0){
	        printf("code error = %d\n", status);
	    }
	else{
		converte(s_info.uptime, &tempo);
		printf("DD:HH:MM:SS == %d:%d:%d:%d\n", tempo.dd, tempo.hh, tempo.mm, tempo.ss);
	}

	return;
}

//END OF UPTIME

//CAT

void getcat(char* arg){
	FILE *fp;
	int file,count;
	char buffer[4096]; //characer buffer to store the bytes
	file = open(arg, O_RDONLY); //delete?
	fp = fopen(arg,"r");
	int c;

	if(fp == NULL) {
		perror("Error in opening file");
	    exit(EXIT_FAILURE);
	}
	do{
	    c = fgetc(fp);
	    if(feof(fp)){
	        break;
	    }
	    printf("%c", c);
	}while(1);

	/*
	if(file==-1){
		printf("ERROR. Cannot open file\n");
		exit(1);
	}
	while((count=read(file, buffer, sizeof(buffer)))>0){ //displaying the content
		printf("%s",buffer);
	}
	*/
	exit(EXIT_SUCCESS);
}

int main(int argc,char *argv[],char **envp) {
	/* This program will use symlinks to this bin,
	when a symlinks its called "./[symlinkName]" the program receives as argv[0]
	the name of that symlink
	Then we will check if that argv is a valid one for our bin
	If so: We run one of the functions
	If not: Return error
	*/

	char* command = argv[0];
	char* argument;

	//printf("%s\n", command);
	//printf("%s\n", argument);

	if(!argc || argc > 2){
			printf("Error in provided arguments\n");
			exit(1);
		}

	if(strcmp(command, "./sleep") == 0){ //Validate the given command.
		argument = argv[1];
		toSleep(argument);
		}
	else if(strcmp(command, "./mkdir") == 0){ //Validate the given command.
		argument = argv[1];
		makedir(argument);
		}
	else if(strcmp(command, "./uptime") == 0){ //Validate the given command.
		if(argc > 1){
			fprintf(stderr, "Error. Too many arguments.\n");
	        exit(EXIT_FAILURE);
		}
		else
			getuptime();
		}
	else if(strcmp(command, "./cat") == 0){ //Validate the given command.
		argument = argv[1];
		getcat(argument);
		}
	else{
		printf("Error. No valid argument was provided.\n");
		exit(EXIT_FAILURE);
	}



	/*
	printf( "\nCommand-line arguments:\n" );
	    for( int count = 0; count < argc; count++ )
	        printf( "  argv[%d]   %s\n", count, argv[count] );
	*/
	return 0;
}
