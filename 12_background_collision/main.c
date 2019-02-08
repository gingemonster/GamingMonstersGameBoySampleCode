#include <gb/gb.h>
#include "MazeSprites.c"
#include "MazeMap.c"
#include "Bloke.c"

UINT8 playerlocation[2];

void performantdelay(UINT8 numloops){
    UINT8 i;
    for(i = 0; i < numloops; i++){
        wait_vbl_done();
    }     
}

void main(){
    set_bkg_data(0, 4, MazeSprites);
    set_bkg_tiles(0, 0, 20, 18, MazeMap);

	set_sprite_data(0, 1, bloke);   /* defines the sprite data */
	set_sprite_tile(0,0);            /* defines the tiles numbers */

    playerlocation[0] = 16;
    playerlocation[1] = 24;

    move_sprite(0,playerlocation[0],playerlocation[1]);

    SHOW_SPRITES;
    SHOW_BKG;
    DISPLAY_ON;

    while(1){
        if(joypad() & J_LEFT){
            playerlocation[0] = playerlocation[0] - 1;
            move_sprite(0,playerlocation[0],playerlocation[1]);
        }
        if(joypad() & J_RIGHT){
            playerlocation[0] = playerlocation[0] + 1;
            move_sprite(0,playerlocation[0],playerlocation[1]);
        }
        if(joypad() & J_UP){
            playerlocation[1] -= 1;
            move_sprite(0,playerlocation[0],playerlocation[1]);
        }
        if(joypad() & J_DOWN){
            playerlocation[1] += 1;
            move_sprite(0,playerlocation[0],playerlocation[1]);
        }        
        performantdelay(2);
    }
}