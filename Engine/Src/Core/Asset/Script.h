#ifndef SCRIPT_H
#define SCRIPT_H

class Script {
public:
	virtual void onStart(void) = 0;
	virtual void onUpdate(void) = 0;

	Object * object;
};

#endif