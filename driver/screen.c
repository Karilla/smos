#include "screen.h"
#include "../cpu/ports.h"
/**
 * Private function declaration
*/

void update_cursor(int x, int y);
void set_cursor_offset(int offset);
void enable_cursor(uint8_t start, uint8_t end);
void print_char(char c, int col, int row);
int get_video_index(int x, int y);


/**
 * Public function
*/

void clear_screen()
{
  int screen_size = MAX_COL * MAX_ROW;
  int i;
  char *screen = (char*)VIDEO_ADDRESS;

  for (i = 0; i < screen_size; i++)
  {
    screen[i * 2] = ' ';
    screen[i * 2 + 1] = 0x0f;
  }
  enable_cursor(0, 15);
  update_cursor(0, 0);
}

void print_simple_string(char* message){
  int i = 0;
  while (message[i] != 0)
  {
    print_char(message[i], i,0);
    i++;
  }
}

/**
 * Private function implementation
*/

void print_char(char c, int col, int row){
  char* screen = (char*) VIDEO_ADDRESS;
  int video_index = get_video_index(col, row);
  screen[video_index] = c;
  screen[video_index + 1] = 0x0f;
  update_cursor(col + 1,row);
}

void update_cursor(int x, int y)
{
  uint16_t pos = y * 20 + x;

  port_byte_out(0x3D4, 0x0F);
  port_byte_out(0x3D5, (uint8_t)(pos & 0xFF));
  port_byte_out(0x3D4, 0x0E);
  port_byte_out(0x3D5, (uint8_t)((pos >> 8) & 0xFF));
}

void printk_char_private(char c, unsigned char forecolour, unsigned char backcolour, int x, int y)
{
  uint16_t attrib =
      (backcolour << 4) | (forecolour & 0x0F);
  volatile uint16_t *where;
  where = (volatile uint16_t *)0xB8000 + (y * 80 + x);
  *where = c | (attrib << 8);
}

void set_cursor_offset(int offset)
{
  /* Similar to get_cursor_offset, but instead of reading we write data */
  offset /= 2;
  port_byte_out(VIDEO_INDEX_REGISTER, 14);
  port_byte_out(VIDEO_INDEX_DATA, (unsigned char)(offset >> 8));
  port_byte_out(VIDEO_INDEX_REGISTER, 15);
  port_byte_out(VIDEO_INDEX_DATA, (unsigned char)(offset & 0xff));
}

void enable_cursor(uint8_t start, uint8_t end)
{
  port_byte_out(VIDEO_INDEX_REGISTER, 0x0A);
  port_byte_out(VIDEO_INDEX_DATA, (port_byte_in(0x3D5) & 0xC0) | start);

  port_byte_out(VIDEO_INDEX_REGISTER, 0x0B);
  port_byte_out(VIDEO_INDEX_DATA, (port_byte_in(0x3D5) & 0xE0) | end);
}

int get_video_index(int x, int y){
  // We double cause the video array data is on 16 bit
  return 2 * (y * MAX_ROW + x);
}