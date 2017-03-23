#include <nm_auto_headers.h>
#include <square.h>
#include <stdio.h>

#define _unused_(x) ((void)(x))

JNIEXPORT jint JNICALL Java_Java2c_square
  (JNIEnv *env, jobject obj, jint n) {

		_unused_(env);
		_unused_(obj);

      printf("Oh, Gandalf\n");
      int v = n * n;
      return (v);
  }

