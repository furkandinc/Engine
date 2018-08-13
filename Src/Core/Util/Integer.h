#ifndef INTEGER_H
#define INTEGER_H

class Integer {
public:
	Integer();
	Integer(int value);
	int get();
	void set(int value);
private:
	int value;
};

#endif