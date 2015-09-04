#include <stdio.h>

void loop() {
  int a[] = {0, 1, 2, 3, 4, 5};
  int i = 0;

begin:
  if (a[i] >= 3) {
      printf("#%d ", i);
      goto end;
  }
  i = i+1;
  goto begin;
end:
  printf("label:end ended");
}

int main(int argc, char *argv[]) {
  printf("Hi\n");
  loop();
}
