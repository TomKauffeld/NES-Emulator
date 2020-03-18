#include "Keys.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

int16_t vispa_key_from_glfw(int glfw)
{
	switch (glfw)
	{
	case GLFW_KEY_UNKNOWN:
		return VISPA_KEY_UNKNOWN;
	case GLFW_KEY_SPACE:
		return VISPA_KEY_SPACE;
	case GLFW_KEY_APOSTROPHE:
		return VISPA_KEY_APOSTROPHE;
	case GLFW_KEY_COMMA:
		return VISPA_KEY_COMMA;
	case GLFW_KEY_MINUS:
		return VISPA_KEY_MINUS;
	case GLFW_KEY_PERIOD:
		return VISPA_KEY_PERIOD;
	case GLFW_KEY_SLASH:
		return VISPA_KEY_SLASH;
	case GLFW_KEY_0:
		return VISPA_KEY_0;
	case GLFW_KEY_1:
		return VISPA_KEY_1;
	case GLFW_KEY_2:
		return VISPA_KEY_2;
	case GLFW_KEY_3:
		return VISPA_KEY_3;
	case GLFW_KEY_4:
		return VISPA_KEY_4;
	case GLFW_KEY_5:
		return VISPA_KEY_5;
	case GLFW_KEY_6:
		return VISPA_KEY_6;
	case GLFW_KEY_7:
		return VISPA_KEY_7;
	case GLFW_KEY_8:
		return VISPA_KEY_8;
	case GLFW_KEY_9:
		return VISPA_KEY_9;
	case GLFW_KEY_SEMICOLON:
		return VISPA_KEY_SEMICOLON;
	case GLFW_KEY_EQUAL:
		return VISPA_KEY_EQUAL;
	case GLFW_KEY_A:
		return VISPA_KEY_A;
	case GLFW_KEY_B:
		return VISPA_KEY_B;
	case GLFW_KEY_C:
		return VISPA_KEY_C;
	case GLFW_KEY_D:
		return VISPA_KEY_D;
	case GLFW_KEY_E:
		return VISPA_KEY_E;
	case GLFW_KEY_F:
		return VISPA_KEY_F;
	case GLFW_KEY_G:
		return VISPA_KEY_G;
	case GLFW_KEY_H:
		return VISPA_KEY_H;
	case GLFW_KEY_I:
		return VISPA_KEY_I;
	case GLFW_KEY_J:
		return VISPA_KEY_J;
	case GLFW_KEY_K:
		return VISPA_KEY_K;
	case GLFW_KEY_L:
		return VISPA_KEY_L;
	case GLFW_KEY_M:
		return VISPA_KEY_M;
	case GLFW_KEY_N:
		return VISPA_KEY_N;
	case GLFW_KEY_O:
		return VISPA_KEY_O;
	case GLFW_KEY_P:
		return VISPA_KEY_P;
	case GLFW_KEY_Q:
		return VISPA_KEY_Q;
	case GLFW_KEY_R:
		return VISPA_KEY_R;
	case GLFW_KEY_S:
		return VISPA_KEY_S;
	case GLFW_KEY_T:
		return VISPA_KEY_T;
	case GLFW_KEY_U:
		return VISPA_KEY_U;
	case GLFW_KEY_V:
		return VISPA_KEY_V;
	case GLFW_KEY_W:
		return VISPA_KEY_W;
	case GLFW_KEY_X:
		return VISPA_KEY_X;
	case GLFW_KEY_Y:
		return VISPA_KEY_Y;
	case GLFW_KEY_Z:
		return VISPA_KEY_Z;
	case GLFW_KEY_LEFT_BRACKET:
		return VISPA_KEY_LEFT_BRACKET;
	case GLFW_KEY_BACKSLASH:
		return VISPA_KEY_BACKSLASH;
	case GLFW_KEY_RIGHT_BRACKET:
		return VISPA_KEY_RIGHT_BRACKET;
	case GLFW_KEY_GRAVE_ACCENT:
		return VISPA_KEY_GRAVE_ACCENT;
	case GLFW_KEY_WORLD_1:
		return VISPA_KEY_WORLD_1;
	case GLFW_KEY_WORLD_2:
		return VISPA_KEY_WORLD_2;
	case GLFW_KEY_ESCAPE:
		return VISPA_KEY_ESCAPE;
	case GLFW_KEY_ENTER:
		return VISPA_KEY_ENTER;
	case GLFW_KEY_TAB:
		return VISPA_KEY_TAB;
	case GLFW_KEY_BACKSPACE:
		return VISPA_KEY_BACKSPACE;
	case GLFW_KEY_INSERT:
		return VISPA_KEY_INSERT;
	case GLFW_KEY_DELETE:
		return VISPA_KEY_DELETE;
	case GLFW_KEY_RIGHT:
		return VISPA_KEY_RIGHT;
	case GLFW_KEY_LEFT:
		return VISPA_KEY_LEFT;
	case GLFW_KEY_DOWN:
		return VISPA_KEY_DOWN;
	case GLFW_KEY_UP:
		return VISPA_KEY_UP;
	case GLFW_KEY_PAGE_UP:
		return VISPA_KEY_PAGE_UP;
	case GLFW_KEY_PAGE_DOWN:
		return VISPA_KEY_PAGE_DOWN;
	case GLFW_KEY_HOME:
		return VISPA_KEY_HOME;
	case GLFW_KEY_END:
		return VISPA_KEY_END;
	case GLFW_KEY_CAPS_LOCK:
		return VISPA_KEY_CAPS_LOCK;
	case GLFW_KEY_SCROLL_LOCK:
		return VISPA_KEY_SCROLL_LOCK;
	case GLFW_KEY_NUM_LOCK:
		return VISPA_KEY_NUM_LOCK;
	case GLFW_KEY_PRINT_SCREEN:
		return VISPA_KEY_PRINT_SCREEN;
	case GLFW_KEY_PAUSE:
		return VISPA_KEY_PAUSE;
	case GLFW_KEY_F1:
		return VISPA_KEY_F1;
	case GLFW_KEY_F2:
		return VISPA_KEY_F2;
	case GLFW_KEY_F3:
		return VISPA_KEY_F3;
	case GLFW_KEY_F4:
		return VISPA_KEY_F4;
	case GLFW_KEY_F5:
		return VISPA_KEY_F5;
	case GLFW_KEY_F6:
		return VISPA_KEY_F6;
	case GLFW_KEY_F7:
		return VISPA_KEY_F7;
	case GLFW_KEY_F8:
		return VISPA_KEY_F8;
	case GLFW_KEY_F9:
		return VISPA_KEY_F9;
	case GLFW_KEY_F10:
		return VISPA_KEY_F10;
	case GLFW_KEY_F11:
		return VISPA_KEY_F11;
	case GLFW_KEY_F12:
		return VISPA_KEY_F12;
	case GLFW_KEY_F13:
		return VISPA_KEY_F13;
	case GLFW_KEY_F14:
		return VISPA_KEY_F14;
	case GLFW_KEY_F15:
		return VISPA_KEY_F15;
	case GLFW_KEY_F16:
		return VISPA_KEY_F16;
	case GLFW_KEY_F17:
		return VISPA_KEY_F17;
	case GLFW_KEY_F18:
		return VISPA_KEY_F18;
	case GLFW_KEY_F19:
		return VISPA_KEY_F19;
	case GLFW_KEY_F20:
		return VISPA_KEY_F20;
	case GLFW_KEY_F21:
		return VISPA_KEY_F21;
	case GLFW_KEY_F22:
		return VISPA_KEY_F22;
	case GLFW_KEY_F23:
		return VISPA_KEY_F23;
	case GLFW_KEY_F24:
		return VISPA_KEY_F24;
	case GLFW_KEY_F25:
		return VISPA_KEY_F25;
	case GLFW_KEY_KP_0:
		return VISPA_KEY_KP_0;
	case GLFW_KEY_KP_1:
		return VISPA_KEY_KP_1;
	case GLFW_KEY_KP_2:
		return VISPA_KEY_KP_2;
	case GLFW_KEY_KP_3:
		return VISPA_KEY_KP_3;
	case GLFW_KEY_KP_4:
		return VISPA_KEY_KP_4;
	case GLFW_KEY_KP_5:
		return VISPA_KEY_KP_5;
	case GLFW_KEY_KP_6:
		return VISPA_KEY_KP_6;
	case GLFW_KEY_KP_7:
		return VISPA_KEY_KP_7;
	case GLFW_KEY_KP_8:
		return VISPA_KEY_KP_8;
	case GLFW_KEY_KP_9:
		return VISPA_KEY_KP_9;
	case GLFW_KEY_KP_DECIMAL:
		return VISPA_KEY_KP_DECIMAL;
	case GLFW_KEY_KP_DIVIDE:
		return VISPA_KEY_KP_DIVIDE;
	case GLFW_KEY_KP_MULTIPLY:
		return VISPA_KEY_KP_MULTIPLY;
	case GLFW_KEY_KP_SUBTRACT:
		return VISPA_KEY_KP_SUBTRACT;
	case GLFW_KEY_KP_ADD:
		return VISPA_KEY_KP_ADD;
	case GLFW_KEY_KP_ENTER:
		return VISPA_KEY_KP_ENTER;
	case GLFW_KEY_KP_EQUAL:
		return VISPA_KEY_KP_EQUAL;
	case GLFW_KEY_LEFT_SHIFT:
		return VISPA_KEY_LEFT_SHIFT;
	case GLFW_KEY_LEFT_CONTROL:
		return VISPA_KEY_LEFT_CONTROL;
	case GLFW_KEY_LEFT_ALT:
		return VISPA_KEY_LEFT_ALT;
	case GLFW_KEY_LEFT_SUPER:
		return VISPA_KEY_LEFT_SUPER;
	case GLFW_KEY_RIGHT_SHIFT:
		return VISPA_KEY_RIGHT_SHIFT;
	case GLFW_KEY_RIGHT_CONTROL:
		return VISPA_KEY_RIGHT_CONTROL;
	case GLFW_KEY_RIGHT_ALT:
		return VISPA_KEY_RIGHT_ALT;
	case GLFW_KEY_RIGHT_SUPER:
		return VISPA_KEY_RIGHT_SUPER;
	case GLFW_KEY_MENU:
		return VISPA_KEY_MENU;
	default:
		return VISPA_KEY_UNKNOWN;
	}
}


int vispa_key_to_glfw(int16_t vispa)
{
	switch (vispa)
	{
	case VISPA_KEY_UNKNOWN:
		return GLFW_KEY_UNKNOWN;
	case VISPA_KEY_SPACE:
		return GLFW_KEY_SPACE;
	case VISPA_KEY_APOSTROPHE:
		return GLFW_KEY_APOSTROPHE;
	case VISPA_KEY_COMMA:
		return GLFW_KEY_COMMA;
	case VISPA_KEY_MINUS:
		return GLFW_KEY_MINUS;
	case VISPA_KEY_PERIOD:
		return GLFW_KEY_PERIOD;
	case VISPA_KEY_SLASH:
		return GLFW_KEY_SLASH;
	case VISPA_KEY_0:
		return GLFW_KEY_0;
	case VISPA_KEY_1:
		return GLFW_KEY_1;
	case VISPA_KEY_2:
		return GLFW_KEY_2;
	case VISPA_KEY_3:
		return GLFW_KEY_3;
	case VISPA_KEY_4:
		return GLFW_KEY_4;
	case VISPA_KEY_5:
		return GLFW_KEY_5;
	case VISPA_KEY_6:
		return GLFW_KEY_6;
	case VISPA_KEY_7:
		return GLFW_KEY_7;
	case VISPA_KEY_8:
		return GLFW_KEY_8;
	case VISPA_KEY_9:
		return GLFW_KEY_9;
	case VISPA_KEY_SEMICOLON:
		return GLFW_KEY_SEMICOLON;
	case VISPA_KEY_EQUAL:
		return GLFW_KEY_EQUAL;
	case VISPA_KEY_A:
		return GLFW_KEY_A;
	case VISPA_KEY_B:
		return GLFW_KEY_B;
	case VISPA_KEY_C:
		return GLFW_KEY_C;
	case VISPA_KEY_D:
		return GLFW_KEY_D;
	case VISPA_KEY_E:
		return GLFW_KEY_E;
	case VISPA_KEY_F:
		return GLFW_KEY_F;
	case VISPA_KEY_G:
		return GLFW_KEY_G;
	case VISPA_KEY_H:
		return GLFW_KEY_H;
	case VISPA_KEY_I:
		return GLFW_KEY_I;
	case VISPA_KEY_J:
		return GLFW_KEY_J;
	case VISPA_KEY_K:
		return GLFW_KEY_K;
	case VISPA_KEY_L:
		return GLFW_KEY_L;
	case VISPA_KEY_M:
		return GLFW_KEY_M;
	case VISPA_KEY_N:
		return GLFW_KEY_N;
	case VISPA_KEY_O:
		return GLFW_KEY_O;
	case VISPA_KEY_P:
		return GLFW_KEY_P;
	case VISPA_KEY_Q:
		return GLFW_KEY_Q;
	case VISPA_KEY_R:
		return GLFW_KEY_R;
	case VISPA_KEY_S:
		return GLFW_KEY_S;
	case VISPA_KEY_T:
		return GLFW_KEY_T;
	case VISPA_KEY_U:
		return GLFW_KEY_U;
	case VISPA_KEY_V:
		return GLFW_KEY_V;
	case VISPA_KEY_W:
		return GLFW_KEY_W;
	case VISPA_KEY_X:
		return GLFW_KEY_X;
	case VISPA_KEY_Y:
		return GLFW_KEY_Y;
	case VISPA_KEY_Z:
		return GLFW_KEY_Z;
	case VISPA_KEY_LEFT_BRACKET:
		return GLFW_KEY_LEFT_BRACKET;
	case VISPA_KEY_BACKSLASH:
		return GLFW_KEY_BACKSLASH;
	case VISPA_KEY_RIGHT_BRACKET:
		return GLFW_KEY_RIGHT_BRACKET;
	case VISPA_KEY_GRAVE_ACCENT:
		return GLFW_KEY_GRAVE_ACCENT;
	case VISPA_KEY_WORLD_1:
		return GLFW_KEY_WORLD_1;
	case VISPA_KEY_WORLD_2:
		return GLFW_KEY_WORLD_2;
	case VISPA_KEY_ESCAPE:
		return GLFW_KEY_ESCAPE;
	case VISPA_KEY_ENTER:
		return GLFW_KEY_ENTER;
	case VISPA_KEY_TAB:
		return GLFW_KEY_TAB;
	case VISPA_KEY_BACKSPACE:
		return GLFW_KEY_BACKSPACE;
	case VISPA_KEY_INSERT:
		return GLFW_KEY_INSERT;
	case VISPA_KEY_DELETE:
		return GLFW_KEY_DELETE;
	case VISPA_KEY_RIGHT:
		return GLFW_KEY_RIGHT;
	case VISPA_KEY_LEFT:
		return GLFW_KEY_LEFT;
	case VISPA_KEY_DOWN:
		return GLFW_KEY_DOWN;
	case VISPA_KEY_UP:
		return GLFW_KEY_UP;
	case VISPA_KEY_PAGE_UP:
		return GLFW_KEY_PAGE_UP;
	case VISPA_KEY_PAGE_DOWN:
		return GLFW_KEY_PAGE_DOWN;
	case VISPA_KEY_HOME:
		return GLFW_KEY_HOME;
	case VISPA_KEY_END:
		return GLFW_KEY_END;
	case VISPA_KEY_CAPS_LOCK:
		return GLFW_KEY_CAPS_LOCK;
	case VISPA_KEY_SCROLL_LOCK:
		return GLFW_KEY_SCROLL_LOCK;
	case VISPA_KEY_NUM_LOCK:
		return GLFW_KEY_NUM_LOCK;
	case VISPA_KEY_PRINT_SCREEN:
		return GLFW_KEY_PRINT_SCREEN;
	case VISPA_KEY_PAUSE:
		return GLFW_KEY_PAUSE;
	case VISPA_KEY_F1:
		return GLFW_KEY_F1;
	case VISPA_KEY_F2:
		return GLFW_KEY_F2;
	case VISPA_KEY_F3:
		return GLFW_KEY_F3;
	case VISPA_KEY_F4:
		return GLFW_KEY_F4;
	case VISPA_KEY_F5:
		return GLFW_KEY_F5;
	case VISPA_KEY_F6:
		return GLFW_KEY_F6;
	case VISPA_KEY_F7:
		return GLFW_KEY_F7;
	case VISPA_KEY_F8:
		return GLFW_KEY_F8;
	case VISPA_KEY_F9:
		return GLFW_KEY_F9;
	case VISPA_KEY_F10:
		return GLFW_KEY_F10;
	case VISPA_KEY_F11:
		return GLFW_KEY_F11;
	case VISPA_KEY_F12:
		return GLFW_KEY_F12;
	case VISPA_KEY_F13:
		return GLFW_KEY_F13;
	case VISPA_KEY_F14:
		return GLFW_KEY_F14;
	case VISPA_KEY_F15:
		return GLFW_KEY_F15;
	case VISPA_KEY_F16:
		return GLFW_KEY_F16;
	case VISPA_KEY_F17:
		return GLFW_KEY_F17;
	case VISPA_KEY_F18:
		return GLFW_KEY_F18;
	case VISPA_KEY_F19:
		return GLFW_KEY_F19;
	case VISPA_KEY_F20:
		return GLFW_KEY_F20;
	case VISPA_KEY_F21:
		return GLFW_KEY_F21;
	case VISPA_KEY_F22:
		return GLFW_KEY_F22;
	case VISPA_KEY_F23:
		return GLFW_KEY_F23;
	case VISPA_KEY_F24:
		return GLFW_KEY_F24;
	case VISPA_KEY_F25:
		return GLFW_KEY_F25;
	case VISPA_KEY_KP_0:
		return GLFW_KEY_KP_0;
	case VISPA_KEY_KP_1:
		return GLFW_KEY_KP_1;
	case VISPA_KEY_KP_2:
		return GLFW_KEY_KP_2;
	case VISPA_KEY_KP_3:
		return GLFW_KEY_KP_3;
	case VISPA_KEY_KP_4:
		return GLFW_KEY_KP_4;
	case VISPA_KEY_KP_5:
		return GLFW_KEY_KP_5;
	case VISPA_KEY_KP_6:
		return GLFW_KEY_KP_6;
	case VISPA_KEY_KP_7:
		return GLFW_KEY_KP_7;
	case VISPA_KEY_KP_8:
		return GLFW_KEY_KP_8;
	case VISPA_KEY_KP_9:
		return GLFW_KEY_KP_9;
	case VISPA_KEY_KP_DECIMAL:
		return GLFW_KEY_KP_DECIMAL;
	case VISPA_KEY_KP_DIVIDE:
		return GLFW_KEY_KP_DIVIDE;
	case VISPA_KEY_KP_MULTIPLY:
		return GLFW_KEY_KP_MULTIPLY;
	case VISPA_KEY_KP_SUBTRACT:
		return GLFW_KEY_KP_SUBTRACT;
	case VISPA_KEY_KP_ADD:
		return GLFW_KEY_KP_ADD;
	case VISPA_KEY_KP_ENTER:
		return GLFW_KEY_KP_ENTER;
	case VISPA_KEY_KP_EQUAL:
		return GLFW_KEY_KP_EQUAL;
	case VISPA_KEY_LEFT_SHIFT:
		return GLFW_KEY_LEFT_SHIFT;
	case VISPA_KEY_LEFT_CONTROL:
		return GLFW_KEY_LEFT_CONTROL;
	case VISPA_KEY_LEFT_ALT:
		return GLFW_KEY_LEFT_ALT;
	case VISPA_KEY_LEFT_SUPER:
		return GLFW_KEY_LEFT_SUPER;
	case VISPA_KEY_RIGHT_SHIFT:
		return GLFW_KEY_RIGHT_SHIFT;
	case VISPA_KEY_RIGHT_CONTROL:
		return GLFW_KEY_RIGHT_CONTROL;
	case VISPA_KEY_RIGHT_ALT:
		return GLFW_KEY_RIGHT_ALT;
	case VISPA_KEY_RIGHT_SUPER:
		return GLFW_KEY_RIGHT_SUPER;
	case VISPA_KEY_MENU:
		return GLFW_KEY_MENU;
	default:
		return GLFW_KEY_UNKNOWN;
	}
}

uint8_t vispa_mod_from_glfw(int glfw)
{
	uint8_t mods = 0x00;
	if ((glfw & GLFW_MOD_SHIFT) > 0)
		mods |= VISPA_MOD_SHIFT;
	if ((glfw & GLFW_MOD_CONTROL) > 0)
		mods |= VISPA_MOD_CONTROL;
	if ((glfw & GLFW_MOD_ALT) > 0)
		mods |= VISPA_MOD_ALT;
	if ((glfw & GLFW_MOD_SUPER) > 0)
		mods |= VISPA_MOD_SUPER;
	if ((glfw & GLFW_MOD_CAPS_LOCK) > 0)
		mods |= VISPA_MOD_CAPS_LOCK;
	if ((glfw & GLFW_MOD_NUM_LOCK) > 0)
		mods |= VISPA_MOD_NUM_LOCK;
	return mods;
}

uint8_t vispa_action_from_glfw(int glfw)
{
	switch (glfw)
	{
	case GLFW_PRESS:
		return VISPA_ACTION_PRESS;
	case GLFW_REPEAT:
		return VISPA_ACTION_REPEAT;
	case GLFW_RELEASE:
		return VISPA_ACTION_RELEASE;
	default:
		return VISPA_ACTION_UNKNOWN;
	}
}

int vispa_get_scan_code(int16_t keyCode)
{
	int glfw = vispa_key_to_glfw(keyCode);
	return glfwGetKeyScancode(glfw);
}

const char* vispa_get_key_name_by_key_code(int16_t keyCode)
{
	int glfw = vispa_key_to_glfw(keyCode);
	return glfwGetKeyName(glfw, 0);
}

const char* vispa_get_key_name_by_scan_code(int scanCode)
{
	return glfwGetKeyName(GLFW_KEY_UNKNOWN, scanCode);
}