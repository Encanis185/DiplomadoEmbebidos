/*
 * LopezJaureguiAlfonsoJosafat_FileStats.c
 *
 *  Created on: Mar 2, 2023
 *      Author: encanis185
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdlib.h>
#include <pwd.h>
#include <unistd.h>
#include <errno.h>


void getFileType(char *file){
	struct stat buffer;
	if(stat(file, &buffer) == 0){
		if(S_ISDIR(buffer.st_mode)){ printf("Directory\n"); return;}
		if(S_ISCHR(buffer.st_mode)){ printf("Character special device\n"); return;}
		if(S_ISBLK(buffer.st_mode)){ printf("Block special file\n"); return;}
		if(S_ISREG(buffer.st_mode)){ printf("Regular file\n"); return;}
		if(S_ISFIFO(buffer.st_mode)){ printf("FIFO file\n"); return;}
		if(S_ISLNK(buffer.st_mode)){ printf("Symbolic link\n"); return;}
		if(S_ISSOCK(buffer.st_mode)){ printf("Socket\n"); return;}
		else printf("Unknown...?");
	}

	return;
}

void getPermissions(char *file){
    struct stat buffer;
    char *modeval = malloc(sizeof(char) * 9 + 1);
    if(stat(file, &buffer) == 0){
        mode_t perm = buffer.st_mode;   //https://man7.org/linux/man-pages/man2/stat.2.html
        modeval[0] = (perm & S_IRUSR) ? 'r' : '-'; //Owner read permission
        modeval[1] = (perm & S_IWUSR) ? 'w' : '-'; //Owner write permission
        modeval[2] = (perm & S_IXUSR) ? 'x' : '-'; //Owner exec permission
        modeval[3] = (perm & S_IRGRP) ? 'r' : '-'; //Group read permission
        modeval[4] = (perm & S_IWGRP) ? 'w' : '-'; //Group write permission
        modeval[5] = (perm & S_IXGRP) ? 'x' : '-'; //Group exec permission
        modeval[6] = (perm & S_IROTH) ? 'r' : '-'; //Others read permission
        modeval[7] = (perm & S_IWOTH) ? 'w' : '-'; //Others write permission
        modeval[8] = (perm & S_IXOTH) ? 'x' : '-'; //Others exec permission
        modeval[9] = '\0';
        puts(modeval);
    }
    else{
        return;
    }
}

int main(int argc, char *argv[]){
	char* filename;
	struct stat buffer;
	register struct passwd *pw;
	uid_t uid;


	pw = getpwuid(uid = getuid());
    //Get time

	//struct tm* clock;

	//Character count
	FILE *fptr;
	char ch;
    int count=0;


	if(!argc || argc < 2){
		printf("Filename is required!\n");
	}
	else{
		filename = argv[1];
		int response = stat(filename, &buffer);
		//clock = gmtime(&(buffer.st_mtime));
		fptr = fopen(filename,"r");
		if (lstat(argv[1], &buffer) == -1) {
			perror("lstat");
			exit(EXIT_FAILURE);
		}
		else{
			printf("---File description---\n");
			printf("File type: ");
			getFileType(filename);
			printf("File permissions: ");
			getPermissions(filename);
			printf("File size(Bytes): %ld\n", buffer.st_size);
			printf("File owner: %s UID(%ld), GID(%ld)\n",pw->pw_name, (long)buffer.st_uid, (long) buffer.st_gid);
			printf("Creation date: %s", ctime(&buffer.st_ctime));
			if(fptr==NULL){
				printf("Can't count characters ¿Are you sure it is a text file?\n");
			}else{
				for(ch = getc(fptr); ch != EOF; ch = getc(fptr)){
					count = count + 1;
				}

				printf("Character count: %d\n", count);
			}
			if(buffer.st_ino){
				printf("File INODE: %lu\n", buffer.st_ino);
			}
			else{
				printf("Can't print File INODE");
			}


		}

	}

	fclose(fptr);

	return 0;
}
