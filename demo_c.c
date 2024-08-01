#include "export.h"

void buttonOnClick() {
	printf("Menu button clicked\n");
}

int main() {
	Voyage_Setup(900, 720, 60, "Voyage Demo", FLAG_WINDOW_RESIZABLE);
	
	Column sidebar = Column_Init(Vector2Dummy, Vector2Dummy, Voyage_Black);
	Image image = LoadImage("./resources/logo.png");
	Column_Add(&sidebar, &ImageContainer_EleInit(&image));
	Column_Add(&sidebar, &Button_EleInit("Menu button 1", &buttonOnClick));
	Column_Add(&sidebar, &Label_EleInit("Sample label with word wrap"));

	Column canvas = Column_Init(Vector2Dummy, Vector2Dummy, Voyage_DarkBrown);
	Column_AddF(&canvas, &Button_EleInit("Fixed button inside canvas", NULL));
	Column_Add(&canvas, &Button_EleInit("Button inside canvas", NULL));
	Column_Add(&canvas, &Heading_EleInit("Lorem Ipsum"));
	Column_Add(&canvas, &Label_EleInit("This is Voyage Demo written with C."));
	Column_Add(&canvas, &Label_EleInit("Type something in the bellow input field."));
	Column_Add(&canvas, &Input_EleInit("", NULL));
	Column_Add(&canvas, &Space_EleInit(100));
	Column_Add(&canvas, &Label_EleInit("There's 100 pixels worth of empty space above."));
	Column_Add(&canvas, &Quote_EleInit("This is a quote."));

	Row row = Row_Init(Vector2Dummy, Vector2Dummy, 2,
					   (Column *[]){&sidebar, &canvas}, (u32 []){1, 3});
	
	while (!WindowShouldClose()) {
		Row_Resize(&row, Voyage_ScreenDimen);
		Row_AttachListeners(&row);

		BeginDrawing();
		ClearBackground(BLACK);
		Row_Draw(row);
		EndDrawing();
	}
	CloseWindow();
	Row_Free(&row);
	
	return 0;
}
