/**********************************
  Copyright (C) Rick Wong (Lick)
  http://lickr.org
  http://licklick.wordpress.com/

  This code is licensed under GPL
***********************************/
#ifndef __REBOOT_H
#define __REBOOT_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef BOOL
#define BOOL int
#endif

//====================================
#ifdef ARM9
//-----------------------------
BOOL can_reboot();
//-----------------------------
void reboot();
//-----------------------------
void reboot_custom(unsigned int arm7_entry);
//====================================
#endif


//====================================
#ifdef ARM7
//-----------------------------
BOOL need_reboot();
//-----------------------------
void reboot();
//====================================
#endif


#ifdef __cplusplus
}
#endif
 
#endif





