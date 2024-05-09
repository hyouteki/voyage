#include <stdio.h>
#include <math.h>
#include "raylib/include/raylib.h"
#include "voyage/export.h"

int main() {
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(900, 720, "Voyage Demo");
	SetTargetFPS(60);
	
	int width = GetScreenWidth(), height = GetScreenHeight();
	Sidebar sidebar = Sidebar_Init((Vector2){width, height}, Voyage_LightBlue);
	Sidebar_AddElement(&sidebar, &Button_EleInit(Vector2Dummy, 0, "Menu button 1"));	
	Sidebar_AddElement(&sidebar, &Button_EleInit(Vector2Dummy, 0, "Menu button 2"));
	
	while (!WindowShouldClose()) {
		width = GetScreenWidth(), height = GetScreenHeight();
		Sidebar_Resize(&sidebar, (Vector2){width, height});
		
		BeginDrawing();
		Sidebar_Draw(sidebar);
		ClearBackground(Voyage_Blue);
		EndDrawing();
	}
	CloseWindow();
	
	return 0;
}
