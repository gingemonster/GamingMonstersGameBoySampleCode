#include <gb/gb.h>
#include <gb/cgb.h>
#include <stdio.h>
#include "BackgroundData.h"
#include "BackgroundMap.h"

const UWORD backgroundpalette[] = 
{
    BackgroundDataCGBPal0c0,BackgroundDataCGBPal0c1,BackgroundDataCGBPal0c2,BackgroundDataCGBPal0c3,
    BackgroundDataCGBPal1c0,BackgroundDataCGBPal1c1,BackgroundDataCGBPal1c2,BackgroundDataCGBPal1c3,
    BackgroundDataCGBPal2c0,BackgroundDataCGBPal2c1,BackgroundDataCGBPal2c2,BackgroundDataCGBPal2c3,
    BackgroundDataCGBPal3c0,BackgroundDataCGBPal3c1,BackgroundDataCGBPal3c2,BackgroundDataCGBPal3c3,
}; 

void main(){
    set_bkg_palette(0, 4, &backgroundpalette[0]); 

    // set background data
    set_bkg_data(0, 6, BackgroundData);

    // switch to 2nd video memory bank
    VBK_REG = 1; 

    // set background color palette map, do this first
    set_bkg_tiles(0, 0, BackgroundMapWidth, BackgroundMapHeight, BackgroundMapPLN1); 

    // switch back to 1st video memory bank
    VBK_REG = 0; 

    // set background map
    set_bkg_tiles(0, 0, BackgroundMapWidth, BackgroundMapHeight, BackgroundMapPLN0);    
    
    
    SHOW_BKG;
    DISPLAY_ON;

    while(1){

    }
}