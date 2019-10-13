#include <gb/gb.h>
#include "parallax_background_data.c"
#include "parallax_background_map.c"
UINT16 backgroundoffset1x;
UINT16 backgroundoffset2x;
UINT16 backgroundoffset3x;

void interuptLCD(){
    switch(LYC_REG){
        case 0x00: // at top
            move_bkg(backgroundoffset1x,0);
            disable_interrupts();
            LYC_REG = 0x35;
            enable_interrupts();
            break;        
        case 0x35: // at mountains
            move_bkg(backgroundoffset2x,0);
            LYC_REG = 0x6c;
            break;
        case 0x6c: // at trees
            
            move_bkg(backgroundoffset3x,0);
            LYC_REG = 0x00;
            break;
    }
}

void performantdelay(UINT8 numloops){
    UINT8 i;
    for(i = 0; i < numloops; i++){
        wait_vbl_done();
    }     
}

void main(){
    backgroundoffset1x = 0;
    backgroundoffset2x = 0;
    backgroundoffset3x = 0;

    set_bkg_data(0, 189, parallax_background_data);
    set_bkg_tiles(0, 0, 32, 18, parallax_background_map);

    STAT_REG = 0x45; // enable LYC=LY interrupt so that we can set a specific line it will fire att
    LYC_REG = 0x00;  // first fire LCD Interupt on the 1st scan line    

    disable_interrupts();
    add_LCD(interuptLCD);
    enable_interrupts();
    
    set_interrupts(VBL_IFLAG | LCD_IFLAG);
    SHOW_BKG;
    DISPLAY_ON;

    while(1){
        backgroundoffset1x += 1;
        backgroundoffset2x += 2;
        backgroundoffset3x += 10;

        performantdelay(7);
    }
}