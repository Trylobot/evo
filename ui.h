// Tyler Cole
// EVO Project Module Header
// ui.h

#ifndef _UI_H_
#define _UI_H_

#include <string>
using std::string;
#include <vector>
#include <iostream>
#include <conio.h>
#include "basic.h"
#include "settings.h"
#include "random.h"
#include "timer.h"
#include "tokenize.h"
#include "output_color.h"
#include "actor.h"

char pause_menu();
void splash();
void menu();
void about();
void options( string& settings_file );

// some helpful definitions, since my parser is complicated
#define ENTER     13
#define ESC       27
#define BACKSPACE 8
#define ARROW_UP  22472
#define ARROW_RT  22477
#define ARROW_DN  22480
#define ARROW_LF  22475
void genetics_edit( vector<Herbivore>& herbivores, vector<Carnivore>& carnivores );

// pong
void pong();
// displays my banner
void kbot();
// displays some fire
void firelord();
// shows a virus-thing animation
void virus();
// shows some pr0n
void asciipr0n();
// throws a meteor onto the freakin screen
void meteor( Location impact =
             Location( random( 0, global("WORLDMAP_HEIGHT") - 1 ),
                       random( 0, global("WORLDMAP_WIDTH") - 1 )),
             Location maxBR  =
             Location( global("WORLDMAP_HEIGHT") - 1,
                       global("WORLDMAP_WIDTH") - 1 ));
// helpful sub for the meteor
void meteor_sub( string rock[10][15],
                 int& rock_index,
                 Location& cursor,
                 Location& rock_ptr,
                 Location& maxBR );


#endif
// end of file
