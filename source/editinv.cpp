#include <iostream>
#include <fstream>
#include <stdio.h>
#include <3ds.h>
#include "editinv.h"
#include "fs.h"
#include <map>

std::map<int, int> inventoryOffsets = {
    {1, 0x56},
    {2, 0x5b},
    {3, 0x60},
    {4, 0x65},
    {5, 0x6a},
    {6, 0x6f},
    {7, 0x74},
    {8, 0x79},
    {9, 0x7e},
    {10, 0x83},
    {11, 0x88},
    {12, 0x8d},
    {13, 0x92},
    {14, 0x97},
    {15, 0x9c},
    {16, 0xa1},
    {17, 0xa6},
    {18, 0xab},
    {19, 0xb0},
    {20, 0xb5},
    {21, 0xba},
    {22, 0xbf},
    {23, 0xc4},
    {24, 0xc9},
    {25, 0xce},
    {26, 0xd3},
    {27, 0xd8},
    {28, 0xdd},
    {29, 0xe2},
    {30, 0xe7},
    {31, 0xec},
    {32, 0xf1},
    {33, 0xf6},
    {34, 0xfb},
    {35, 0x100},
    {36, 0x105},
    {37, 0x122},
    {38, 0x127},
    {39, 0x12c},
    {40, 0x131}
};

void editInventory(Handle fileHandle, int inventorySlotNumber, int itemID) {

    if (itemID < 255) {
        int itemWhitespaceOffset = inventoryOffsets[inventorySlotNumber] + 0x01;
        uint8_t itemWhitespace = 0x00;
		uint8_t itemID8 = (uint8_t)itemID;
		FSFILE_Write( fileHandle, NULL, inventoryOffsets[inventorySlotNumber], &itemID8, sizeof(itemID8), NULL );
        FSFILE_Write( fileHandle, NULL, itemWhitespaceOffset, &itemWhitespace, sizeof(itemWhitespace), NULL );
	}
	else {
		uint16_t itemID16 = (uint16_t)itemID;
		FSFILE_Write( fileHandle, NULL, inventoryOffsets[inventorySlotNumber], &itemID16, sizeof(itemID16), NULL );

	} 
}

void editQuantity(Handle fileHandle, int inventorySlotNumber, int quantityInput) {

	int quantityOffset = inventoryOffsets[inventorySlotNumber] + 0x02;
	FSFILE_Write( fileHandle, NULL, quantityOffset, &quantityInput, sizeof(quantityInput), NULL );
	
}

void editModifier(Handle fileHandle, int inventorySlotNumber, int modifierInput) {

    int modifierOffset = inventoryOffsets[inventorySlotNumber] + 0x04;
    FSFILE_Write( fileHandle, NULL, modifierOffset, &modifierInput, sizeof(modifierInput), NULL );

}

void maxStats(Handle fileHandle) {
    
    uint16_t maxHealth = 0x0190;
    uint8_t maxMana = 0xc8;
    int healthOffset = 0x14;
    int manaOffset = 0x18;

    FSFILE_Write( fileHandle, NULL, healthOffset, &maxHealth, sizeof(maxHealth), NULL );
    FSFILE_Write( fileHandle, NULL, manaOffset, &maxMana, sizeof(maxMana), NULL );

    printf("\x1b[30Done!\n");
}

int keypadInput() {
	static SwkbdState swkbd;
	char inputBuffer[60];
	int returnInput;
	SwkbdButton button = SWKBD_BUTTON_NONE;
	swkbdInit(&swkbd, SWKBD_TYPE_NUMPAD, 1, 4);
	swkbdSetValidation(&swkbd, SWKBD_ANYTHING, 0, 0);
	swkbdSetFeatures(&swkbd, SWKBD_FIXED_WIDTH);
	button = swkbdInputText(&swkbd, inputBuffer, sizeof(inputBuffer));

	if (button != SWKBD_BUTTON_NONE) {
		returnInput = atoi(inputBuffer);
		return atoi(inputBuffer);
	}
}

void editInventoryHandler(int inventorySlotNumber) {

	OpenArchiveFile savefile;
    const char *saveFileLocation = "/rando.p";
    savefile.openSaveFile(saveFileLocation);
	int itemID = keypadInput();
	editInventory(savefile.fileHandle, inventorySlotNumber, itemID);
	savefile.destroyArchive();
		
}

void editQuantityHandler(int inventorySlotNumber) {

    OpenArchiveFile savefile;
    const char *saveFileLocation = "/rando.p";
    savefile.openSaveFile(saveFileLocation);
    int itemQuantityNumber = keypadInput();
    editQuantity(savefile.fileHandle, inventorySlotNumber, itemQuantityNumber);
    savefile.destroyArchive();
}

void editModifierHandler(int inventorySlotNumber) {

    OpenArchiveFile savefile;
    const char *saveFileLocation = "/rando.p";
    savefile.openSaveFile(saveFileLocation);
	int itemModifierNumber = keypadInput();
	editModifier(savefile.fileHandle, inventorySlotNumber, itemModifierNumber);
	savefile.destroyArchive();

}