#include "JNIKit.h"


JNIKit::JNIKit(JNIEnv *env) {
	this->env = env;
}


JNIKit::~JNIKit() {
}


JavaClass *JNIKit::getClass(string name) {
	jclass resolved = env->FindClass(name.c_str());

	if (!resolved)
		return nullptr;

	return new JavaClass(env, resolved);
}

JavaField *JNIKit::getStaticField(JavaClass *declaredIn, string fieldName, string desc) {
	jfieldID resolved = env->GetStaticFieldID(declaredIn->jniRef(), fieldName.c_str(), desc.c_str());

	// Did we manage to resolve it?
	if (resolved) {
		return new JavaField(env, declaredIn->jniRef(), resolved, true);
	}

	return nullptr;
}

JavaField *JNIKit::getStaticField(string declaredIn, string fieldName, string desc) {
	// Resolve class and resolve field in succession
	JavaClass *declaringClass = getClass(declaredIn);

	if (!declaringClass)
		throw JNIError("could not resolve class from string");

	return getStaticField(declaringClass, fieldName, desc);
}

JavaVM *JNIKit::getVm() {
	JavaVM *vm;

	if (env->GetJavaVM(&vm) != JNI_OK)
		return nullptr;

	return vm;
}

bool JNIKit::detach() {
	if (env) {
		auto jvm = getVm();
		if (jvm)
			return jvm->DetachCurrentThread() == JNI_OK;
	}

	return false;
}

JavaString *JNIKit::createString(string str) {
	return new JavaString(env->NewStringUTF(str.c_str()));
}


vector<JavaVM *> JNIKit::listJvms() {
	vector<JavaVM *> vms;

	// Make call to JNI to acquire the list of VMs..
	JavaVM *temp[64];
	jint count;
	jint result = JNI_GetCreatedJavaVMs(temp, 64, &count);

	// Did it fail?
	if (result != JNI_OK)
		throw JNIError("could not obtain jvm list");

	// And put them neatly in a vec.
	for (int i = 0; i < count; i++) {
		vms.push_back(temp[i]);
	}

	return vms;
}

JNIKit JNIKit::attach(JavaVM *vm) {
	if (!vm)
		throw std::invalid_argument("vm instance is null");

	JNIEnv *env;
	jint result = vm->AttachCurrentThread((void **) &env, NULL);

	// Check if this call failed..
	if (result != JNI_OK)
		throw JNIError("could not attach to thread: " + std::to_string(result));

	return JNIKit(env);
}

JNIKit JNIKit::attachAny() {
	auto jvms = listJvms();

	// We can't do anything without a jvm..
	if (jvms.empty())
		return nullptr;

	return attach(jvms.front());
}