// Tyler Cole
// EVO Project Module Header
// settings.h

#ifndef _SETTINGS_H_
#define _SETTINGS_H_

#define EVO_PROJECT_VERSION "1.00"

#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
using std::string;
#include "basic.h"
#include "tokenize.h"
#include "output_color.h"

// some non-volatile globals
#define COUNT_DIRECTIONS  4
#define COUNT_ACTOR_TYPES 5
#define COUNT_MEMORIES    5
#define COUNT_ACTIONS     4

// defines total number of volatile globals
#define COUNT_GLOBALS     20

// key[i][0] == i'th KEY NAME
// key[i][1] == i'th KEY DESCRIPTION
static string key[COUNT_GLOBALS][2] = {
  { "FLAG_FAST",              "; 0:slow, 1:fast" },
  { "FLAG_MENU",              "; 0:detailed, 1:minimal" },
  { "WORLDMAP_HEIGHT",        "; Height of the world map grid" },
  { "WORLDMAP_WIDTH",         "; Width of the world map grid" },
  { "PLANT_POPULATION",       "; Number of plants present in the world" },
  { "PLANT_CLUMPS",           "; Number of clumps for plants to spawn near to" },
  { "HERBIVORE_POPULATION",   "; Number of herbivores present in the world" },
  { "CARNIVORE_POPULATION",   "; Number of carnivores present in the world" },
  { "CYCLE_LENGTH",           "; Length of a single cycle in days (turns)" },
  { "MUTATION_RATE",          "; Chance in 10,000 of any single gene being mutated" },
  { "CROSSOVER_RATE",         "; Chance in 10,000 of a dna set having 2 parents (rather than 1)" },
  { "COUNT_STATES",           "; Maximum state value" },
  { "PLANT_NOURISH_VALUE",    "; Score added to herbivores on consuming a plant" },
  { "HERBIVORE_DEATH_VALUE",  "; Score subtracted from herbivores on death" },
  { "HERBIVORE_NOURISH_VALUE","; Score added to carnivores on consuming an herbivore" },
  { "FLAG_SHOW_ELITES",       "; 0:don't show, 1:highlight top scorers" },
  { "FLAG_PLANT_RESPAWN",     "; 0:middle, 1:sides, 2:anywhere, 3:clumps" },
  { "FLAG_HERBIVORE_RESPAWN", "; 0:middle, 1:sides, 2:anywhere" },
  { "FLAG_CARNIVORE_RESPAWN", "; 0:middle, 1:sides, 2:anywhere" },
  { "WAIT_TIME",              "; Time in milliseconds to wait between slow-mode grid updates" }
};

// value[i][0] == i'th VOLATILE VALUE
// value[i][1] == i'th LOWER BOUND
// value[i][2] == i'th UPPER BOUND
// value[i][3] == i'th DEFAULT VALUE
static int value[COUNT_GLOBALS][4] = {
  /* fF  */{ 0, 0,  1,      0 },
  /* fM  */{ 0, 0,  1,      0 },
  /* wmH */{ 0, 5,  100,    7 },
  /* wmW */{ 0, 5,  300,    10 },
  /* pP  */{ 0, 1,  15000,  6 },
  /* pc  */{ 0, 1,  3000,   2 },
  /* hP  */{ 0, 1,  10000,  3 },
  /* cP  */{ 0, 1,  10000,  1 },
  /* CL  */{ 0, 1,  100000, 20 },
  /* Mr  */{ 0, 1,  10000,  25 },
  /* Cr  */{ 0, 1,  10000,  7500 },
  /* cS  */{ 0, 1,  100,    15 },
  /* pNV */{ 0, 1,  100,    1 },
  /* hDV */{ 0, 1,  100,    2 },
  /* hNV */{ 0, 1,  100,    1 },
  /* fSE */{ 0, 0,  1,      0 },
  /* fpR */{ 0, 0,  3,      1 },
  /* fhR */{ 0, 0,  2,      1 },
  /* fcR */{ 0, 0,  2,      0 },
  /* WT  */{ 0, 50, 1000,   100 }
};

// functionality for settings I/O
string read_ini();
bool init_settings_external( string filename );
void init_settings_defaults();
void write_ini( string filename );
void write_settings( string filename );

string global_name( int i );
string global_desc( int i );

// returns the saught-after value, or a code
// value: success, -1: failed find key
int global( string k );
int global_default( string k );

// returns a code which describes what happened.
// 1: success, 2: fail bounds check, 3: failed find key
int set_global( string k, int v );

#endif
// end of file
