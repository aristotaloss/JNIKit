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

jobject JavaField::get(jobject instance) {
	if (staticField) {
		return env->GetStaticObjectField(defined, ref);
	} else {
		return env->GetObjectField(instance, ref);
	}
}

jobject JavaField::get() {
	return get(nullptr);
}

bool JavaField::isStatic() {
	return staticField;
}
