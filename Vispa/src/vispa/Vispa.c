#include "Vispa.h"

#include <stdlib.h>

uint8_t nbScreens = 0;

Vispa* vispa_init(int width, int height, const char* title)
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
	nbScreens++;
	return vispa;
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