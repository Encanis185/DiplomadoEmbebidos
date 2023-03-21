/*
 * sleep.c
 *
 *  Created on: Mar 19, 2023
 *      Author: encanis185
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>


int isNumber(char number[]){

    for (int i = 0; number[i] != 0; i++)
    {
        //if (number[i] > '9' || number[i] < '0')
        if (!isdigit(number[i]))
            return 0;
    }
    return 1;
}

int main(int argc,char *argv[]) {
	int seconds2sleep = 0;

	//int length = strlen(argv[1]);


        /* if (!isdigit(argv[1])){
            printf ("Entered input is not a number\n");
            exit(1);
        }
*/

	//seconds2sleep = atoi(argv[1]);

	if(isNumber(argv[1]) == 1){
		seconds2sleep = atoi(argv[1]);
		sleep(seconds2sleep);
		printf("We're back!\n");
	}
	else{
		printf("Argument is not a number\n");
	}


	return 0;


}



