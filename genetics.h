// Tyler Cole
// EVO Project Module Header
// genetics.h

#ifndef _GENETICS_H_
#define _GENETICS_H_

#include <vector>
using std::vector;
#include <queue>
using std::queue;
#include "settings.h"
#include "basic.h"
#include "random.h"
  
// Data-only class for a single gene
class Gene
{
  public:
  Gene();
  Gene( int, Direction, Actor_Type, Action, Action );
  
  unsigned int state;
  Direction    direction;
  Actor_Type   sight;
  Action       memory;
  Action       next_action;
};

// Creates a randomized set of genes.
void new_dna( vector<Gene>& dna );

// Randomly mutates a set of genes based on the current
// rate of mutation.
void mutate( vector<Gene>& dna );

// Natural Selection.
// Picks two (or possibly just one) dna sets for reproduction.
// If two are chosen, they are spliced together.
// Probability of Dna[i] being chosen is score[i]/total_score.
void breed( vector<Gene>& dna_nextgen, vector< vector<Gene> >& dna_pool, Statistics& stats );

// Actual Splicing Operation
void splice( vector<Gene>& result, vector<Gene>& donor_f, vector<Gene>& donor_m );
                     
// DNA I/O
void init_genetics_external( bool& success, string filename,
                             vector< vector<Gene> >& extern_herb_dna_pool,
                             vector< vector<Gene> >& extern_carn_dna_pool );

void write_genetics( string filename,
                     vector< vector<Gene> >& herb_dna_pool,
                     vector< vector<Gene> >& carn_dna_pool );

#endif
// end of file
