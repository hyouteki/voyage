#ifndef VOYAGE_XML_HANDLER_H_
#define VOYAGE_XML_HANDLER_H_

#include "../cxmlp/export.h"
#include "row.h"
#include "column.h"
#include "helper.h"

static Row *Voyage_ContentRoot = NULL;

void Voyage_SetContentView(char *);
void *Voyage_GetElementById(char *);

void Voyage_SetContentView(char *filepath) {
	XmlNode *root = Cxmlp_ParseFile(filepath);
	/* Cxmlp_XmlNode_Print(root); */
	Voyage_ContentRoot = Row_InitAtr(root);
}

void *Voyage_GetElementById(char *id) {
	if (!Voyage_ContentRoot) Voyage_Error("content root is not set");
	return Row_GetElementById(Voyage_ContentRoot, id);
}

void Voyage_MainLoop() {
	if (!Voyage_ContentRoot) Voyage_Error("content root is not set");
	while (!WindowShouldClose()) {
		Row_Resize(Voyage_ContentRoot, Voyage_ScreenDimen);
		Row_AttachListeners(Voyage_ContentRoot);

		BeginDrawing();
		ClearBackground(BLACK);
		Row_Draw(*Voyage_ContentRoot);
		EndDrawing();
	}
	CloseWindow();
	Row_Free(Voyage_ContentRoot);
}

#endif // VOYAGE_XML_HANDLER_H_
