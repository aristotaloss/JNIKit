#include "JavaField.h"


JavaField::JavaField(JNIEnv *env, jclass defined, jfieldID field, bool staticField) {
	this->env = env;
	this->ref = field;
	this->defined = defined;
	this->staticField = staticField;
}

JavaField::~JavaField() {
}

bool JavaField::set(jobject value) {
	if (staticField) {
		env->SetStaticObjectField(defined, ref, value);
		return true;
	}

	return false;
}

bool JavaField::set(jobject instance, jobject value) {
	if (!staticField) {
		env->SetObjectField(instance, ref, value);
		return true;
	}

	return false;
}
