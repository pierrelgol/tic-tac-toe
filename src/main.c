/*
*
* Title : Tic-Tac-Toe
* Date of creation : 10/04/2023
* Author : PierreLgol
* github : https://github.com/pierrelgol
* 
* More : 
*
*   This is my first attempt at building anything serious in C.
*   It'a small project but as a self taught a pretty challenging.
*   at the time i had started learning C in february 2023.
*   it's not optimised, and probably not very elegant but its working.
*   The goal for me was to work on using struct and pointers.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//definition of constant :
#define NAME_LENGTH 9
#define CELL_SIZE 4
#define BOARD_SIZE 3
#define EXIT_SUCCESS 0
#define DEFAULT_CELL_STRING_REPRESENTATION "[_]"

//----------[ STRUCTS ]----------//

struct player
{

  _Bool is_winner;
  _Bool is_turn;
  char player_sigle;
  char name[NAME_LENGTH];

}g_player_1 = {0,1,'X',"Player_1"}, g_player_2 = {0,0,'O',"Player_2"};

struct square
{

  char string_representation[CELL_SIZE];

};

// definition of function:


//----------[ VIEW FUNCTIONS ]----------//

void print_start_menu();
void print_input_request_message(char* input_request);
void print_error_message(char* message);
void print_winner_message();
void print_board();


//----------[ CONTROLLER FUNCTIONS ]----------//

void play_turn();
void set_default_state();

//----------[ MODULE FUNCTIONS ]----------//

void player_has_win(struct player *ptr);
_Bool move_is_legal(int row, int col);

_Bool g_there_is_a_winner = 0;
int g_turn_count = 0;

// use of a global variable to limit usage of pointers.
struct square g_board[BOARD_SIZE][BOARD_SIZE];

int main()
{

  set_default_state();

  while(g_there_is_a_winner != 1)
  {
    print_start_menu();
    print_board();
    play_turn();
  }

  return EXIT_SUCCESS;
}

//----------[ VIEW FUNCTIONS ]----------//

void print_start_menu()
{
  printf("-------------------- Tic-Tac-Toe --------------------\n"); // 53 char long
}

void print_input_request_message(char* input_request)
{
  printf("%s\n",input_request);
}

void print_error_message(char* message)
{
  printf("%s\n",message);
}

void print_winner_message()
{
  struct player *ptr_winner;

  if (g_player_1.is_winner == 1)
  {
    ptr_winner = &g_player_1;
  }
  if (g_player_2.is_winner == 1)
  {
    ptr_winner = &g_player_2;
  }

  printf("GG %s win the game\n",ptr_winner->name);

}

void print_board()
{
  int i;
  int j;

  for( i = 0; i < BOARD_SIZE; ++i )
  {
    for( j = 0; j < BOARD_SIZE; ++j )
    {
      printf("%s",g_board[i][j].string_representation);
    }

    printf("\n");

  }

}

//----------[ CONTROLLER FUNCTIONS ]----------//

void play_turn()
{
  int input_row = -1;
  int input_col = -1;
  struct player* current_player;
  struct player* next_player;

  current_player = (g_player_1.is_turn == 1 ) ? (&g_player_1) : (&g_player_2);
  next_player = (g_player_1.is_turn != 1 ) ? (&g_player_1) : (&g_player_2);

  if(g_turn_count == 9)
  {
    printf("this is a draw no winner !\n");
    g_there_is_a_winner = 1;
    return;
  }
  while (input_row == -1 && input_col == -1)
  {
    print_input_request_message("Select the cell you want to play");
    scanf("%d %d",&input_row,&input_col);
  }

  if(input_row >= 0 && input_row <= 2 && input_col >= 0 && input_col <= 2)
  {
    if(move_is_legal(input_row,input_col))
    {
      g_turn_count += 1;
      g_board[input_row][input_col].string_representation[1] = current_player->player_sigle;
      current_player->is_turn = 0;
      next_player->is_turn = 1;
      player_has_win(current_player);
    }
    else
    {
      print_error_message("The cell has already been played :");
        play_turn();
    } 
  }
  else
  {
    print_error_message("The coordinates are out of bond try again :");
    play_turn();
  }

  if(current_player->is_winner == 1)
  {
    print_winner_message();
    g_there_is_a_winner = 1;
    return;
  }

}

void set_default_state()
{

  struct square c00 = {"[_]"};
  struct square c01 = {"[_]"};
  struct square c02 = {"[_]"};
  struct square c10 = {"[_]"};
  struct square c11 = {"[_]"};
  struct square c12 = {"[_]"};
  struct square c20 = {"[_]"};
  struct square c21 = {"[_]"};
  struct square c22 = {"[_]"};
  
  g_board[0][0] = c00;
  g_board[0][1] = c01;
  g_board[0][2] = c02;
  g_board[1][0] = c10;
  g_board[1][1] = c11;
  g_board[1][2] = c12;
  g_board[2][0] = c20;
  g_board[2][1] = c21;
  g_board[2][2] = c22;

}

//----------[ MODULE FUNCTIONS ]----------//

_Bool move_is_legal(int row, int col)
{
  _Bool is_empty_flag = 1;
  if( (strcmp(g_board[row][col].string_representation, DEFAULT_CELL_STRING_REPRESENTATION)) != 0 )
  {
    is_empty_flag = 0;
  }

  return is_empty_flag;
}


void player_has_win(struct player *current_player) // very verbose aproach but easier to work with for me.
{
  
  if( current_player->player_sigle == g_board[0][0].string_representation[1] )
  {
    if( current_player->player_sigle == g_board[0][1].string_representation[1] )
    {
      if (current_player->player_sigle == g_board[0][2].string_representation[1])
      {
        current_player->is_winner = 1;
      }
    }
  }
  if( current_player->player_sigle == g_board[1][0].string_representation[1] )
  {
    if( current_player->player_sigle == g_board[1][1].string_representation[1] )
    {
      if (current_player->player_sigle == g_board[1][2].string_representation[1])
      {
        current_player->is_winner = 1;
      }
    }
  }
  if( current_player->player_sigle == g_board[2][0].string_representation[1] )
  {
    if( current_player->player_sigle == g_board[2][1].string_representation[1] )
    {
      if (current_player->player_sigle == g_board[2][2].string_representation[1])
      {
        current_player->is_winner = 1;
      }
    }
  }
  if( current_player->player_sigle == g_board[0][0].string_representation[1] )
  {
    if( current_player->player_sigle == g_board[1][0].string_representation[1] )
    {
      if (current_player->player_sigle == g_board[2][0].string_representation[1])
      {
        current_player->is_winner = 1;
      }
    }
  }
  if( current_player->player_sigle == g_board[0][1].string_representation[1] )
  {
    if( current_player->player_sigle == g_board[1][1].string_representation[1] )
    {
      if (current_player->player_sigle == g_board[2][1].string_representation[1])
      {
        current_player->is_winner = 1;
      }
    }
  }
  if( current_player->player_sigle == g_board[0][2].string_representation[1] )
  {
    if( current_player->player_sigle == g_board[1][2].string_representation[1] )
    {
      if (current_player->player_sigle == g_board[2][2].string_representation[1])
      {
        current_player->is_winner = 1;
      }
    }
  }
  if( current_player->player_sigle == g_board[0][0].string_representation[1] )
  {
    if( current_player->player_sigle == g_board[1][1].string_representation[1] )
    {
      if (current_player->player_sigle == g_board[2][2].string_representation[1])
      {
        current_player->is_winner = 1;
      }
    }
  }
  if( current_player->player_sigle == g_board[0][2].string_representation[1] )
  {
    if( current_player->player_sigle == g_board[1][1].string_representation[1] )
    {
      if (current_player->player_sigle == g_board[2][0].string_representation[1])
      {
        current_player->is_winner = 1;
      }
    }
  }
}


