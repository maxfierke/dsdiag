/**********************************
  Copyright (C) Rick Wong (Lick)
  http://lickr.org
  http://licklick.wordpress.com/
  
  This code is licensed under GPL
***********************************/
#include "reboot.h"

#include <nds.h>
#include <sys/stat.h>


//====================================
#ifdef ARM9
//-----------------------------
#define DEVICE_MPCF        (0x4643504D)
#define DEVICE_MPSD        (0x4453504D)
#define DEVICE_M3CF        (0x4643334D)
#define DEVICE_M3SD        (0x4453334D)
#define DEVICE_SCCF        (0x46434353)
#define DEVICE_SCSD        (0x44534353)
#define DEVICE_SCLT        (0x544C4353)
//#define DEVICE_EFA2        (0x32414645)
//#define DEVICE_EZSD        (0x44535A45)
//#define DEVICE_g6fl        (0x6C663667) //"g6fl"
//#define DEVICE_G6FL        (0x4C463647) //"G6FL"
//#define DEVICE_DLMS        (0x534D4C44)
//-----------------------------
void reboot_prepare_default();
//-----------------------------
//void reboot_prepare_ez();
//-----------------------------
void reboot_prepare_m3();
//-----------------------------
void reboot_prepare_sc();
//----------------------------- G6 reset by Puyo
//void reboot_prepare_g6();
//-----------------------------
//void reboot_prepare_dlms();

//====================================
//-----------------------------
BOOL can_reboot() {
//-----------------------------
  struct stat st;
  stat("/.", &st);
  u32 device = st.st_dev;

  switch(device) {
    case DEVICE_MPCF:
    case DEVICE_MPSD:
    case DEVICE_M3CF:
    case DEVICE_M3SD:
    case DEVICE_SCCF:
    case DEVICE_SCSD:
    case DEVICE_SCLT: return true;
    //case DEVICE_EFA2:
    //case DEVICE_EZSD:
    //case DEVICE_g6fl:
    //case DEVICE_G6FL:
    //case DEVICE_DLMS: 
    default: return false;
  }
}

//-----------------------------
void reboot() {
//-----------------------------
  REG_IME = 0;
  REG_EXEMEMCNT = 0;

  struct stat st;
  stat("/.", &st);
  u32 device = st.st_dev;

  switch(device) {
    case DEVICE_MPCF: reboot_prepare_default();  break;
    case DEVICE_MPSD: reboot_prepare_default();  break;
    case DEVICE_M3CF: reboot_prepare_m3();       break;
    case DEVICE_M3SD: reboot_prepare_m3();       break;
    case DEVICE_SCCF: reboot_prepare_sc();       break;
    case DEVICE_SCSD: reboot_prepare_sc();       break;
    case DEVICE_SCLT: reboot_prepare_sc();       break;
    //case DEVICE_EFA2: reboot_prepare_ez();       break;
    //case DEVICE_EZSD: reboot_prepare_ez();       break;
    //case DEVICE_g6fl: reboot_prepare_g6();       break;
    //case DEVICE_G6FL: reboot_prepare_g6();       break;
    //case DEVICE_DLMS: reboot_prepare_dlms();     break;
    default:          reboot_prepare_default();  break;
  }

  *(vu32*)0x27FFFFC = 0;
  *(vu32*)0x27FFE04 = 0xE59FF018;
  *(vu32*)0x27FFE24 = 0x27FFE04;
  REG_EXEMEMCNT = 0xFFFF;
  swiSoftReset();
}

//-----------------------------
void reboot_custom(u32 arm7_entry) {
//-----------------------------
  REG_IME = 0;
  REG_EXEMEMCNT = 0;

  struct stat st;
  stat("/.", &st);
  u32 device = st.st_dev;

  switch(device) {
    case DEVICE_MPCF: reboot_prepare_default();  break;
    case DEVICE_MPSD: reboot_prepare_default();  break;
    case DEVICE_M3CF: reboot_prepare_m3();       break;
    case DEVICE_M3SD: reboot_prepare_m3();       break;
    case DEVICE_SCCF: reboot_prepare_sc();       break;
    case DEVICE_SCSD: reboot_prepare_sc();       break;
    case DEVICE_SCLT: reboot_prepare_sc();       break;
    //case DEVICE_EFA2: reboot_prepare_ez();       break;
    //case DEVICE_EZSD: reboot_prepare_ez();       break;
    //case DEVICE_g6fl: reboot_prepare_g6();       break;
    //case DEVICE_G6FL: reboot_prepare_g6();       break;
    //case DEVICE_DLMS: reboot_prepare_dlms();     break;
    default:          reboot_prepare_default();  break;
  }

  *(vu32*)0x27FFFF8 = arm7_entry;

  *(vu32*)0x27FFFFC = 0;
  *(vu32*)0x27FFE04 = 0xE59FF018;
  *(vu32*)0x27FFE24 = 0x27FFE04;
  REG_EXEMEMCNT = 0xFFFF;
  swiSoftReset();
}
//====================================
#endif


//====================================
#ifdef ARM7
//-----------------------------
BOOL need_reboot() {
//-----------------------------
  return (*(vu32*)0x27FFE24 == 0x27FFE04);
}

//-----------------------------
void reboot() {
//-----------------------------
  REG_IME = 0;

  *(vu32*)0x27FFE34 = *(vu32*)0x27FFFF8;
  swiSoftReset();
}
//====================================
#endif
