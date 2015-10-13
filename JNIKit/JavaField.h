#pragma once

#include <jni.h>

class JavaField {

public:
	JavaField(JNIEnv *env, jclass defined, jfieldID field, bool staticField);
	~JavaField();
	bool set(jobject value);
	bool set(jobject instance, jobject value);
	jobject get();
	jobject get(jobject instance);
	bool isStatic();

private:
	JNIEnv *env;
	jfieldID ref;
	jclass defined;
	bool staticField;

};