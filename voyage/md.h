#include "helper.h"

#define HeadingOptions ((LabelOptions)									\
						{.bgColor=Voyage_LightGrey, .fgColor=Voyage_LightGreen, \
						 .font=GetFontDefault(), .fontSize=32, .textSpacing=3, \
						 .textSpacingV=5, .hOffset=10, .vOffset=10})

#define Heading_EleInit(text)								\
	((Element){.type=Element_Label, .label=Label_InitC(Vector2Dummy, 0, text, HeadingOptions)})
