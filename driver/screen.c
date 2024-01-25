#include "screen.h"


void printk_char_private(unsigned char c, unsigned char forecolour, unsigned char backcolour, int x, int y)
{
     uint16_t attrib = (backcolour << 4) | (forecolour & 0x0F);
     volatile uint16_t * where;
     where = (volatile uint16_t *)0xB8000 + (y * 80 + x) ;
     *where = c | (attrib << 8);
}

void clear_screen(){
     for(int i = 0; i < MAX_ROW; i++){
          for (int j = 0; j < MAX_COL; j++)
          {
               printk_char_private(' ',128,0,j,i);
          }
          
     }
}
