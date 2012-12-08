//Gfx converted using Mollusk's PAGfx Converter

//This file contains all the .h, for easier inclusion in a project

#ifndef ALL_GFX_H
#define ALL_GFX_H

#ifndef PAGfx_struct
    typedef struct{
    void *Map;
    int MapSize;
    void *Tiles;
    int TileSize;
    void *Palette;
    int *Info;
} PAGfx_struct;
#endif


// Sprite files : 
extern const unsigned char backon_Sprite[256] __attribute__ ((aligned (4))) ;  // Pal : sprite0_Pal
extern const unsigned char backoff_Sprite[256] __attribute__ ((aligned (4))) ;  // Pal : sprite1_Pal
extern const unsigned char fattest_Sprite[2048] __attribute__ ((aligned (4))) ;  // Pal : sprite2_Pal
extern const unsigned char gba_Sprite[2048] __attribute__ ((aligned (4))) ;  // Pal : sprite3_Pal
extern const unsigned char sram_Sprite[2048] __attribute__ ((aligned (4))) ;  // Pal : sprite4_Pal
extern const unsigned char ip_Sprite[2048] __attribute__ ((aligned (4))) ;  // Pal : sprite5_Pal
extern const unsigned char reset_Sprite[2048] __attribute__ ((aligned (4))) ;  // Pal : sprite6_Pal
extern const unsigned char help_Sprite[2048] __attribute__ ((aligned (4))) ;  // Pal : sprite7_Pal
extern const unsigned char sound_Sprite[2048] __attribute__ ((aligned (4))) ;  // Pal : sprite8_Pal
extern const unsigned char motionbuton_Sprite[2048] __attribute__ ((aligned (4))) ;  // Pal : sprite9_Pal
extern const unsigned char rumblebutton_Sprite[2048] __attribute__ ((aligned (4))) ;  // Pal : sprite10_Pal
extern const unsigned char mic_Sprite[2048] __attribute__ ((aligned (4))) ;  // Pal : sprite11_Pal
extern const unsigned char hbboot_Sprite[2048] __attribute__ ((aligned (4))) ;  // Pal : sprite12_Pal
extern const unsigned char right_Sprite[256] __attribute__ ((aligned (4))) ;  // Pal : sprite13_Pal
extern const unsigned char left_Sprite[256] __attribute__ ((aligned (4))) ;  // Pal : sprite14_Pal
extern const unsigned char finished_Sprite[2048] __attribute__ ((aligned (4))) ;  // Pal : sprite15_Pal

// Background files : 
extern const unsigned short topdsdiag_Bitmap[49152] __attribute__ ((aligned (4))) ;  // 16bit bitmap

extern const unsigned short bottomdsdiag_Bitmap[49152] __attribute__ ((aligned (4))) ;  // 16bit bitmap

extern const unsigned short compobottom_Bitmap[49152] __attribute__ ((aligned (4))) ;  // 16bit bitmap

extern const unsigned short compotop_Bitmap[49152] __attribute__ ((aligned (4))) ;  // 16bit bitmap

extern const unsigned short fatfail_Bitmap[49152] __attribute__ ((aligned (4))) ;  // 16bit bitmap

extern const unsigned short sramformat_Bitmap[49152] __attribute__ ((aligned (4))) ;  // 16bit bitmap

extern const unsigned short plzreset_Bitmap[49152] __attribute__ ((aligned (4))) ;  // 16bit bitmap

extern const unsigned short sramcorrect_Bitmap[49152] __attribute__ ((aligned (4))) ;  // 16bit bitmap

extern const unsigned short helpcrdit_Bitmap[49152] __attribute__ ((aligned (4))) ;  // 16bit bitmap

extern const unsigned short rumble_Bitmap[49152] __attribute__ ((aligned (4))) ;  // 16bit bitmap

extern const unsigned short norumble_Bitmap[49152] __attribute__ ((aligned (4))) ;  // 16bit bitmap

extern const unsigned short nodsmotion_Bitmap[49152] __attribute__ ((aligned (4))) ;  // 16bit bitmap

extern const unsigned short startrecord_Bitmap[49152] __attribute__ ((aligned (4))) ;  // 16bit bitmap

extern const unsigned short tdsplash_Bitmap[49152] __attribute__ ((aligned (4))) ;  // 16bit bitmap

extern const unsigned short dsmotion_Bitmap[49152] __attribute__ ((aligned (4))) ;  // 16bit bitmap

extern const unsigned short blank_Bitmap[49152] __attribute__ ((aligned (4))) ;  // 16bit bitmap

extern const unsigned short neo_Bitmap[49152] __attribute__ ((aligned (4))) ;  // 16bit bitmap

extern const unsigned short devsplash_Bitmap[49152] __attribute__ ((aligned (4))) ;  // 16bit bitmap

extern const unsigned short devsplash2_Bitmap[49152] __attribute__ ((aligned (4))) ;  // 16bit bitmap


// Palette files : 
extern const unsigned short sprite0_Pal[3] __attribute__ ((aligned (4))) ;
extern const unsigned short sprite1_Pal[3] __attribute__ ((aligned (4))) ;
extern const unsigned short sprite2_Pal[3] __attribute__ ((aligned (4))) ;
extern const unsigned short sprite3_Pal[3] __attribute__ ((aligned (4))) ;
extern const unsigned short sprite4_Pal[3] __attribute__ ((aligned (4))) ;
extern const unsigned short sprite5_Pal[3] __attribute__ ((aligned (4))) ;
extern const unsigned short sprite6_Pal[3] __attribute__ ((aligned (4))) ;
extern const unsigned short sprite7_Pal[3] __attribute__ ((aligned (4))) ;
extern const unsigned short sprite8_Pal[3] __attribute__ ((aligned (4))) ;
extern const unsigned short sprite9_Pal[8] __attribute__ ((aligned (4))) ;
extern const unsigned short sprite10_Pal[3] __attribute__ ((aligned (4))) ;
extern const unsigned short sprite11_Pal[8] __attribute__ ((aligned (4))) ;
extern const unsigned short sprite12_Pal[3] __attribute__ ((aligned (4))) ;
extern const unsigned short sprite13_Pal[3] __attribute__ ((aligned (4))) ;
extern const unsigned short sprite14_Pal[2] __attribute__ ((aligned (4))) ;
extern const unsigned short sprite15_Pal[8] __attribute__ ((aligned (4))) ;


#endif

