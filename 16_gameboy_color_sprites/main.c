#include <gb/gb.h>
#include <gb/cgb.h> 
#include <stdio.h>
#include "sprites.h"

const UWORD backgroundpalette[] = {
    RGB_DARKGRAY, RGB_DARKGRAY, RGB_DARKGRAY, RGB_DARKGRAY
};

const UWORD spritepalette[] = {
    spritesCGBPal0c0,
    spritesCGBPal0c1,
    spritesCGBPal0c2,
    spritesCGBPal0c3,

    spritesCGBPal1c0,
    spritesCGBPal1c1,
    spritesCGBPal1c2,
    spritesCGBPal1c3,

    spritesCGBPal2c0,
    spritesCGBPal2c1,
    spritesCGBPal2c2,
    spritesCGBPal2c3,
};

void main(){
    
    SPRITES_8x16;

    set_bkg_palette(0,1,&backgroundpalette[0]);

    set_sprite_palette(0,3,&spritepalette[0]);
   
    set_sprite_data(0, 6, sprites);

    set_sprite_tile(0, 0);
    set_sprite_prop(0,0);
    move_sprite(0, 20, 78);

    set_sprite_tile(1, 2);
    set_sprite_prop(1,1);
    move_sprite(1, 80, 78);

    set_sprite_tile(2, 4);
    set_sprite_prop(2,2);
    move_sprite(2, 140, 78);

    SHOW_SPRITES;
    SHOW_BKG;
}