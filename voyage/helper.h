#ifndef VOYAGE_HELPER_H_
#define VOYAGE_HELPER_H_

#include <stdio.h>
#include "../raylib/include/raylib.h"
#include "button.h"
#include "elements.h"

#define Vector2Dummy ((Vector2){0, 0})
#define Button_EleInit(...) ((Element){.type=BUTTON, \
									   .button=Button_Init(__VA_ARGS__)})

#endif // VOYAGE_HELPER_H_
