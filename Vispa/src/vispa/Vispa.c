#include "Vispa.h"
#include <stdlib.h>
#include <stdio.h>

uint8_t nbScreens = 0;
Vispa* active = NULL;

void vispa_set_active(Vispa* vispa)
{
	if (vispa == NULL)
		return;
	if (active == vispa)
		return;
	glfwMakeContextCurrent(vispa->window);
	active = vispa;
}

void vispa_viewport(Vispa* vispa)
{
	if (vispa == NULL)
		return;
	int width, height;
	glfwGetFramebufferSize(vispa->window, &width, &height);
	vispa_set_active(vispa);
	glViewport(0, 0, width, height);
}


Vispa* vispa_init(int width, int height, const char* title, on_frame_fun* on_frame)
{
	if (glfwInit() != GLFW_TRUE)
		return NULL;
	Vispa* vispa = (Vispa*)malloc(sizeof(Vispa));
	if (vispa == NULL)
		return NULL;
	vispa->closed = FALSE;
	vispa->window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (vispa->window == NULL)
	{
		free(vispa);
		if (nbScreens == 0)
			glfwTerminate();
		return NULL;
	}
	glfwSetWindowUserPointer(vispa->window, vispa);
	vispa_set_active(vispa);
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		printf("error : %s\n", glewGetErrorString(err));
		glfwDestroyWindow(vispa->window);
		free(vispa);
		if (nbScreens == 0)
			glfwTerminate();
		return NULL;
	}

	vispa_viewport(vispa);
	vispa->on_frame = on_frame;
	nbScreens++;
	return vispa;
}

void vispa_set_resolution(Vispa* vispa, int width, int height)
{
	
}


void vispa_destroy(Vispa* vispa)
{
	if (vispa == NULL)
		return;
	if (is_true(vispa->closed))
		return;

	glfwDestroyWindow(vispa->window);
	vispa->closed = TRUE;
	free(vispa);
	nbScreens--;
	if (nbScreens == 0)
		glfwTerminate();
}


bool vispa_should_close(Vispa* vispa)
{
	if (vispa == NULL)
		return TRUE;
	return is_true(glfwWindowShouldClose(vispa->window));
}

void vispa_tick_once(Vispa* vispa)
{
	if (vispa == NULL)
		return;
	vispa_set_active(vispa);
	vispa_viewport(vispa);
	glClear(GL_COLOR_BUFFER_BIT);
	vispa->on_frame(vispa);
	glfwSwapBuffers(vispa->window);
	glfwPollEvents();
}

void vispa_tick_automatic(Vispa* vispa)
{
	if (vispa == NULL)
		return;
	while (!vispa_should_close(vispa))
		vispa_tick_once(vispa);
}