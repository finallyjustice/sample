#include "jni.h"
#include <stdio.h>
#include "HelloWorld.h"

JNIEXPORT void JNICALL
Java_HelloWorld_print(JNIEnv *env, jobject obj, jstring jname, jint id)
{
	const jbyte *name = (const jbyte *)env->GetStringUTFChars(jname, JNI_FALSE);
	printf("Helllo: %s, %d\n", name, id);
	env->ReleaseStringUTFChars(jname, (const char *)name);
}
