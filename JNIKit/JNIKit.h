#pragma once

#include <jni.h>
#include <vector>
#include <string>

#include "JavaClass.h"
#include "JavaField.h"
#include "JavaString.h"
#include "JNIError.h"
#include <fstream>

#pragma comment(lib, "jvm.lib")

using namespace std;

// Fwd decl.
class JavaClass;
class JavaField;
class JavaString;

class JNIKit {

public:
	JNIKit(JNIEnv *env);
	~JNIKit();
	JavaClass *getClass(string name);
	JavaField *getField(JavaClass *declaredIn, string fieldName, string desc);
	JavaField *getField(string declaredIn, string fieldName, string desc);
	JavaMethod *getMethod(JavaClass *declaredIn, string methodName, string desc);
	JavaMethod *getMethod(string declaredIn, string methodName, string desc);
	JavaVM *getVm();
	bool detach();

	JavaString *createString(string str);
	JavaClass *defineClass(string name, string filename, jobject classLoader = nullptr);
	JavaClass *defineClass(string name, vector<char> &data, jobject classLoader = nullptr);

	static vector<JavaVM*> listJvms();
	static JNIKit attach(JavaVM *vm);
	static JNIKit attachAny();
private:
	JNIEnv *env;

};