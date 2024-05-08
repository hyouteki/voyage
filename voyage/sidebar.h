#ifndef VOYAGE_SIDEBAR_H_
#define VOYAGE_SIDEBAR_H_

#include <stdio.h>
#include "../raylib/include/raylib.h"
#include "elements.h"

// TODO: move this to Sidebar_Options
#define SIDEBAR_WIDTH_FACTOR 0.25
#define Sidebar_Size(windowSize, widthFactor) \
	((Vector2){windowSize.x*widthFactor, windowSize.y})

typedef struct Sidebar {
	Vector2 size;
	Color color;
	ElementList *elements;
} Sidebar;

Sidebar Sidebar_Init(Vector2, Color);
void Sidebar_AddElement(Sidebar *, Element *);
void Sidebar_Resize(Sidebar *, Vector2);
void Sidebar_Draw(Sidebar);

Sidebar Sidebar_Init(Vector2 windowSize, Color color) {
	return (Sidebar){.size=Sidebar_Size(windowSize, SIDEBAR_WIDTH_FACTOR),
					 .color=color, .elements=NULL};
}

void Sidebar_AddElement(Sidebar *sidebar, Element *element) {
	ElementList_Add(&sidebar->elements, element);
}

void Sidebar_Resize(Sidebar *sidebar, Vector2 windowSize) {
	sidebar->size=Sidebar_Size(windowSize, SIDEBAR_WIDTH_FACTOR);
}

void Sidebar_Draw(Sidebar sidebar) {
	DrawRectangleV((Vector2){0, 0}, sidebar.size, sidebar.color);
	ElementList_Draw(sidebar.elements);
}

#endif // VOYAGE_SIDEBAR_H_
