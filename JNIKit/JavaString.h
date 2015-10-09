#pragma once

#include <jni.h>

class JavaString {
public:
	JavaString(jstring ref);
	~JavaString();
	int length();
	jstring jniRef();
private:
	jstring ref;
};

