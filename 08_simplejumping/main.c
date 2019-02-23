#include <gb/gb.h>
#include <stdio.h>

INT8 playerlocation[2]; // stores two INT8 x and y position of player
BYTE jumping;
UINT8 gravity = -2;
UINT8 currentspeedY;
UINT8 floorYposition = 100;

unsigned char bloke[] =
{
  0x00,0x00,0x38,0x38,0x7C,0x44,0x7F,0x7F,
  0x44,0x74,0x46,0x7C,0x40,0x78,0x24,0x3C,
  0x18,0x3C,0x00,0x24,0x00,0x24,0x00,0x24,
  0x00,0x24,0x00,0x36,0x00,0x00,0x00,0x00,
  0x00,0x00,0x38,0x38,0x7C,0x44,0x7F,0x7F,
  0x44,0x74,0x46,0x7C,0x40,0x78,0x24,0x3C,
  0x18,0x3C,0x00,0x22,0x00,0x22,0x00,0x22,
  0x00,0x23,0x00,0x30,0x00,0x00,0x00,0x00,
  0x00,0x00,0x38,0x38,0x7C,0x44,0x7F,0x7F,
  0x44,0x74,0x46,0x7C,0x40,0x78,0x24,0x3C,
  0x18,0x3C,0x00,0x42,0x00,0x42,0x00,0x42,
  0x00,0x42,0x00,0x63,0x00,0x00,0x00,0x00,
  0x00,0x00,0x38,0x38,0x7C,0x44,0x7F,0x7F,
  0x44,0x74,0x46,0x7C,0x40,0x78,0x24,0x3C,
  0x18,0x3C,0x00,0x44,0x00,0x44,0x00,0x44,
  0x00,0x64,0x00,0x06,0x00,0x00,0x00,0x00
};

void performantdelay(UINT8 numloops){
    UINT8 i;
    for(i = 0; i < numloops; i++){
        wait_vbl_done();
    }     
}

INT8 wouldhitsurface(UINT8 projectedYPosition){
    if(projectedYPosition >= floorYposition){
        return floorYposition;
    }
    return -1;
}

void jump(UINT8 spriteid, UINT8 spritelocation[2]){
    INT8 possiblesurfaceY;

    if(jumping==0){
        jumping=1;
        currentspeedY = 10;
    }

    // work out current speed - effect of gravities accelleration down
    currentspeedY = currentspeedY + gravity;    

    spritelocation[1] = spritelocation[1] - currentspeedY;

    possiblesurfaceY = wouldhitsurface(spritelocation[1]);

    if(possiblesurfaceY > -1){
        jumping = 0;
        move_sprite(spriteid,spritelocation[0],possiblesurfaceY);
    }
    else{
        move_sprite(spriteid,spritelocation[0],spritelocation[1]);
    }
}

void main(){

	set_sprite_data(0, 8, bloke);   /* defines the sprite data */
	
	set_sprite_tile(0,0);            /* defines the tiles numbers */

    playerlocation[0] = 10;
    playerlocation[1] = floorYposition;
    jumping = 0;

    move_sprite(0,playerlocation[0],playerlocation[1]);

	DISPLAY_ON;						// Turn on the display
    SHOW_SPRITES;

    while(1){
        if((joypad() & J_A) || jumping == 1){
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
        performantdelay(5);
    }
}

