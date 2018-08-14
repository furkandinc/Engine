#ifndef INTEGER_CPP
#define INTEGER_CPP

#include "Integer.h"
Integer::Integer() {
	value = 0;
}
Integer::Integer(int value) {
	this->value = value;
}

int Integer::get() {
	return this->value;
}

void Integer::set(int value) {
	this->value = value;
}
#endif