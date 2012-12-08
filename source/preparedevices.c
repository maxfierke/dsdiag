/**********************************
  Copyright (C) Rick Wong (Lick)
  http://lickr.org
  http://licklick.wordpress.com/

  This code is licensed under GPL
***********************************/
#include <nds.h>


//====================================
#ifdef ARM9
//-----------------------------
void reboot_prepare_default() {
//-----------------------------
  *(vu32*)0x27FFFF8 = 0x80000C0;
}

//-----------------------------
/*void reboot_prepare_ez() {
//-----------------------------
  *(vu16*)0x9FE0000 = 0xD200;
  *(vu16*)0x8000000 = 0x1500;
  *(vu16*)0x8020000 = 0xD200;
  *(vu16*)0x8040000 = 0x1500;
  *(vu16*)0x9880000 = (1<<15);
  *(vu16*)0x9FC0000 = 0x1500;
  *(vu32*)0x27FFFF8 = 0x80000C0;
}*/

//-----------------------------
void reboot_prepare_m3() {
//-----------------------------
  u32 mode = 0x00400004;
  vu16 tmp;
  tmp = *(vu16*)0x08E00002;
  tmp = *(vu16*)0x0800000E;
  tmp = *(vu16*)0x08801FFC;
  tmp = *(vu16*)0x0800104A;
  tmp = *(vu16*)0x08800612;
  tmp = *(vu16*)0x08000000;
  tmp = *(vu16*)0x08801B66;
  tmp = *(vu16*)(0x08000000 + (mode << 1));
  tmp = *(vu16*)0x0800080E;
  tmp = *(vu16*)0x08000000;
  tmp = *(vu16*)0x080001E4;
  tmp = *(vu16*)0x080001E4;
  tmp = *(vu16*)0x08000188;
  tmp = *(vu16*)0x08000188;
  *(vu32*)0x27FFFF8 = 0x80000C0;
}

//-----------------------------
void reboot_prepare_sc() {
//-----------------------------
  *(vu16*)0x09FFFFFE = 0xA55A;
  *(vu16*)0x09FFFFFE = 0xA55A;
  *(vu16*)0x09FFFFFE = 0;
  *(vu16*)0x09FFFFFE = 0;
  *(vu32*)0x27FFFF8 = 0x8000000;
}

//----------------------------- G6 reset by Puyo
/*void reboot_prepare_g6() {
//-----------------------------
  u32 mode = 0;
  vu16 tmp;
  tmp = *(vu16*)0x09000000;
  tmp = *(vu16*)0x09FFFFE0;
  tmp = *(vu16*)0x09FFFFEC;
  tmp = *(vu16*)0x09FFFFEC;
  tmp = *(vu16*)0x09FFFFEC;
  tmp = *(vu16*)0x09FFFFFC;
  tmp = *(vu16*)0x09FFFFFC;
  tmp = *(vu16*)0x09FFFFFC;
  tmp = *(vu16*)0x09FFFF4A;
  tmp = *(vu16*)0x09FFFF4A;
  tmp = *(vu16*)0x09FFFF4A;
  tmp = *(vu16*)(0x09200000 + (mode << 1));
  tmp = *(vu16*)0x09FFFFF0;
  tmp = *(vu16*)0x09FFFFE8;
  *(vu32*)0x27FFFF8 = 0x80000C0;
}*/

//-----------------------------
/*void reboot_prepare_dlms() {
//-----------------------------
  asm("MOV R10, #0");
  asm("MCR p15, 0, R10,c7,c5,0");
  asm("MCR p15, 0, R10,c7,c6,0");
  asm("MCR p15, 0, R10,c7,c10,4");
  asm("MCR p15, 0, R10,c3,c0,0");
  asm("MCR p15, 0, R10,c1,c0");

  *((vu8 *)0x40001A1) = 0xC0;
  *((vu32*)0x40001A8) = 0xEDEDDEDE;
  *((vu32*)0x40001AC) = 2 << 24;
  CARD_CR2 = 0xA0000000;
  while(CARD_CR2 & CARD_BUSY);

  *((vu32*)0x40001A8) = 0x100200A4;
  *((vu8 *)0x40001AC) = 0;
  CARD_CR2 = 0xAA000000;

  u32 data;
  u32 *dest = (u32*)0x2100000;
  u32 *target = dest + 1024;
  do {
  	if(CARD_CR2 & CARD_DATA_READY) {
  			data = CARD_DATA_RD;
  			if(dest < target)
       *dest = data;
  			dest++;
  	}
  } while(CARD_CR2 & CARD_BUSY);
  *(vu32*)0x27FFFF8 = 0x2100000;
}*/
//====================================
#endif
