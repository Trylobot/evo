// Tyler Cole
// EVO Project Module Exhaustive Testing Application
// test.cpp

#include <iostream>
#include <ctime>
#include <vector>
#include <string>
#include "basic.h"
#include "settings.h"
#include "genetics.h"
#include "actor.h"
#include "random.h"
#include "timer.h"
#include "ui.h"
#include "world.h"
#include "tokenize.h"
#include "output_color.h"
using namespace std;

string to_string( Location L );
string to_string( Gene );
string to_string( vector< vector<Gene> >& dna_pool );

int main()
{
  seed(time(0));
  
  // Ä³Ú¿ÀÙÁÂ
  output_color("ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿\n");
  output_color("³ $WEVO$w Project ³ $YModule Exhaustive Testing App$w ³\n");
  output_color("ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ\n");
  
  init_settings_external("test.dat");
  World sim;
  unsigned int i;
  
  /*** CONTAINMENT ***
  
  output_color("\n");
  vector< vector<Gene> > herb_dna_pool;
  unsigned int pop = sim.herbivores.size();
  
  for (i = 0; i < pop; i++)
    herb_dna_pool.push_back( sim.herbivores[i].dna );
  vector<Gene> child;
  splice( child, sim.herbivores[7].dna, sim.herbivores[6].dna );
  herb_dna_pool.push_back( child );
  
  output_color( to_string( herb_dna_pool ));
  output_color("\n");
    
   *** END CONTAINMENT ***/  
  /*** TEST ACTIVE ***/
  
  sim.do_cycle();
  
  /*** END ***/
  
  output_color("Test concluded.\n");  
  return( EXIT_SUCCESS );
}

string to_string( Location L )
{
  string out = "";
  out += "(" + to_string(L.row) + "," + to_string(L.col) + ")";
  return out;
}

string to_string( Gene g )
{
  string out = "";
  switch( g.next_action )
  {
    case( move_forward ) : out += "$yF"; break;
    case( move_backward ): out += "$gB"; break;
    case( turn_left )    : out += "$bL"; break;
    case( turn_right )   : out += "$rR"; break;
  }
  return out;
}

string to_string( vector< vector<Gene> >& dna_pool )
{
  unsigned int i, j;
  string out = "";
  
  for (i = 0; i < dna_pool.size(); i++)
    out += to_string( i );
  out += "$w\n";
  
  for (i = 0; i < dna_pool[0].size(); i++)
  {
    for (j = 0; j < dna_pool.size(); j++)
      out += to_string( dna_pool[j][i] );

    out += "$w\n";
  }  
  return out;
}

// end of file
