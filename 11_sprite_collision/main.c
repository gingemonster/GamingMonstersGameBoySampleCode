#include <gb/gb.h>
#include <stdio.h>
#include "GameSprites.c"
#include "GameCharacter.c"

GameCharacter ship;
GameCharacter bug;
UBYTE spritesize = 8;

void performantdelay(UINT8 numloops){
    UINT8 i;
    for(i = 0; i < numloops; i++){
        wait_vbl_done();
    }     
}

void movegamecharacter(GameCharacter* character, UINT8 x, UINT8 y){
    move_sprite(character->spritids[0], x, y);
    move_sprite(character->spritids[1], x + spritesize, y);
    move_sprite(character->spritids[2], x, y + spritesize);
    move_sprite(character->spritids[3], x + spritesize, y + spritesize);
}

void setupship(){
    ship.x = 80;
    ship.y = 130;
    ship.width = 16;
    ship.height = 16;

    // load sprites for ship
    set_sprite_tile(0, 0);
    ship.spritids[0] = 0;
    set_sprite_tile(1, 1);
    ship.spritids[1] = 1;
    set_sprite_tile(2, 2);
    ship.spritids[2] = 2;
    set_sprite_tile(3, 3);
    ship.spritids[3] = 3;

    movegamecharacter(&ship,ship.x,ship.y);
}

void setupbug(){
    bug.x = 30;
    bug.y = 0;
    bug.width = 16;
    bug.height = 16;    

    // load sprites for bug
    set_sprite_tile(4, 4);
    bug.spritids[0] = 4;
    set_sprite_tile(5, 5);
    bug.spritids[1] = 5;
    set_sprite_tile(6, 6);
    bug.spritids[2] = 6;
    set_sprite_tile(7, 7);
    bug.spritids[3] = 7;
    movegamecharacter(&bug,bug.x,bug.y);
}

BYTE checkcollisions(GameCharacter* one, GameCharacter* two){
    return ((one->x >= two->x && one->x <= two->x + two->width) && (one->y >= two->y && one->y <= two->y + two->height)) || ((two->x >= one->x && two->x <= one->x + one->width) && (two->y >= one->y && two->y <= one->y + one->height));
}

void main(){
    set_sprite_data(0, 8, GameSprites);
    setupship();
    setupbug();
    
    SHOW_SPRITES;
    DISPLAY_ON;

    while(!checkcollisions(&ship,&bug)){
        if(joypad() & J_LEFT){
            ship.x -= 2;
            movegamecharacter(&ship,ship.x,ship.y);
        }
        if(joypad() & J_RIGHT){
            ship.x += 2;
            movegamecharacter(&ship,ship.x,ship.y);
        }
        bug.y += 5;

        // check if bug at bottom of screen, if so reset position to top
        if(bug.y >= 144){
            bug.y = 0;
            bug.x = ship.x; // be nasty and chase the ship!
        }

        movegamecharacter(&bug,bug.x,bug.y);

        performantdelay(5);
    }
    printf(" \n \n \n \n \n \n === GAME  OVER === ");
}
