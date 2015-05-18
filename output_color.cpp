// Tyler Cole
// EVO Project Module Implementation
// output_color.cpp

#include "output_color.h"
using namespace std;

void output_color( const string& s, unsigned int width, char align )
{
  static WORD F = 0, B = 0;  
  unsigned int i, size = s.size();
  
  while ( align == 'R' && width > size )
  {
    cout << " ";
    width--;
  }
  
  for (i = 0; i < size; i++)
  {
    if (i != size - 1) // not end of string
    {
      if (s[i] == '$' || s[i] == '%')
      {
        switch( s[i] )
        {
          case('$'): switch( s[i + 1] )
          {
            case('k'): F = FOREGROUND_BLACK; break;
            case('r'): F = FOREGROUND_RED; break;
            case('g'): F = FOREGROUND_GREEN; break;
            case('b'): F = FOREGROUND_BLUE; break;
            case('c'): F = FOREGROUND_CYAN; break;
            case('p'): F = FOREGROUND_MAGENTA; break;
            case('y'): F = FOREGROUND_BROWN; break;
            case('w'): F = FOREGROUND_LIGHTGRAY; break;
            case('K'): F = FOREGROUND_DARKGRAY; break;
            case('R'): F = FOREGROUND_LIGHTRED; break;
            case('G'): F = FOREGROUND_LIGHTGREEN; break;
            case('B'): F = FOREGROUND_LIGHTBLUE; break;
            case('C'): F = FOREGROUND_LIGHTCYAN; break;
            case('P'): F = FOREGROUND_LIGHTMAGENTA; break;
            case('Y'): F = FOREGROUND_YELLOW; break;
            case('W'): F = FOREGROUND_WHITE; break;
            default: cout << '$' << s[i + 1]; break;
          } break;
          
          case('%'): switch( s[i + 1] )
          {
            case('k'): B = BACKGROUND_BLACK; break;
            case('r'): B = BACKGROUND_RED; break;
            case('g'): B = BACKGROUND_GREEN; break;
            case('b'): B = BACKGROUND_BLUE; break;
            case('c'): B = BACKGROUND_CYAN; break;
            case('p'): B = BACKGROUND_MAGENTA; break;
            case('y'): B = BACKGROUND_BROWN; break;
            case('w'): B = BACKGROUND_LIGHTGRAY; break;
            case('K'): B = BACKGROUND_DARKGRAY; break;
            case('R'): B = BACKGROUND_LIGHTRED; break;
            case('G'): B = BACKGROUND_LIGHTGREEN; break;
            case('B'): B = BACKGROUND_LIGHTBLUE; break;
            case('C'): B = BACKGROUND_LIGHTCYAN; break;
            case('P'): B = BACKGROUND_LIGHTMAGENTA; break;
            case('Y'): B = BACKGROUND_YELLOW; break;
            case('W'): B = BACKGROUND_WHITE; break;
            default: cout << '%' << s[i + 1]; break;
          } break;
        }        
        
        set_text_color( F, B );
        i++;
      }
      else
      { // output this char because it's normal.
        cout << s[i];
      }
    }
    else
    { // just output the last char, no checks
      cout << s[i];
    }
  }
  
  while ( align == 'L' && width > size )
  {
    cout << " ";
    width--;
  }
}

//------------------------------------------------------------------------------

string filter_color( const string& s )
{
  string rs = "";
  
  unsigned int i, size = s.size();
  for (i = 0; i < size; i++)
  {
    if (i != size - 1) // not end of string
    {
      if (s[i] == '$' || s[i] == '%')
      {
        i++; // skip next char
      }
      else
      {
        rs += s[i];
      }
    }
    else
    {
      rs += s[i];
    }
  }
  return rs;
  
}

// end of file
