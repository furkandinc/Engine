#include <Component\Control.h>

Control::Control() {
	//Nothing;
}

void Control::setScript(Script * script) {
	this->script = script;
	this->script->object = this->object;
}

Script * Control::getScript() {
	return script;
}