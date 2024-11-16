//gcc provides header files automatically

#include <stddef.h>
#include <stdint.h>

//first, we need to do some basic checks to make sure the cross compiler is being used correctly

#if defined (__linux__)
#error "this code must be compiled with a cross compiler, lol."

#elif !defined (__i386__)
# error "this code must be compiled with an x86-elf compiler, lol"
#endif

//this is the x86's VGA textmode buffer. To display text, we write data to this memory location
volatile uint16_t* vga_buffer = (uint16_t*)0xB8000;
const int VGA_COLS = 80;
const int VGA_ROWS = 25; 
//display text in the top left of screen column = 0, row = 0
int term_col = 0;
int term_row = 0;
uint8_t term_color = 0x0F;

//function initiates terminal by clearing it
void term_init()
{
	//clear textmode buffer
	for (int col = 0; col<VGA_COLS; col++)
	{
	for (int row = 0; row< VGA_ROWS; row++)
	{
		//vga textmode buffer has size (vga cols*vga rows), given this, we find an index into the buffer for our character
		const size_t index = (VGA_COLS * row) + col;
		// Entries in the VGA buffer take the binary form BBBBFFFFCCCCCCCC, where:
			// - B is the background color
			// - F is the foreground color
			// - C is the ASCII character
		vga_buffer[index] = ((uint16_t))term_color << 8 | ''; //set character to blank (space character)
	
		}
	}
}

//this function places a single character onto the screen!!!
void term_putc(char c)
{
//we dont want to display ALL characters!!
switch(c)
{
	case '\n': //newline characters should return the column to 0, and incrment the row
	{
		term_col=0;
		term_row ++;
		break;
	}
	default://normal characters just get displayed and then incrment the column
	{
		const size_t index = (VGA_COLS*term_row)+term_col;
		//calculate buffer index
		vga_buffer[index]=((uint16_t)term_color<<8)|c;
		term_col ++;
		break;
		
	}
}
//we need to reset the column to 0 and increment the row to get to a new line if we get past the last column obv
if (term_col>= VGA_COLS)
{
	term_col = 0;
	term_row ++;
}
//with the last row, if we get past it, then we need to reset both column and row to 0 in order to loop back to the top of the screen

if (term_row >=VGA_ROWS)
{
	term_col=0;
	term_row=0;
}
}
//this prints an entire string onto the screen!! hurrah!!! yippe!!
void term_print (const char* str)
{
	for(size_t i = 0; str[i] != '\0'; i++)//keeps placing chars until we hit null terminating character ('\0')
	term_putc(str[i]);
}

//this is our kernels main function

void kernel_main()
{
	//WE DID LET LESSGO!!! now we can initiate the terminal and display a message
	//insert osaka nerd meme here
	
	//initate
	term_init();
	//diplay...
	term_print("Hello, World!\n");
	term_print("Meet Cyberbomb! Cyberbomb, say hi!\n");
}
