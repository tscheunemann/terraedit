#include <stdio.h>
#include <string.h>
#include <3ds.h>
#include <fstream>
#include <stdlib.h>
#include "editinv.h"
#include "menu.h"

int main(int argc, char** argv)
{

	// Initialize services
	gfxInitDefault();
	cfguInit();

	// Init console for text output
	PrintConsole topScreen, bottomScreen;
	consoleInit(GFX_TOP, &topScreen);
	consoleInit(GFX_BOTTOM, &bottomScreen);

	consoleSelect(&topScreen);
	printf("Terraria Inventory Editor - by \033[0;35mlando\033[0m\n");
	printf("\x1b[30;16HPress Start to exit.");

	consoleSelect(&bottomScreen);

	Menu menu;
	menu.inventoryMenu();
	// Exit services
	cfguExit();
	gfxExit();
}
