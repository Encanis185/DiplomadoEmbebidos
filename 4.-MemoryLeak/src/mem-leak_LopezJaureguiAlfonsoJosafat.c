#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

void main(){
	/* Original code

	char *path = NULL; //char pointer(path) points to nothing

	while(1) {
		path=malloc(100); Receives a int value instead of a pointer. Malloc allocates size bytes and returns a pointer
       	   	   	   	   	   	to the allocated memory.  The memory is not initialized.
							-Path has been allocated 100 bytes. The 100 bytes might contain garbage data
							-A good practice is use memset or calloc, so every byte is initialized
							char ∗p = malloc (10);
							memset(p,â€™\0â€™,10);

	    path = strdup("STRING"); The strdup() function returns a pointer to a new string which is
       	   	   	   	   	   	   	   a duplicate of the string s.  Memory for the new string is
       	   	   	   	   	   	   	   obtained with malloc(3), and can be freed with free(3)

		path=NULL; path is then reassigned to NULL, and we lose both references

	*/

	//Modifications

	char *path;
	int len = 100;

	while(1){
		path = (char*)malloc(len*sizeof(char));

		printf("First allocation: ");
		if(path != NULL){
			printf("%ld bytes on Memory Address: %p\n", (len*sizeof(char)), path);
			//Didn´t find a way to obtain size of the dynamic allocated memory given by malloc()
		} else{
			printf("Something wrong happened, could not assign memory\n");
			perror("malloc()");
			exit(EXIT_FAILURE);
		}

		printf("Deallocating memory...\n");
		free(path);
		//free(path); Double free = error

		printf("New allocation: ");
		path=strdup("STRING");
		if (path!=NULL){
			printf("%ld bytes on Memory Address: %p\n", (sizeof("STRING")), path);
		} else{
			printf("Something wrong happened, could not assign memory\n");
			perror("strdup()");
			exit(EXIT_FAILURE);
		}
		printf("Deallocating memory...\n");
		free(path);

		printf("\n");
		sleep(3);
	}

	if(path!=NULL){
		free(path);
	}

	return;

}
