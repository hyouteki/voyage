#include <stdio.h>
#include <math.h>
#include "raylib/include/raylib.h"
#include "voyage/export.h"

int main() {
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(900, 720, "Voyage Demo");
	SetTargetFPS(60);
	
	int width = GetScreenWidth(), height = GetScreenHeight();

	Sidebar sidebar = Sidebar_Init((Vector2){width, height}, DARKGRAY);

	ButtonOptions buttonOptions = (ButtonOptions)			\
		{.centerText=1, .bgColor=BLACK, .fgColor=WHITE};

	Button menuButton1 = Button_Init(Vector2Dummy, 0, "Menu button 1",
								buttonOptions);
	Element element1 = (Element){.type=BUTTON, .button=menuButton1};
	Sidebar_AddElement(&sidebar, &element1);

	Button menuButton2 = Button_Init(Vector2Dummy, 0, "Menu button 2",
									 buttonOptions);
	Element element2 = (Element){.type=BUTTON, .button=menuButton2};
	Sidebar_AddElement(&sidebar, &element2);
	
	while (!WindowShouldClose()) {
		width = GetScreenWidth();
		height = GetScreenHeight();

		Sidebar_Resize(&sidebar, (Vector2){width, height});
		
		BeginDrawing();
		Sidebar_Draw(sidebar);
		ClearBackground(GRAY);
		EndDrawing();
	}
	CloseWindow();
	
	return 0;
}
