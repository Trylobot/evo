// Tyler Cole
// EVO Project Module Header
// world.h

#ifndef _WORLD_H_
#define _WORLD_H_

#include <iostream>
#include <iomanip>
#include <conio.h>
#include <fstream>
using std::ofstream;
#include <sstream>
#include <string>
using std::string;
#include <vector>
using std::vector;
#include "basic.h"
#include "actor.h"
#include "settings.h"
#include "random.h"
#include "genetics.h"
#include "output_color.h"
#include "ui.h"

void nudge( Location& L ); // modify the calling location; randomly translate one square
bool in_bounds( Location L ); // returns true if 0<row<max, and 0<col<max
Location random_location(); // returns a random in_bounds location

// This is the primary class of the entire project.
class World
{
  public:
  World();
  ~World();
  
  // driver function for the world class.
  void do_cycle( unsigned int resume_day = 1 );
  // accessor
  unsigned int get_current_day();
  unsigned int get_current_cycle();
  unsigned int get_current_century();
  unsigned int get_current_millenium();
  // modifier
  void increment_current_cycle( unsigned int amount = 1 );
  // flag for new dna
  void set_flag_new();
  // loads / saves dna
  void init_dynamic( string filename = "" );
  void write_genetics_drv( string filename );
  // edit mode
  void genetics_edit_drv();
  // some string info
  string one_liner_field_labels_compact,
         one_liner_field_labels_detailed,
         frame_info_one_liner,
         compact_stats_one_liner,
         detailed_stats_one_liner;
  ofstream statsfile;
  
  //private:
  // retrieval functions
  Actor** get( Location L );
  Actor_Type get_type( Location L );
  Direction get_direction( Location L );
  char get_char( Location L );
  bool is_dynamic( Location L );
  
  // location generation
  Location random_spawn_anywhere();
  Location random_spawn_sides();
  Location random_spawn_clump( Location clump );
  
  // data items; lists, and the grid itself
  vector< vector<Actor*> > grid;
  vector<Location> plant_clumps;
  vector<Herbivore> herbivores;
  vector<Carnivore> carnivores;
  
  // statistics and minor data items
  unsigned int current_day;
  unsigned int current_cycle;
  bool flag_new;
  
  // local version of some important globals
  struct
  { bool elites;
    unsigned
     int height,
         width,
         plant_p,
         clump_p,
         herb_p,
         carn_p,
         cycle_len;
    double wait_time;
  } vol; /* For VOLATILE */
  // call when settings change during execution
  void update_vol();
  
  Statistics herb_stats, carn_stats;
  Herbivore* lawn_mower; // top scorers
  bool lawn_mower_defined;
  Carnivore* the_ripper;
  bool the_ripper_defined;
  
  Empty* emptyP; // special pointers
  Wall* wallP;
  Plant* plantP;
  Actor* invalidP;
  
  // *** main simulation functions ***
  
  // calls perform_action on each dynamic actor,
  // and also displays the grid if appropriate mode is set
  // returns false on any keystroke
  void do_day();
  
  // dynamic_actor functions
  void look( Dynamic_Actor* mob );
  void perform_action( Dynamic_Actor* mob );
  // a little checkup.
  void exam();
  
  // spawning and initialization functions
  void init_stats();
  void respawn();
  void init_grid();
  void re_init_grid();
  void spawn_plant();
  void spawn_herbivore( Herbivore* target );
  void spawn_carnivore( Carnivore* target );  
  void examine_scores();
  void calculate_stats();
  void natural_selection();
  
  // writes the latest statistics out to a one liner
  string create_frame_info_one_liner();
  string create_compact_stats_one_liner();
  string create_detailed_stats_one_liner();
  
  // translates the grid into a displayable map
  string grid_to_string();
  void display_grid();
};

#endif
// end of file
