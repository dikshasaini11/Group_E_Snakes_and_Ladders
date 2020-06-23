#ifndef snakesladders_H
#define snakesladders_H

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

#endif
