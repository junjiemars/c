#include <_ffi_.h>
#include <Java2c.h>
#include <stdio.h>


JNIEXPORT jint JNICALL 
Java_Java2c_square(JNIEnv *env, jobject obj, jint n)
{
	_unused_(env);
	_unused_(obj);

	printf("Oh, Gandalf\n");
	int v = n * n;
	return (v);
}

