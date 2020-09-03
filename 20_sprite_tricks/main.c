#include <gb/gb.h>
#include <stdio.h>
#include "ExampleSprite.c"
#include "BackgroundData.c"
#include "BackgroundMap.c"

void performantdelay(UINT8 numloops){
    UINT8 i;
    for(i = 0; i < numloops; i++){
        wait_vbl_done();
    }     
}

void main(){

    set_bkg_data(0,4,BackgroundData);
    set_bkg_tiles(0,0,20,18,BackgroundMap);

    set_sprite_data(0, 2, ExampleSprite);

    set_sprite_tile(0, 0);
    set_sprite_tile(1, 0);
    set_sprite_tile(2, 0);
    set_sprite_tile(3, 0);
    set_sprite_tile(4, 0);

    move_sprite(0, 22, 78);
    move_sprite(1, 44, 78);
    move_sprite(2, 66, 78);
    move_sprite(3, 88, 78);
    move_sprite(4, 26, 59);

    set_sprite_prop(1,S_FLIPX);
    set_sprite_prop(2,S_FLIPY);
    set_sprite_prop(3,S_FLIPX | S_FLIPY);

    set_sprite_prop(4,S_PRIORITY | S_FLIPX);

    SHOW_SPRITES;
    SHOW_BKG;

    while(1){
        switch(joypad()){
            case J_LEFT: 
                scroll_sprite(4,-1,0);
                break;
            case J_RIGHT: 
                scroll_sprite(4,1,0);
                break;  
            case J_UP: 
                scroll_sprite(4,0,-1);

                set_sprite_prop(4,get_sprite_prop(4) & ~S_PRIORITY);
                break; 
            case J_DOWN: 
                scroll_sprite(4,0,1);
                break;                                                   
        }
        performantdelay(2);
    }
}