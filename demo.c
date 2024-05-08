#include <stdio.h>
#include <math.h>
#include "raylib/include/raylib.h"
#include "voyage/export.h"

int main() {
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(900, 720, "Voyage Demo");
	SetTargetFPS(60);
	
	const int width = GetScreenWidth();
	const int height = GetScreenHeight();
	Sidebar sidebar = Sidebar_Init(width*0.25, height, DARKGRAY);
	ButtonOptions buttonOptions = (ButtonOptions){.centerText=1};
	Vector2 buttonPos = (Vector2){width/2, height/2};
	Button button = Button_Init(buttonPos, 200, BLACK,
								"Hello moto", buttonOptions);
	Element element = (Element){.type=BUTTON, .button=button};
	Sidebar_AddElement(&sidebar, &element);
	
	while (!WindowShouldClose()) {
		BeginDrawing();
		Sidebar_Draw(sidebar);
		/* Button_Draw(button); */
		ClearBackground(GRAY);
		EndDrawing();
	}
	CloseWindow();
	return 0;
}
