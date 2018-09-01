#include <Component\Control.h>

Control::Control() {
	//Nothing;
}

void Control::setScript(Script * script) {
	this->script = script;
}

Script * Control::getScript() {
	return script;
}