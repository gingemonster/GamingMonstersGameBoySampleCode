#include <gb/gb.h>
#include <stdio.h>
#include "ExampleSprite.c"

void main(){
    UINT8 currentspriteindex = 0;

    set_sprite_data(0, 2, ExampleSprite);
    set_sprite_tile(0, 0);
    set_sprite_tile(1, 0);
    set_sprite_tile(2, 0);
    set_sprite_tile(3, 0);
    move_sprite(0, 22, 78);
    move_sprite(1, 44, 78);
    move_sprite(2, 66, 78);
    move_sprite(3, 88, 78);

    set_sprite_prop(1,S_FLIPX);
    set_sprite_prop(2,S_FLIPY);
    set_sprite_prop(3,S_FLIPX | S_FLIPY);
    SHOW_SPRITES;

    while(1){
        
    }
}