/*
* 
*/

#include <stdio.h>
#include <stdint.h>

uint8_t Cs, Cd, S, D; 

uint8_t calculate_component( uint8_t _cmp, uint8_t _factor)
{   
    uint8_t cmp = 0;
    uint8_t factor = _factor + 1;
    if(!factor)
       cmp = _cmp;  
    else
    {
        uint16_t c = (uint16_t)_cmp;
        cmp = (c*factor)>>8;
    } 
    return cmp;
}


void main()
{
    Cs = 72;
    Cd = 156;
    D  = 0;
    S  = 255;
    
    int i;
    for(i=0; i<256; i++)
    {   
        uint8_t componentS = calculate_component( Cs, S );
        uint8_t componentD = calculate_component( Cd, D );
        printf("[%u, %u]\t--> ( %u, %u)\t- added --> %u\n", S, D, componentS, componentD, componentS + componentD );
        D += 1;
        S = 255 - D; 
    }
}
