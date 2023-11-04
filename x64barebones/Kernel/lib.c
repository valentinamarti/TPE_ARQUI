#include <stdint.h>

void * memset(void * destination, int32_t c, uint64_t length)
{
	uint8_t chr = (uint8_t)c;
	char * dst = (char*)destination;

	while(length--)
		dst[length] = chr;

	return destination;
}

void * memcpy(void * destination, const void * source, uint64_t length)
{
	/*
	* memcpy does not support overlapping buffers, so always do it
	* forwards. (Don't change this without adjusting memmove.)
	*
	* For speedy copying, optimize the common case where both pointers
	* and the length are word-aligned, and copy word-at-a-time instead
	* of byte-at-a-time. Otherwise, copy by bytes.
	*
	* The alignment logic below should be portable. We rely on
	* the compiler to be reasonably intelligent about optimizing
	* the divides and modulos out. Fortunately, it is.
	*/
	uint64_t i;

	if ((uint64_t)destination % sizeof(uint32_t) == 0 &&
		(uint64_t)source % sizeof(uint32_t) == 0 &&
		length % sizeof(uint32_t) == 0)
	{
		uint32_t *d = (uint32_t *) destination;
		const uint32_t *s = (const uint32_t *)source;

		for (i = 0; i < length / sizeof(uint32_t); i++)
			d[i] = s[i];
	}
	else
	{
		uint8_t * d = (uint8_t*)destination;
		const uint8_t * s = (const uint8_t*)source;

		for (i = 0; i < length; i++)
			d[i] = s[i];
	}

	return destination;
}

void itoa(int value, char* buff, int base){
    int i = 0;
    int val = abs(value);       // tomo el valor absoluto para no mandarme un moco con los signos

    if(val == 0){
        buff[i++] = '0';
    }

    while(val != 0){
        int resto = val % base; 
        if(resto < 10){
            buff[i++] = resto + '0';
        }else{                          // con esto vemos si es hexa
            buff[i++] = resto + 'A' - 10;   
        }
        val /= base; 
    }

    if (value < 0 && base == 10) {      // si es base 10, le pongo el signo menos 
        buff[i++] = '-';
    }
    int dim = i;        // me guardo dim del numero
    
    int j = 0; 
    i -= 1;  
    char aux;
    while(j < i){
        aux = buff[j];
        buff[j] = buff[i];
        buff[i] = aux; 
        j++;
        i--;
    }
    buff[dim] = 0;

}

int abs(int value){
	if(value < 0){
        return -value;
    }
    return value; 
}

