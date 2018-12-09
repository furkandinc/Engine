#pragma once

class Integer {
public:
	Integer();
	Integer(int value);
	int get();
	void set(int value);
private:
	int value;
};