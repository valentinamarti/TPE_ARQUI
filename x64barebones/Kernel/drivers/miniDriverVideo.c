#include <miniDriverVideo.h>


static uint8_t * currentVideo = (uint8_t*)0xB8000;

void printMessageSpecificColor(const char * string, uint8_t colorLetra, uint8_t colorFondo){
	int i;
	for (i = 0; string[i] != 0; i++)
		printCharSpecificColor(string[i], colorLetra, colorFondo);
}

void printCharSpecificColor(char character, uint8_t colorLetra, uint8_t colorFondo){
	uint8_t color = (colorLetra << 4) | colorFondo;  //shifteo 4 (osea 0x02 paso a 0x20; luego hago un or para que me queden ambos valores)
	*currentVideo = character;		// en este byte va la letra
	currentVideo += 1;					
	*currentVideo = color;			// en este byte va el color
	currentVideo += 1;					
}


void printMessageBackwards(const char * string, uint8_t colorLetra, uint8_t colorFondo){
	int i;
	for (i = 0; string[i] != 0; i++)
		printCharBackwards(string[i], colorLetra, colorFondo);
}

void printCharBackwards(char character, uint8_t colorLetra, uint8_t colorFondo){
	uint8_t color = (colorLetra << 4) | colorFondo;  //shifteo 4 (osea 0x02 paso a 0x20; luego hago un or para que me queden ambos valores)
	*currentVideo = character;		// en este byte va la letra
	currentVideo -= 1;					
	*currentVideo = color;			// en este byte va el color
	currentVideo -= 1;		
}


