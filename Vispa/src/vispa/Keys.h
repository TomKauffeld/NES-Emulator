#ifndef __VISPA_KEYS_INTERNAL_H__
#define __VISPA_KEYS_INTERNAL_H__
#include <vispa/keys.h>
#include <inttypes.h>


int16_t vispa_key_from_glfw(int glfw);
int vispa_key_to_glfw(int16_t vispa);
uint8_t vispa_mod_from_glfw(int glfw);
uint8_t vispa_action_from_glfw(int glfw);

#endif