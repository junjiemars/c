#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define _unused_(x) ((void)(x))
#define ROW_SIZE 4
#define COL_SIZE 4

char *
read_file(const char* f) {
	FILE *fp;
	char *buf = 0;
	long flen;
	
	fp = fopen(f, "rb");
	if (0 == fp) goto clean_exit;

	fseek(fp, 0, SEEK_END);
	flen = ftell(fp);
	rewind(fp);

	buf = malloc((flen+1) * sizeof * buf);
	fread(buf, flen, 1, fp);
	if (ferror(fp)) {
		free(buf);
		buf = 0;
	}
	
clean_exit:
	if (fp) fclose(fp);

	return buf;
}

int
main(int argc, const char *argv[]) {
	_unused_(argc);
	_unused_(argv);

	if (argc < 2) {
		printf("pls, specifiy file name\n");
		return 1;	
	}

	char *buf = read_file(argv[1]);
	if (0 == buf) {
		printf("error when read file: %s\n", argv[1]);
		return 1;
	}

	char *prow;
	char *pbuf = buf;
	char *rows[ROW_SIZE][COL_SIZE] = {{0}};
	size_t i = 0;

	while ((prow = strchr(pbuf, '\n')) != 0) {
		char *pcol, *pre = 0;	
		size_t j = 0;

		while (((pcol = strchr(pbuf, ',')) != 0) && (pcol < prow) && (j < COL_SIZE)) {
			rows[i][j] = malloc((pcol-pbuf) * sizeof *rows);
			strncpy(rows[i][j], pbuf, (pcol-pbuf));
			pre = pcol;
			j++;
			pbuf += (pcol-pbuf) + 1;	
		}	
		if ((pre < prow) && (j < COL_SIZE)) {
			rows[i][j] = malloc((prow-pre) * sizeof *rows);
			strncpy(rows[i][j], pbuf, (prow-pre)-1);
			j++;
			pbuf += (prow-pre) + 1;
		}

		i++;
		pbuf += (prow-pbuf) + 1;
	}

	for (size_t m = 0; m < ROW_SIZE; m++) {
		putchar('#');
		for (size_t n = 0; n < COL_SIZE; n++) {
			if (rows[m][n]) {
				printf("%4s,", rows[m][n]);
				free(rows[m][n]);
			}
		}
		putchar('\n');
	}

	//char buff[200];
	//char tokens[10][30];
	//fgets(buff, 200, stdin);
	//char *ptok = buff; // for iterating
	//char *pch; 
	//int i = 0;
	//while ((pch = strchr(ptok, ',')) != NULL) {
	//	*pch = 0; 
	//	strcpy(tokens[i++], ptok);
	//	ptok = pch+1;
	//}
	//strcpy(tokens[i++], ptok);

	free(buf);
}
