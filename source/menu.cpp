#include <iostream>
#include <fstream>
#include <stdio.h>
#include <3ds.h>
#include "editinv.h"
#include "menu.h"

typedef void(*editFunctions)(int counter);

void Menu::inventoryMenu() {
    
	int counter = 1;
	int arrow = 0;
	int update_counter = 1;
	char buffer [33];

    const char* menuOptions[3] = {"Edit inventory slot", "Edit quantity", "Edit modifier"};
	editFunctions functions[] = {
		editInventoryHandler,
		editQuantityHandler,
		editModifierHandler,
	};

	while(aptMainLoop()) {
		gspWaitForVBlank();
		hidScanInput();

		u32 kDown = hidKeysDown();

        if (kDown & KEY_RIGHT) {
			update_counter = 1;
			counter++;
			if (counter >= 40) {
				counter = 40;
			}
		}

		if (kDown & KEY_LEFT) {
		    update_counter = 1;
		    counter--;
		    if (counter <= 1) {
		    	counter = 1;
			}
		}

		if (kDown & KEY_DOWN) {
			update_counter = 1;
			arrow++;
			if (arrow >= 2) {
				arrow = 2;
			}
		}

		if (kDown & KEY_UP) {
			update_counter = 1;
			arrow--;
			if (arrow <= 0) {
				arrow = 0;
			}
		}

		if (kDown & KEY_A) {
			functions[arrow](counter);
		}

		if (kDown & KEY_START) {
			break;
		}

		if (update_counter) {
			itoa(counter, buffer, 10);
			consoleClear();
			update_counter = 0;
			printf("Editing inventory space %s", buffer);
			for (int i = 0; i < 3; i++) {
			
				if (arrow == i) {
					printf("\n> %s", menuOptions[i]);
				}
				else {
					printf("\n%s", menuOptions[i]);
				}
			}
		}

		gfxFlushBuffers();
		gfxSwapBuffers();
	}
	cfguExit();
	gfxExit();
}
