#include <gb/gb.h>
#include <stdio.h>
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

UBYTE canplayermove(INT8 movex, INT8 movey, UINT8 playerx, UINT8 playery){
    // get background tile index
    UINT8 indexX, indexY, tileindex;

    if(movex<0 || movex == 0){
        // check left edge of sprite
        indexX = (UINT8)(((INT8)playerx + movex -8) / 8); // will always round down
    }
    else if(movex>0){
        // check right edge of sprite
        indexX = (playerx + movex - 1) / 8; // will always round down
    }
    if(movey<0 || movey == 0){
        // check top edge of sprite
       indexY = (playery + movey - 15) / 8; // will always round down 
    }
    else if(movey>0){
        // check bottom edge of sprite
        indexY = (playery + movey - 8) / 8; // will always round down 
    }   
    
    // background map has 20 by 16 tiles
    tileindex = 20 * indexY + indexX;
    //printf("%u %u %u %u %u\n",(UINT16)(playerx + movex),(UINT16)(playery + movey),(UINT16)indexX,(UINT16)indexY,(UINT16)tileindex);
    
    // check if index tileindex in background map is empty (0x00);
    return MazeMap[tileindex] == 0;
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
            if(canplayermove(-1,0,playerlocation[0],playerlocation[1])){
                playerlocation[0] -= 1;
                move_sprite(0,playerlocation[0],playerlocation[1]);
            }
        }
        else if(joypad() & J_RIGHT){
            if(canplayermove(1,0,playerlocation[0],playerlocation[1])){
                playerlocation[0] += 1;
                move_sprite(0,playerlocation[0],playerlocation[1]);
            }
        }
        else if(joypad() & J_UP){
            if(canplayermove(0,-1,playerlocation[0],playerlocation[1])){
                playerlocation[1] -= 1;
                move_sprite(0,playerlocation[0],playerlocation[1]);
            }
        }
        else if(joypad() & J_DOWN){
            if(canplayermove(0,1,playerlocation[0],playerlocation[1])){
                playerlocation[1] += 1;
                move_sprite(0,playerlocation[0],playerlocation[1]);
            }
        }
        performantdelay(2);
    }
}