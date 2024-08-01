#include "export.h"

void buttonOnClick() {
	printf("Menu button clicked\n");
}

int main() {
	Voyage_Setup(900, 720, 60, "Voyage Demo", FLAG_WINDOW_RESIZABLE);
	Voyage_SetContentView("demo_xml_content_view.xml");
	
	Button *menuButton = Voyage_GetElementById("menu-button-1");
	menuButton->onClick = &buttonOnClick;
	
	Voyage_MainLoop();
	
	return 0;
}
