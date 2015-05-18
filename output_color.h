// Tyler Cole
// EVO Project Module Header
// output_color.h

#ifndef _OUTPUT_COLOR_
#define _OUTPUT_COLOR_

#include <iostream>
#include <string>
using std::string;
#include "basic.h"

// assumes stdout but user can specify any output stream
void output_color( const string& s, unsigned int width = 0, char align = 'R' );

// also a filter function that removes color tokens
string filter_color( const string& s );

// lets you output a colored string to specified ostream without
// having to break up the output into seperate statements.

/*
------------------------------------------
 color escape characters are as follows:
 $_ : set foreground color
 %_ : set background color
-----------------------------------------------
 color characters can be any of the following:
 k : black            K : dark grey
 r : dark red         R : bright red
 g : dark green       G : bright green
 b : dark blue        B : bright blue
 c : dark cyan        C : bright cyan
 p : dark purple      P : bright purple
 y : dark yellow      Y : bright yellow
 w : light grey       W : white
----------------------------------------
 console default is $w%k (grey on black)
----------------------------------------
 unrecognized tokens are treated as regular text
*/

#endif
// end of file
