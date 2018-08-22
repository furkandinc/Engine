#ifndef COMPONENT_H
#define COMPONENT_H

class Object;

class Component {
public:
	virtual ~Component() = default;
	Object * object;
};

#endif