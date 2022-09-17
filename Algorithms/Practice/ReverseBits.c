#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

uint8_t reverse_bits( const uint8_t inval) {
/*
sample in: 1000 0010b (0x82)
sample out 0100 0001b (0X41)
MSB becomes LSB
*/

    uint8_t refData = 1;
    uint8_t outval = 0;
    for(int i = 0 ; i < 8 ; ++i)
    {
        refData = refData << i;
        outval = (outval) | ( (inval & refData) << (7 - i) );
    }

    return outval;
}

void Displaydata(uint8_t inval)
{
    printf("Displaydata - inval = %d\n", inval);
    uint8_t dispData[8];
    for(int i = 0 ; inval > 8 ; ++i)
    {
        printf("(inval<<i) MOD 2 : %d", (int)((inval<<i) % 2));
        dispData[i] = (inval<<i) % 2;
    }
    for(int i = 7 ; i <= 0 ; --i)
        printf("%d", dispData[i]);
    printf("\n");
}

void main()
{
    uint8_t inpData = 0b11001110;
    uint8_t outData = reverse_bits(inpData);
    Displaydata(inpData);
    Displaydata(outData);


}