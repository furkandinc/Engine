#pragma once

template <class T>
class ArrayList {
private:
	T * listData;
	int listCount;
	int listMax;
	size_t unitSize;

	void checkSize();

public:
	ArrayList(void);

	void add(T element);
	void set(int index, T element);
	T get(int index);
	T * toArray();
	int getCount();
	int size();
};