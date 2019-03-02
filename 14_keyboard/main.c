#include <gb/gb.h>
#include "keyboarddata.c"
#include "sprites.c"
#include "keyboardmap.c"
#include "cursor.c"

unsigned char playername[18];
struct Cursor cursor;
const UINT8 mincursorx = 12;
const UINT8 mincursory = 80;
const UINT8 maxcursorx = 156;
const UINT8 maxcursory = 128;

UINT8 namecharacterindex;
UBYTE keydown, playerhasname;

void performantdelay(UINT8 numloops){
    UINT8 ii;
    for(ii = 0; ii < numloops; ii++){
        wait_vbl_done();
    }     
}

UBYTE isWithinKeyboard(UINT8 x, UINT8 y){
    // check special locations at bottom of keyboard
    if(x==140 && y==144 || x==156 && y==144){
        return 1;
    }
    return x >= mincursorx && x <= maxcursorx && y >= mincursory && y <= maxcursory;
}

void addtoplayername(struct Cursor* cursor){
    // work out index of select character in charactermap
    UINT8 characterindex = cursor->row * 10 + cursor->col + 1; // add one as space is first character in sprites

    if(namecharacterindex == 18) return; // max name length reached

    playername[namecharacterindex] = characterindex;
    namecharacterindex++;
}

void removefromplayername(){
    if(namecharacterindex>0){
        namecharacterindex--;
        playername[namecharacterindex] = 0;// replace with space
    }
}

void drawplayername(){
    set_bkg_tiles(1, 4, 18, 1, playername);
}

void updateplayername(struct Cursor* cursor){
    // check if cursor at delete or done
    if(cursor->col==8 && cursor->row == 4){
        // delete
        removefromplayername();
        drawplayername();
    }
    else if (cursor->col==9 && cursor->row == 4){
        // player finished
        playerhasname = 1;
    }
    else{
        addtoplayername(cursor);
        drawplayername();
    }
}

void main(){
    // load cursor sprite
    set_sprite_data(0, 1, sprites);
    set_sprite_tile(0, 0);

    cursor.x = 12;
    cursor.y = 80;
    cursor.col = 0;
    cursor.row = 0;
    move_sprite(0, cursor.x, cursor.y);
    
    set_bkg_data(0, 45, keyboarddata);
    set_bkg_tiles(0, 0, 20, 18, keyboardmap);
    scroll_bkg(-4,0); // move half a sprite to give even spacing either side of keyboard

    SHOW_BKG;
    SHOW_SPRITES;
    DISPLAY_ON;

    while(!playerhasname){
        if(keydown){
            waitpadup();
            keydown = 0;
        }

        switch(joypad()){
            case J_UP:
                if(isWithinKeyboard(cursor.x, cursor.y - 16)){
                    cursor.y -= 16;
                    scroll_sprite(0,0,-16);
                    keydown = 1;
                    cursor.row--;
                }
                break;
            case J_DOWN: 
                if(isWithinKeyboard(cursor.x, cursor.y + 16)){            
                    cursor.y += 16;
                    scroll_sprite(0,0,16);
                    keydown = 1;
                    cursor.row++;
                }
                break;  
            case J_LEFT: 
                if(isWithinKeyboard(cursor.x - 16, cursor.y)){
                    cursor.x -= 16;
                    scroll_sprite(0,-16,0);
                    keydown = 1;
                    cursor.col--;
                }
                break; 
            case J_RIGHT: 
                if(isWithinKeyboard(cursor.x + 16, cursor.y)){            
                    cursor.x += 16;
                    scroll_sprite(0,16,0);
                    keydown = 1;
                    cursor.col++;
                }
                break;
            case J_A:
                updateplayername(&cursor);
                keydown = 1;                
                break;
        }
        performantdelay(2);
    }
}