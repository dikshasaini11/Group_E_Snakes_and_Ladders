/**
* \file snakesladders.c
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
#include <termios.h>
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
/**
 * \Brief: This function decides if player should move, increments players turn and outputs player's new position
 *	Based on if turn is even or odd, function decides which player's turn it is. It does not let player's start playing till
 *	they roll 1 or 6. After each turn, function checks if player settles on snake or ladders and changes positions accordingly.
 *	Player's keep playing till one of them reaches 100. Player cannot exceed the value of 100.
 */
int main_game();
	
/** /brief Function to move the cursor  to specific position.
*Input parameters are x-coordinate and y-co-ordinate.
*Places cursor at given coordinate position.
*/
int locate(int x,int y);

/** /brief Function to display the first screen of the game
*Takes location in form of x,y coordinates
*prints the name at given position.
*/
void display_fstscr();

/** /brief Function to draw a layout for game which is a grid of 10x10
*/
void draw_layout();

/** /brief Function to draw snakes and ladders on the board
*/
int draw_snakesladders();

/** /brief Function to pick a random number between 1 and 6 and return as dice value*/

int roll_dice();

/** /Brief Function to read positions of snakes and ladders from file ‘snakesladders.dat’
 */

int check_snake_ladder(int current_position);

/** /Brief Function to load any previously saved game’
* It takes gamename and password as user input
* Reads data from 'players.dat' file
* Loads game according to data read from file.
*/

void loadgame();

/**
* /brief variable declaration before main function begins
*
* @param[in] players pdata This is the variable of structure players_t
* @param[in] startup declaring and initialising startup value.. 
*/

players_t pdata;
position_t p1in,p2in;
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
    /* Variables are declared to take input from the user*/	
    int option;   
    char choice;  
  
    if (startup==46){
        /*First screen function is called and the screen automatically moves to main menu screen*/
        display_fstscr();  
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
 * \Brief: This function decides if player should move, increments players turn and outputs player's new position
 *	Based on if turn is even or odd, function decides which player's turn it is. It does not let player's start playing till
 *	they roll 1 or 6. After each turn, function checks if player settles on snake or ladders and changes positions accordingly.
 *	Player's keep playing till one of them reaches 100. Player cannot exceed the value of 100.
 */
int main_game()
{
	/*initialise console screen to print text*/

	HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	/* draw layout */
	draw_layout();
	getchar();

	/*p1 is position of player 1. */
	while (p1!=100&&p2!=100){

	    turn++;

	    /*dice function will return value of dice*/

	    int dice_value=roll_dice();

	    /*if turn no is even, this is used to indicate that it is player one's turn*/
		if (turn%2==0){

			printf ("\nPlayer 1, it is your turn. Press enter to roll the dice.\n");
			getchar();
			/*using value obtained from dice roll function */
			printf("Player1, The value of your dice is %d\n", dice_value);
			/* player cannot exceed 100*/
			if ((p1+dice_value)>100){
				printf("Player 1, you have exceeded the value of 100. Please wait for your turn and try again\n");
			}else if (p1==0){
				/* player can only start playing if the obtain 1 or 6*/
				if (dice_value==1 || dice_value==6){
					locate(45,45);
					printf ("Player 1,you may now start playing the game in your next turn.");
					p1=1;
				}
			}else{
				/*loop to increment value of p1 according to dice value*/
				for (int j=1;j<=dice_value;j++){
					p1=p1+1;
				}
				/*checks position to see if it lands on snakes or ladders*/
				p1=check_snake_ladder(p1);
				printf("After this turn, your new position  is %d.\n",p1);

				}

			}else {
			/*repeated for player 2*/

			printf ("Player 2, it is your turn. Press enter to continue.\n");
			getchar();
			printf("The value of your dice is %d\n", dice_value);
			if ((p2+dice_value)>100){
				  printf("Player 2, you have exceeded the value of 100. Please wait for your turn and try again");
			}else if (p2==0){
				if (dice_value==1 || dice_value==6){
					locate(45,45);
					printf ("Player 2, you may now start playing the game in your next turn.");
					p2=1;
				}
			}
			else{
				for (int j=1;j<=dice_value;j++){
					p2=p2+1;



				}
				p2=check_snake_ladder(p2);
				printf("After this turn, your new position  is %d. \n",p2);

			 }

		}

	}
	/*winning condition*/
	if (p1==100){

		printf("Player 1, you are the winner!");

	}else if(p2==100){

		printf("Player 2, you are the winner!");
	}



	return 0;

}

/**
* This function sets cursor position to specific coordinates so output can be printed at the location
* @param[in] x, y Coordinates from user 
* @param[out] coord output at the specific position on the screen
*/
int locate(int x,int y){

    COORD coord;
    coord.X=x;
    coord.Y=y;


    HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition( hConsole, coord);


    if (! SetConsoleCursorPosition(hConsole, coord)){
          //printf("Function failed (%d)\n", GetLastError());
          return 0;

     }else{
    	 return 1;
     }
}

/**
*display_fstscr() displays the very first screen of the project
*GetStdHandle() is used for standard output on console window which is used to color text on the screen
*
*/

void display_fstscr()
{
	HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 14);
    
	system("clear"); 
	locate (48,17);
	printf("*********************************************************************\n");
        printf("\t\t\t\t\t\t                   Snakes and Ladders Game                     \n");
	printf("\t\t\t\t\t\t*********************************************************************\n");
            locate(30,30);      
			printf("\t\t\t\t\t\tLOADING.......\n");
            locate (105,35);
			printf ("Programmed By (Group E)\n");
         
}


/** 
* Draws layout of the game board with yellow colour.
* GetStdHandle() is used for standard output on console window which is used to color the grid of layout. 
*/
void draw_layout() {
	system("clear");
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
	draw_snakesladders();

	}

/**Draws snakes and ladders on the grid of 10x10.
*Snakes are displayed in red colour, ladders are displayed in green colour.
*GetStdHandle() is used for standard output on console window which is used to color snakes and ladders.
*Positions of snakes and ladders are read from file 'snakesladders.dat' and stored in structure 'position_t'.
*/
int draw_snakesladders()
{
    HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    position_t pos;

    /*Opening dat file to read data*/
    FILE *file;
    file=fopen("snakesladders.dat","r");

   /* Loop to check end of file.It reads integer values from first four columns.*/
   while (EOF != fscanf(file,"%d%d%d%d",&pos.startpt,&pos.endpt,&pos.xpos,&pos.ypos)){
        /*Decides whether it is a starting point of snake or ladder*/
        //For ladder
        if(pos.startpt<pos.endpt){
            SetConsoleTextAttribute(hConsole,FOREGROUND_INTENSITY | FOREGROUND_GREEN);

            /*Moves cursor to specific position to draw ladder.*/
            locate(pos.xpos,pos.ypos);
            printf("<##");
            pos.xpos += 2;

            /*To decide height of ladder*/
            if(pos.xpos % 2 == 0){
                for(int i=0;i<6;i++){
                   pos.ypos -= 1;
                   locate(pos.xpos,pos.ypos);
                   printf("#");
                }
            }else{
                for(int i=0;i<8;i++){
                   pos.ypos -= 1;
                   locate(pos.xpos,pos.ypos);
                   printf("#");
                }

            }
         }
        /*For snakes*/
        else{
            SetConsoleTextAttribute(hConsole,FOREGROUND_INTENSITY | FOREGROUND_RED);
            /*Moves cursor to specific position to draw snakes*/
            locate(pos.xpos,pos.ypos);
            printf("<**");
            pos.xpos += 2;

            /*To decide length of snake*/
            if(pos.xpos %2 == 0){
              for(int i=0;i<5;i++){

                pos.ypos += 1;
                locate(pos.xpos,pos.ypos);
                printf("*");
               }
                pos.ypos += 1;
                locate(pos.xpos,pos.ypos);
                printf("t");
            }else{
                for(int i=0;i<9;i++){
                    pos.ypos += 1;
                    locate(pos.xpos,pos.ypos);
                    printf("*");
                }
                pos.ypos += 1;
                locate(pos.xpos,pos.ypos);
                printf("t");
            }

        }
    }

   locate(50,20);
   SetConsoleTextAttribute(hConsole,FOREGROUND_BLUE+FOREGROUND_RED+FOREGROUND_GREEN+FOREGROUND_RED+FOREGROUND_RED);
   return 0;
}


/**
 * \Brief fn to pick a random number between 1 and 6 and return as dice value
 */

int roll_dice()
{
    int dice_value;
    /* set seed value according to computer's internal clock */
    srand(time(NULL));
    /* rand() function generates value between 0 and 5*/
    dice_value=(rand()%6)+1;
    return dice_value;
}

/**
 * \Brief fn read positions of snakes and ladders from file ‘snakesladders.dat’
 */

int check_snake_ladder(int current_position)
{
	position_t pos;

	/*Opening dat file to read data*/
	FILE *file;
	file=fopen("snakesladders.dat","r");
	if (file==NULL){
		return 0;
	}
   /* Loop to check end of file.It reads integer values from first four columns.*/
   while (EOF != fscanf(file,"%d%d%d%d",&pos.startpt,&pos.endpt,&pos.xpos,&pos.ypos)){
	   //printf ("the initial and final positions are %d,%d\n.",pos.startpt,pos.endpt);
	   if (current_position==pos.startpt){
		   if (pos.startpt<pos.endpt){
			   printf ("Woohoo! You have settled on a ladder\n");
			   current_position=pos.endpt;

		   }else if (pos.startpt>pos.endpt){
			   printf ("Sorry you have hit a snake\n");
			   current_position=pos.endpt;
		   }else{

		   }

	   }
   }
   return (current_position);


}

/**
 * \Brief loads previously saved game using gamename and password.
 */

void loadgame()
{
    FILE *p;
    int flag=0,temp[3];
    char pw[11];
    int filesize = 0;

    //Reads data from players.dat file
    p=fopen("players.dat","r");
    
    //Check if file doesn't exist
    if(p == NULL)
    {
        printf("File does not exist. You will be redirected soon.");
        sleep(3);
    }

    else
    {
        fseek(p, 0, SEEK_END);
        filesize = ftell(p);
        fclose(p);
    if(filesize != 0)
    {

    p=fopen("players.dat","r");

    for (;flag!=1 && p!=NULL;)
    {
	// verify gamename and password after entering
        printf ("\nEnter the authentication name of the game  ");
        scanf (" %[^\n]",name);
        printf ("Enter the password ");
		scanf("%c",pw);
        get_password(pw);
        while (!(feof(p)))
        {
            fscanf (p,"%d %d %d",&p1,&p2,&turn);
            fread(&pdata,sizeof(players_t),1,p);

            if ((strcmp(pdata.gamename,name))==0 && (strcmp(pdata.password,pw))==0)
            {
                printf ("\n**Authentication and Password Matched**\n press any key to load the game......");
                getchar();

                fclose(p);
                main_game();
                flag=1;
            }
            else continue;

        }
                printf ("Invalid Authentication name or Password!!!! Please Re-enter the data");
                getchar();
                main();

    }

    }
    else{
        printf("File is empty. You will be redirected soon");
        sleep(3);
    }
    }

}



