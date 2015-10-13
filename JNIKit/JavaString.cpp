#include "JavaString.h"



JavaString::JavaString(JNIKit *kit, jstring ref) {
	this->kit = kit;
	this->ref = ref;
}


JavaString::~JavaString() {
}

jstring JavaString::jniRef() {
	return ref;
}

string JavaString::unwrap() {
	return kit->getEnv()->GetStringUTFChars(ref, jboolean(false));
}