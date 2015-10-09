#pragma once

#include <jni.h>

class JavaString {
public:
	JavaString(jstring ref);
	~JavaString();
	int length();
private:
	jstring ref;
};

