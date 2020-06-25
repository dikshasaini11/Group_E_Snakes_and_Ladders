#ifndef snakesladders_H
#define snakesladders_H

/** @brief Function decides if player should move, increments players turn and outputs player's new position
*
*	Player's keep playing till one of them reaches 100. Player cannot exceed the value of 100.
*
*/

int main_game()
  

/**  @brief Function prototypes to move the cursor  to specific position
* 
* This Function places curser at given coordinate position and takes Input parameters are x-coordinate and y-coordinate
*
*
*/

int locate(int x,int y);


/** @brief Function prototype to display the first screen of the game
*
* This Function is used to display the first screen of the game and takes the location in form of x,y coordinates
*
*
*/

void display_fstscr(void);


/**  @brief Function prototypes to draw a game board
*
* This function is used to draw a 10x10 grid as a game board
*
*
*/

void draw_layout(void);


/**  @brief Function prototypes to draw snakes and ladders on the board
*
* This function is used to draw snakes and ladders on the board
*
*
*/
 void draw_snakesladders(void);
  
  
 /** @brief Function prototypes to pick a random number between 1 and 6 and return as dice value
 *
 * This Function is used to pick a random number between 1 and 6 and return as dice value
 */
 
  int roll_dice();
  
 /** @brief Function read positions of snakes and ladders from file ‘snakesladders.dat’
 *
 * This Function is used to read positions of snakes and ladders from file ‘snakesladders.dat’
 *
 *
 */

int check_snake_ladder(int current_position);



/** @brief Function to get password from user’
*
* It takes memory pointer as input andGives password as output.
*/

void loadgame();



/** @brief Function to get password from user’
* It takes memory pointer as input and Gives password as output.
*/


int get_password(char *memory);



/** @brief Function to save the game’
* It takes user input for game name and password
* Saves data in file 'players.dat'.
*/
void save_game();

/**
* @brief function defined for functions to be used with cygwin terminal*/
int getch();

#endif
