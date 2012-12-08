// lib Includes
#include <PA9.h>      
#include <nds.h>
#include <fat.h>
#include <sys/dir.h>
#include <sys/unistd.h>
#include <stdio.h>
#include <nds/arm9/rumble.h>
#include <nds/arm9/console.h>
#include <stdlib.h>
#include <malloc.h>

// Data Includes
#include "gfx/all_gfx.h"
#include "gfx/all_gfx.c"
#include "scifi1.h"
#include "click.h"

// Code Includes
#ifdef __cplusplus // Reset.h
extern "C" { 
#endif 

#include "reboot.h" 

#ifdef __cplusplus 
} 
#endif

#include "bootgba.h"
#include "file.h"


// Variables and Defines
#define RUMBLE_PAK (*(vuint16 *)0x08000000)
int ndsmotion = 0;
u8 MicData[100000]; 
char string[20]; 
char text[200];
FILE *romfile;
int choosingfile = 1;


// Functions
void sramtest(void);
void fattest(void);
void page1(void);
void page2(void);
void splashNow(void);
void hdw_init(void);
void pageturnL(void);
void pageturnR(void);
void externFunction(void);
void backIn(void);
void neo(void);
void devfr(void);
int FileChoose()
{
	consoleClear();
	romfile=NULL;

	romfile==loadFile();

	if(romfile == NULL) {
		return 0; // we didn't get a file
	}
	else {
		return 1; // we got a file
	}
}	


// Function: main()
int main(int argc, char ** argv)
{
	PA_Init();    
	PA_InitVBL(); 
	
	PA_InitWifi(); 
	PA_InitSound(); 	
	
	fatInitDefault(); 
	
	PA_Init16bitBg(0, 3);
	PA_Init16bitBg(1, 3);
	
	PA_SetBrightness(0, -31); 
	PA_SetBrightness(1, -31); 	
	
	
	PA_Load16bitBitmap(1, compotop_Bitmap); 
	PA_Load16bitBitmap(0, compobottom_Bitmap); 

	s8 i;
	
	for(i = -31; i <= 0; i++){
		PA_SetBrightness(0, i); 
		PA_SetBrightness(1, i); 
		PA_WaitForVBL();		   
	}   

	s16 time = 180; 
	while(time && (!Pad.Newpress.Anykey) && (!Stylus.Newpress)){ 
		time--; 
		PA_WaitForVBL();
	}		
	
	
	for(i = 0; i > -32; i--){
		PA_SetBrightness(0, i); 
		PA_SetBrightness(1, i); 
		PA_WaitForVBL();		   
	}  	


	
	PA_ResetBgSys();
	PA_SetBrightness(0, 0); 
	PA_SetBrightness(1, 0);

	devfr();
	neo();
	
	
	splashNow();
	
	FILE* testWrite = fopen ("results.txt", "w"); 
	fwrite("                          ", 30, 1, testWrite);
	fclose(testWrite);	
	

	PA_Init16bitBg(0, 3);
	PA_Init16bitBg(1, 3);
	
	PA_InitText(1, 0);
	PA_InitText(0, 0);
	
	PA_InitSpriteExtPrio(1); // Enable extended priorities
	
	PA_SetTextCol(0, 255, 0, 0);
	PA_SetTextCol(1, 255, 0, 0);
	
	
	
	page1();

	
	PA_PlaySimpleSound(0, scifi1);
	
	
	while (1)
	{
	
	
		
		
		
		PA_OutputText(0, 24, 1, "%02d:%02d", PA_RTC.Hour, PA_RTC.Minutes);
		
		
		if (PA_SpriteTouched(1)) {
			PA_PlaySimpleSound(0, click);
			PA_SetScreenLight(0, 0); 
			PA_SetScreenLight(1, 0); 
			
		}	
		
		if (PA_SpriteTouched(0)) {
			PA_PlaySimpleSound(0, click);
			PA_SetScreenLight(0, 1);
			PA_SetScreenLight(1, 1); 
			
		}								
		
		if (PA_SpriteTouched(2)) {
			PA_PlaySimpleSound(0, click);
			PA_WaitForVBL();
			fattest();
		}	
		
		if (PA_SpriteTouched(3)) {
			PA_PlaySimpleSound(0, click);

			PA_WaitForVBL();
			
			
			
			
			
			REG_IPC_FIFO_CR = IPC_FIFO_ENABLE | IPC_FIFO_SEND_CLEAR;
			REG_IPC_FIFO_TX = 26;
			
			BootGBA();
			
			
			
		}	
		
		if (PA_SpriteTouched(4)) {
			PA_PlaySimpleSound(0, click);
			sramtest();
		}	
		
		
		if (PA_SpriteTouched(5)) {
			PA_PlaySimpleSound(0, click);
			PA_ConnectWifiWFC();
			char *buffer2 = malloc(256*256);
			PA_GetHTTP(buffer2,"http://teendev.789mb.com/ip.php3");
				
			PA_OutputText(0, 10, 21, "%s",buffer2);
		}
		
		if (PA_SpriteTouched(6)) {
			PA_PlaySimpleSound(0, click);
			if(can_reboot())
				reboot();
		}

		if (PA_SpriteTouched(7)) {
			PA_PlaySimpleSound(0, click);
			PA_Load16bitBitmap(1, helpcrdit_Bitmap);
		}	
		
		if (PA_SpriteTouched(8)) {
			PA_PlaySimpleSound(0, scifi1);  
		}
			
		if (PA_SpriteTouched(9)) {
			PA_PlaySimpleSound(0, click);
			
			PA_MotionInit();
			
			if ( !PA_CheckDSMotion()) {
				PA_Load16bitBitmap(1, nodsmotion_Bitmap);
				FILE* testWrite = fopen ("results.txt", "a"); 
				fwrite("Motion TEST Failed!\n", 30, 1, testWrite);
				fclose(testWrite);
			}	
			else {
				PA_Load16bitBitmap(1, dsmotion_Bitmap);
				FILE* testWrite = fopen ("results.txt", "a"); 
				fwrite("Motion TEST Successful!\n", 30, 1, testWrite);
				fclose(testWrite);
			}	
			
		}	
			
		if (PA_SpriteTouched(10)) {
			PA_PlaySimpleSound(0, click);
			if(	isRumbleInserted() == true) {
				PA_Load16bitBitmap(1, rumble_Bitmap);
				FILE* testWrite = fopen ("results.txt", "a"); 
				fwrite("\nRumble TEST Successful!\n", 30, 1, testWrite);
				fclose(testWrite);
			}	
			if( isRumbleInserted() == false) {	
				PA_Load16bitBitmap(1, norumble_Bitmap);
				FILE* testWrite = fopen ("results.txt", "a"); 
				fwrite("Rumble TEST Failed!\n", 30, 1, testWrite);
				fclose(testWrite);
			}	
		}	
		
		if (PA_SpriteTouched(11)) {
			PA_PlaySimpleSound(0, click);
			
			 

			PA_Load16bitBitmap(1, startrecord_Bitmap);
			
			while (!Pad.Newpress.A) { 
				PA_MicGetVol();
			}

			while (!Pad.Newpress.B) { 
				PA_MicGetVol();
			}
							
			if (Pad.Newpress.A) {
				PA_MicStartRecording(MicData, 100000);  // Buffer, buffer length
			}

			// If B, replay recorded sound
			if(Pad.Newpress.B) {
				PA_MicReplay(0, MicData, 100000);   // Channel, buffer used, buffer length
				
			}
			
				
				
		}	
		
		if (PA_SpriteTouched(12)) {
			PA_PlaySimpleSound(0, click);
			
			
			PA_ResetBgSys();
			PA_ResetSpriteSys();
			
			externFunction();
			
			backIn();
			
			hdw_init();
			
			//struct stat st;
			
			//char filename[256];
			
			
			iprintf("\x1b[2J");
		
				// Wait two VBlanks as instructed in the FAT docs
			PA_WaitForVBL();
			PA_WaitForVBL();
		
			chdir("/");
			FileChoose();
			
			
			
			
		}
		
		if(PA_SpriteTouched(13)) {
			PA_PlaySimpleSound(0, click);
			pageturnR();
			
			page2();
			backIn();
		}

		if(PA_SpriteTouched(14)) {
			PA_PlaySimpleSound(0, click);
			pageturnL();
			
			page1();
			backIn();
			
		}	
		
		if(PA_SpriteTouched(15)) {
			PA_PlaySimpleSound(0, click);
			PA_WaitForVBL();
			IPC->aux |= BIT(6);
		}	
		
		
		if (Pad.Newpress.R) {
			
			
			
			pageturnR();
			
			page2();
			backIn();
		}	
		if (Pad.Newpress.L) {
			
			
			
			pageturnL();
			
			page1();
			backIn();
			
		}	
	
		PA_CheckLid();	
		
		PA_WaitForVBL();
	}
	
	return 0;
} // End of main()

void sramtest(void) {
	
	
	PA_LoadData(1, 
			string, 
			20);  
	
	
	
	if (!PA_CompareText(string, "DSdiag waz here")){
		
		PA_Load16bitBitmap(1, sramformat_Bitmap);
		
		while (!Pad.Newpress.A) { 
			PA_WaitForVBL();
		}
		
		PA_SaveData(1, (void*)Blank, 30000); 
		
		
		PA_SaveString(1, "DSdiag waz here");
		
		
		PA_Save8bit(21, 
					PA_RTC.Hour);
		PA_Save8bit(22, PA_RTC.Minutes);
		
		PA_Load16bitBitmap(1, plzreset_Bitmap);
		
		FILE* testWrite = fopen ("results.txt", "a"); 
		fwrite("SRAM Test Successful!\n", 30, 1, testWrite);
		fclose(testWrite);
		
		if (Pad.Newpress.Start) {
			if(can_reboot())
				reboot();
			
		}	
	}
	else{ 
		PA_Load16bitBitmap(1, sramcorrect_Bitmap);
		
		if (Pad.Newpress.Start) {
			if(can_reboot())
				reboot();
			
			
		}	
	}	
}	
	

void fattest(void) {
	PA_ClearTextBg(1);
	PA_ClearTextBg(0);
	
	PA_ResetSpriteSysScreen(0);
	
	externFunction();
	
	backIn();
	
	PA_ResetBgSys();
	
	PA_InitText(1, 0);
	PA_InitText(0, 0);
	
	
	
	PA_SetTextCol(0, 255, 0, 0);
	PA_SetTextCol(1, 255, 0, 0);

		
		

	int linenumber =0; 
	int screen = 1;

	struct stat st;
	char filename[256];
	DIR_ITER* dir = diropen("/");

	if (dir == NULL) 
	{
		page1();
		PA_Load16bitBitmap(1, fatfail_Bitmap);
		
	} 
	else 
	while (dirnext(dir, filename, &st) == 0) 
	{
	   if (linenumber ==24) 
		{ 
		   screen=0; 
		   linenumber = 0; 
		}   
		FILE* testWrite = fopen ("results.txt", "a"); 
		fwrite("FAT TEST Successful!\n", 30, 1, testWrite);
		fclose(testWrite);


		PA_OutputText(screen,0,linenumber, "%02d%s: %s\n", linenumber, (st.st_mode & S_IFDIR ? "D" : "-"), filename);
		linenumber++;
		
	}
	
	while (1)
	{ 
		if (Pad.Newpress.Start) {
			
			if(can_reboot())
				reboot();
				
			
			
		}	
	
		
	}
}





void page1(void) {

	
	
	PA_ResetSpriteSysScreen(0);
	
	PA_Init16bitBg(0, 3);
	PA_Init16bitBg(1, 3);
	
	PA_InitText(1, 0);
	PA_InitText(0, 0);
	
	
	
	PA_SetTextCol(0, 255, 0, 0);
	PA_SetTextCol(1, 255, 0, 0);
	
	PA_OutputText(0, 8, 1, "Hello, %s", PA_UserInfo.Name);
		
		
	
		
	
	
	PA_Load16bitBitmap(1, topdsdiag_Bitmap);
	PA_Load16bitBitmap(0, bottomdsdiag_Bitmap);
	
	PA_LoadSpritePal(0, 0, (void*)sprite0_Pal);
	
	PA_CreateSprite(0, 0, (void*)backon_Sprite, OBJ_SIZE_16X16, 1, 0, 18, 0);	

	PA_LoadSpritePal(0, 1, (void*)sprite1_Pal);
	
	PA_CreateSprite(0, 1, (void*)backoff_Sprite, OBJ_SIZE_16X16, 1, 1, 0, 0);
	
	PA_LoadSpritePal(0, 2, (void*)sprite2_Pal);
	
	PA_CreateSprite(0, 2, (void*)fattest_Sprite, OBJ_SIZE_64X32, 1, 2, 20, 24);
	
	PA_LoadSpritePal(0, 3, (void*)sprite3_Pal);
	
	PA_CreateSprite(0, 3, (void*)gba_Sprite, OBJ_SIZE_64X32, 1, 3, 20, 64);
	
	PA_LoadSpritePal(0, 4, (void*)sprite4_Pal);
	
	PA_CreateSprite(0, 4, (void*)sram_Sprite, OBJ_SIZE_64X32, 1, 4, 104, 24);
	
	PA_LoadSpritePal(0, 5, (void*)sprite5_Pal);
	
	PA_CreateSprite(0, 5, (void*)ip_Sprite, OBJ_SIZE_64X32, 1, 5, 104, 64);
	
	PA_LoadSpritePal(0, 7, (void*)sprite7_Pal);
	
	PA_CreateSprite(0, 7, (void*)help_Sprite, OBJ_SIZE_64X32, 1, 6, 20, 104);
	
	PA_LoadSpritePal(0, 6, (void*)sprite6_Pal);
	
	PA_CreateSprite(0, 6, (void*)reset_Sprite, OBJ_SIZE_64X32, 1, 7, 104, 104);
	
	PA_LoadSpritePal(0, 8, (void*)sprite8_Pal);
	
	PA_CreateSprite(0, 8, (void*)sound_Sprite, OBJ_SIZE_64X32, 1, 8, 184, 24);
	
	PA_LoadSpritePal(0, 9, (void*)sprite9_Pal);

	PA_CreateSprite(0, 9, (void*)motionbuton_Sprite, OBJ_SIZE_64X32, 1, 9, 184, 64);
	
	PA_LoadSpritePal(0, 10, (void*)sprite10_Pal);
	
	PA_CreateSprite(0, 10, (void*)rumblebutton_Sprite, OBJ_SIZE_64X32, 1, 10, 184, 104);
	
	PA_LoadSpritePal(0, 13, (void*)sprite13_Pal);
	
	PA_CreateSprite(0, 13, (void*)right_Sprite, OBJ_SIZE_16X16, 1, 13, 196, 140);
	
	PA_LoadSpritePal(0, 15, (void*)sprite15_Pal);
	
	PA_CreateSprite(0, 15, (void*)finished_Sprite, OBJ_SIZE_64X32, 1, 15, 104, 136);
	
		

}	

void page2(void) {

	
	
	PA_ResetBgSys();
	
	PA_Init16bitBg(0, 3);
	PA_Init16bitBg(1, 3);
	
	PA_InitText(1, 0);
	PA_InitText(0, 0);
	
	
	
	PA_SetTextCol(0, 255, 0, 0);
	PA_SetTextCol(1, 255, 0, 0);
	
	PA_OutputText(0, 8, 1, "Hello, %s", PA_UserInfo.Name);
	
	
	PA_Load16bitBitmap(1, topdsdiag_Bitmap);
	PA_Load16bitBitmap(0, blank_Bitmap);
	
	PA_LoadSpritePal(0, 11, (void*)sprite11_Pal);
	
	PA_CreateSprite(0, 11, (void*)mic_Sprite, OBJ_SIZE_64X32, 1, 11, 20, 24);
	
	PA_LoadSpritePal(0, 12, (void*)sprite12_Pal);
	
	PA_CreateSprite(0, 12, (void*)hbboot_Sprite, OBJ_SIZE_64X32, 1, 12, 104, 24);
	
	PA_LoadSpritePal(0, 14, (void*)sprite14_Pal);
	
	PA_CreateSprite(0, 14, (void*)left_Sprite, OBJ_SIZE_16X16, 1, 14, 25, 140);
	
	PA_LoadSpritePal(0, 15, (void*)sprite15_Pal);
	
	PA_CreateSprite(0, 15, (void*)finished_Sprite, OBJ_SIZE_64X32, 1, 15, 104, 136);
	
}

void splashNow(void) {

	PA_Init16bitBg(0, 3);
	PA_Init16bitBg(1, 3);
	
	PA_SetBrightness(0, -31); 
	PA_SetBrightness(1, -31); 
	
	
	PA_Load16bitBitmap(1, tdsplash_Bitmap); 
	PA_Load16bitBitmap(0, tdsplash_Bitmap); 

	s8 i;
	
	for(i = -31; i <= 0; i++){
		PA_SetBrightness(0, i); 
		PA_SetBrightness(1, i); 
		PA_WaitForVBL();		   
	}   

	s16 time = 180;
	while(time && (!Pad.Newpress.Anykey) && (!Stylus.Newpress)){ 
		time--; 
		PA_WaitForVBL();
	}		
	
	
	for(i = 0; i > -32; i--){
		PA_SetBrightness(0, i); 
		PA_SetBrightness(1, i); 
		PA_WaitForVBL();		   
	}  	

	
	
	
	PA_ResetBgSys();
	PA_SetBrightness(0, 0); 
	PA_SetBrightness(1, 0);
	backIn();

	
}	

void hdw_init(void) {
	powerON(POWER_ALL);

	videoSetMode(MODE_5_2D | DISPLAY_BG3_ACTIVE);

	// Set up the sub screen
	videoSetModeSub(MODE_5_2D | DISPLAY_BG0_ACTIVE);

	vramSetMainBanks(VRAM_A_MAIN_BG, VRAM_B_MAIN_BG, VRAM_C_SUB_BG , VRAM_D_LCD);
	
	SUB_BG0_CR = BG_MAP_BASE(31);

	// Set the colour of the font to White.
	BG_PALETTE_SUB[255] = RGB15(31,31,31);

	consoleInitDefault((u16*)SCREEN_BASE_BLOCK_SUB(31), (u16*)CHAR_BASE_BLOCK_SUB(0), 16);
}

void pageturnR(void) {

	s8 i;
	
	PA_ResetSpriteSysScreen(0);
	
	PA_InitBgTrans(0); // Init BgTransition system, uses background 0 but little memory...
	// If you want it to hide your sprites, set your sprites' priorities to 1 or more...
	PA_InitBgTrans(1);
	
	for (i = 0; i <= TRANS_LENGTH; i++) { // Fade length...
		PA_BgTransLeftRight(0, // screen
					  0, // fade type, from 0 to 4, test them out !
					  0, // horizontal flip
					  i); // Time, 0 being the screen completely visible, 32 completely out

		PA_BgTransLeftRight(1, // screen
					  0, // fade type, from 0 to 4, test them out !
					  0, // horizontal flip
					  i); // Time, 0 being the screen completely visible, 32 completely out
		PA_WaitForVBL(); // To slow down the fades, we wait a frame...
	}
	
}

void pageturnL(void) {

	s8 i;
	
	
	PA_ResetSpriteSysScreen(0);
	
	PA_InitBgTrans(0); // Init BgTransition system, uses background 0 but little memory...
	// If you want it to hide your sprites, set your sprites' priorities to 1 or more...
	PA_InitBgTrans(1);
	
	for (i = 0; i <= TRANS_LENGTH; i++) { // Fade length...
		PA_BgTransLeftRight(0, // screen
					  0, // fade type, from 0 to 4, test them out !
					  1, // horizontal flip
					  i); // Time, 0 being the screen completely visible, 32 completely out
		
		PA_BgTransLeftRight(1, // screen
					  0, // fade type, from 0 to 4, test them out !
					  1, // horizontal flip
					  i); // Time, 0 being the screen completely visible, 32 completely out
		PA_WaitForVBL(); // To slow down the fades, we wait a frame...
	}
	
}

void externFunction(void) {

	s8 i;
			
			// First we fade out... to fade out, move the time from 0 to 32, 32 included !
	for (i = 0; i <= 32; i++) {
		PA_WindowFade(0, // screen
					0, // fade type, from 0 to 7, test them out !
					i); // Time, 0 being the screen completely visible, 32 completely out
	
		PA_WindowFade(1, // screen
					0, // fade type, from 0 to 7, test them out !
					i); // Time, 0 being the screen completely visible, 32 completely out
		PA_WaitForVBL(); // To slow down the fades, we wait a frame...
	}
	
	
	
}

void backIn(void) {

	s8 i;
	
	for (i = 32; i >= 0; i--) {
		PA_WindowFade(0, 0, i);
		PA_WindowFade(1, 0, i);
		PA_WaitForVBL(); // To slow down the fades, we wait a frame...
	
	
	}
}

void neo(void) {
	
	PA_Init16bitBg(0, 3);
	PA_Init16bitBg(1, 3);
	
	PA_SetBrightness(0, -31); 
	PA_SetBrightness(1, -31); 	
	
	
	PA_Load16bitBitmap(1, neo_Bitmap); 
	PA_Load16bitBitmap(0, neo_Bitmap); 

	s8 i;
	
	for(i = -31; i <= 0; i++){
		PA_SetBrightness(0, i); 
		PA_SetBrightness(1, i); 
		PA_WaitForVBL();		   
	}   

	s16 time = 180; 
	while(time && (!Pad.Newpress.Anykey) && (!Stylus.Newpress)){ 
		time--; 
		PA_WaitForVBL();
	}		
	
	
	for(i = 0; i > -32; i--){
		PA_SetBrightness(0, i); 
		PA_SetBrightness(1, i); 
		PA_WaitForVBL();		   
	}  	


	
	PA_ResetBgSys();
	PA_SetBrightness(0, 0); 
	PA_SetBrightness(1, 0); 


}



void devfr(void) {

	PA_Init16bitBg(0, 3);
	PA_Init16bitBg(1, 3);
	
	PA_SetBrightness(0, -31); 
	PA_SetBrightness(1, -31); 	
	
	
	PA_Load16bitBitmap(1, devsplash_Bitmap); 
	PA_Load16bitBitmap(0, devsplash2_Bitmap); 

	s8 i;
	
	for(i = -31; i <= 0; i++){
		PA_SetBrightness(0, i); 
		PA_SetBrightness(1, i); 
		PA_WaitForVBL();		   
	}   

	s16 time = 180; 
	while(time && (!Pad.Newpress.Anykey) && (!Stylus.Newpress)){ 
		time--; 
		PA_WaitForVBL();
	}		
	
	
	for(i = 0; i > -32; i--){
		PA_SetBrightness(0, i); 
		PA_SetBrightness(1, i); 
		PA_WaitForVBL();		   
	}  	


	
	PA_ResetBgSys();
	PA_SetBrightness(0, 0); 
	PA_SetBrightness(1, 0); 
}	


