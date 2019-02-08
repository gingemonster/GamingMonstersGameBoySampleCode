#include <gb/gb.h>

//generical character structure: id, position, graphics
typedef struct GameCharacter {
	UBYTE spritids[4]; // all characters use 4 sprites
	UINT8 x;
	UINT8 y;
	UINT8 width;
	UINT8 height;
} GameCharacter;