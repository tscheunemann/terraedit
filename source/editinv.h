#include <iostream>

void editInventory(Handle fileHandle, int inventorySlotNumber, int itemID);
void maxStats(Handle fileHandle);
void editInventoryHandler(int inventorySlotNumber);
void editQuantity(Handle fileHandle, int inventorySlotNumber, int quantityInput);
void editQuantityHandler(int inventorySlotNumber);
void editModifier(Handle fileHandle, int inventorySlotNumber, int modifierInput);
void editModifierHandler(int inventorySlotNumber);
int keypadInput();
