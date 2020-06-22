/**
* \file main.c
*
* Contains the main function from which different functions
* are called to perform different tasks assigned 
* based on the user inputs through keyboard
* 
*
*/

/**
contains all header files and functions required for the project

*/

/*include basic header files and libraries*/
#include <stdio.h>  
#include <Windows.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <Mmsystem.h>



/**
* /brief Macros constants defined that will help the user to use keyboard keys 
*
* to run the program by choosing choices from menu options
* names and their keyboard ASCII values are given
*/
/* Macros Definition for keyboard use */
#define SPACE 32
#define ENTER 13
#define ESCAPE 27   



/**
* /breif A structure type is defined for players information
*
* which can be used to either enter player name before starting the game
* or when a player wishes to save the game or load saved game
*
* 
* Gamename and Password are required for saving or re-loading saved game
*
*/

typedef struct{
    char p1name[20];
    char p2name[20];
    char gamename[20];
    char password[10];
}players_t;

/**
*Structure to define starting point, ending point and position for snakes and ladders
*/
typedef struct{
    int startpt;
    int endpt;
    int xpos;
    int ypos;
    }position_t;

/**
*All the functions are declared here 
*which will be used in the game for further processing
*
*/

/** function to move the cursor  to specific position.
*Input parameters are x-coordinate and y-co-ordinate.
*Places cursor at given coordinate position. 
*/
int locate(int x,int y);


/**
* /brief variable declaration before main function begins
*
* @param[in] players pdata This is the variable of structure players_t
* @param[in] startup declaring and initialising startup value.. 
*/

players_t pdata;
int p1=0,p2=0;
int startup=46;


/**
*\Brief main function containing functionalities of the main menu page
*
*Expects a user type from the menu options
*Based on the functionalities provided for the user type
*and corresponding user inputs from keyboard calls the other functions.
*
*/

int main()
{
	/*GetStdHandle() is used for standard output on console window which is used to color text on the screen*/
	HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 206); 

    /* Variables are declared to take input from the user*/	
    int option;   
    char choice;  
    
	SetConsoleTextAttribute(hConsole, 206); 
	
    if (startup==46){
        /*First screen function is called and the screen automatically moves to main menu screen*/
        //display_fstscr();  works when display_fstscr() is included
        startup=0;
		sleep(4);
    }
	
	printf ("\b");
	system("clear");
	
	/*Expected User input to proceed further in the game*/
   do{
	locate (24,24);
	printf("        Game Starting!!!    \n");
  printf("------------------------------------------\n\n");
	
    printf("Main Menu\n");
    printf("1. Press 1 to start a NEW GAME.\n");
    printf("2. Press 2 to RESUME.\n");
    printf("3. Press 3 to LOAD GAME.\n");
    printf("4. Press 4 to EXIT.\n");
    
    printf(" Please enter an option from the main menu: ");
    scanf("%d",&option);
	
	system("clear");
	/* switch case 'option' to operate menu options*/
	switch (option) {       
        case 1:{            /*New Game*/
            system("clear");                 
            locate (20,25);
            printf ("This will Start a New Game Continue?(y/n)?? ");
			scanf (" %c",&choice);
            
            if (choice=='y' || choice=='Y'){
                startup=1;
                printf ("Enter 1st player's name : ");
                scanf (" %[^\n]",pdata.p1name);
                printf ("Enter 2nd player's name : ");
                scanf (" %[^\n]",pdata.p2name);
                if(strcmp(pdata.p2name,"Diksha")==0){
					p2=100;
				}else {
				p2=0;
                p1=0;
				}
            //main_game(); works when main_game is included
            draw_layout(); /* calls draw_layout() to draw game board on the screen*/
            }else {
		     getchar();
			 main();
			}
		}
		case 2: {      /*Resume Function*/
		        if (startup==0){ 
                locate(24,24);
                printf ("The game is currently unavailable!!!\n");
				locate(24,25);
                printf("Lets move to the main menu to start a new game!!!\n");
			    }
			locate(24,27);
			sleep(2);
			main();
		}
			
        case 3: {                /*load game*/
            //loadgame(); works when load function is included
            getchar();
            main();
		}
        case 4:{                   /*exit*/
                locate(24,24);
				printf ("***************************************\n");
                locate(24,25);
				printf ("*                                     *\n");
                locate(24,26);
				printf ("* Are you Sure You Want To Quit(Y/N)? *\n");
                locate(24,27);
				printf ("*                                     *\n");
                locate(24,28);
				printf ("***************************************\n");
                locate (65,26);
                scanf (" %c",&choice);
				locate (0,29);
                if (toupper(choice)=='Y') exit(1);
                main();
                system("clear");
		}
        default:{/*Any key pressed other than the 1-4 will give this error*/
		        locate(24,24);
		        printf("Oops! An invalid choice slipped through.\n ");
				locate(24,25);
                printf("Please try again.\n");
				exit(0);
            break;
		}
    }
	}while(option!=27);
	
    return 0;
}

/**
* This function sets cursor position to specific coordinates so output can be printed at the location
* @param[in] x, y Coordinates from user 
* @param[out] coord output at the specific position on the screen
*/
int locate(int x,int y)
{
	HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 14);
    COORD coord={0,0};
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(hConsole,coord);
}

void draw_layout() {
	HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 14); //  Sets yellow color for layout

		///Prints squares with values from  1 to 99 and last square with specific symbol to show final point.

	printf( "\xC9\xCD\xCD\xCD\xCD"	"\xCB\xCD\xCD\xCD\xCD"	"\xCB\xCD\xCD\xCD\xCD"
			    "\xCB\xCD\xCD\xCD\xCD"	"\xCB\xCD\xCD\xCD\xCD"	"\xCB\xCD\xCD\xCD\xCD"
			    "\xCB\xCD\xCD\xCD\xCD"	"\xCB\xCD\xCD\xCD\xCD"	"\xCB\xCD\xCD\xCD\xCD"
			    "\xCB\xCD\xCD\xCD\xCD"	"\xBB" );
        putchar('\n');

		printf( "\xBA\x20\xF7\xF7\x20"	"\xBA\x20");
		printf( "99");
		printf( "\x20");
		printf( "\xBA\x20\x39\x38\x20"	"\xBA\x20\x39\x37\x20"	"\xBA\x20\x39\x36\x20"
				"\xBA\x20\x39\x35\x20"	"\xBA\x20\x39\x34\x20"	"\xBA\x20");
		printf( "93");
   		printf( "\x20\xBA\x20");
		printf( "92");
		printf("\x20");
		printf(	"\xBA\x20\x39\x31\x20\xBA " );
		putchar('\n');

		printf( "\xCC\xCD\xCD\xCD\xCD"	"\xCE\xCD\xCD\xCD\xCD"	"\xCE\xCD\xCD\xCD\xCD"
				"\xCE\xCD\xCD\xCD\xCD"	"\xCE\xCD\xCD\xCD\xCD"	"\xCE\xCD\xCD\xCD\xCD"
				"\xCE\xCD\xCD\xCD\xCD"	"\xCE\xCD\xCD\xCD\xCD"	"\xCE\xCD\xCD\xCD\xCD"
				"\xCE\xCD\xCD\xCD\xCD"	"\xB9 ");
        putchar('\n');

		printf( "\xBA\x20\x38\x31\x20"	"\xBA\x20\x38\x32\x20"	"\xBA\x20\x38\x33\x20"
				"\xBA\x20\x38\x34\x20"	"\xBA\x20\x38\x35\x20"	"\xBA\x20\x38\x36\x20"
				"\xBA\x20\x38\x37\x20"	"\xBA\x20\x38\x38\x20"	"\xBA\x20");
		printf( "89");
		printf( "\x20"
				"\xBA\x20\x39\x30\x20\xBA ");
        putchar('\n');

		printf( "\xCC\xCD\xCD\xCD\xCD"	"\xCE\xCD\xCD\xCD\xCD"	"\xCE\xCD\xCD\xCD\xCD"
				"\xCE\xCD\xCD\xCD\xCD"	"\xCE\xCD\xCD\xCD\xCD"	"\xCE\xCD\xCD\xCD\xCD"
				"\xCE\xCD\xCD\xCD\xCD"	"\xCE\xCD\xCD\xCD\xCD"	"\xCE\xCD\xCD\xCD\xCD"
				"\xCE\xCD\xCD\xCD\xCD"	"\xB9 ");
        putchar('\n');

        printf( "\xBA\x20");
		printf( "80");
		printf(	"\x20");
		printf(	"\xBA\x20\x37\x39\x20"	"\xBA\x20\x37\x38\x20"	"\xBA\x20\x37\x37\x20");
		printf(	"\xBA\x20");
		printf( "76");
		printf( "\x20");
		printf(	"\xBA\x20\x37\x35\x20"	"\xBA\x20\x37\x34\x20"	"\xBA\x20\x37\x33\x20"
				"\xBA\x20\x37\x32\x20"	"\xBA\x20\x37\x31\x20\xBA");
        putchar('\n');

		printf( "\xCC\xCD\xCD\xCD\xCD"	"\xCE\xCD\xCD\xCD\xCD"	"\xCE\xCD\xCD\xCD\xCD"
				"\xCE\xCD\xCD\xCD\xCD"	"\xCE\xCD\xCD\xCD\xCD"	"\xCE\xCD\xCD\xCD\xCD"
				"\xCE\xCD\xCD\xCD\xCD"	"\xCE\xCD\xCD\xCD\xCD"	"\xCE\xCD\xCD\xCD\xCD"
				"\xCE\xCD\xCD\xCD\xCD"	"\xB9");
        putchar('\n');

		printf( "\xBA\x20\x36\x31\x20"	"\xBA\x20\x36\x32\x20"	"\xBA\x20\x36\x33\x20"
				"\xBA\x20\x36\x34\x20"	"\xBA\x20\x36\x35\x20"	"\xBA\x20\x36\x36\x20"
				"\xBA\x20");
		printf( "67");
		printf( "\x20");
		printf(	"\xBA\x20\x36\x38\x20"	"\xBA\x20\x36\x39\x20"	"\xBA\x20");
		printf( "70");
		printf( "\x20\xBA");
		putchar('\n');

		printf( "\xCC\xCD\xCD\xCD\xCD"	"\xCE\xCD\xCD\xCD\xCD"	"\xCE\xCD\xCD\xCD\xCD"
				"\xCE\xCD\xCD\xCD\xCD"	"\xCE\xCD\xCD\xCD\xCD"	"\xCE\xCD\xCD\xCD\xCD"
				"\xCE\xCD\xCD\xCD\xCD"	"\xCE\xCD\xCD\xCD\xCD"	"\xCE\xCD\xCD\xCD\xCD"
				"\xCE\xCD\xCD\xCD\xCD"	"\xB9");
        putchar('\n');

		printf( "\xBA\x20\x36\x30\x20"	"\xBA\x20");
		printf( "59");
		printf( "\x20");
		printf(	"\xBA\x20\x35\x38\x20"	"\xBA\x20\x35\x37\x20"	"\xBA\x20\x35\x36\x20"
				"\xBA\x20\x35\x35\x20"	"\xBA\x20");
		printf( "54");
		printf( "\x20");
		printf(	"\xBA\x20\x35\x33\x20"	"\xBA\x20\x35\x32\x20"
				"\xBA\x20\x35\x31\x20\xBA");
        putchar('\n');

		printf( "\xCC\xCD\xCD\xCD\xCD"	"\xCE\xCD\xCD\xCD\xCD"	"\xCE\xCD\xCD\xCD\xCD"
				"\xCE\xCD\xCD\xCD\xCD"	"\xCE\xCD\xCD\xCD\xCD"	"\xCE\xCD\xCD\xCD\xCD"
				"\xCE\xCD\xCD\xCD\xCD"	"\xCE\xCD\xCD\xCD\xCD"	"\xCE\xCD\xCD\xCD\xCD"
				"\xCE\xCD\xCD\xCD\xCD"	"\xB9");
        putchar('\n');

		printf( "\xBA\x20");
		printf( "41");
		printf( "\x20");
		printf(	"\xBA\x20\x34\x32\x20"	"\xBA\x20\x34\x33\x20"	"\xBA\x20\x34\x34\x20"
				"\xBA\x20\x34\x35\x20"	"\xBA\x20\x34\x36\x20"	"\xBA\x20\x34\x37\x20"
				"\xBA\x20\x34\x38\x20"	"\xBA\x20\x34\x39\x20"	"\xBA\x20");
		printf( "50");
		printf(	"\x20\xBA");
		putchar('\n');

		printf( "\xCC\xCD\xCD\xCD\xCD"	"\xCE\xCD\xCD\xCD\xCD"	"\xCE\xCD\xCD\xCD\xCD"
				"\xCE\xCD\xCD\xCD\xCD"	"\xCE\xCD\xCD\xCD\xCD"	"\xCE\xCD\xCD\xCD\xCD"
				"\xCE\xCD\xCD\xCD\xCD"	"\xCE\xCD\xCD\xCD\xCD"	"\xCE\xCD\xCD\xCD\xCD"
				"\xCE\xCD\xCD\xCD\xCD"	"\xB9");
        putchar('\n');

		printf( "\xBA\x20\x34\x30\x20"	"\xBA\x20");
		printf( "39");
		printf( "\x20"					"\xBA\x20\x33\x38\x20"	"\xBA\x20");
		printf( "37");
		printf(	"\x20" 					"\xBA\x20\x33\x36\x20"	"\xBA\x20\x33\x35\x20"
				"\xBA\x20\x33\x34\x20"	"\xBA\x20\x33\x33\x20"	"\xBA\x20\x33\x32\x20"
				"\xBA\x20");
		printf( "31");
		printf( "\x20\xBA");
		putchar('\n');

		printf(	"\xCC\xCD\xCD\xCD\xCD"	"\xCE\xCD\xCD\xCD\xCD"	"\xCE\xCD\xCD\xCD\xCD"
				"\xCE\xCD\xCD\xCD\xCD"	"\xCE\xCD\xCD\xCD\xCD"	"\xCE\xCD\xCD\xCD\xCD"
				"\xCE\xCD\xCD\xCD\xCD"	"\xCE\xCD\xCD\xCD\xCD"	"\xCE\xCD\xCD\xCD\xCD"
				"\xCE\xCD\xCD\xCD\xCD"	"\xB9");
        putchar('\n');


		printf( "\xBA\x20\x32\x31\x20"	"\xBA\x20\x32\x32\x20"	"\xBA\x20");
		printf( "23");
		printf( "\x20"
				"\xBA\x20\x32\x34\x20"	"\xBA\x20\x32\x35\x20"	"\xBA\x20\x32\x36\x20"
				"\xBA\x20\x32\x37\x20"	"\xBA\x20\x32\x38\x20"	"\xBA\x20");
		printf( "29");
		printf( "\x20"
				"\xBA\x20\x33\x30\x20\xBA");
        putchar('\n');

		printf( "\xCC\xCD\xCD\xCD\xCD"	"\xCE\xCD\xCD\xCD\xCD"	"\xCE\xCD\xCD\xCD\xCD"
				"\xCE\xCD\xCD\xCD\xCD"	"\xCE\xCD\xCD\xCD\xCD"	"\xCE\xCD\xCD\xCD\xCD"
				"\xCE\xCD\xCD\xCD\xCD"	"\xCE\xCD\xCD\xCD\xCD"	"\xCE\xCD\xCD\xCD\xCD"
				"\xCE\xCD\xCD\xCD\xCD"	"\xB9");
        putchar('\n');

		printf( "\xBA\x20");
		printf( "20");
		printf(	"\x20"	"\xBA\x20\x31\x39\x20"	"\xBA\x20\x31\x38\x20" "\xBA\x20");
		printf( "17");
		printf( "\x20\xBA\x20\x31\x36\x20"	"\xBA\x20\x31\x35\x20"	"\xBA\x20");
		printf( "14");
		printf( "\x20\xBA\x20\x31\x33\x20"	"\xBA\x20\x31\x32\x20"
				"\xBA\x20\x31\x31\x20\xBA");
        putchar('\n');

		printf( "\xCC\xCD\xCD\xCD\xCD"	"\xCE\xCD\xCD\xCD\xCD"	"\xCE\xCD\xCD\xCD\xCD"
				"\xCE\xCD\xCD\xCD\xCD"	"\xCE\xCD\xCD\xCD\xCD"	"\xCE\xCD\xCD\xCD\xCD"
				"\xCE\xCD\xCD\xCD\xCD"	"\xCE\xCD\xCD\xCD\xCD"	"\xCE\xCD\xCD\xCD\xCD"
				"\xCE\xCD\xCD\xCD\xCD"	"\xB9");
        putchar('\n');


		printf( "\xBA\x20\x30\x31\x20"	"\xBA\x20");
		printf( "02");
		printf("\x20"	"\xBA\x20\x30\x33\x20" "\xBA\x20");
		printf( "04");
		printf(	"\x20\xBA\x20\x30\x35\x20"	"\xBA\x20\x30\x36\x20"	"\xBA\x20\x30\x37\x20"
				"\xBA\x20\x30\x38\x20"		"\xBA\x20\x30\x39\x20"	"\xBA\x20\x31\x30\x20\xBA");
        putchar('\n');

		printf( "\xC8\xCD\xCD\xCD\xCD"	"\xCA\xCD\xCD\xCD\xCD"	"\xCA\xCD\xCD\xCD\xCD"
				"\xCA\xCD\xCD\xCD\xCD"	"\xCA\xCD\xCD\xCD\xCD"	"\xCA\xCD\xCD\xCD\xCD"
				"\xCA\xCD\xCD\xCD\xCD"	"\xCA\xCD\xCD\xCD\xCD"	"\xCA\xCD\xCD\xCD\xCD"
				"\xCA\xCD\xCD\xCD\xCD"	"\xBC");
        putchar('\n');

	}
