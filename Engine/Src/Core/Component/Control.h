#pragma once
#include "Component.h"
#include "..\Asset\Script.h"

class DLLDIR Control : public Component {
public:
	Control();
	void setScript(Script * script);
	Script * getScript();
protected:
	Script * script;
};