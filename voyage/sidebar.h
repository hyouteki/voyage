#ifndef VOYAGE_SIDEBAR_H_
#define VOYAGE_SIDEBAR_H_

#include <stdio.h>
#include "../raylib/include/raylib.h"
#include "elements.h"

typedef struct Sidebar {
	int width;
	int height;
	Color color;
	ElementList *elements;
} Sidebar;

Sidebar Sidebar_Init(int, int, Color);
void Sidebar_AddElement(Sidebar *, Element *);
void Sidebar_Draw(Sidebar);

Sidebar Sidebar_Init(int width, int height, Color color) {
	return (Sidebar){.width=width, .height=height,
					 .color=color, .elements=NULL};
}

void Sidebar_AddElement(Sidebar *sidebar, Element *element) {
	ElementList_Add(&sidebar->elements, element);
}

void Sidebar_Draw(Sidebar sidebar) {
	DrawRectangle(0, 0, sidebar.width, sidebar.height, sidebar.color);
	ElementList_Draw(sidebar.elements);
}

#endif // VOYAGE_SIDEBAR_H_
