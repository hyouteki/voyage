#include "helper.h"

extern FontW defaultFont;

#define HeadingOptions ((LabelOptions)									\
						{.bgColor=Voyage_LightGrey, .fgColor=Voyage_LightGreen, \
								.font=Voyage_ChangeFontSize(defaultFont, 44), \
								.fontSize=44, .textSpacing=defaultFont.textSpacing,	\
								.textSpacingV=5, .hOffset=10, .vOffset=10})

#define Heading_EleInit(text)								\
	((Element){.type=Element_Label, .label=Label_InitC(Vector2Dummy, 0, text, HeadingOptions)})
