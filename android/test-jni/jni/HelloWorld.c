#include <jni.h>
#include <string.h>

/*
 * Class:     com_example_hello1_MainActivity
 * Method:    helloWorldFromJNI
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_example_hello1_MainActivity_helloWorldFromJNI(JNIEnv *env, jobject thiz)
{
	 return (*env)->NewStringUTF(env, "HelloWorld! I am from JNI too!");
}

