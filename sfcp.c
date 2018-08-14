#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/sendfile.h>

int main(int argc, char *argv[])
{
	if (argc == 2 && (!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help"))) {
		puts("Usage: sfcp <source> <dest>");
		return EXIT_SUCCESS;
	}
	if (argc != 3) {
		return EXIT_FAILURE;
	}
	int src = open(argv[1], O_RDONLY);
	if (src == -1) {
		fprintf(stderr, "Error opening for reading: %s\n", argv[1]);
		return EXIT_FAILURE;
	}

	struct stat src_st;
	if (fstat(src, &src_st) == -1) {
		close(src);
		fprintf(stderr, "Could not stat: %s\n", argv[1]);
		return EXIT_FAILURE;
	}

	int dest = creat(argv[2], src_st.st_mode & 0777);
	if (dest == -1) {
		close(src);
		fprintf(stderr, "Error opening for writing: %s\n", argv[2]);
		return EXIT_FAILURE;
	}

	off_t bytes_left = src_st.st_size;
	off_t offset = 0;
	while (bytes_left > 0) {
		ssize_t res = sendfile(dest, src, &offset, bytes_left);
		if (res == -1) {
			close(dest);
			close(src);
			fprintf(stderr, "Error copying file\n");
			return EXIT_FAILURE;
		}
		bytes_left -= res;
	}

	if (close(dest) == -1) {
		close(src);
		fprintf(stderr, "Error closing: %s\n", argv[2]);
		return EXIT_FAILURE;
	}
	if (close(src) == -1) {
		fprintf(stderr, "Error closing: %s\n", argv[1]);
	}

	return EXIT_SUCCESS;
}
