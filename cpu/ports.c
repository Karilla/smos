
// Read byte from port
unsigned char port_byte_in(unsigned short port)
{
    unsigned char result;
    asm("in %%dx, %%al": "=a" (result) : "d" (port));
    return result;
}

// Write byte to port
void port_byte_out(unsigned short port, unsigned char data)
{
    asm("out %%al, %%dx": : "a" (data), "d" (port));
}

// Read word from port
unsigned char port_word_in(unsigned short port)
{
    unsigned char result;
    asm("in %%dx, %%ax": "=a" (result) : "d" (port));
    return result;
}

// Write word to port
void port_word_out(unsigned short port, unsigned short data)
{
    asm("out %%ax, %%dx": : "a" (data), "d" (port));
}
