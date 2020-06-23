#include "card.h"

// Metadata
MODULE_DESCRIPTION(
    "Cardio: a driver for the dummy \"Mfrc522\" iHaospace Kit RFID RC522, Module Carte de Lecteur MFRC-522 RF IC avec RFID Carte Puce Chip S50 13.56MHz pour Mifare Arduino Raspberry Pi device node");
MODULE_AUTHOR("Caproute <cap.route@freemail.bcd>");
MODULE_LICENSE("GPL v2");

// Init & Exit
module_init(cardio_init);
module_exit(cardio_exit);
