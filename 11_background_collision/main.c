#include <gb/gb.h>
#include <stdio.h>
#include "MazeSprites.c"
#include "MazeMap.c"
#include "Snail.c"

const char blankmap[1] = {0x00};
UINT8 playerlocation[2];
UBYTE debug, haskey, gamerunning;

void performantdelay(UINT8 numloops){
    UINT8 i;
    for(i = 0; i < numloops; i++){
        wait_vbl_done();
    }     
}

UBYTE canplayermove(UINT8 newplayerx, UINT8 newplayery){
    UINT16 indexTLx, indexTLy, tileindexTL;
    UBYTE result;

    indexTLx = (newplayerx - 8) / 8;
    indexTLy = (newplayery - 16) / 8;
    tileindexTL = 20 * indexTLy + indexTLx;

    if(debug){
        printf("%u %u\n",(UINT16)(newplayerx),(UINT16)(newplayery));
        printf("%u %u %u\n",(UINT16)indexTLx,(UINT16)indexTLy,(UINT16)tileindexTL);   
    }    

    result = MazeMap[tileindexTL] == blankmap[0];

    if(tileindexTL==321){
        // collect key
        set_bkg_tiles(1,16,1,1,blankmap);
        haskey = 1;
        result = 1;
    }
    else if(tileindexTL==263 && haskey){
        // open door
        set_bkg_tiles(3,13,1,1,blankmap);
        result = 1;
    }
    else if(tileindexTL==340){
        // finish game
        gamerunning = 0;
        HIDE_SPRITES;
        printf("\n \n \n \n \n \n \n \n \n      YOU WIN!");
        result = 1;        
        result = 1;
    }

    return result;
}

void animatesprite(UINT8 spriteindex, INT8 movex, INT8 movey){
    while(movex!=0){
        scroll_sprite(spriteindex, movex < 0 ? -1 : 1, 0);
        movex += (movex < 0 ? 1 : -1);
        wait_vbl_done();
    }
    while(movey!=0){
        scroll_sprite(spriteindex, 0, movey < 0 ? -1 : 1);
        movey += movey < 0 ? 1 : -1;
        wait_vbl_done();
    }    
}

void main(){

    set_bkg_data(0, 4, MazeSprites);
    set_bkg_tiles(0, 0, 20, 18, MazeMap);

	set_sprite_data(0, 1, Snail);   /* defines the sprite data */
	set_sprite_tile(0,0);            /* defines the tiles numbers */

    playerlocation[0] = 16;
    playerlocation[1] = 24;

    move_sprite(0,playerlocation[0],playerlocation[1]);

    gamerunning = 1;

    SHOW_SPRITES;
    SHOW_BKG;
    DISPLAY_ON;

    while(gamerunning){
        if(joypad() & J_A){
            debug = 1;
        }        
        if(joypad() & J_LEFT){
            if(canplayermove(playerlocation[0]-8,playerlocation[1])){
                playerlocation[0] -= 8;
                animatesprite(0,-8,0);
            }
        }
        else if(joypad() & J_RIGHT){
            if(canplayermove(playerlocation[0]+8,playerlocation[1])){            
                playerlocation[0] += 8;
                animatesprite(0,8,0);
            }
        }
        else if(joypad() & J_UP){
            if(canplayermove(playerlocation[0],playerlocation[1]-8)){
                playerlocation[1] -= 8;
                animatesprite(0,0,-8);
            }
        }
        else if(joypad() & J_DOWN){
            if(canplayermove(playerlocation[0],playerlocation[1]+8)){
                playerlocation[1] += 8;
                animatesprite(0,0,8);
            }
        }
        
        performantdelay(6);
    }
}