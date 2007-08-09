#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>

#define MAX_BUF_SIZE 1*1024*1024

int main(int argc, char *argv[])
{
	FILE *fdr, *fdw;
	struct stat fst;
	char *from, *to, *buf;
	int size, ret, i, j;
	char *str_0x = "0x", str_col[1] = {','}, *newline = "\n";
	char d2c[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8',
			'9', 'a', 'b', 'c', 'd', 'e', 'f'};
	char name[32] = "static unsigned char irom[ ] = {";
	char end[2] = "};";

	if (argc < 3) {
		printf("%s from-file to-file\n", argv[0]);
		exit(1);
	}

	from = argv[1];
	to = argv[2];

	if ((fdr = fopen(from, "rb")) == NULL) {
		printf("Cannot open file %s (%s)\n", from, strerror(errno));
		exit(1);
	}

	if (stat(from, &fst) == -1) {
		printf("Cannot get fstat %s (%s)\n", from, strerror(errno));
		exit(1);
	}

	size = fst.st_size;

	if (size > MAX_BUF_SIZE) {
		printf("file size is bigger than %d\n", MAX_BUF_SIZE);
		exit(1);
	}

	buf = malloc(MAX_BUF_SIZE);
	if (!buf) {
		printf("No enough memory\n");
		exit(1);
	}
	memset(buf, 0, MAX_BUF_SIZE);

	if ((ret = fread(buf, sizeof(char), size, fdr)) != size) {
		printf("Cannot read %s (%s)\n", from, strerror(errno));
		exit(1);
	}

	fclose(fdr);

	if ((fdw = fopen(to, "w+")) == NULL) {
		printf("Cannot open file %s\n", to);
		exit(1);
	}

	if ((ret = fwrite(name, sizeof(char), 32, fdw)) != 32) {
		printf("Cannot write name to file %s\n", to);
		exit(1);
	}

	if ((ret = fwrite(newline, sizeof(char), 1, fdw)) != 1) {
		printf("Cannot write to file %s\n", to);
		exit(1);
	}

	// convert here
	for (i = 0; i < size; i++) {
		unsigned char val, msb, lsb;

		val = *(unsigned char *)(buf + i);
		msb = (val >> 4) & 0xf;
		lsb = (val) & 0xf;

		if ((ret = fwrite(str_0x, sizeof(char), 2, fdw)) != 2) {
			printf("Cannot write 0x to file %s\n", to);
			exit(1);
		}

		if ((ret = fwrite(&d2c[msb], sizeof(char), 1, fdw)) != 1) {
			printf("Cannot write 0x to file %s\n", to);
			exit(1);
		}

		if ((ret = fwrite(&d2c[lsb], sizeof(char), 1, fdw)) != 1) {
			printf("Cannot write 0x to file %s\n", to);
			exit(1);
		}

		if ((ret = fwrite(str_col, sizeof(char), 1, fdw)) != 1) {
			printf("Cannot write to file %s\n", to);
			exit(1);
		}

		if ((ret = fwrite(newline, sizeof(char), 1, fdw)) != 1) {
			printf("Cannot write to file %s\n", to);
			exit(1);
		}
	}

	if ((ret = fwrite(end, sizeof(char), 2, fdw)) != 2) {
		printf("Cannot write end to file %s\n", to);
		exit(1);
	}

	if ((ret = fwrite(newline, sizeof(char), 1, fdw)) != 1) {
		printf("Cannot write to file %s\n", to);
		exit(1);
	}

	fclose(fdw);

	return 0;
}
