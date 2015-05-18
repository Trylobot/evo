// Tyler Cole
// EVO Project Module Implementation
// basic.cpp

#include "basic.h"
using namespace std;

string to_string( int i, unsigned int width, char align )
{
  string out = "";
  
  if      (align == 'r' || align == 'R') align = 'R';
  else if (align == 'l' || align == 'L') align = 'L';
  else                                   align = 'R';  
  
  if (i == 0) // zero
    out = "0";  
  else {
    if (i > 0) // positive
    {
      while (i > 0)
      {
        // add the LSB to the return string
        out = (char)((i % 10) + 48) + out;
        // pluck it off the integer value
        i /= 10;
      }
    }
    else // negative
    {
      i *= -1; // make it positive
      while (i > 0)
      {
        // add the LSB to the return string
        out = (char)((i % 10) + 48) + out;
        // pluck it off the integer value
        i /= 10;
      }
      out = "-" + out; // attach a (-) minus sign
    }
  }
  
  while (out.size() < width)
  {
    // fill with characters until it's wide enough
    if (align == 'R')
      out = " " + out;
    else
      out = out + " ";
  }
  
  return out;
}

//------------------------------------------------------------------------------

string to_lower( string s )
{
  for (unsigned int i = 0; i < s.size(); i++)
    s[i] = (char)tolower(s[i]);
  return s;
}

//------------------------------------------------------------------------------

string to_upper( string s )
{
  for (unsigned int i = 0; i < s.size(); i++)
    s[i] = (char)toupper(s[i]);
  return s;
}

//------------------------------------------------------------------------------

bool file_extension( string filename, string extension )
{
  if (filename.substr( (filename.size() - 4), 4 ) == (string(".") + extension) &&
      filename.size() > (1 + extension.size()) )
    return true;
  else
    return false;
}

//------------------------------------------------------------------------------

bool file_exist( string filename )
{
  ifstream file(filename.c_str());
  if (file)
    return true;
  else
    return false;
}

//------------------------------------------------------------------------------

void wait( double seconds )
{
  timer t;
  t.restart();
  while (t.elapsed_time() < seconds)
    { /* chill */ }
  t.stop();
}

//------------------------------------------------------------------------------

Location::Location()
{
  row = -1;
  col = -1;
}

Location::Location( int init_row, int init_col )
{
  row = init_row;
  col = init_col;
}

void Location::set( int new_row, int new_col )
{
  row = new_row;
  col = new_col;
}

Location Location::operator +  ( Location L )
{ return Location( row + L.row, col + L.col ); }

Location Location::operator += ( Location L )
{ row += L.row; col += L.col; return *this; }

Location Location::operator -  ( Location L )
{ return Location( row - L.row, col - L.col ); }

Location Location::operator -= ( Location L )
{ row -= L.row; col -= L.col; return *this; }

Location Location::operator *  ( int scalar )
{ return Location( row * scalar, col * scalar ); }

Location Location::operator /  ( int scalar )
{ return Location( row / scalar, col / scalar ); }

bool     Location::operator == ( Location L )
{ if (row == L.row && col == L.col) return true; else return false; }

bool     Location::operator != ( Location L )
{ if (row != L.row || col != L.col) return true; else return false; }

//------------------------------------------------------------------------------

void set_cursor( Location L )
{
  static COORD pos; pos.X = L.col; pos.Y = L.row;
  if (pos.X < 0) pos.X = 0;
  if (pos.Y < 0) pos.Y = 0;
  SetConsoleCursorPosition( GetStdHandle(STD_OUTPUT_HANDLE), pos );
}

//------------------------------------------------------------------------------

Location get_cursor()
{
  static CONSOLE_SCREEN_BUFFER_INFO info;
  GetConsoleScreenBufferInfo( GetStdHandle(STD_OUTPUT_HANDLE), &info );
  return Location( info.dwCursorPosition.Y, info.dwCursorPosition.X );
}

//------------------------------------------------------------------------------

void set_size( unsigned int height, unsigned int width )
{
  COORD dwSize;
  dwSize.Y = height; dwSize.X = width;
  SetConsoleScreenBufferSize( GetStdHandle(STD_OUTPUT_HANDLE), dwSize );
}

//------------------------------------------------------------------------------

void set_text_color( WORD fore, WORD back )
{
  SetConsoleTextAttribute( GetStdHandle(STD_OUTPUT_HANDLE), fore | back );
}

//------------------------------------------------------------------------------

void hide_cursor()
{
  static CONSOLE_CURSOR_INFO info;
  info.dwSize = 30;
  info.bVisible = false;
  SetConsoleCursorInfo( GetStdHandle(STD_OUTPUT_HANDLE), &info );
}

//------------------------------------------------------------------------------

void show_cursor()
{
  static CONSOLE_CURSOR_INFO info;
  info.dwSize = 30;
  info.bVisible = true;
  SetConsoleCursorInfo( GetStdHandle(STD_OUTPUT_HANDLE), &info );
}

// end of file
