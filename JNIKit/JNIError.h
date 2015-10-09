#pragma once

#include <exception>
#include <string>

using namespace std;

class JNIError: public exception {
public:
	JNIError(string error) {
		this->error = error;
	}
	virtual const char* what() const throw() {
		return error.c_str();
	}
private:
	string error;
};