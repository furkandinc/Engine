#pragma once
#include <Component\Component.h>
#include <Asset\Script.h>

class Control : public Component {
public:
	Control();
	void setScript(Script * script);
	Script * getScript();
protected:
	Script * script;
};