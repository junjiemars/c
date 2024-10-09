#include <Java2c.h>
#include <_ffi_.h>
#include <stdio.h>

JNIEXPORT jint JNICALL
Java_Java2c_square (__attribute__ ((unused)) JNIEnv *env,
                    __attribute__ ((unused)) jobject obj, jint n)
{
  printf ("Oh, Gandalf\n");
  int v = n * n;
  return (v);
}
