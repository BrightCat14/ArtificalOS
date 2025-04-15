#define WHITE_TXT 0x07
#define VIDEO_MEMORY (char *) 0xb8000
#define KEYBOARD_PORT 0x60

void k_clear_screen();
void k_putc(char c, unsigned int row, unsigned int col);
void k_printf(char *message, unsigned int row);
void k_info(unsigned int *line);
void k_clear(unsigned int *line);
void k_help(unsigned int *line);
void k_read_input(char *buffer, unsigned int max_len, unsigned int *line);
unsigned int k_strcmp(char *s1, char *s2);
void k_hide_cursor(void);
void k_show_cursor();
void k_move_cursor(unsigned int row, unsigned int col);
unsigned char inb(unsigned short port);
void outb(unsigned short port, unsigned char val);

void k_main()
{
    unsigned int current_line = 0;
    char input[100];

    k_clear_screen();
    k_hide_cursor();
    k_printf("Hello, world! Welcome to my kernel.", current_line++);
    k_info(&current_line);

    while (1) {
        k_printf("Enter command: ", current_line);
        k_read_input(input, 100, &current_line);
    
        if (k_strcmp(input, "info") == 0) {
            k_info(&current_line);
        } else if (k_strcmp(input, "help") == 0) {
            k_help(&current_line);
        } else if (k_strcmp(input, "clear") == 0) { 
            k_clear_screen(); 
        } else {
            k_printf("Unknown command.", current_line); 
        }
    }

}

void k_clear_screen()
{
    char *vidmem = VIDEO_MEMORY;
    for (int i = 0; i < 80 * 25 * 2; i += 2)
    {
        vidmem[i] = ' ';
        vidmem[i + 1] = WHITE_TXT;
    }
}

void k_putc(char c, unsigned int row, unsigned int col)
{
    char *vidmem = VIDEO_MEMORY;
    unsigned int offset = (row * 80 + col) * 2;
    vidmem[offset] = c;
    vidmem[offset + 1] = WHITE_TXT;
}

void k_printf(char *message, unsigned int row)
{
    char *vidmem = VIDEO_MEMORY;
    unsigned int offset = row * 80 * 2;
    while (*message)
    {
        if (*message == '\n') {
            row++;
            offset = row * 80 * 2;
            message++;
            continue;
        }
        vidmem[offset++] = *message++;
        vidmem[offset++] = WHITE_TXT;
    }
}

void k_info(unsigned int *line)
{
    k_printf("Kernel version: 0.0.1", (*line)++);
    k_printf("Developed by: AkaruiNeko", (*line)++);
    k_printf("This is a tiny kernel shell.", (*line)++);
}

void k_clear(unsigned int *line)
{
    k_clear_screen();
}

void k_help(unsigned int *line)
{
    k_printf("Available commands:", (*line)++);
    k_printf("info - Display kernel information.", (*line)++);
    k_printf("help - Show this help message.", (*line)++);
    k_printf("clear - Clear the screen.", (*line)++);
}

void k_read_input(char *buffer, unsigned int max_len, unsigned int *line)
{
    unsigned int i = 0;
    unsigned char scancode;
    unsigned char ascii;
    int done = 0;
    unsigned char last_scancode = 0;
    int ready = 0;

    const char scancode_ascii[] = {
        0,  27, '1','2','3','4','5','6','7','8','9','0','-','=', '\b',
        '\t','q','w','e','r','t','y','u','i','o','p','[',']','\n', 0,
        'a','s','d','f','g','h','j','k','l',';','\'','`', 0, '\\',
        'z','x','c','v','b','n','m',',','.','/', 0, '*', 0, ' '
    };

    while (!done && i < max_len - 1)
    {
        scancode = inb(KEYBOARD_PORT);

        if (scancode & 0x80) {
            ready = 1;
            continue;
        }

        if (!ready || scancode == last_scancode) {
            continue;
        }

        last_scancode = scancode;
        ready = 0;

        if (scancode < sizeof(scancode_ascii))
        {
            ascii = scancode_ascii[scancode];

            if (ascii == '\n') {
                buffer[i] = '\0';
                (*line)++;
                k_printf("\n", *line - 1);
                done = 1;
            }
            else if (ascii == '\b') {
                if (i > 0) {
                    i--;
                    k_putc(' ', *line, i + 15);
                }
            }
            else if (ascii) {
                buffer[i] = ascii;
                k_putc(ascii, *line, i + 15);
                i++;
            }
        }
    }

    buffer[i] = '\0';
    k_move_cursor(*line, i + 15); 
}

unsigned int k_strcmp(char *s1, char *s2)
{
    while (*s1 && (*s1 == *s2))
    {
        s1++;
        s2++;
    }
    return *s1 - *s2;
}

void k_hide_cursor(void)
{
    outb(0x3D4, 0x0A); 
    outb(0x3D5, 0x20);  
}

void k_show_cursor()
{
    k_printf("\033[?25h", 0); 
}

void k_move_cursor(unsigned int row, unsigned int col)
{
    unsigned short position = (row * 80) + col;
    outb(0x3D4, 0x0E);  
    outb(0x3D5, (unsigned char)(position >> 8));
    outb(0x3D4, 0x0F); 
    outb(0x3D5, (unsigned char)(position & 0xFF));
}


void outb(unsigned short port, unsigned char val)
{
    __asm__ volatile("outb %0, %1" : : "a"(val), "Nd"(port));
}

unsigned char inb(unsigned short port)
{
    unsigned char result;
    __asm__ volatile("inb %1, %0" : "=a"(result) : "Nd"(port));
    return result;
}

