#include <stdio.h>
#include <stdint.h>

#define MEMSIZE     0xFFF
#define VX	   		0x10
#define STACK       0x10


uint8_t     memory[MEMSIZE];
uint8_t     Vx[VX];
uint16_t    Ireg; 	//lowest 12 bits register is that in use.
uint16_t    PC = 0x200;

struct _delay
{
    uint8_t __ST;
    uint8_t __DT;
}delay;


void disassembleChip8Op(uint8_t *, int );
void loadGameOnMemory(uint8_t*, uint8_t*, int);

int main(int argc, char** argv)
{
    FILE *rom = fopen(argv[1], "r");
	if(!rom)
	{
		printf("File could not open");
	}

    //Get the file size
    fseek(rom, 0, SEEK_END);
    int romSize = ftell(rom);
    fseek(rom, 0, SEEK_SET);

    uint8_t loadGame[romSize];			//memory allocation for game on array
    fread(&loadGame, romSize, 1, rom);	//Save the game on char arrays
	fclose(rom);
}




//Load ROM on Memory
void loadGameOnMemory(uint8_t* mem, uint8_t* loadGame, int romSize){
    int memGame = 0x200;
    for (int i = 0; i < romSize; i++)
    {
        mem[memGame] = loadGame[i];
        memGame++;
    }

}



void disassembleChip8Op(uint8_t *codebuffer, int pc)
{
	uint8_t *code = &codebuffer[pc];
    uint8_t firstnib = (code[0] >> 4);

    printf("%04x %02x %02x ", pc, code[0], code[1]);

    switch (firstnib)
    {
        case 0x00: printf("0 not handled yet"); break;
        case 0x01: printf("1 not handled yet"); break;
        case 0x02: printf("2 not handled yet"); break;
        case 0x03: printf("3 not handled yet"); break;
        case 0x04: printf("4 not handled yet"); break;
        case 0x05: printf("5 not handled yet"); break;
        case 0x06:
            {
                uint8_t reg = code[0] & 0x0f;
                printf("%-10s V%01X,#$%02x", "MVI", reg, code[1]);
            }
            break;
        case 0x07: printf("7 not handled yet"); break;
        case 0x08: printf("8 not handled yet"); break;
        case 0x09: printf("9 not handled yet"); break;
        case 0x0a:
            {
                uint8_t addresshi = code[0] & 0x0f;
                printf("%-10s I,#$%01x%02x", "MVI", addresshi, code[1]);
            }
            break;
        case 0x0b: printf("b not handled yet"); break;
        case 0x0c: printf("c not handled yet"); break;
        case 0x0d: printf("d not handled yet"); break;
        case 0x0e: printf("e not handled yet"); break;
        case 0x0f: printf("f not handled yet"); break;
    }
}
