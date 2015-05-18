// Tyler Cole
// EVO Project Module Implementation
// genetics.cpp

#include "genetics.h"
using namespace std;

Gene::Gene()
{ }

Gene::Gene( int init_state,
            Direction init_direction,
            Actor_Type init_sight,
            Action init_memory,
            Action init_next_action )
{
  state = init_state;
  direction = init_direction;
  sight = init_sight;
  memory = init_memory;
  next_action = init_next_action;
}

//------------------------------------------------------------------------------

void new_dna( vector<Gene>& dna )
{
  static unsigned int s,d,t,m;
  static unsigned int count_states = global("COUNT_STATES");
  dna.clear();  
  dna.reserve( count_states * COUNT_DIRECTIONS * COUNT_ACTOR_TYPES * COUNT_MEMORIES );
  
  for (s = 0; s < count_states; s++)
  { for (d = 0; d < COUNT_DIRECTIONS; d++)
    { for (t = 0; t < COUNT_ACTOR_TYPES; t++)
      { for (m = 0; m < COUNT_MEMORIES; m++)
        { 
          dna.push_back(
          Gene(// GENE IDENTIFIER
               /*State*/s,
               (Direction)d,
               (Actor_Type)t,
               (Action)m,
               // GENE RULE (ACTION)
               (Action)random( 0, COUNT_ACTIONS - 1 )));
        }
      }
    }
  }  
}

//------------------------------------------------------------------------------

void mutate( vector<Gene>& dna )
{
  // mutates a target dna according to the mutation rate
  vector<Gene>::iterator p = dna.begin();
  while( p != dna.end())
  {
    // both rules have chances of being modified
   	static int mutation_rate = global("MUTATION_RATE");
   	if( random( 1, 10000 ) < mutation_rate )
    {
      p->next_action = (Action)random( 0, COUNT_ACTIONS - 1 );
    }
	  p++;
  }
}

//------------------------------------------------------------------------------

void breed( vector<Gene>& dna_nextgen, vector< vector<Gene> >& dna_pool, Statistics& stats )
{
  unsigned int i, f,m,c;
  vector<int> wheel;
  
  // this will fill the wheel with the index of each dna_pool candidate. however,
  // the number of copies that get inserted is equal to its score.
  for (i = 0; i < stats.score_vector.size(); i++)
    wheel.insert( wheel.end(), stats.score_vector[i], i );  
  
  if ( random( 0, 10000 ) < global("CROSSOVER_RATE") )
  {
    // Crossover occurs
    
    // "father"
    f = random( 0, wheel.size() - 1 );

    // "mother" ( != father )
    do
    {
      m = random( 0, wheel.size() - 1 );
    } while( wheel[m] == wheel[f] );
    
    splice( dna_nextgen, dna_pool[wheel[f]], dna_pool[wheel[m]] );
  }
  else 
  {
    // No crossover; copy only
    
    c = random( 0, wheel.size() - 1 );
    dna_nextgen = dna_pool[ wheel[c]];
  }
}

//------------------------------------------------------------------------------

void splice( vector<Gene>& dna_nextgen, vector<Gene>& donor_f, vector<Gene>& donor_m )
{
  dna_nextgen.clear();
  dna_nextgen.reserve( donor_f.size() );
  
  // crossover index determination: random( 0, (dna.size) - 1 )
  int cross = random( 0, donor_f.size() - 1 );
  
  int i;  
  // insert the subsequences
  for (i = 0; i < cross; i++)
    dna_nextgen.push_back( donor_f[i] );
  for (i = cross; i < donor_f.size(); i++)
    dna_nextgen.push_back( donor_m[i] );
}

//------------------------------------------------------------------------------

void init_genetics_external( bool& success, string filename,
                             vector< vector<Gene> >& extern_herb_dna_pool,
                             vector< vector<Gene> >& extern_carn_dna_pool )
{
  // validate extension
  if (!file_extension( filename, "dat" ))
  {
    output_color( string("$RError$w: file [$W") + filename + string("$w] is not a '$W.dat$w' file.\n") );
    success = false;
    return;
  }
  // validate existence
  if (!file_exist( filename ))
  {
    output_color( string("$RError$w: file [$W") + filename + string("$w] not found.\n") );
    success = false;
    return;
  }  
  
  ifstream data;
  data.open( filename.c_str() );
  
  unsigned int race, i, s,d,t,m, gene;
  vector< vector<Gene> >* race_container = &extern_herb_dna_pool;
  string race_pop = "HERBIVORE_POPULATION";
  
  // READ IN THE DATA
  for (race = 0; race <= 1; race++, race_container = &extern_carn_dna_pool, race_pop = "CARNIVORE_POPULATION")
  {
    for (i = 0; i < global(race_pop); i++)
    {
      vector<Gene> organism;
      
      gene = 0;
      for (s = 0; s < global("COUNT_STATES"); s++)
      { for (d = 0; d < COUNT_DIRECTIONS; d++)
        { for (t = 0; t < COUNT_ACTOR_TYPES; t++)
          { for (m = 0; m < COUNT_MEMORIES; m++)
            {
              Gene g;
              
              g.state = /*State*/s;
              g.direction = (Direction)d;
              g.sight = (Actor_Type)t;
              g.memory = (Action)m;
              
              gene =  s * (COUNT_DIRECTIONS * COUNT_ACTOR_TYPES * COUNT_MEMORIES)
                    + d * (COUNT_ACTOR_TYPES * COUNT_MEMORIES)
                    + t * COUNT_MEMORIES
                    + m;    

              while (1)
              {
                while ( isspace( data.peek() ) )
                  data.get();
                if ( data.peek() == ';')  
                  data.ignore( 1024, '\n' );
                else
                  break;
              }

              switch( data.get() )
              {
                case('F'): g.next_action = move_forward; break;
                case('B'): g.next_action = move_backward; break;
                case('L'): g.next_action = turn_left; break;
                case('R'): g.next_action = turn_right; break;
                default: success = false; output_color( string("$RError$w: file [$W") + filename + string("$w] contains corrupted or incompatible genetic data.\n")); return;
              }
              
              organism.push_back( g );
              gene++;
            }
          }
        }
      }
      
      race_container->push_back( organism );
    }
  }

  output_color( string("$WSuccessfully$w initialized all organisms from file [$W") + filename + string("$w].\n") );
  success = true;
  return;
}
    
//------------------------------------------------------------------------------

void write_genetics( string filename,
                     vector< vector<Gene> >& herb_dna_pool,
                     vector< vector<Gene> >& carn_dna_pool )
{
  ofstream data;
  data.open( filename.c_str() );
  if (!data) // if the file couldn't be opened for writing
  {
    output_color( string("$yWarning$w: file [$W") + filename + string("$w] could not be written to.\n") );
    data.close();
    return;
  }
  
  unsigned int i, s,d,t,m, gene;
  
  // header
  data << "; Tyler Cole" << endl;
  data << "; EVO Project Genetics Data" << endl;
  data << "; " << filename << endl;
  data << endl;
  
  data << "; DNA_LENGTH           " << global("COUNT_STATES") * COUNT_DIRECTIONS * COUNT_ACTOR_TYPES * COUNT_MEMORIES << endl;
  data << "; HERBIVORE_POPULATION " << global("HERBIVORE_POPULATION") << endl;
  data << "; CARNIVORE_POPULATION " << global("CARNIVORE_POPULATION") << endl;
  data << endl;
  
  data << endl << "; Herbivore data" << endl << endl;
  
  for (i = 0; i < herb_dna_pool.size(); i++)
  {
    gene = 0;
    data << "; ID " << i + 1 << endl;
    for (s = 0; s < global("COUNT_STATES"); s++)
    { for (d = 0; d < COUNT_DIRECTIONS; d++)
      { for (t = 0; t < COUNT_ACTOR_TYPES; t++)
        { for (m = 0; m < COUNT_MEMORIES; m++)
          {
            switch(herb_dna_pool[i][gene].next_action)
            {
              case(move_forward) : data << "F"; break;
              case(move_backward): data << "B"; break;
              case(turn_left)    : data << "L"; break;
              case(turn_right)   : data << "R"; break;
              default            : data << "*"; break;
            }
            gene++;
          }
        }
      }
      data << endl; // newline at end of each state, to keep visible text looking half-decent
    }
    data << endl;
  }
  
  data << endl << "; Carnivore data" << endl << endl;
  
  for (i = 0; i < carn_dna_pool.size(); i++)
  {
    gene = 0;
    data << "; ID " << i + 1 << endl;
    for (s = 0; s < global("COUNT_STATES"); s++)
    { for (d = 0; d < COUNT_DIRECTIONS; d++)
      { for (t = 0; t < COUNT_ACTOR_TYPES; t++)
        { for (m = 0; m < COUNT_MEMORIES; m++)
          {
            switch(carn_dna_pool[i][gene].next_action)
            {
              case(move_forward) : data << "F"; break;
              case(move_backward): data << "B"; break;
              case(turn_left)    : data << "L"; break;
              case(turn_right)   : data << "R"; break;
              default            : data << "*"; break;
            }
            gene++;
          }
        }
      }
      data << endl; // newline at end of each state, to keep visible text looking half-decent
    }
    data << endl;
  }
  
  data.close();
  output_color( string("$WSuccessfully$w wrote genetics data to file [$W") + filename + string("$w].\n") );
}

// end of file
