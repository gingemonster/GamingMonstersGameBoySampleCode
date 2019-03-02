#include <gb/gb.h>

typedef struct GameCharacter{
    UINT8 x;
    UINT8 y;
    UINT8 spriteid;
    INT8 velocityX;
    INT8 velocityY;
    INT8 currentFriction;
    UINT8 width;
    UINT8 height;
    UBYTE isjumping;
} GameCharacter;