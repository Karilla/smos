#include "screen.h"
#include "../cpu/ports.h"
/*
unsigned char backcolour, int x, int y) {
  
*/

void update_cursor(int x, int y)
{
	uint16_t pos = y * 20 + x;
 
	port_byte_out(0x3D4, 0x0F);
	port_byte_out(0x3D5, (uint8_t) (pos & 0xFF));
	port_byte_out(0x3D4, 0x0E);
	port_byte_out(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
}

void printk_char_private(char c ,unsigned char forecolour,unsigned char backcolour, int x, int y){
  uint16_t attrib =
      (backcolour << 4) | (forecolour & 0x0F);
  volatile uint16_t *where;
  where = (volatile uint16_t *)0xB8000 + (y * 80 + x);
  *where = c | (attrib << 8);
}
void clear_screen()
{
  int screen_size = MAX_COL * MAX_ROW;
    int i;
    char *screen = 0xB8000;

    for (i = 0; i < screen_size; i++) {
        screen[i*2] = ' ';
        screen[i*2+1] = 0x0f;
    }
  update_cursor(0,0);
}

void print_string(char *message)
{
  int iterator = 0;
  while (message + iterator != 0)
  {
    printk_char_private(*(message + iterator), 0,
                        0xff, -1, -1);
  }
}

int get_offset()
{
  /*
  uint16_t offset;
  port_byte_out(0x3D4, 0x0F);
  offset = port_word_in(0X3D5);
  port_byte_out(0x3D4, 0x0E);
  offset
*/  
}

void set_cursor_offset(int offset) {
    /* Similar to get_cursor_offset, but instead of reading we write data */
    offset /= 2;
    port_byte_out(VIDEO_INDEX_REGISTER, 14);
    port_byte_out(VIDEO_INDEX_DATA, (unsigned char)(offset >> 8));
    port_byte_out(VIDEO_INDEX_REGISTER, 15);
    port_byte_out(VIDEO_INDEX_DATA, (unsigned char)(offset & 0xff));
}



void enable_cursor(uint8_t start, uint8_t end)
{
  update_cursor(0,0);
  port_byte_out(VIDEO_INDEX_REGISTER, 0x0A);
  port_byte_out(VIDEO_INDEX_DATA, (port_byte_in(0x3D5) & 0xC0) | start);

  port_byte_out(VIDEO_INDEX_REGISTER, 0x0B);
  port_byte_out(VIDEO_INDEX_DATA, (port_byte_in(0x3D5) & 0xE0) | end);
}

