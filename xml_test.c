#include "cxmlp/export.h"
#include "export.h"

void buttonOnClick() {
	printf("Menu button clicked\n");
}

int main() {
	Voyage_Setup(900, 720, 60, "Voyage Demo", FLAG_WINDOW_RESIZABLE);

	XmlNode *root = Cxmlp_ParseFile("./demo.xml");
	Cxmlp_XmlNode_Print(root);
	Row *row = Voyage_GenSourceTree(root);
	
	while (!WindowShouldClose()) {
		if (row) {
			Row_Resize(row, Voyage_ScreenDimen);
			Row_AttachListeners(row);
		}

		BeginDrawing();
		ClearBackground(BLACK);
		if (row) Row_Draw(*row);
		EndDrawing();
	}
	CloseWindow();
	if (row) Row_Free(row);
	
	return 0;
}
