#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "tarc.h"

// TODO: handle errors
// Get blocks size right
// Check other device files - extend test cases
// write up
// make a helpers file
int main(int argc, char *argv[])
{
	if (argc < 3) {
		printf("please provide a directory name and target files\n");
		return 1;
	}

	int file_count = argc - 2;
	char **files = &argv[2];

	char *archive_name = argv[1];

	int archive = open(archive_name, O_RDWR | O_CREAT, 0644);
	if (archive == -1) {
		perror(archive_name);
		return 2;
	}

	for (int i = 0; i < file_count; i++) {
		if (tar_it(archive, files[i]) == 0) {
			printf("cannot tar file\n");
			break;
		}
	} 

	pad_file(archive);
	close(archive);
	return 0;
}