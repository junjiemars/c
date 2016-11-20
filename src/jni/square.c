#include <nm_auto_headers.h>
#include <square.h>
#include <stdio.h>

#if (MSYS_NT)

	#if (CC_MSVC)
		#define W_C4100(x) { (x); }
	#endif 
#endif


JNIEXPORT jint JNICALL Java_Java2c_square
  (JNIEnv *env, jobject obj, jint n) {
			W_C4100(env)
			W_C4100(obj)

      printf("Oh, Gandalf\n");
      int v = n * n;
      return (v);
  }

