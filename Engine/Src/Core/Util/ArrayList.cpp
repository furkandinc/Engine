#ifndef ARRAYLIST_CPP
#define ARRAYLIST_CPP

#include <stdlib.h>
#include "ArrayList.h"
#include "Integer.h"
#include "../includes/Angel.h"
#include "../OpenGL/PointGL.h"
#include "../Asset/Material.h"

template <class T>
ArrayList<T>::ArrayList(void) {
	unitSize = sizeof(T);
	listMax = 10;
	listCount = 0;
	listData = (T *)malloc(unitSize*listMax);
}

template <class T>
void ArrayList<T>::checkSize() {
	if (listCount == listMax){

		listMax *= 2;

		T * tempData = (T *)malloc(unitSize*listMax);

		int i;
		for (i = 0; i < listCount; i++) {
			tempData[i] = listData[i];
		}

		free(listData);
		listData = tempData;
	}
}

template <class T>
void ArrayList<T>::add(T element) {
	checkSize();

	listData[listCount] = element;
	listCount++;
}

template <class T>
void ArrayList<T>::set(int index, T element) {
	if (index < 0 || index >= listCount) {
		return;
	}

	listData[index] = element;
}

template <class T>
T ArrayList<T>::get(int index) {
	if (index < 0 || index >= listCount) {
		T t;
		return t;
	}

	return listData[index];
}

template <class T>
T *  ArrayList<T>::toArray() {
	return listData;
}

template <class T>
int ArrayList<T>::getCount() {
	return listCount;
}

template <class T>
int ArrayList<T>::size() {
	return listCount * unitSize;
}

template class ArrayList<PointGL>;
template class ArrayList<Integer>;
template class ArrayList<mat4>;
template class ArrayList<Material>;
#endif