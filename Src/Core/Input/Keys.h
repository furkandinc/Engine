#ifndef KEYS_H
#define KEYS_H
class Keys {
public:
	const static enum keys : int { KEY_UP_ARROW, KEY_DOWN_ARROW, KEY_LEFT_ARROW, KEY_RIGHT_ARROW, COUNT = KEY_RIGHT_ARROW + 1 };

	const static enum status : int { STATUS_PRESSED, STATUS_PRESS, STATUS_RELEASED, STATUS_IDLE };

};
#endif