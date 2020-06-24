#ifndef snakesladders_H
#define snakesladders_H

/** @brief Function decides if player should move, increments players turn and outputs player's new position
*
*	Based on if turn is even or odd, function decides which player's turn it is. It does not let player's start playing till
*
*	they roll 1 or 6. After each turn, function checks if player settles on snake or ladders and changes positions accordingly.
*
*	Player's keep playing till one of them reaches 100. Player cannot exceed the value of 100.
*
*/

int main_game()
  

/**  @brief Function prototypes to move the cursor  to specific position
* 
* This Function is used to move the curser to specific position
*
* Input parameters are x-coordinate and y-coordinate
*
* This Function places curser at given coordinate position
*
*
*/

int locate(int x,int y);


/** @brief Function prototypes to display the first screen of the game
*
* This Function is used to display the first screen of the game
*
* This Funtion takes the location in form of x,y coordinates
*
* This Function prints the name at given location
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
void draw_snakesladders(void)
  
  
 /** @brief Function prototypes to pick a random number between 1 and 6 and return as dice value
 *
 * This Function is used to pick a random number between 1 and 6 and return as dice value
 *
 *
 */

int roll_dice()
  
 /** @brief Function read positions of snakes and ladders from file ‘snakesladders.dat’
 *
 * This Function is used to read positions of snakes and ladders from file ‘snakesladders.dat’
 *
 *
 */

int check_snake_ladder(int current_position)


void loadgame();

/** /Brief Function to get password from user’
* It takes memory pointer as input
* Gives password as output.
*/

int get_password(char *memory);

/** /Brief Function to save the game’
* It takes user input for game name and password
* Saves data in file 'players.dat'.
*/

void save_game();

/**
* /brief variable declaration before main function begins
*
* @param[in] players pdata This is the variable of structure players_t
* @param[in] startup declaring and initialising startup value.. 
*/

/**
* /brief function defined for functions to be used with cygwin terminal*/
int getch();

#endif
