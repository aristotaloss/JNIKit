#pragma once

#include <jni.h>
#include <vector>
#include <string>

#include "JavaClass.h"
#include "JavaField.h"
#include "JavaString.h"
#include "JNIError.h"

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
	JavaField *getStaticField(JavaClass *declaredIn, string fieldName, string desc);
	JavaField *getStaticField(string declaredIn, string fieldName, string desc);
	JavaVM *getVm();
	bool detach();

	JavaString *createString(string str);

	static vector<JavaVM*> listJvms();
	static JNIKit attach(JavaVM *vm);
	static JNIKit attachAny();
private:
	JNIEnv *env;

};