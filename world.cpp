// Tyler Cole
// EVO Project Module Implementation
// world.cpp

#include "world.h"
using namespace std;

void nudge( Location& L )
{
  switch( (Direction)random( 0, COUNT_DIRECTIONS - 1 ) )
	{
    case(north): L.row--; break;
    case(east): L.col++; break;
    case(south): L.row++; break;
    case(west): L.col--; break;
  }
}

//------------------------------------------------------------------------------

bool in_bounds( Location L )
{
  static int height = global("WORLDMAP_HEIGHT"),
             width = global("WORLDMAP_WIDTH");
  if (L.row >= 0 && L.row < height && L.col >= 0 && L.col < width)
    return true;
  else
    return false;
}

//------------------------------------------------------------------------------

Location random_location()
{
  static unsigned int height = global("WORLDMAP_HEIGHT"),
                      width = global("WORLDMAP_WIDTH");
  return Location ( random( 1, height - 2 ), random( 1, width - 2 ) );
}

//------------------------------------------------------------------------------

World::World()
{
  one_liner_field_labels_compact  = "$w[ Cycle][  HIGH][   AVG][  HIGH][   AVG]";
  one_liner_field_labels_detailed = "        $w[  Herbivores  ][  Carnivores  ]\n";
  one_liner_field_labels_detailed += one_liner_field_labels_compact;
  
  frame_info_one_liner = "";
  compact_stats_one_liner = "";
  detailed_stats_one_liner = "";
  
  current_cycle = 1;
  current_day = 1;
  flag_new = true;
  
  // four special pointers, used by grid
  lawn_mower = NULL; lawn_mower_defined = false;
  the_ripper = NULL; the_ripper_defined = false;
  emptyP = new Empty();
  wallP = new Wall();
  plantP = new Plant();
  invalidP = new Actor();
  
  vol.elites = global("FLAG_SHOW_ELITES");
  vol.height = global("WORLDMAP_HEIGHT");
  vol.width = global("WORLDMAP_WIDTH");
  vol.plant_p = global("PLANT_POPULATION");
  vol.clump_p = global("PLANT_CLUMPS");
  vol.herb_p = global("HERBIVORE_POPULATION");
  vol.carn_p = global("CARNIVORE_POPULATION");
  vol.cycle_len = global("CYCLE_LENGTH");
  vol.wait_time = (double)global("WAIT_TIME") / 1000.0;
  
  statsfile.open("stats.log");
  output_color("Using file [$Wstats.log$w] for saving statistics.\n");
  statsfile << filter_color(one_liner_field_labels_detailed) << endl;
  
  init_grid();
  init_dynamic();
}

//------------------------------------------------------------------------------

World::~World()
{
  delete emptyP; emptyP = NULL;
  delete wallP; wallP = NULL;
  delete plantP; plantP = NULL;
  delete invalidP; invalidP = NULL;
  
  statsfile.close();
    
  // no need for delete keyword on the grid, as it points
  // to actors in a container class; they'll be handled auto-
  // matically by the STL.  <3 STL!! XD
  grid.clear();
}

//------------------------------------------------------------------------------

void World::update_vol()
{
  vol.elites = global("FLAG_SHOW_ELITES");
  vol.height = global("WORLDMAP_HEIGHT");
  vol.width = global("WORLDMAP_WIDTH");
  vol.plant_p = global("PLANT_POPULATION");
  vol.clump_p = global("PLANT_CLUMPS");
  vol.herb_p = global("HERBIVORE_POPULATION");
  vol.carn_p = global("CARNIVORE_POPULATION");
  vol.cycle_len = global("CYCLE_LENGTH");
  vol.wait_time = (double)global("WAIT_TIME") / 1000.0;
}

//------------------------------------------------------------------------------

unsigned int World::get_current_day()
  { return current_day; }

unsigned int World::get_current_cycle()
  { return current_cycle; }

unsigned int World::get_current_century()
  { return ((current_cycle / 100) + 1); }

unsigned int World::get_current_millenium()
  { return ((current_cycle / 1000) + 1); }

void World::increment_current_cycle( unsigned int amount )
  { current_cycle += amount; }

//------------------------------------------------------------------------------

Actor** World::get( Location L )
{
  if (in_bounds(L))
    return &grid[L.row][L.col];

  else
    return &invalidP;
}

//------------------------------------------------------------------------------

Actor_Type World::get_type( Location L )
{
  if (in_bounds(L))
    return grid[L.row][L.col]->type;

  else
    return invalid_actor_type;
}

//------------------------------------------------------------------------------

Direction World::get_direction( Location L )
{
  if (in_bounds(L) && is_dynamic(L) )
    return ((Dynamic_Actor*)grid[L.row][L.col])->direction;

  else
    return invalid_direction;
}

//------------------------------------------------------------------------------

char World::get_char( Location L )
{
  Actor* ptr = *get(L);
  switch( ptr->type )
  {        
    case( empty ): return 'e';
    case( wall ):  return 'w';
    case( plant ): return 'p';
      
    case( herbivore ):
      switch( ((Dynamic_Actor*)ptr)->direction )
      {
        case( north ): return 'h';
        case( east ):  return 'j';
        case( south ): return 'k';
        case( west ):  return 'l';
        default: return 'x';
      }
      
    case( carnivore ):
      switch( ((Dynamic_Actor*)ptr)->direction )
      {
        case( north ): return 'c';
        case( east ):  return 'v';
        case( south ): return 'b';
        case( west ):  return 'n';
        default: return 'x';
      }
    
    default: return 'x';
  }
}

//------------------------------------------------------------------------------

bool World::is_dynamic( Location L )
{
  if (in_bounds(L) && (get_type(L) == herbivore || get_type(L) == carnivore) )
    return true;

  else
    return false;
}

//------------------------------------------------------------------------------

Location World::random_spawn_anywhere()
{
  Location spawn = random_location();

  while( get_type(spawn) != empty )
    spawn = random_location();
  
  return spawn;
}

//------------------------------------------------------------------------------

Location World::random_spawn_sides()
{
  Location spawn;
  
  // since this loop quits when spawn is in bounds, and the second loop
  // inside of this one quits when spawn is NOT in bounds, the only way
  // to quit the whole process is find a location which is not empty.
  while ( !in_bounds(spawn) )
  {
    Direction side_indicator = (Direction)random( 0, COUNT_DIRECTIONS - 1 );
    switch( side_indicator )
    {
      case( north ): spawn.set( 1, random( 1, vol.width - 2 ) ); break;
      case( east ):  spawn.set( random( 1, vol.height - 2 ), vol.width - 2 ); break;
      case( south ): spawn.set( vol.height - 2, random( 1, vol.width - 2 ) ); break;
      case( west ):  spawn.set( random( 1, vol.height - 2 ), 1 ); break;
    }
    // tries to find a location, but will quit if it goes out of bounds to find it
    while (get_type(spawn) != empty && in_bounds(spawn))
    {
      switch( side_indicator )
      {
        case( north ): spawn.row++; break;
        case( east ):  spawn.col++; break;
        case( south ): spawn.row--; break;
        case( west ):  spawn.col--; break;
      }
    }
  }
  
  return spawn;
}

//------------------------------------------------------------------------------

Location World::random_spawn_clump( Location clump )
{
  Location spawn = clump;
  while( get_type(spawn) != empty )
  {
    nudge(spawn);
    if (!in_bounds(spawn))
      spawn = clump;
  }
  return spawn;
}

//------------------------------------------------------------------------------

void World::set_flag_new()
{
  flag_new = true;
  current_cycle = 1;
}

//------------------------------------------------------------------------------

void World::init_grid()
{
  grid.clear();
  
  unsigned int row, col;
  for (row = 0; row < vol.height; row++)
  {
    vector< Actor* > this_row;
    for (col = 0; col < vol.width; col++)
    {
      Actor* this_element = NULL;      
      
      if (row == 0 || row == (vol.height - 1) || col == 0 || col == (vol.width - 1))
        this_element = (Actor*)wallP;
      else
        this_element = (Actor*)emptyP;
      
      this_row.push_back( this_element );
    }
    grid.push_back( this_row );
  }
}

//------------------------------------------------------------------------------

void World::re_init_grid() // faster
{
  unsigned int row, col;
  for (row = 1; row < (vol.height - 1); row++)
  {
    for (col = 1; col < (vol.width - 1); col++)
    {
      grid[row][col] = (Actor*)emptyP;
    }
  }
}

//------------------------------------------------------------------------------

void World::init_dynamic( string filename )
{
  vector< vector<Gene> > extern_herb_dna_pool;
  vector< vector<Gene> > extern_carn_dna_pool;
  bool success = false;
  
  if (filename.size() > 0)
  {
    init_genetics_external( success, filename, extern_herb_dna_pool, extern_carn_dna_pool );    
    
    if (success)
    {
      current_cycle = 1;
      herbivores.clear();
      carnivores.clear();
    }
    else
    {
      return; // do not re-initialize
    }
  }  
  
  unsigned int i;
  for (i = 0; i < vol.herb_p; i++)
  {
    Herbivore this_actor;
    this_actor.id = i;
    
    if (success)
      this_actor.dna = extern_herb_dna_pool[i];
    else
      new_dna( this_actor.dna );
    
    herbivores.push_back( this_actor );
  }
  for (i = 0; i < vol.carn_p; i++)
  {
    Carnivore this_actor;
    this_actor.id = i;
    
    if (success)
      this_actor.dna = extern_carn_dna_pool[i];
    else
      new_dna( this_actor.dna );
    
    carnivores.push_back( this_actor );
  }
}

//------------------------------------------------------------------------------

void World::write_genetics_drv( string filename )
{
  vector<vector<Gene> > herb_dna_pool;
  vector<vector<Gene> > carn_dna_pool;
  unsigned int i;
  for (i = 0; i < vol.herb_p; i++)
  {
    herb_dna_pool.push_back( herbivores[i].dna );
  }
  for (i = 0; i < vol.carn_p; i++)
  {
    carn_dna_pool.push_back( carnivores[i].dna );
  }
  
  write_genetics( filename, herb_dna_pool, carn_dna_pool );
}

//------------------------------------------------------------------------------

void World::genetics_edit_drv()
{
  genetics_edit( herbivores, carnivores );
}

//------------------------------------------------------------------------------

void World::spawn_plant()
{
  Location spawn;
  switch( global("FLAG_PLANT_RESPAWN") )
  {
    case(0): // middle
      spawn = random_spawn_clump( Location( vol.height / 2, vol.width / 2 ) );
    break;
	
    case(1): // sides
	    spawn = random_spawn_sides();
    break;
	
    case(2): // anywhere
      spawn = random_spawn_anywhere();
    break;
    
    case(3): // clumps
      spawn = random_spawn_clump( plant_clumps[random( 0, vol.clump_p - 1 )] );
    break;
  }
  *get(spawn) = (Actor*)plantP;
}

//------------------------------------------------------------------------------

void World::spawn_herbivore( Herbivore* target )
{
  Location spawn;
  switch( global("FLAG_HERBIVORE_RESPAWN") )
  {
    case(0): // middle
      spawn = random_spawn_clump( Location( vol.height / 2, vol.width / 2 ) );
    break;
	
    case(1): // sides
	    spawn = random_spawn_sides();
    break;
    
    case(2): // anywhere
      spawn = random_spawn_anywhere();
    break;
  }
  // update grid
  *get(spawn) = (Actor*)target;
  // update target info
  target->just_spawned(spawn);
}

//------------------------------------------------------------------------------

void World::spawn_carnivore( Carnivore* target )
{
  Location spawn;
  switch( global("FLAG_CARNIVORE_RESPAWN") )
  {
    case(0): // middle
      spawn = random_spawn_clump( Location( vol.height / 2, vol.width / 2 ) );
    break;
	
    case(1): // sides
	    spawn = random_spawn_sides();
    break;
    
    case(2): // anywhere
      spawn = random_spawn_anywhere();
    break;
  }
  // update grid
  *get(spawn) = (Actor*)target;
  // update target info
  target->just_spawned(spawn);
}

//------------------------------------------------------------------------------

void World::look( Dynamic_Actor* mob )
{
  Location L = mob->location;
  switch( mob->direction )
  {
    case( north ): L.row--; break;
    case( east ): L.col++; break;
    case( south ): L.row++; break;
    case( west ): L.col--; break;
  }
  mob->sight = get_type( L );
}

//------------------------------------------------------------------------------

void World::perform_action( Dynamic_Actor* mob )
{
  look( mob );
  
  Location Lsrc = mob->location;
  Location Ldest = Lsrc;
  
  int index = 0;
  // get the gene which matches current situation
  index += (int)(mob->state) * (COUNT_DIRECTIONS * COUNT_ACTOR_TYPES * COUNT_MEMORIES);
  index += (int)(mob->direction) * (COUNT_ACTOR_TYPES * COUNT_MEMORIES);
  index += (int)(mob->sight) * COUNT_MEMORIES;
  index += (int)(mob->memory);
  
  switch( mob->dna[index].next_action )
  {
    //-------------------------------------
    case( move_forward ):
      
      // modify Ldest based on direction
      switch( mob->direction ) {
        case( north ): Ldest.row--; break; // one up
        case( east ): Ldest.col++; break; // one right
        case( south ): Ldest.row++; break; // one down
        case( west ): Ldest.col--; break; // one left
      }
      
      switch( mob->sight ) {
        
        case( empty ):
          // movement
          *get(Ldest) = *get(Lsrc);
          *get(Lsrc) = emptyP;
          mob->location = Ldest;
          mob->remember( move_forward );
        break;
        
        case( wall ):
          // change state
          mob->state = random( 0, global("COUNT_STATES") - 1 );
          mob->remember( change_state );
        break;
        
        case( plant ):
          // movement
          *get(Ldest) = *get(Lsrc);
          *get(Lsrc) = emptyP;
          mob->location = Ldest;
          mob->remember( move_forward );
          // plant destruction
          if (mob->type == herbivore)
          {
            ((Herbivore*)mob)->consumed_plant();
            if (mob->score > herb_stats.cycle.high_score)
            { // new top-scorer
              lawn_mower = (Herbivore*)mob;
              lawn_mower_defined = true;
            }
          }
          spawn_plant();
        break;
        
        case( herbivore ):
          if (mob->type == herbivore)
          {
            // change state
            mob->state = random( 0, global("COUNT_STATES") - 1 );
            mob->remember( change_state );
          }
          else // carnivore
          {
            // movement
            Herbivore* victim = (Herbivore*)(*get(Ldest));
            *get(Ldest) = *get(Lsrc);
            *get(Lsrc) = emptyP;
            mob->location = Ldest;
            mob->remember( move_forward );
            // herbivore destruction
            victim->was_consumed();
            ((Carnivore*)mob)->consumed_herbivore();
            if (mob->score > carn_stats.cycle.high_score)
            { // new top-scorer
              the_ripper = (Carnivore*)mob;
              the_ripper_defined = true;
            }
            spawn_herbivore( victim );
          }                
        break;
        
        // And finally, the strangest case of all:
        // the herbivore decides to leap into the drooling mouth
        // of a carnivore; much to the meat-eater's surprise.
        case( carnivore ):
          if (mob->type == herbivore)
          {
            // omfg herbivore destruction
            ((Herbivore*)mob)->was_consumed();
            ((Carnivore*)(*get(Ldest)))->consumed_herbivore();
            if (((Carnivore*)(*get(Ldest)))->score > carn_stats.cycle.high_score)
            { // new top-scorer
              the_ripper = (Carnivore*)(*get(Ldest));
              the_ripper_defined = true;
            }
            *get(Lsrc) = emptyP;
            spawn_herbivore((Herbivore*)mob);
          }
          // That, or it's his buddy.
          else // carnivore
          {
            // change state
            mob->state = random( 0, global("COUNT_STATES") - 1 );
            mob->remember( change_state );
          }
        break;
        
      }
      
    break;
    
    //-------------------------------------
    case( move_backward ):
      
      // modify Ldest based on [reversed]direction
      switch( mob->direction ) {
        case( north ): Ldest.row++; break; // one down
        case( east ): Ldest.col--; break; // one left
        case( south ): Ldest.row--; break; // one up
        case( west ): Ldest.col++; break; // one right
      }
      
      switch( get_type(Ldest) ) {
        
        case( empty ):
          // movement
          *get(Ldest) = *get(Lsrc);
          *get(Lsrc) = emptyP;
          mob->location = Ldest;
          mob->remember( move_backward );
        break;
        
        case( wall ):
          // change state
          mob->state = random( 0, global("COUNT_STATES") - 1 );
          mob->remember( change_state );
        break;
        
        case( plant ):
          // movement
          *get(Ldest) = *get(Lsrc);
          *get(Lsrc) = emptyP;
          mob->location = Ldest;
          mob->remember( move_backward );
          // plant destruction
          if (mob->type == herbivore)
          {
            ((Herbivore*)mob)->consumed_plant();
            if (mob->score > herb_stats.cycle.high_score)
            { // new top-scorer
              lawn_mower = (Herbivore*)mob;
              lawn_mower_defined = true;
            }
          }
          spawn_plant();
        break;
        
        case( herbivore ):
          if (mob->type == herbivore)
          {
            // change state
            mob->state = random( 0, global("COUNT_STATES") - 1 );
            mob->remember( change_state );
          }
          else // carnivore
          {
            // movement
            Herbivore* victim = (Herbivore*)(*get(Ldest));
            *get(Ldest) = *get(Lsrc);
            *get(Lsrc) = emptyP;
            mob->location = Ldest;
            mob->remember( move_backward );
            // herbivore destruction
            victim->was_consumed();
            ((Carnivore*)mob)->consumed_herbivore();
            if (mob->score > carn_stats.cycle.high_score)
            { // new top-scorer
              the_ripper = (Carnivore*)mob;
              the_ripper_defined = true;
            }
            spawn_herbivore( victim );
          }                
        break;
        
        // And finally, the strangest case of all:
        // the herbivore decides to leap into the drooling mouth
        // of a carnivore; much to the meat-eater's surprise.
        case( carnivore ):
          if (mob->type == herbivore)
          {
            // omfg herbivore destruction
            ((Herbivore*)mob)->was_consumed();
            ((Carnivore*)(*get(Ldest)))->consumed_herbivore();
            if (((Carnivore*)(*get(Ldest)))->score > carn_stats.cycle.high_score)
            { // new top-scorer
              the_ripper = (Carnivore*)(*get(Ldest));
              the_ripper_defined = true;
            }
            *get(Lsrc) = emptyP;
            spawn_herbivore((Herbivore*)mob);
          }
          // That, or it's his buddy.
          else // carnivore
          {
            // change state
            mob->state = random( 0, global("COUNT_STATES") - 1 );
            mob->remember( change_state );
          }
        break;
        
      }
      
    break;
    
    //-------------------------------------
    case( turn_left ):
      
      mob->remember( turn_left );
      
      switch( mob->direction ) {
        case( north ): mob->direction = west; break;
        case( east ): mob->direction = north; break;
        case( south ): mob->direction = east; break;
        case( west ): mob->direction = south; break;
      }
    break;

    //-------------------------------------
    case( turn_right ):
      
      mob->remember( turn_right );
      
      switch( mob->direction ) {
        case( north ): mob->direction = east; break;
        case( east ): mob->direction = south; break;
        case( south ): mob->direction = west; break;
        case( west ): mob->direction = north; break;
      }
    break;
  }
}

//------------------------------------------------------------------------------

void World::exam()
{
  
}

//------------------------------------------------------------------------------

void World::do_day()
{
  unsigned int i;
  
  for (i = 0; i < vol.herb_p; i++)
    perform_action( (Dynamic_Actor*)(&herbivores[i]) );
  
  for (i = 0; i < vol.carn_p; i++)
    perform_action( (Dynamic_Actor*)(&carnivores[i]) );
  
  if( !global("FLAG_FAST"))
  {
    // show the grid
    display_grid();
    
    // show some frame info
    output_color( frame_info_one_liner );
    
    // wait
    wait( vol.wait_time );
  }
  
  // check for keyboard input, pause if present
  if (kbhit())
  {
    getch(); // erase the invoking keystroke
    char temp = pause_menu();
    switch( temp )
    {
      case('M'):
        // exit to main menu
        throw 1;
      break;
      
      case('K'):
        display_grid();
        output_color( frame_info_one_liner );
        for (i = 0; i < 5; i++)
          { meteor(); }
        throw 1;
      break;
      
      case('C'):
        // do nothing
      break;
      
      case('0'):
        getch(); // there's another character in the buffer, erase it
        // then do nothing
      break;
    }
  }
}

//------------------------------------------------------------------------------

void World::do_cycle( unsigned int resume_day )
{
  hide_cursor();
  // initialize statistics structs
  init_stats();  
  // re-start the grid, and spawn actors
  respawn();

  // churn out another generation
  for (current_day = resume_day; current_day <= vol.cycle_len; current_day++)
  {
    if ( !global("FLAG_FAST") )
    { // Update the little one liner about the current day;
      frame_info_one_liner = create_frame_info_one_liner();
    }    
    
    try
    { 
      do_day();
    }
    catch( int ex )
    {
      throw ex;
    }
  }

  // bubblesorts a list of indices based on scores
  examine_scores();
  // calculates all stats
  calculate_stats();  
  
  // destroy the old generation and make room for the new
  natural_selection();
  // next cycle, please
  increment_current_cycle();
  
  if (global("FLAG_FAST")) // FLAG_FAST == true
  {
    output_color( string("$wCycle $W") + to_string(get_current_cycle()) + string("$w\n") );
  }
}

//------------------------------------------------------------------------------

void World::init_stats()
{
  // elite reset
  herb_stats.cycle.high_score = 1; carn_stats.cycle.high_score = 1;
  lawn_mower_defined = false; the_ripper_defined = false;
  
  herb_stats.score_vector.clear();
  //herb_stats.sorted_index.clear();
  herb_stats.cycle.high_score = 1;
  herb_stats.cycle.total_score = 0;
  herb_stats.cycle.average_score = 1.0;
  
  carn_stats.score_vector.clear();
  //carn_stats.sorted_index.clear();
  carn_stats.cycle.high_score = 1;
  carn_stats.cycle.total_score = 0;
  carn_stats.cycle.average_score = 1.0;
  
  // every century
  if (get_current_century() > 1 && get_current_cycle() % 100 == 0)
  { 
    herb_stats.century.high_score = 1;
    herb_stats.century.total_score = 0;
    herb_stats.century.average_score = 1.0;
    
    carn_stats.century.high_score = 1;
    carn_stats.century.total_score = 0;
    carn_stats.century.average_score = 1.0;
  }
  
  // every millenium
  if (get_current_millenium() > 1 && get_current_cycle() % 1000 == 0)
  { 
    herb_stats.millenium.high_score = 1;
    herb_stats.millenium.total_score = 0;
    herb_stats.millenium.average_score = 1.0;
    
    carn_stats.millenium.high_score = 1;
    carn_stats.millenium.total_score = 0;
    carn_stats.millenium.average_score = 1.0;
  }
}

//------------------------------------------------------------------------------

void World::respawn()
{
  // ** Spawning/Respawning sequence **
  re_init_grid();
  if (flag_new)
  {
    init_dynamic();
    flag_new = false;
  }
  
  unsigned int i;
  
  // init the plant_clumps table, if applicable
  if (global("FLAG_PLANT_RESPAWN") == 3)
  {
    plant_clumps.clear();
    for (i = 0; i < vol.clump_p; i++)
      plant_clumps.push_back( random_location() );
  }
  // spawn the plants
  for (i = 0; i < vol.plant_p; i++)
    spawn_plant();
  
  // spawn the herbivores
  for (i = 0; i < vol.herb_p; i++)
  {
    spawn_herbivore( &herbivores[i] );
    herbivores[i].reset_score();
  }
  
  // spawn the carnivores
  for (i = 0; i < vol.carn_p; i++)
  {
    spawn_carnivore( &carnivores[i] );
    carnivores[i].reset_score();
  }
}

//------------------------------------------------------------------------------

void World::examine_scores()
{
  unsigned int i;
  
  for (i = 0; i < vol.herb_p; i++)
  {
    herb_stats.score_vector.push_back( herbivores[i].score );
    
    herb_stats.cycle.total_score += herbivores[i].score;
    
    if (herbivores[i].score > herb_stats.cycle.high_score)
      herb_stats.cycle.high_score = herbivores[i].score;
  }

  for (i = 0; i < vol.carn_p; i++)
  {
    carn_stats.score_vector.push_back( carnivores[i].score );
    
    carn_stats.cycle.total_score += carnivores[i].score;
    
    if (carnivores[i].score > carn_stats.cycle.high_score)
      carn_stats.cycle.high_score = carnivores[i].score;
  }
}

//------------------------------------------------------------------------------

void World::calculate_stats()
{
  herb_stats.cycle.average_score = (double)herb_stats.cycle.total_score / (double)herb_stats.score_vector.size();
  carn_stats.cycle.average_score = (double)carn_stats.cycle.total_score / (double)carn_stats.score_vector.size();
  
  // create some one_liners based on the stats
  compact_stats_one_liner = create_compact_stats_one_liner();
  detailed_stats_one_liner = create_detailed_stats_one_liner();
  
  if (get_current_cycle() > 1)
    statsfile << filter_color(detailed_stats_one_liner) << endl;
}

//------------------------------------------------------------------------------

void World::natural_selection()
{
  vector<vector<Gene> > herb_dna_pool;
  vector<vector<Gene> > carn_dna_pool;
  unsigned int i;

  // mutate and populate the dna pools with the old dna
  for (i = 0; i < vol.herb_p; i++)
  {
    mutate( herbivores[i].dna );
    herb_dna_pool.push_back( herbivores[i].dna );
  }
  // replace dna with that of the new generation
  for (i = 0; i < vol.herb_p; i++)
    breed( herbivores[i].dna, herb_dna_pool, herb_stats );
  
  for (i = 0; i < vol.carn_p; i++)
  {
    mutate( carnivores[i].dna );
    carn_dna_pool.push_back( carnivores[i].dna );
  }
  for (i = 0; i < vol.carn_p; i++)
    breed( carnivores[i].dna, carn_dna_pool, carn_stats );
}

//------------------------------------------------------------------------------

string World::create_frame_info_one_liner()
{
  string c = to_string(get_current_cycle());
  string cl = to_string(global("CYCLE_LENGTH"));
  string d = to_string(get_current_day(), cl.size());
  
  return ("Day $W"+ d +"$w of "+ cl +", Cycle $W"+ c +string("$w"));
}

//------------------------------------------------------------------------------

string World::create_compact_stats_one_liner()
{
  stringstream s("\n");
  
  s << setw( 0 ) << "$W";
  s << setw( 8 ) << setprecision( 2 );
  s << get_current_cycle();
  
  s << setw( 0 ) << "$g";
  s << setw( 8 ) << setprecision( 2 );
  s << herb_stats.cycle.high_score;
  s << setw( 8 ) << setprecision( 2 );
  s << herb_stats.cycle.average_score;
  
  s << setw( 0 ) << "$r";
  s << setw( 8 ) << setprecision( 2 );
  s << carn_stats.cycle.high_score;
  s << setw( 8 ) << setprecision( 2 );
  s << carn_stats.cycle.average_score;
  
  string out = "";
  getline( s, out );
  return out;
}

//------------------------------------------------------------------------------

string World::create_detailed_stats_one_liner()
{
  /*
  stringstream s("\n");
  
  
  
  string out = "";
  getline( s, out );
  return out;
  */
  return create_compact_stats_one_liner();
}

//------------------------------------------------------------------------------

string World::grid_to_string()
{
  string out = "";
  Location L;
  int H = global("WORLDMAP_HEIGHT"), W = global("WORLDMAP_WIDTH");
  
  for (L.row = 0; L.row < H; L.row++)
  { // for current row    
    for (L.col = 0; L.col < W; L.col++)
    { // for current (row, col)    
      out += get_char(L);
    }
  }
  return out;
}

//------------------------------------------------------------------------------

void World::display_grid()
{
  unsigned int row, col;
  static Location c;
  string token;
  bool skip = false; // this is for optimizing output speed
  
  set_cursor( Location( 0, 0 ) );
  
  output_color("$w");
  cout << "É";
  for (col = 1; col < (vol.width - 1); col++)
    cout << "Í";
  cout << "»" << endl;
    
  for (row = 1; row < (vol.height - 1); row++)
  {
    for (col = 0; col < vol.width; col++)
    {    
      c.set( row, col );
      
      switch( get_char( c ) )
      {
        case('e'): cout << " "; skip = true;         break; // empty; bypass color and elites thing
        case('w'): output_color("$wº"); skip = true; break; // wall
        case('p'): output_color("$yù"); skip = true; break; // plant
        case('h'): token = "$g"; skip = false;      break; // north
        case('j'): token = "$g"; skip = false;      break; // east
        case('k'): token = "$g"; skip = false;      break; // south
        case('l'): token = "$g"; skip = false;      break; // west
        case('c'): token = "$r"; skip = false;      break; // north
        case('v'): token = "$r"; skip = false;      break; // east
        case('b'): token = "$r"; skip = false;      break; // south
        case('n'): token = "$r"; skip = false;      break; // west
      }
      
      // if outputting an actor
      if (!skip)
      {
        // and if he's an elite
        if (vol.elites)
        {
          if      ( *get( c ) == lawn_mower ) token[1] = 'G';
          else if ( *get( c ) == the_ripper ) token[1] = 'R';
        }        
        // output a special token
        output_color( token );
      }
    }
    cout << endl;
  }
    
  output_color("$w");
  cout << "È";
  for (col = 1; col < (vol.width - 1); col++)
    cout << "Í";
  cout << "¼" << endl;
}

// end of file
