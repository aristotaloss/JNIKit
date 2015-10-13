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

jobject JavaMethod::invoke(jobject instance, ...) {
	va_list varargs;
	va_start(varargs, instance);

	if (staticMethod) {
		return env->CallStaticObjectMethodV(definedIn, ref, varargs);
	} else {
		return env->CallObjectMethodV(instance, ref, varargs);
	}
}

bool JavaMethod::isStatic() {
	return staticMethod;
}
