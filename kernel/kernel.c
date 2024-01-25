#include "kernel.h"
#include <stdint.h>

void enable_cursor(){
    
}

void kernel_main() {
    clear_screen();
    for(char i = 0; i < 26; i++){
        WriteCharacter('a' + i,0xff,0,i,i);
    }
}