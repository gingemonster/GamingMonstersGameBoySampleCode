#include <gb/gb.h>
#include <stdio.h>

unsigned char bloke[] =
{
  /* Tile 0 */
  0x00,0x00,0x38,0x38,0x7C,0x44,0x7F,0x7F,
  0x44,0x74,0x46,0x7C,0x40,0x78,0x24,0x3C,
  /* Tile 1 */
  0x18,0x3C,0x00,0x24,0x00,0x24,0x00,0x24,
  0x00,0x24,0x00,0x36,0x00,0x00,0x00,0x00,
  /* Tile 2 */
  0x00,0x00,0x38,0x38,0x7C,0x44,0x7F,0x7F,
  0x44,0x74,0x46,0x7C,0x40,0x78,0x24,0x3C,
  /* Tile 3 */
  0x18,0x3C,0x00,0x22,0x00,0x22,0x00,0x22,
  0x00,0x23,0x00,0x30,0x00,0x00,0x00,0x00,
  /* Tile 4 */
  0x00,0x00,0x38,0x38,0x7C,0x44,0x7F,0x7F,
  0x44,0x74,0x46,0x7C,0x40,0x78,0x24,0x3C,
  /* Tile 5 */
  0x18,0x3C,0x00,0x42,0x00,0x42,0x00,0x42,
  0x00,0x42,0x00,0x63,0x00,0x00,0x00,0x00,
  /* Tile 6 */
  0x00,0x00,0x38,0x38,0x7C,0x44,0x7F,0x7F,
  0x44,0x74,0x46,0x7C,0x40,0x78,0x24,0x3C,
  /* Tile 7 */
  0x18,0x3C,0x00,0x44,0x00,0x44,0x00,0x44,
  0x00,0x64,0x00,0x06,0x00,0x00,0x00,0x00
};

BYTE jumping;
UINT8 gravity = -2;
UINT8 currentspeedY;
INT8 playerlocation[2]; // stores two INT8 x and y position of player
UINT8 floorYposition = 100;

INT8 wouldhitsurface(UINT8 projectedYposition){
    if(projectedYposition >= floorYposition){
        return floorYposition;
    }
    return -1;
}

void jump(UINT8 spriteid, UINT8 spritelocation[2]){
    INT8 possiblesurfaceY;

    if(jumping==0){
        currentspeedY = 10;
        jumping = 1; // record a jump is now in progress
    }
    // work out current speed - effect of gravities accelleration down
    currentspeedY = currentspeedY + gravity;

    // work out new Y location
    spritelocation[1] = spritelocation[1] - currentspeedY;
    
    // check if would hit a surface, and if so get back surfaces Y position
    // otherwise gets -1
    possiblesurfaceY = wouldhitsurface(spritelocation[1]);
    
    if(possiblesurfaceY > -1){
        // this new Y location would be at or below the Y position of a surface
        move_sprite(spriteid,spritelocation[0],possiblesurfaceY);
        jumping = 0; // stop jumping
    }
    else{
        //printf("%d",(INT16)spritelocation[1]);
        // move sprite
        move_sprite(spriteid,spritelocation[0],spritelocation[1]);
    }
}

void performantdelay(UINT8 numloops){
    UINT8 i;
    for(i = 0; i < numloops; i++){
        wait_vbl_done();
    }     
}

void main(){

	set_sprite_data(0, 8, bloke);   /* defines the sprite data */
	
	set_sprite_tile(0,0);            /* defines the tiles numbers */

    playerlocation[0] = 10;
    playerlocation[1] = floorYposition;

    move_sprite(0,playerlocation[0],playerlocation[1]);

	DISPLAY_ON;						// Turn on the display
    SHOW_SPRITES;

    jumping = 0;

    while(1){
        if((joypad() & J_A && jumping == 0) || jumping==1){
            jump(0,playerlocation);
        }
        if(joypad() & J_LEFT){
            playerlocation[0] = playerlocation[0] - 2;
            move_sprite(0,playerlocation[0],playerlocation[1]);
        }
        if(joypad() & J_RIGHT){
            playerlocation[0] = playerlocation[0] + 2;
            move_sprite(0,playerlocation[0],playerlocation[1]);
        }

        // delay without using CPU expensive delay function
        performantdelay(5);
        
    }
}

