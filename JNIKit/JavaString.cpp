#include "JavaString.h"



JavaString::JavaString(jstring ref) {
	this->ref = ref;
}


JavaString::~JavaString() {
}

jstring JavaString::jniRef() {
	return ref;
}
