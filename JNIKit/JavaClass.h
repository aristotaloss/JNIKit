#pragma once

#include <jni.h>

class JavaClass {

public:
	JavaClass(JNIEnv *env, jclass ref);
	~JavaClass();
	jclass jniRef();
	jobject constructNew();

private:
	JNIEnv *env;
	jclass ref;

};