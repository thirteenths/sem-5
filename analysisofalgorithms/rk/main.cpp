#include <iostream>
using namespace std;
#include <stdio.h>

#include "head.h"

#define home() 			printf(ESC "[H") //Move cursor to the indicated row, column (origin at 1,1)
#define clrscr()		printf(ESC "[2J") //lear the screen, move to (1,1)
#define gotoxy(x,y)		printf(ESC "[%d;%dH", y, x);
#define visible_cursor() printf(ESC "[?251");
//Set Display Attribute Mode	<ESC>[{attr1};...;{attrn}m
#define resetcolor() printf(ESC "[0m")
#define set_display_atrib(color) 	printf(ESC "[%dm",color)

void frame_draw () {
	home();
	set_display_atrib(B_BLUE);
//            12345678901234567890123456789012345678901234567890123456789012345678901234567890
	puts(	"┌────────────────────────────────────────────────────────────────────────────────┐\n" //0
			"│                                                                                │\n" //1
			"│                                                                                │\n" //2
			"│                                                                                │\n" //3
			"│                                                                                |\n" //4
			"│                                                                                │\n" //5
			"│                                                                                │\n" //6
			"│                                                                                │\n" //7
			"│                                                                                │\n" //8
			"└────────────────────────────────────────────────────────────────────────────────┘\n" //9
			"┌──────────────────────────────────────────────────────────────────────────────────┐\n" //10
			"│                                                                                  │\n" //11
			"└────────────────────|────────────────────|───────────────────|────────────────────┘");  //12
//            12345678901234567890123456789012345678901234567890123456789012345678901234567890
	resetcolor();
}


int main (void) {
	home();
	clrscr();
	printf("Home + clrscr\n");

    frame_draw();

	/*gotoxy(20,7);
	printf("gotoxy(20,7)");
	
	gotoxy(1,10);
	printf("gotoxy(1,10)  \n\n");
	
	set_display_atrib(BRIGHT);
	printf("Formatting text:\n");
	resetcolor();
	
	set_display_atrib(BRIGHT);
	printf("Bold\n");
	resetcolor();
	
	set_display_atrib(DIM);
	printf("Dim\n");
	resetcolor();

	set_display_atrib(BLINK);
	printf("Blink\n");
	resetcolor();

	set_display_atrib(REVERSE);
	printf("Reverse\n");
	printf("\n");
	

	set_display_atrib(BRIGHT);
	printf("Text color example:\n");
	resetcolor();
	
	set_display_atrib(F_RED);
	printf("Red\n");
	resetcolor();
	
	set_display_atrib(F_GREEN);
	printf("Green\n");
	resetcolor();

	set_display_atrib(F_BLUE);
	printf("Blue\n");
	resetcolor();

	set_display_atrib(F_CYAN);
	printf("Cyan\n");
	resetcolor();

	set_display_atrib(BRIGHT);
	printf("\nBottom color example:\n");
	resetcolor();	
	
	set_display_atrib(B_RED);
	printf("Red\n");
	resetcolor();
	
	set_display_atrib(B_GREEN);
	printf("Green\n");
	resetcolor();

	set_display_atrib(B_BLUE);
	printf("Blue\n");
	resetcolor();

	set_display_atrib(B_CYAN);
	printf("Cyan\n");
	printf("\n");
	resetcolor();*/
	return 0;
}