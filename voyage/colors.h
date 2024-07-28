#ifndef VOYAGE_COLORS_H_
#define VOYAGE_COLORS_H_

#include <string.h>
#include <raylib.h>

#define Voyage_LightGrey (Color){58, 58, 58, 225}
#define Voyage_DarkGrey (Color){26, 26, 26, 225}
#define Voyage_White (Color){245, 245, 245, 255}
#define Voyage_LightAqua (Color){233, 241, 242, 255}
#define Voyage_DarkAqua (Color){198, 210, 198, 255}
#define Voyage_LightBlue (Color){185, 214, 232, 255}
#define Voyage_Blue (Color){93, 156, 189, 255}
#define Voyage_Brown (Color){117, 113, 94, 255}
#define Voyage_DarkBrown (Color){39, 40, 34, 255}
#define Voyage_Black (Color){9, 9, 9, 255}
#define Voyage_LightGreen (Color){166, 226, 46, 255}
#define Voyage_OffBrown (Color){73, 72, 62, 255}
#define Voyage_Color_Default (Voyage_Blue)

Color Voyage_Color_FromString(char *name) {
	if (strcmp("light-grey", name) == 0) return Voyage_LightGrey;
	if (strcmp("dark-grey", name) == 0) return Voyage_DarkGrey;
	if (strcmp("white", name) == 0) return Voyage_White;
	if (strcmp("light-aqua", name) == 0) return Voyage_LightAqua;
	if (strcmp("dark-aqua", name) == 0) return Voyage_DarkAqua;
	if (strcmp("light-blue", name) == 0) return Voyage_LightBlue;
	if (strcmp("blue", name) == 0) return Voyage_Blue;
	if (strcmp("brown", name) == 0) return Voyage_Brown;
	if (strcmp("dark-brown", name) == 0) return Voyage_DarkBrown;
	if (strcmp("black", name) == 0) return Voyage_Black;
	if (strcmp("light-green", name) == 0) return Voyage_LightGreen;
	if (strcmp("off-brown", name) == 0) return Voyage_OffBrown;
	return Voyage_Color_Default;
}

#endif // VOYAGE_COLORS_H_
