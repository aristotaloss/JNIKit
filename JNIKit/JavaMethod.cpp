#include "JavaMethod.h"


JavaMethod::JavaMethod(JNIEnv *env, jmethodID ref, jclass definedIn, bool staticMethod) {
	this->env = env;
	this->ref = ref;
	this->definedIn = definedIn;
	this->staticMethod = staticMethod;
}

JavaMethod::~JavaMethod() {
}


jmethodID JavaMethod::jniRef() {
	return ref;
}

jobject JavaMethod::invoke(...) {
	va_list varargs;
	va_start(varargs, this);
	if (staticMethod) {
		env->CallStaticVoidMethodV(definedIn, ref, varargs);
	} else {
		//env->CallVoidMethodV();
	}
	va_end(varargs);
	return nullptr;
}
