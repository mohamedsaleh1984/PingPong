struct ButtonState {
	bool isDown;
	bool changed;
};
enum  enumButtons
{
	BUTTON_UP,
	BUTTON_DOWN,
	BUTTON_LEFT,
	BUTTON_RIGHT,
	BUTTON_W,
	BUTTON_S,

	BUTTON_COUNT,		// Should be the last item
};

struct Input
{
	ButtonState buttons[BUTTON_COUNT];
};