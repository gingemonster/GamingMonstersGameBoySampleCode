#include <gb/gb.h>
#include <stdio.h>
#include "mario_data.c"
#include "mario_map.c"

void main(){
    set_bkg_data(0, 114, mario_data);
    set_bkg_tiles(0, 0, 20, 18, mario_map);

    SHOW_BKG;
    DISPLAY_ON;

    waitpad(J_START);

    printf("START OF MY GAME");
}