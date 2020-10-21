#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main (int argc, char **argv){
	const char *fname[255];
	int ret;
 	struct stat var;
	int counter = 1;
	int prog_count = 0;

	struct dirent *dp;

	DIR *dirp;
	const char *path;

	if (argc == 1){
		path = ".";
  		dirp = opendir(path);
  		if (dirp == NULL){
    			perror("error");
    			return -1;
		}
  		while((dp = readdir(dirp))){
  			puts(dp->d_name);
  			ret = stat(dp->d_name, &var);
			if(ret < 0){
				printf("\nSystem call stat exited with an error code %d", ret);
			}
			else if (var.st_nlink >= 2){
				printf("\nDevice id: %ld ", var.st_dev);
				printf(" Inode number: %ld ", var.st_ino);
				printf(" Hard Link : %ld ", var.st_nlink);
				printf(" Mode: %ld ", var.st_mode);
				printf(" UID: %ld ", var.st_uid);
				printf(" GID: %ld ", var.st_gid);
				printf(" Size: %ld ",var.st_size);
				prog_count++;
			}
				else
					printf("\nNo file with more than 2 hardlinks\n");
		}
		closedir(dirp);

 		while (++counter <= argc) {
    			printf("\nListing %s...\n", argv[counter-1]);
    			path = argv[counter-1];
		}
	}
	printf("\n\nTotal programs with more than 2 hardlinks : %d \n", prog_count);
	return 0;
}

