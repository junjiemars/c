#include <env.h>

#include <stdlib.h>
#include <stdio.h>

int main(){
	char *c = getenv("COUNT");
	int count = c ? atoi(c) : 3;

	char *text = getenv("TEXT");
	if (!text)text = "Hello.";

	for (int i=0; i< count; i++)
		printf("%s\n", text);
}
