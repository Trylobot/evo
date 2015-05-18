// Tyler Cole
// EVO Project Module Implementation
// actor.cpp

#include "actor.h"
using namespace std;

Actor::Actor()
{
  type = invalid_actor_type;
}

Empty::Empty()
{
  type = empty;
}

Wall::Wall()
{
  type = wall;
}

Plant::Plant()
{
  type = plant;
}

//------------------------------------------------------------------------------

Dynamic_Actor::Dynamic_Actor()
{
  type = invalid_actor_type;
  id = -1;
  state = 0;
  direction = invalid_direction;
  sight = invalid_actor_type;
  memory = invalid_action;
  location.set( -1, -1 );
  score = 1;
}

void Dynamic_Actor::just_spawned( Location spawn )
{
  state = 0;
  location = spawn;
  direction = (Direction)random( 0, COUNT_DIRECTIONS - 1 );
  memory = change_state;
}

void Dynamic_Actor::reset_score()
{
  score = 1;
}

void Dynamic_Actor::remember( Action new_memory )
{
  memory = new_memory;
}

//------------------------------------------------------------------------------

Herbivore::Herbivore()
{
  type = herbivore;
  id = -1;
  state = 0;
  direction = invalid_direction;
  sight = invalid_actor_type;
  location.set( -1, -1 );
  score = 1;
  memory = change_state;
  dna.clear();
}

void Herbivore::consumed_plant()
{
  static unsigned int val = global("PLANT_NOURISH_VALUE");
  score = score + val;
}

void Herbivore::was_consumed()
{
  static unsigned int val = global("HERBIVORE_DEATH_VALUE");
  if (score > val)
    score = score - val;
}

//------------------------------------------------------------------------------

Carnivore::Carnivore()
{
  type = carnivore;
  id = -1;
  state = 0;
  direction = invalid_direction;
  sight = invalid_actor_type;
  location.set( -1, -1 );
  score = 1;
  memory = change_state;
  dna.clear();
}

void Carnivore::consumed_herbivore()
{
  static unsigned int val = global("HERBIVORE_NOURISH_VALUE");
  score = score + val;
}

// end of file
