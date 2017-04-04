#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define _unused_(x) ((void)(x))

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

	buf = (char *)malloc((flen+1) * sizeof(char));
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
