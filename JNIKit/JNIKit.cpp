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

JavaField *JNIKit::getField(JavaClass *declaredIn, string fieldName, string desc) {
	jfieldID resolved = env->GetStaticFieldID(declaredIn->jniRef(), fieldName.c_str(), desc.c_str());

	// Did we manage to resolve it?
	if (resolved) {
		return new JavaField(env, declaredIn->jniRef(), resolved, true);
	}

	// Attempt to get a nonstatic field variant
	resolved = env->GetFieldID(declaredIn->jniRef(), fieldName.c_str(), desc.c_str());
	if (resolved) {
		return new JavaField(env, declaredIn->jniRef(), resolved, false);
	}

	return nullptr;
}

JavaField *JNIKit::getField(string declaredIn, string fieldName, string desc) {
	// Resolve class and resolve field in succession
	JavaClass *declaringClass = getClass(declaredIn);

	if (!declaringClass)
		throw JNIError("could not resolve class from string");

	return getField(declaringClass, fieldName, desc);
}

JavaMethod *JNIKit::getMethod(JavaClass *declaredIn, string methodName, string desc) {
	jmethodID resolved = env->GetStaticMethodID(declaredIn->jniRef(), methodName.c_str(), desc.c_str());

	// Did we manage to resolve it?
	if (resolved) {
		return new JavaMethod(env, resolved, declaredIn->jniRef(), true);
	}

	// Attempt to resolve the nonstatic variant
	resolved = env->GetMethodID(declaredIn->jniRef(), methodName.c_str(), desc.c_str());

	// Did we manage to resolve it?
	if (resolved) {
		return new JavaMethod(env, resolved, declaredIn->jniRef(), false);
	}

	return nullptr;
}

JavaMethod *JNIKit::getMethod(string declaredIn, string methodName, string desc) {
	// Resolve class and resolve method in succession
	JavaClass *declaringClass = getClass(declaredIn);

	if (!declaringClass)
		throw JNIError("could not resolve class from string");

	return getMethod(declaringClass, methodName, desc);
}

JavaVM *JNIKit::getVm() {
	JavaVM *vm;

	if (env->GetJavaVM(&vm) != JNI_OK)
		return nullptr;

	return vm;
}

JNIEnv *JNIKit::getEnv() {
	return env;
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
	return new JavaString(this, env->NewStringUTF(str.c_str()));
}

string JNIKit::unwrapString(jstring str) {
	return string(env->GetStringUTFChars(str, jboolean(false)));
}

JavaClass *JNIKit::defineClass(string name, string filename, jobject classLoader) {
	// Load the file data
	std::ifstream file(filename, std::ios::binary);
	file.seekg(0, std::ios::end);
	std::streamsize size = file.tellg();
	file.seekg(0, std::ios::beg);

	std::vector<char> buffer(size);
	if (!file.read(buffer.data(), size)) {
		throw JNIError("could not read file contents into buffer");
	}

	// Construct new class from data buffer
	return defineClass(name, buffer, classLoader);
}

JavaClass *JNIKit::defineClass(string name, vector<char>& data, jobject classLoader) {
	jobject loader = classLoader;

	// Use system class loader if we don't pass any
	if (!loader) {
		auto classLoaderClass = getClass("java/lang/ClassLoader");
		jmethodID getSystemClassLoader = env->GetStaticMethodID(classLoaderClass->jniRef(), "getSystemClassLoader", "()Ljava/lang/ClassLoader;");
		jobject instance = env->CallStaticObjectMethod(classLoaderClass->jniRef(), getSystemClassLoader);
	}

	jclass defined = env->DefineClass(name.c_str(), loader, (jbyte *) data.data(), data.size());
	if (!defined) {
		throw new JNIError("could not define class");
		// TODO find a way to acquire what exactly went wrong under the hood..
	}

	return new JavaClass(env, defined);
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