// Tyler Cole
// EVO Project Module Header
// basic.h

#ifndef _BASIC_H_
#define _BASIC_H_

#include <windows.h>
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <fstream>
#include "timer.h"

// converts [i] to a string, with field width [width], using fill character [fill]
string to_string( int i, unsigned int width = 0, char align = 'R');

// misc string functions
string to_lower( string s );
string to_upper( string s );

// waits a specified number of milliseconds
void wait( double seconds );

// filename tests
bool file_extension( string filename, string extension );
bool file_exist( string filename );

// enumerations
enum Direction
{ north, east, south, west, invalid_direction };
enum Actor_Type
{ empty, wall, plant, herbivore, carnivore, invalid_actor_type };
enum Action
{ move_forward, move_backward, turn_left, turn_right, change_state, invalid_action };

// Define the statistics data struct and some sub-structs
struct Data_Structure
{
  unsigned int  high_score;
  unsigned int  total_score;
  double        average_score;
  //deque<int>    score_q;
  //deque<double> average_q;
};
struct Statistics
{
  // top_scorer == score_vector[ sorted_index[ 0 ] ];
  //vector<unsigned int> sorted_index;
  
  // herbivores[i].score == score_vector[i];
  vector<unsigned int> score_vector;
  
  // These are storage structures for various misc statistics to be displayed at a later time.
  Data_Structure cycle;
  Data_Structure century;
  Data_Structure millenium;
};

// a basic two-element integer vector class
class Location
{
  public:  
  Location();
  Location( int init_row, int init_col ); // creates location with given (row,col)
  
  void set( int new_row, int new_col );
  Location operator +  ( Location L );
  Location operator += ( Location L );
  Location operator -  ( Location L );
  Location operator -= ( Location L );
  Location operator *  ( int scalar );
  Location operator /  ( int scalar );
  bool     operator == ( Location L );
  bool     operator != ( Location L );

  int row;
  int col;
};

// Console functions and some defines
void set_cursor( Location L );
Location get_cursor();
void hide_cursor();
void show_cursor();
void set_size( unsigned int height, unsigned int width );
void set_text_color( WORD fore, WORD back );

#define FOREGROUND_BLACK        0x0000  // text color is black
#define FOREGROUND_BLUE         0x0001  // text color is blue
#define FOREGROUND_GREEN        0x0002  // text color is green
#define FOREGROUND_CYAN         0x0003  // text color is cyan
#define FOREGROUND_RED          0x0004  // text color is red
#define FOREGROUND_MAGENTA      0x0005  // text color is magenta
#define FOREGROUND_BROWN        0x0006  // text color is brown
#define FOREGROUND_LIGHTGRAY    0x0007  // text color is lightgray
#define FOREGROUND_DARKGRAY     0x0008  // text color is darkgray
#define FOREGROUND_LIGHTBLUE    0x0009  // text color is lightblue
#define FOREGROUND_LIGHTGREEN   0x000A  // text color is lightgreen
#define FOREGROUND_LIGHTCYAN    0x000B  // text color is lightcyan
#define FOREGROUND_LIGHTRED     0x000C  // text color is lightred
#define FOREGROUND_LIGHTMAGENTA 0x000D  // text color is lightmagenta
#define FOREGROUND_YELLOW       0x000E  // text color is yellow
#define FOREGROUND_WHITE        0x000F  // text color is white
#define BACKGROUND_BLACK        0x0000  // background color is black
#define BACKGROUND_BLUE         0x0010  // background color is blue
#define BACKGROUND_GREEN        0x0020  // background color is green
#define BACKGROUND_CYAN         0x0030  // background color is cyan
#define BACKGROUND_RED          0x0040  // background color is red
#define BACKGROUND_MAGENTA      0x0050  // background color is magenta
#define BACKGROUND_BROWN        0x0060  // background color is brown
#define BACKGROUND_LIGHTGRAY    0x0070  // background color is lightgray
#define BACKGROUND_DARKGRAY     0x0080  // background color is darkgray
#define BACKGROUND_LIGHTBLUE    0x0090  // background color is lightblue
#define BACKGROUND_LIGHTGREEN   0x00A0  // background color is lightgreen
#define BACKGROUND_LIGHTCYAN    0x00B0  // background color is lightcyan
#define BACKGROUND_LIGHTRED     0x00C0  // background color is lightred
#define BACKGROUND_LIGHTMAGENTA 0x00D0  // background color is lightmagenta
#define BACKGROUND_YELLOW       0x00E0  // background color is yellow
#define BACKGROUND_WHITE        0x00F0  // background color is white

#endif
// end of file
