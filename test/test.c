/**
* @file test.c
*
* @brief Implementation of unit test cases.
*
* @author Diksha Saini
* @author Sayali Dhokar -
* @author Vidushi Gupta -
* @author Rupneet Kaur Gill -
*/

//We could generate only these testcases due to user input incursion.

#include <stdio.h>
#include <windows.h>//used in locate function
#include <string.h>
#include <stdio.h>
//#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <wincon.h>


typedef struct{
    char p1name[20];
    char p2name[20];
    char gamename[20];
    char password[10];
}players_t;

typedef struct{
	int startpt;
	int endpt;
    int xpos;
    int ypos;
    }position_t;


//definition of assert test

#define ASSERT_TEST(x)                        \
{                                         \
    if (x)                                \
    {                                     \
        fprintf(fp,"\n\nPASSED\n\n\n");               \
    }                                     \
    else                                  \
    {                                     \
        fprintf(fp,"\n\nFAILED\n\n\n"); \
    }                                     \
}

//All these functions are defined as per testing vesrion

void test_snakesladders();
int locate(int x, int y);
int check_snake_ladder(int current_position);
int draw_snakesladders(char filename[1500]);
int loadgame(char playersfile[1500], char name[10], char pw[11]);


players_t pdata;
int p1=0,p2=0,turn=1;

//main function that calls test cases

int main(){

    //This test function is called to test functions of the game.
	test_snakesladders();
	getchar();
	return 0;
}

//test cases
void test_snakesladders()
{
	//check locate functions
	 FILE *fp = fopen("testresults.txt","w");
     fprintf(fp,"***********************************TEST 1A*******************************\n");
     fprintf(fp,"We are going to test locate function with positive coordinate values \n");
     fprintf(fp,"Expected result is it should locate cursor at specific location\n ");
     ASSERT_TEST(locate(5,5)==1);
     fprintf(fp,"***********************************TEST 1B*******************************\n");
     fprintf(fp,"We are going to test locate function with negative coordinate values \n");
     fprintf(fp,"Expected result is it should give error\n ");
     ASSERT_TEST(locate(-50,21)==1);
     fprintf(fp,"***********************************TEST 1B*******************************\n");
     fprintf(fp,"We are going to test locate function with coordinate values (0,0) \n");
     fprintf(fp,"Expected result is it should place cursor at left upper corner\n ");
     ASSERT_TEST(locate(0,0)==1);

     //checks check_snake_ladder function

     fprintf(fp,"***********************************TEST 2A*******************************\n");
     fprintf(fp,"We are going to test if player is at ladder when 'snakesladders.dat' file is present\n");
     fprintf(fp,"Expected result is player should go to top of ladder that is current position should increment");
     ASSERT_TEST(check_snake_ladder(14)== 48);
     fprintf(fp,"***********************************TEST 2B*******************************\n");
     fprintf(fp,"We are going to test if player is at snake,when 'snakesladders.dat' file is present\n");
     fprintf(fp,"Expected result is current position should decreament\n ");
     ASSERT_TEST(check_snake_ladder(98)== 64);

     //checks draw snakes and ladders function

     fprintf(fp,"***********************************TEST 3A*******************************\n");
     fprintf(fp,"We are going to test draw_snakesladders function when 'snakesladders.dat' file is present\n");
     fprintf(fp,"Expected result is, it should draw snakes,ladders\n ");
     ASSERT_TEST(draw_snakesladders("snakesladders.dat") == 1);

     fprintf(fp,"***********************************TEST 3B*******************************\n");
     fprintf(fp,"We are going to test draw_snakesladders function when 'snakesladders.dat' file is not present\n");
     fprintf(fp,"Expected result is it should return 'file does not exist' since we are passing different file name\n ");
	 ASSERT_TEST(draw_snakesladders("dummyfile.dat") == 1);

	 //check load_game function
     fprintf(fp,"***********************************TEST 4A*******************************\n");
     fprintf(fp,"We are going to test load game function when given gamename and password matches with present in the file\n");
     fprintf(fp,"Expected result is 'Authentication successful\n ");
	 ASSERT_TEST(draw_snakesladders("dummyfile.dat") == 1);


	 fprintf(fp,"**********************************************************************\n");
	 fprintf(fp,"Only these many testcases we have generated due to user input incursion");
     fprintf(fp,"Expected result is 'Authentication successful\n ");

     fclose(fp);


}


//new way to define locate function to enable testing

int locate(int x,int y){

	COORD coord;
	coord.X=x;
	coord.Y=y;


	HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition( hConsole, coord);

    //exception handling coe that will return different value if function fails
    if (! SetConsoleCursorPosition(hConsole, coord)){
          //printf("Function failed (%d)\n", GetLastError());
          return 0;

     }else{
    	 // will return 1 is function is successfull
    	 return 1;
     }
}



int check_snake_ladder(int current_position)
{
	position_t pos;

	/*Opening dat file to read data*/
	FILE *file;
	file=fopen("snakesladders.dat","r");

	//this is exception handling I put in this code to make it work. Will return 0 if function fails
	if (file==NULL){
		return 0;
	}

   /* Loop to check end of file.It reads integer values from first four columns.*/
   while (EOF != fscanf(file,"%d%d%d%d",&pos.startpt,&pos.endpt,&pos.xpos,&pos.ypos)){
	   /* if player lands at a starting position, check if this is a snake or ladder*/

	   if (current_position==pos.startpt){
		   if (pos.startpt<pos.endpt){
			   printf ("Woohoo! You have settled on a ladder\n");
			   current_position=pos.endpt;

		   }else if (pos.startpt>pos.endpt){
			   printf ("Sorry you have hit a snake\n");
			   /*players position is moved to end point of snake or ladder*/
			   current_position=pos.endpt;
		   }else{

		   }

	   }
   }
   return (current_position);
}

/*exception handling version*/
int draw_snakesladders(char filename[1500])
{
    HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    position_t pos;

    /*Opening dat file to read data*/
	//filename = "snakesladders.dat"
    FILE *file;
    file=fopen(filename,"r");

	if (file==NULL){
		return 0;
	}


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

   SetConsoleTextAttribute(hConsole,FOREGROUND_BLUE+FOREGROUND_RED+FOREGROUND_GREEN+FOREGROUND_RED+FOREGROUND_RED);
   return 1;
}




























