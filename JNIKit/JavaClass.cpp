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
	
	return jobject();
}
