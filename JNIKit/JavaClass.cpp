#include "JavaClass.h"

JavaClass::JavaClass(JNIEnv *env, jclass ref) {
	this->env = env;
	this->ref = ref;
}

JavaClass::~JavaClass() {

}

jclass JavaClass::jniRef() {
	return ref;
}

jobject JavaClass::constructNew() {
	jmethodID constructor = env->GetMethodID(ref, "<init>", "()V");
	return env->NewObject(ref, getMethod("<init>")->jniRef());
}

JavaMethod *JavaClass::getMethod(string name, string desc) {
	jmethodID method = env->GetMethodID(ref, name.c_str(), desc.c_str());

	// Return a nullpointer if the resolving failed.
	if (!method)
		return nullptr;

	return new JavaMethod(env, method, ref, false);
}


JavaMethod *JavaClass::getStaticMethod(string name, string desc) {
	jmethodID method = env->GetStaticMethodID(ref, name.c_str(), desc.c_str());

	// Return a nullpointer if the resolving failed.
	if (!method)
		return nullptr;

	return new JavaMethod(env, method, ref, true);
}