#ifndef __VISPA_VISPA_H__
#define __VISPA_VISPA_H__
#include <vispa/vispa.h>
#include <utils/boolean.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>


struct vispa {
	bool closed;
	GLFWwindow* window;
	on_frame_fun* on_frame;
	int height;
	int width;
	uint32_t* buffer;
};



#endif