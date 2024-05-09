#ifndef VOYAGE_SIDEBAR_H_
#define VOYAGE_SIDEBAR_H_

#include <stdio.h>
#include "../raylib/include/raylib.h"
#include "elements.h"

typedef struct SidebarOptions {
	double widthFactor;
	int hPadding;
	int vPadding;
} SidebarOptions;

#define SidebarDefaultOptions ((SidebarOptions)						\
							   {.widthFactor=0.25, .hPadding=10,	\
								.vPadding=10})

typedef struct Sidebar {
	Vector2 size;
	Color color;
	ElementList *elements;
	SidebarOptions options;
} Sidebar;

#define Sidebar_Size(windowSize, options)							\
	((Vector2){windowSize.x*(options.widthFactor), windowSize.y})

Sidebar Sidebar_Init(Vector2, Color);
void Sidebar_SetOptions(Sidebar *, SidebarOptions);
void Sidebar_AddElement(Sidebar *, Element *);
void Sidebar_Resize(Sidebar *, Vector2);
void Sidebar_Draw(Sidebar);

Sidebar Sidebar_Init(Vector2 windowSize, Color color) {
	return (Sidebar){.size=Sidebar_Size(windowSize, SidebarDefaultOptions),
					 .color=color, .elements=NULL,
					 .options=SidebarDefaultOptions};
}

void Sidebar_SetOptions(Sidebar *sidebar, SidebarOptions options) {
	sidebar->options = options;
}

void Sidebar_AddElement(Sidebar *sidebar, Element *element) {
	int height = ElementList_TotalHeightTill(sidebar->elements,
											 sidebar->options.vPadding, -1);
	Element_ResizeReposition(element, (Vector2){sidebar->options.hPadding,
												height},
							 (Vector2){sidebar->size.x, 0});
	ElementList_Add(&sidebar->elements, element);
}

void Sidebar_Resize(Sidebar *sidebar, Vector2 windowSize) {
	sidebar->size=Sidebar_Size(windowSize, sidebar->options);
	ElementList *itr = sidebar->elements;
	int _counter = 0;
	while (itr) {
		int height = ElementList_TotalHeightTill(sidebar->elements,
												 sidebar->options.vPadding,
												 _counter);
		Element_ResizeReposition(itr->element, (Vector2){sidebar->options.hPadding, height},
								 (Vector2){sidebar->size.x-2*sidebar->options.hPadding, 0});
		itr = itr->next;
		_counter++;
	}
}

void Sidebar_Draw(Sidebar sidebar) {
	DrawRectangleV((Vector2){0, 0}, sidebar.size, sidebar.color);
	ElementList_Draw(sidebar.elements);
}

#endif // VOYAGE_SIDEBAR_H_
