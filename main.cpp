/**************************************
*  EVO - The Evolution Simulator      *
*    (c) 2005 Tyler W. Cole           *
*                                     *
*  Done while in Computer Science     *
*  Program at the University of       *
*  North Texas, on my own time.       *
*  I'm pretty sure this program       *
*  R0xx0rz j00 b0xx0rz!!111eleven     *
*                                     *
**************************************/

/**************************************
*  Additional Credits go to:          *
*  Makoto Matsumoto (random.cpp)      *
*  Kenneth Wilder   (timer.cpp)       *
*  David Eck        ("Eaters" idea)   *
**************************************/

// EVO Project Main Module
// main.cpp

#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <string>
#include "basic.h"
#include "random.h"
#include "settings.h"
#include "ui.h"
#include "output_color.h"
#include "world.h"
#include "time.h"
using namespace std;

string settings_file;

int interpret( string cmd );
int parse( string line, World& sim );

//-----------------------------------------------------------------------------

int main()
{
  // seed the RNG
  seed(time(0));  
  
  // initialize global settings
  settings_file = read_ini();
  
  World sim;
  
  splash();
  int x;
  bool done = false;
  
  while( !done )
  {
    show_cursor();
    menu();
    output_color("$W");
    
    string line;
    getline( cin, line );
    output_color("$w\n\n");
  
    x = parse( line, sim );
    show_cursor();
          
    if (x == 0)
      continue; // do nothing more, start over
    
    else if (x < 0)
    {
      output_color("Simulator [$WEXIT$w]\n");
      done = true;
      break;
    }
    else // x > 0
    {
      if (global("FLAG_FAST") == 0)
      {
        system("cls"); // clear the screen once
      }
      
      while( x > 0 )
      {
        try
        {
          sim.do_cycle();
        }
        catch( int ex )
        {
          break;
        }
                
        x--;
      }
      
      if ( !global("FLAG_FAST") )
      {
        output_color("\n");
      }
      if (sim.get_current_cycle() > 1)
        output_color( sim.one_liner_field_labels_compact + string("\n") + sim.compact_stats_one_liner + string("\n\n") );
    }
  }
  
  // done, dude!
  return( EXIT_SUCCESS );
}

//------------------------------------------------------------------------------

int parse( string line, World& sim )
{
  if (line.empty())
    return 0;
  
  vector<string> token = tokenize( to_upper(line) );
  
  while( token.size() < 2 )
    token.push_back("BLANK");
  
  int x;
  switch( interpret( token[0] ))
  {
    // MENU
    case(    5):
      set_global("FLAG_MENU", ( (global("FLAG_MENU") == 0)? 1 : 0 ));
      return 0;
    break;
    
    // SLOW
    case(   10):
      set_global("FLAG_FAST", 0);
      return 1;
    break;
    
    // FAST
    case(   11):
      if (token[1] == "BLANK")
      { // need one more argument
        output_color("How many $Wcycles$w should I run in minimal mode?\n");
        cout << endl;
        return 0;
      }
      set_global("FLAG_FAST", 1);
      x = 0;
      x = atoi(token[1].c_str());
      return x;
    break;
    
    // ABOUT
    case(   30):
      hide_cursor();
      about();
      return 0;
    break;
    
    // NEW
    case(   40):
      sim.set_flag_new();
      output_color(
        string("DNA is set to re-initialize at the beginning of the next cycle. However,\n") +
        string("If you $WSAVE$w now, you can still write the current DNA to disk.\n")
      );
      cout << endl;
      return 0;
    break;
    
    // SAVE
    case(   41):
      if (token[1] == "BLANK")
      { // need one more argument
        output_color("What $Wfile$w should I save genetic data to?\n");
        cout << endl;
        return 0;
      }
      sim.write_genetics_drv( to_lower(token[1]) );
      output_color("\n");
      return 0;
    break;
    
    // LOAD
    case(   42):
      if (token[1] == "BLANK")
      { // need one more argument
        output_color("What $Wfile$w should I load genetic data from?\n");
        cout << endl;
        return 0;
      }
      sim.init_dynamic( to_lower(token[1]) );
      output_color("\n");
      return 0;
    break;
    
    // EDIT
    case(   43):
      sim.genetics_edit_drv();
      return 0;
    break;
    
    // OPTION
    case(   50):
      options( settings_file );
      sim.update_vol();
      write_settings( settings_file );
      return 0;
    break;
    
    case(65535):
      return -1;
    break;
    
    case( 1337):
      kbot();
      return 0;
    break;
    
    case(  100):
      output_color("They call me the DARKNESS!\n");
      cout << endl;
      return 0;
    break;
    
    case(  101):
      output_color("Lightning Round!!\n");
      cout << endl;
      return 0;
    break;
    
    case(  102):
      hide_cursor();
      firelord();
      return 0;
    break;
    
    case( 1000):
      hide_cursor();
      virus();
      return 0;
    break;
    
    case( 1001):
      hide_cursor();
      pong();
      return 0;
    break;
    
    case(    0):
      output_color( string("$w[$W") + line + string("$w] was not recognized by Simulation.\n") );
      cout << endl;
      return 0;
    break;
      
    default:
      output_color("Sorry, that command has not yet been implemented :d\n");
      cout << endl;
      return 0;
    break;
  }
}

//------------------------------------------------------------------------------

int interpret( string cmd )
{
  // 10 documented commands
  // 8  documented & implemented
  // 6  secret commands
  
  if      (cmd == "MENU") return 5;
  else if (cmd == "SLOW") return 10;
  else if (cmd == "FAST") return 11;
  else if (cmd == "ABOUT") return 30;
  
  else if (cmd == "NEW") return 40;
  else if (cmd == "SAVE") return 41;
  else if (cmd == "LOAD") return 42;
  else if (cmd == "EDIT") return 43;
  
  else if (cmd == "OPTION" ||
           cmd == "OPTIONS") return 50;
  else if (cmd == "EXIT") return 65535;
  
  //---------------------------------------------------------------
  else if (cmd == "KBOT" ||
           cmd == "K-BOT") return 1337;
  else if (cmd == "LOGAN") return 100;
  else if (cmd == "CLAYTON") return 101;
  else if (cmd == "FIRELORD") return 102;
  else if (cmd == "VIRUS") return 1000;
  else if (cmd == "PONG") return 1001;
  else return 0; // the user is a complete moron
            
}

// end of file
