#pragma once

#include <jni.h>
#include "JNIKit.h"
#include <string>

class JNIKit;

using namespace std;

class JavaString {
public:
	JavaString(JNIKit *kit, jstring ref);
	~JavaString();
	int length();
	jstring jniRef();
	string unwrap();
private:
	JNIKit *kit;
	jstring ref;
};

