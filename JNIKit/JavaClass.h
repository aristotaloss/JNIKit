#pragma once

#include <jni.h>
#include "JavaMethod.h"
#include <string>

using namespace std;

class JavaClass {

public:
	JavaClass(JNIEnv *env, jclass ref);
	~JavaClass();
	jclass jniRef();
	jobject constructNew();
	JavaMethod *getMethod(string name, string desc = "()V");
	JavaMethod *getStaticMethod(string name, string desc = "()V");

private:
	JNIEnv *env;
	jclass ref;

};