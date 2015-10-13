#pragma once

#include <jni.h>
#include <varargs.h>

class JavaMethod {
public:
	JavaMethod(JNIEnv *env, jmethodID ref, jclass definedIn, bool staticMethod);
	~JavaMethod();
	jmethodID jniRef();
	jobject invoke(jobject instance, ...);
	bool isStatic();
private:
	JNIEnv *env;
	jclass definedIn;
	jmethodID ref;
	bool staticMethod;
};

