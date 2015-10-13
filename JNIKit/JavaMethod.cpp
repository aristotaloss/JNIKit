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

jobject JavaMethod::invoke(int x, ...) {
	va_list varargs;
	va_start(varargs, x);
	if (staticMethod) {
		return env->CallStaticObjectMethodV(definedIn, ref, varargs);
	} else {
		//env->CallVoidMethodV();
	}
	va_end(varargs);
	return nullptr;
}
