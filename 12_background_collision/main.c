#include <gb/gb.h>
#include <stdio.h>
#include "MazeSprites.c"
#include "MazeMap.c"
#include "Snail.c"

const char blankmap[1] = {0x00};
UINT8 playerlocation[2];
UBYTE haskey;
UBYTE debug;
UBYTE gamerunning = 1;


void performantdelay(UINT8 numloops){
    UINT8 i;
    for(i = 0; i < numloops; i++){
        wait_vbl_done();
    }     
}

UBYTE canplayermove(UINT8 newplayerx, UINT8 newplayery){
    UBYTE result;
    // get background tile index, can be > 255 so use UINT16
    UINT16 indexTLx, indexTLy, indexTRx, indexTRy, indexBRx, indexBRy, indexBLx, indexBLy, tileindexTL,tileindexTR,tileindexBL,tileindexBR;

    // get index for all corners of sprite
    indexTLx = (newplayerx - 8) / 8;
    indexTLy = (newplayery - 16) / 8;
    tileindexTL = 20 * indexTLy + indexTLx;

    indexTRx = (newplayerx - 2) / 8;
    indexTRy = (newplayery - 16) / 8;
    tileindexTR = 20 * indexTRy + indexTRx;    

    indexBRx = (newplayerx - 2) / 8;
    indexBRy = (newplayery - 10) / 8;
    tileindexBR = 20 * indexBRy + indexBRx;

    indexBLx = (newplayerx - 8) / 8;
    indexBLy = (newplayery - 10) / 8;
    tileindexBL = 20 * indexBLy + indexBLx; 

    if(debug){

        printf("%u %u\n",(UINT16)(newplayerx),(UINT16)(newplayery),(UINT16)indexTLx,(UINT16)indexTLy,(UINT16)tileindexTL);
        printf("%u %u %u\n",(UINT16)indexTLx,(UINT16)indexTLy,(UINT16)tileindexTL);
        printf("%u %u %u\n",(UINT16)indexBRx,(UINT16)indexBRy,(UINT16)tileindexBR);
    }   
    
    // check if tile index, for top left and bottom right of sprite, in background map is empty (0x00);
    result = MazeMap[tileindexTL] == 0 && MazeMap[tileindexBR] == 0 && MazeMap[tileindexTR] == 0 && MazeMap[tileindexBL] == 0;

    // check for the two special locations, key and door
    if(tileindexBR==321){
        // colect key
        set_bkg_tiles(1, 16, 1, 1, blankmap);
        MazeMap[321] = 0;
        haskey = 1;
    }
    else if(tileindexBR==263 && haskey){
        // open door
        set_bkg_tiles(3, 13, 1, 1, blankmap);
        MazeMap[263] = 0;
    }
    else if (tileindexBR==340){
        // finish game
        gamerunning = 0;
        HIDE_SPRITES;
        printf("\n \n \n \n \n \n \n \n \n      YOU WIN!");
    }

    return result;
}

void main(){

    set_bkg_data(0, 4, MazeSprites);
    set_bkg_tiles(0, 0, 20, 18, MazeMap);

	set_sprite_data(0, 1, Snail);   /* defines the sprite data */
	set_sprite_tile(0,0);            /* defines the tiles numbers */

    playerlocation[0] = 16;
    playerlocation[1] = 24;

    move_sprite(0,playerlocation[0],playerlocation[1]);

    SHOW_SPRITES;
    SHOW_BKG;
    DISPLAY_ON;

    while(gamerunning){
        if(joypad() & J_A){
            debug = 1;
        }
        if(joypad() & J_LEFT){
            if(canplayermove(playerlocation[0]-1,playerlocation[1])){
                playerlocation[0] -= 1;
                move_sprite(0,playerlocation[0],playerlocation[1]);
            }
        }
        else if(joypad() & J_RIGHT){
            if(canplayermove(playerlocation[0]+1,playerlocation[1])){
                playerlocation[0] += 1;
                move_sprite(0,playerlocation[0],playerlocation[1]);
            }
        }
        else if(joypad() & J_UP){
            if(canplayermove(playerlocation[0],playerlocation[1]-1)){
                playerlocation[1] -= 1;
                move_sprite(0,playerlocation[0],playerlocation[1]);
            }
        }
        else if(joypad() & J_DOWN){
            if(canplayermove(playerlocation[0],playerlocation[1]+1)){
                playerlocation[1] += 1;
                move_sprite(0,playerlocation[0],playerlocation[1]);
            }
        }
        performantdelay(2);
    }
}