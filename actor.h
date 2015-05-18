// Tyler Cole
// EVO Project Module Header
// actor.h

#ifndef _ACTOR_H_
#define _ACTOR_H_

#include <vector>
using std::vector;
#include <string>
using std::string;
#include "basic.h"
#include "genetics.h"
#include "settings.h"

// note: the following classes are abstract:
// Actor, Dynamic_Actor
// and therefore are not meant to be initialized

class Actor
{ 
  public:
  Actor();
  
  string name;
  Actor_Type type;
};

class Empty : public Actor
{ 
  public:
  Empty();
};

class Wall : public Actor
{
  public:
  Wall();
};

class Plant : public Actor
{
  public:
  Plant();
};

class Dynamic_Actor : public Actor
{
  public:
  Dynamic_Actor();
  
  void just_spawned( Location spawn );
  void remember( Action new_memory );
  void reset_score();
  
  unsigned int id;
  Direction direction;
  Actor_Type sight;
  Action memory;
  unsigned int state;
  Location location;
  unsigned int score;
  vector<Gene> dna;
};

class Herbivore : public Dynamic_Actor
{
  public:  
  Herbivore();
  
  void consumed_plant();
  void was_consumed();
};

class Carnivore : public Dynamic_Actor
{
  public:  
  Carnivore();
  
  void consumed_herbivore();
};

#endif
// end of file
