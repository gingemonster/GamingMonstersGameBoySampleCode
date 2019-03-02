#include <gb/gb.h>
#include <stdio.h>
#include "GameCharacter.c"
#include "level01map.c"
#include "levelsprites.c"
#include "man.c"

GameCharacter player;
UINT8 gravity = 2;
const char blankmap[1] = {0x00};


void performantdelay(UINT8 numloops){
    UINT8 i;
    for(i = 0; i < numloops; i++){
        wait_vbl_done();
    }     
}

UBYTE isleftedgeofscreen(UINT8 x){
    return x==8;
}

UBYTE istouchingground(GameCharacter* character){
    // check if when velocity is applied character would be touching solid surface BELOW them
    UBYTE result;    
    UINT16 indexTLx, indexTLy, tileindexTL;

    // as we are checking below character need to check Y + character height
    indexTLx = (character->x - 8) / 8;
    indexTLy = (character->y + character->height + 1 - 16) / 8;   // TODO problem is probably its calculating a non round number!

    tileindexTL = 20 * indexTLy + indexTLx; // will have to change as level scrolls?
    
    result = level01map[tileindexTL] != blankmap[0]; // todo will have to look for specific tiles when we have platforms you can jump through

    if(result){
        //printf("%u %u %u %u \n", (UINT16)tileindexTL, (UINT16)indexTLx, (UINT16)indexTLy, (UINT16)character->y);
        // SOMETHING still screwed here when your fall vs jump
        if(character->velocityY != -10){
            character->velocityY = 0;
            character->isjumping = 0; // stop falling
        }
        
        character->y = indexTLy * 8 + character->height; // set character y to be surface y
        
    }

    return result;
}

void movecharacter(GameCharacter* character){
    UBYTE hasmoved = 0;
    // check if player moving in x or y, apply friction, accelleration and gravity

    // if velocity in x direction, move x unless moving left and at edge of screen
    if(character->velocityX!=0 && !(character->velocityX<0 && isleftedgeofscreen(character->x))){ // TODO scroll camera as character gets to center?
        character->x += character->velocityX;
        character->velocityX += (character->velocityX>0?-character->currentFriction:character->currentFriction);
        hasmoved = 1;
    }
    if(character->velocityY > 4){
        //printf("test");
        character->velocityY = 4; // dont want it to fall more than 1 cell in a step
    }    
    if(!istouchingground(character) || character->velocityY < 0){ // not falling and touching ground OR is moving up screen as part of jump

        character->y += character->velocityY;
        character->velocityY += gravity;
        hasmoved = 1;
    }

    // ISSUE is hasmoved is not called when it touches the ground which sets Y to the grounds Y
    
    if(hasmoved) {
        move_sprite(0,character->x,character->y);
    }
}

void main(){
    set_bkg_data(0,2,levelsprites);
    set_bkg_tiles(0,0,20,18,level01map);
	set_sprite_data(0, 1, man);   /* defines the sprite data */
	set_sprite_tile(0,0);            /* defines the tiles numbers */

    player.spriteid = 0;
    player.x = 8;
    player.y = 144;
    player.currentFriction = 2;
    player.width = 8;
    player.height = 8;
    player.isjumping = 0;

    move_sprite(0,player.x,player.y);
    
    SHOW_SPRITES;
    SHOW_BKG;
	DISPLAY_ON;						// Turn on the display

    while(1){
        if((joypad() & J_A) && player.isjumping == 0){
           player.velocityY = -10;
           player.isjumping = 1;
        }
        if(joypad() & J_LEFT){
            player.velocityX = -2;
        }
        if(joypad() & J_RIGHT){
            player.velocityX = 2;
        }
        movecharacter(&player);
        performantdelay(2);
    }
}

