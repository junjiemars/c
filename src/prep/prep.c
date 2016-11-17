#include <stdio.h>
#include <math.h> //NAN

#define setup_list(name, ...)                             \
	double *name ## _list = (double []){__VA_ARGS__, NAN};  \
	int name ## _len = 0;                                   \
	for (name ## _len =0;                                   \
	        !isnan(name ## _list[name ## _len]);            \
	        ) name ## _len ++;


int main(){
	setup_list(item, 1, 2, 4, 8);
	double sum=0;
	for (double *ptr= item_list; !isnan(*ptr); ptr++)
	    sum += *ptr;
	printf("sum=%g, length<|nan=%i of item_list\n", sum, item_len);
	
	double sum1=0;
	setup_list(another, -1, 2.2, 4.8, 0.1);
	for (int i=0; i < another_len; i++)
	    sum1 += another_list[i];
	printf("sum=%g, length<|nan=%i of another_list\n", sum1, another_len);
}
