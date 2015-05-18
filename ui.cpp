// Tyler Cole
// EVO Project Module Header
// ui.h

#include "ui.h"
using namespace std;

char pause_menu()
{
  char temp;
  show_cursor();
  
  system("cls");
  output_color(
    string("\n   $wÚÄÄÄÄÄ¿         \n") +
    string("   ³ $WEVO$w ³         \n") +
    string(" ÉÍÏÍÍÍÍÍÏÍÍÍÍÍÍÍÍ»\n") +
    string(" º *** $WPAUSED$w *** º\n") +
    string(" º $WM$w : Main Menu  º\n") +
    string(" º $WK$w : Meteor! :D º\n") +
    string(" º $GC$w : Continue   º\n") +
    string(" ÓÄÂÄÄÄÄÄÂÄÄÄÂÄÄÄÄ½\n") +
    string("   ³ $W>>>$w ³   ³     \n") +
    string("   ÀÄÄÄÄÄÁÄÄÄÙ     $W\n")
  );
  
  static Location pause_prompt( 9, 11 );
  set_cursor( pause_prompt );
  
  do
  {
    temp = toupper((char)getch());
    set_cursor( pause_prompt );
    cout << " ";
    set_cursor( pause_prompt );
  } while (temp != 'M' && temp != 'K' && temp != 'C');
  
  output_color("$w\n\n");
  
  return temp;
}

//------------------------------------------------------------------------------

void splash()
{
  output_color(
    string("$g\n") +
    string("$g ßÛÛßßÛßÛÛ ÛßŞÛÛİ  $wThe\n") +
    string("$g  ÛÛÜİ  ÛÛ Û ÛÛ Û  $wEvolution\n") +
    string("$g  ÛÛ İ  ÛÛ Û ÛÛ Û  $wSimulator\n") +
    string("$g ÜÛÛÜÜÛ ŞÛÛİ ŞÛÛİ  $w($Wc$w) 2005 $WTyler W$w. $WCole\n") +
    string("$w\n")
  );
}

//------------------------------------------------------------------------------

void menu()
{
  switch( global("FLAG_MENU") )
  {
    case( 0 ): // detailed
      output_color(
        string("$w") +
        string(" ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿\n") +
        string(" ³ [$WEVO$w] $WMain Menu$w ³\n") +
        string(" ÃÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿\n") +
        string(" ³ $WMENU$w          cycle between detailed and minimalistic menu modes.       ³\n") +
        string(" ³ $YSLOW$w          run the simulation for one cycle in observation mode.     ³\n") +
        string(" ³ $YFAST$w <$Ynumber$w> run the simulation in minimal mode for <$Ynumber$w> cycles.   ³\n") +
        string(" ³ $GABOUT$w         learn about this simulation, and the theory behind it.    ³\n") +
        string(" ÃÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ´\n") +
        string(" ³ $CNEW$w           erase the current genetics, and restart the simulation.   ³\n") +
        string(" ³ $BSAVE$w <$Bfile$w>   save the genetics data to <$Bfile$w>.                         ³\n") +
        string(" ³ $BLOAD$w <$Bfile$w>   load the genetics data in <$Bfile$w>.                         ³\n") +
        string(" ³ $YEDIT$w          go to genetics editing mode.                              ³\n") +
        string(" ÃÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ´\n") +
        string(" ³ $WOPTION$w        change the current settings (may require restart).        ³\n") +
        string(" ³ $WEXIT$w          exit the simulation.                                      ³\n") +
        string(" ÀÄÄÂÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄÄÙ\n") +
        string("    ³ $WPAUSE$w the simulation by pressing $Wany key$w while running. ³\n") +
        string(" ÚÄÄÁÄÄÂÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ\n") +
        string(" ³ $W>>>$w ³                               $w³           ($Wc$w) 2005 $WTyler W$w. $WCole$w\n") +
        string(" ÀÄÄÄÄÄÁÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ$W\n")
      );
    break;
    
    case( 1 ): // minimal
      output_color(
        string("$w") +
        string(" ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿\n") +
        string(" ³ [$WEVO$w] Main Menu ³\n") +
        string(" ÃÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿\n") +
        string(" ³ $WMENU $YSLOW FAST $GABOUT $CNEW $BSAVE LOAD $YEDIT $WOPTION EXIT$w ³\n") +
        string(" ÃÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ\n") +
        string(" ³ $W>>>$w ³                               ³ ($Wc$w) 2005 $WTyler W$w. $WCole$w\n") +
        string(" ÀÄÄÄÄÄÁÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ$W\n")
      );
    break;
  }  
  // move the cursor to the command line
  set_cursor( get_cursor() + Location( -2, 9 ) );
}

//------------------------------------------------------------------------------

void options( string& settings_file )
{
  unsigned int i,
               top_row = 3,
               selected = 0,
               key,
               input;
  
  string color_token,
         field_token,
         status_str = global_desc(0),
         arrow;
  
  Location settings_file_display( 1, 26 ),
           status( top_row + COUNT_GLOBALS + 1, 0 );
  
  system("cls");
  hide_cursor();
  
  output_color(
    string("              $wÚÄÄÄÄÄÄÄÄÄ¿\n") +
    string("              ³ $WOptions$w ³\n") +
    string("              ÀÄÄÄÄÄÄÄÄÄÙ\n")
  );
  
  bool done = false;
  while (!done)
  {
    // display the settings
    set_cursor( settings_file_display );
    output_color( string("%k$Y") + settings_file );
    
    set_cursor( Location( top_row, 0 ));
    for (i = 0; i < COUNT_GLOBALS; i++)
    {
      switch (i)
      {
        case( 0): color_token = "$w"; break;
        case( 1): color_token = "$w"; break;
        case( 2): color_token = "$y"; break;
        case( 3): color_token = "$y"; break;
        case( 4): color_token = "$y"; break;
        case( 5): color_token = "$w"; break;
        case( 6): color_token = "$y"; break;
        case( 7): color_token = "$y"; break;
        case( 8): color_token = "$w"; break;
        case( 9): color_token = "$w"; break;
        case(10): color_token = "$w"; break;
        case(11): color_token = "$r"; break;
        case(12): color_token = "$r"; break;
        case(13): color_token = "$r"; break;
        case(14): color_token = "$r"; break;
        case(15): color_token = "$w"; break;
        case(16): color_token = "$y"; break;
        case(17): color_token = "$y"; break;
        case(18): color_token = "$y"; break;
        case(19): color_token = "$w"; break;
      }      
      field_token = "%w$K";
      arrow = " %k$W  ";
      if (i == selected)
      {
        color_token[1] = toupper(color_token[1]);
        field_token = "%W$k";
        arrow = " %k$W ";
      }
      
      output_color( color_token );
      output_color( global_name(i), 25, 'R' );
      output_color(" ");
      output_color( field_token );
      output_color( to_string( global( global_name(i) ), 8, 'R' ));
      output_color( arrow );
      output_color(" \n%k$w");
    }
    set_cursor( status );
    status_str = global_desc( selected );
    output_color( string("$w") + status_str.substr( 1, status_str.size()-1 ), 80, 'L' );
    set_cursor( status + Location( 1, 0 ) );
    output_color( string(" ESC or Q to return to menu"), 0, 'L' );
    
    // get user input
    set_cursor( Location( top_row + selected, 33 ));
    key = getch();
    switch( key )
    {
      // [][]
      case(224):
        key = (key * 100) + getch();
        if (key == ARROW_UP)
        {
          if (selected == 0)
            selected = COUNT_GLOBALS - 1;
          else
            selected--;
        }
        else if (key == ARROW_DN)
        {
          if (selected == COUNT_GLOBALS - 1)
            selected = 0;
          else
            selected++;
        }        
      break;
      
      case(ENTER):
        set_cursor( Location( top_row + selected, 26 ));
        show_cursor();
        output_color("%W$k        ");
        
        input = 0;        
        while (input / 10000000 == 0)
        {
          key = getch();
          
          if (key >= 48 && key <= 57)
          {
            if (input < 0)
              input = (key - 48);
            else
            {
              input *= 10; // shift number left a digit
              input += (key - 48); // add the number
            }
            set_cursor( Location( top_row + selected, 26 ));
            output_color("%W$k");
            output_color( to_string( input, 8, 'R' ) );
          }
          
          // done  
          else if (key == ENTER)
          {
            set_global( global_name( selected ), input );
            break;
          }
          
          // cancel command
          else if (key == BACKSPACE)
            break;
          
          else if (key == 0 || key == 224)
            getch(); // erase next key
        }
        hide_cursor();
      break;
      
      case(ESC):
      case('q'):
      case('Q'):
        done = true;
        system("cls");
      break;
    }
  }
}

//------------------------------------------------------------------------------

void about()
{
  system("cls");
  string dummy;

  output_color(
    string( string("\n%k$w[$WEVO$w] current version: $W") + string(EVO_PROJECT_VERSION) + string("$w\n\n") ) +
    string("This simulation demonstrates the genetic algorithm, and it uses the process\n") +
    string("of natural evolution as a model for solving a specific problem. It implements\n") +
    string("(with varying degrees of success) $Wnatural selection$w, $Wmutation$w, and $Wgenetic\n") +
    string("recombination$w in an attempt to 'evolve' a solution to the problem. The way that\n") +
    string("I've applied it here to simulated organisms, and there are two different types.\n") +
    string("You'll notice the green arrows, those represent $GHerbivores$w, who are trying to\n") +
    string("eat the small yellow dots, which represent $YPlants$w. The red arrows are $RCarnivores$w.\n") +
    string("Whenever an organism is destroyed, it respawns somewhere else, so\n") +
    string("the population is held constant for simplicity. However, if an Herbivore is\n") +
    string("eaten, it does take a score decrease (this is to discourage being eaten).\n") +
    string("$YPlants$w don't have any genetics in the simulation, but you can affect how all 3 \n") +
    string("types of organisms respawn in the settings file (default is 'settings.dat').$w\n") +
    string("Press ENTER to continue . . . ")
  );
  
  getline(cin,dummy);
    
  output_color(
    string("\nThe world is a grid of squares. Each can be occupied by no more than one type\n") +
    string("of organism at a time. The behavior of the $GHerbivores$w and $RCarnivores$w is entire-\n") +
    string("ly determined by rules. The rules for each organism are unique and start out\n") +
    string("randomized and chaotic. A single rule has the format of, for a specified\n") +
    string("current state (direction, sight, and state number) there is an action to take.\n") +
    string("An action can be one of (move forward or backward, or turn left or right).\n") +
    string("The full set of rules for each organism covers every possible state. At the end\n") +
    string("of each cycle, scores are calculated and the genetics takes over. Mutation is\n") +
    string("applied to each gene, using the rate specified in settings. Crossover can occur\n") +
    string("as well. High-scoring organisms are likely to be copied many times, but every\n") +
    string("single organism has a possibility of being copied. Once the new generation has\n") +
    string("been created, it starts all over again at the beginning of a new cycle.\n") +
    string("Press ENTER to continue . . . ")
  );
  
  getline(cin,dummy);
  
  output_color(
    string("\nThere are some other things you can do just for fun :) One is to send a meteor\n") +
    string("down to stop the current cycle, instead of pausing and returning. Do this by\n") +
    string("starting up a slow simulation, pause, and hit K. This will show the meteor impact\n") +
    string("and completely obliterate the current organisms. (Note that their dna is not\n") +
    string("erased, as that would be kind of retarded!) There are also some undocumented\n") +
    string("commands. Try these: $Wvirus$w (not actual virus), $Wpong$w. Have fun :)\n") +
    string("Press ENTER to return to [$WMain Menu$w] . . . ")
  );
  
  getline(cin,dummy);
  
  cout << endl;  
}

//------------------------------------------------------------------------------

void genetics_edit( vector<Herbivore>& herbivores, vector<Carnivore>& carnivores )
{
  system("cls");
  unsigned int count_states = global("COUNT_STATES");
               
  output_color(
    string("$w") +
    string("ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿    ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿ \n") +
    string("³ [$WDNA$w] Edit Mode ³    ³    - $WKEY$w -             ³³ ($YF$w|$GB$w|$BL$w|$RR$w)    : Modify target gene         ³ \n") +
    string("ÃÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÁÄÄÄ¿³ st $yState$w     [$Y1$w - $Y") + to_string( count_states, 3, 'R' ) + string("$w] ³³ ($GH$w|$RC$w) <$Wid$w>   : Switch organism $Wtype$w & $Wid$w  ³ \n") +
    string("³ _________ _____     ³³  d $bDirection$w ($BN$w|$BE$w|$BS$w|$BW$w) ³³ $WS$w <$Yst$w $Bd$w $Gs$w $Cm$w> : Search for specified gene  ³ \n") +
    string("³ st d s m : action   ³³  s $gSight$w   ($Ge$w|$Gw$w|$Gp$w|$Gh$w|$Gc$w) ³³ [$W$w][$W$w][$W$w][$W$w] : Move around visual display ³ \n") +
    string("³ __ _ _ _   ________ ³³  m $cMemory$w  ($CF$w|$CB$w|$CL$w|$CR$w|$CS$w) ³³ $WEXIT$w         : Return to [$WMain Menu$w]      ³ \n") +
    string("ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ \n")
  );

  // DNA Visual Box BEGIN
  // top row
  unsigned int i;
  output_color("$wÚ");
  for (i = 0; i < COUNT_DIRECTIONS * COUNT_ACTOR_TYPES * COUNT_MEMORIES; i++)
      output_color("Ä");
  output_color("¿\n");
  // middle rows
  for (i = 0; i < count_states; i++)
  { 
    output_color("³");
    set_cursor( get_cursor() + Location( 0, COUNT_DIRECTIONS * COUNT_ACTOR_TYPES * COUNT_MEMORIES) );
    output_color("³\n");
  }
  // bottom row
  output_color("À");
  for (i = 0; i < COUNT_DIRECTIONS * COUNT_ACTOR_TYPES * COUNT_MEMORIES; i++)
      output_color("Ä");
  output_color("Ù\n");
  // Visual Box END

  // Command Box
  output_color(  
    string("ÚÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿ ($Wc$w) 2005 $WTyler W$w. $WCole$w\n") +
    string("³ $W>>>$w ³               ³\n") +
    string("ÀÄÄÄÄÄÁÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ\n")
  );
  
  // DECLARATIONS BEGIN
  Dynamic_Actor* organism = (Dynamic_Actor*) &herbivores[0];

  bool done = false,
       parsing,
       flag_big_refresh = true;

  unsigned int gene_index = 0, // index into the dna of the organism
               line, gi, q, // temporary gene drawing variables
               top_row = 8, // gene_cursor limits
               bottom_row = top_row + (count_states - 1),
               left_col = 1,
               right_col = COUNT_DIRECTIONS * COUNT_ACTOR_TYPES * COUNT_MEMORIES,
               key, // temp integer for storing keypresses
               digits,
               max_digits;
  
  int s = 0, d = 0, t = 0, m = 0, // gene identifiers
      ts, td, tt, tm, // temporary gene identifiers
      organism_i; // temp integer for storing possible organism index
           
  Location organism_tag( 3, 2 ),
           gene_string( 5, 2 ),
           gene_box_init( 7, 0 ),
           command_line( 10 + count_states, 8 ), // where the command line box is
           gene_cursor = gene_box_init + Location( 1, 1 ); // describes where the CENTER of the target box is
  
  Direction cursor_mv = invalid_direction;
  // DECLARATIONS END
  
  while (!done)
  {
    // calculations
    if (m == COUNT_MEMORIES)
    {
      m = 0;
      t++;
      if (t == COUNT_ACTOR_TYPES)
      {
        t = 0;
        d++;
        // ASSERTION
        // if (d == COUNT_DIRECTIONS) { set_cursor( gene_cursor ); output_color("\n$RError$w: Assertion failed (d too high)\n"); system("pause"); }
      }
    }
    if (m < 0)
    {
      m = COUNT_MEMORIES - 1;
      t--;
      if (t < 0)
      {
        t = COUNT_ACTOR_TYPES - 1;
        d--;
        // ASSERTION
        // if (d < 0) { set_cursor( gene_cursor ); output_color("\n$RError$w: Assertion failed (d negative)\n"); system("pause"); }
      }
    }
    gene_index =   s * (COUNT_DIRECTIONS * COUNT_ACTOR_TYPES * COUNT_MEMORIES)
                 + d * (COUNT_ACTOR_TYPES * COUNT_MEMORIES)
                 + t * COUNT_MEMORIES
                 + m;
    
    // draw the info    
    hide_cursor();
    
    set_cursor( organism_tag );
    switch( organism->type )
    {
      case( herbivore ): output_color("$GHERBIVORE$W "); break;
      case( carnivore ): output_color("$RCARNIVORE$W "); break;
    }
    // pretend we have a naturally indexed array instead of a zero-indexed one.
    output_color( to_string((organism->id + 1), 5, 'L'));
    
    set_cursor( gene_string );
    output_color( string("$Y") + to_string( s + 1, 2, 'R') + string(" ") );
    switch( d )
    {
      case( north ): output_color("$BN "); break;
      case( east ) : output_color("$BE "); break;
      case( south ): output_color("$BS "); break;
      case( west ) : output_color("$BW "); break;
    }
    switch( t )
    {
      case( empty )    : output_color("$Ge "); break;
      case( wall )     : output_color("$Gw "); break;
      case( plant )    : output_color("$Gp "); break;
      case( herbivore ): output_color("$Gh "); break;
      case( carnivore ): output_color("$Gc "); break;
    }
    switch( m )
    {
      case( move_forward ) : output_color("$CF   "); break;
      case( move_backward ): output_color("$CB   "); break;
      case( turn_left )    : output_color("$CL   "); break;
      case( turn_right )   : output_color("$CR   "); break;
      case( change_state ) : output_color("$CS   "); break;
    }
    switch( organism->dna[gene_index].next_action )
    {
      case( move_forward ) : output_color("$WFORWARD "); break;
      case( move_backward ): output_color("$WBACKWARD"); break;
      case( turn_left )    : output_color("$WLEFT    "); break;
      case( turn_right )   : output_color("$WRIGHT   "); break;
    }
    
    if (flag_big_refresh)
    {
      flag_big_refresh = false;
      
      set_cursor( gene_box_init );
      output_color("$wÚ");
      for (i = 0; i < COUNT_DIRECTIONS * COUNT_ACTOR_TYPES * COUNT_MEMORIES; i++)
          output_color("Ä");
      output_color("¿\n");
      for (line = 0, gi = 0; line < count_states; line++)
      {
        output_color("$w³");
        for (q = 0; q < (COUNT_DIRECTIONS * COUNT_ACTOR_TYPES * COUNT_MEMORIES); q++)
        {
          switch( organism->dna[gi].next_action )
          {
            case( move_forward ) : output_color("$yF"); break;
            case( move_backward ): output_color("$gB"); break;
            case( turn_left )    : output_color("$bL"); break;
            case( turn_right )   : output_color("$rR"); break;
          }
          gi++;
        }
        output_color("$w³\n");
      }
      // bottom row
      output_color("$wÀ");
      for (i = 0; i < COUNT_DIRECTIONS * COUNT_ACTOR_TYPES * COUNT_MEMORIES; i++)
          output_color("Ä");
      output_color("Ù\n");
    }
    // draw the new cursor
    set_cursor( gene_cursor );
    switch( organism->dna[gene_index].next_action )
    {
      case( move_forward ) : output_color("%W$kF%k$w"); break;
      case( move_backward ): output_color("%W$kB%k$w"); break;
      case( turn_left )    : output_color("%W$kL%k$w"); break;
      case( turn_right )   : output_color("%W$kR%k$w"); break;
    }
    
    // get the command    
    show_cursor();
    output_color("%k$W");
    
    parsing = true;
    while( parsing )
    {
      // move cursor to command box.
      set_cursor( command_line );
      // erase whatever crap was there.
      output_color("              ");
      set_cursor( command_line );
      // wait for a single keypress
      while( !kbhit() )
        { /* chill */ }
      // now there's at least one char waiting to be getch'ed
      // note: in my switch statements, I list uppercase char, then lowercase version
      
      // initialize vars
      organism_i = -1;
      ts = -1;
      td = -1;
      tt = -1;
      tm = -1;
      
      // switch on first keypress
      key = getch();
      switch(key)
      {
        
        // F
        case( 70):case(102):
          organism->dna[gene_index].next_action = move_forward;
          parsing = false;
        break;
        
        // B
        case( 66):case( 98):
          organism->dna[gene_index].next_action = move_backward;
          parsing = false;
        break;
        
        // L
        case( 76):case(108):
          organism->dna[gene_index].next_action = turn_left;
          parsing = false;
        break;
        
        // R
        case( 82):case(114):
          organism->dna[gene_index].next_action = turn_right;
          parsing = false;
        break;
        
        // H
        case( 72):case(104):
          output_color("$GH $W");
          while( organism_i / 10001 == 0 )
          {
            // add a numeral to it
            key = getch();
            // zero - nine
            if (key >= 48 && key <= 57)
            {
              if (organism_i < 0)
                organism_i = (key - 48);
              else
              {
                organism_i *= 10; // shift number left a digit
                organism_i += (key - 48); // add the number
              }
              set_cursor( command_line + Location( 0, 2 ) );
              output_color( to_string(organism_i) );
            }
            // done  
            else if (key == ENTER)
              break;
            // cancel command
            else if (key == BACKSPACE)
            {
              parsing = false;
              break;
            }
            else if (key == 0 || key == 224)
              getch(); // erase next key
            // otherwise, we loop back. the user is (hopefully?) figuring out what to do.
          }
          // I'm showing the user a naturally-indexed array of organisms.
          organism_i--;
          // that should do it.
          if (organism_i >= 0 && organism_i < global("HERBIVORE_POPULATION"))
          {
            // change target organism.
            organism = (Dynamic_Actor*) &herbivores[organism_i];
            flag_big_refresh = true;
          }
          // either way, this command is done with.
          parsing = false;
        break;
        
        // C
        case( 67):case( 99):
          output_color("$RC $W");
          while( organism_i / 10000 == 0 )
          {
            // add a numeral to it
            key = getch();
            // zero - nine
            if (key >= 48 && key <= 57)
            {
              if (organism_i < 0)
                organism_i = (key - 48);
              else
              {
                organism_i *= 10; // shift number left a digit
                organism_i += (key - 48); // add the number
              }
              set_cursor( command_line + Location( 0, 2 ) );
              output_color( to_string(organism_i) );
            }
            // done  
            else if (key == ENTER)
              break;
            // cancel command
            else if (key == BACKSPACE)
            {
              parsing = false;
              break;
            }              
            else if (key == 0 || key == 224)
              getch(); // erase next key
            // otherwise, we loop back. the user is (hopefully?) figuring out what to do.
          }
          // early cut
          if (!parsing)
            break;
            
          // I'm showing the user a naturally-indexed array of organisms.
          organism_i--;
          // that should do it.
          if (organism_i >= 0 && organism_i < global("CARNIVORE_POPULATION"))
          {
            // change target organism.
            organism = (Dynamic_Actor*) &carnivores[organism_i];
            flag_big_refresh = true;
          }
          // either way, this command is done with.
          parsing = false;
        break;
        
        // S
        case( 83):case(115):
          output_color("$WS ");
          // state ($Y)
          digits = 0;
          max_digits = to_string(count_states).size();
          while ( digits < max_digits ) // ts still valid
          {
            key = getch();
            // zero - nine
            if (key >= 48 && key <= 57)
            {
              if ( !(digits == 0 && key == 48))
                digits++;
              
              if (ts < 0)
                ts = (key - 48);
              else
              {
                ts *= 10; // shift number left a digit
                ts += (key - 48); // add the number
              }
              
              if (ts < 1 || ts > (count_states))
              { // reset ts
                ts = -1;
                digits = 0;
                set_cursor( command_line + Location( 0, 2 ) );
                output_color("  ");
                set_cursor( command_line + Location( 0, 2 ) );
                continue;
              }
              set_cursor( command_line + Location( 0, 2 ) );
              output_color( string("$Y") + to_string( ts, 2, 'R' ) );
            }
            else if (key == ENTER || key == BACKSPACE)
            {
              parsing = false;
              break;
            }
            else if (key == 0 || key == 224)
              getch(); // erase next key
            
            else if (digits > 0 &&
                     (key == 78 || key == 110 ||
                      key == 69 || key == 101 ||
                      key == 83 || key == 115 ||
                      key == 87 || key == 119 ))
            {
              ungetch(key);
              break;
            }
          }
          // check early.
          if (!parsing)
            break;
          output_color(" ");
          
          while (1)
          {
            // direction ($B)
            key = getch();
            // N
            if (key == 78 || key == 110)
            {
              set_cursor( command_line + Location( 0, 5 ) );
              output_color("$BN ");
              td = (int) north;
              break;
            }
            // E
            else if (key == 69 || key == 101)
            {
              set_cursor( command_line + Location( 0, 5 ) );
              output_color("$BE ");
              td = (int) east;
              break;
            }
            // S
            else if (key == 83 || key == 115)
            {
              set_cursor( command_line + Location( 0, 5 ) );
              output_color("$BS ");
              td = (int) south;
              break;
            }
            // W
            else if (key == 87 || key == 119)
            {
              set_cursor( command_line + Location( 0, 5 ) );
              output_color("$BW ");
              td = (int) west;
              break;
            }
            else if (key == ENTER || key == BACKSPACE)
            {
              parsing = false;
              break;
            }
            else if (key == 0 || key == 224)
              getch(); // erase next key
          }
          if (!parsing)
            break;
              
          while(1)
          {
            // sight ($G)
            key = getch();
            // e
            if (key == 69 || key == 101)
            {
              set_cursor( command_line + Location( 0, 7 ) );
              output_color("$Ge ");
              tt = (int) empty;
              break;
            }
            // w
            else if (key == 87 || key == 119)
            {
              set_cursor( command_line + Location( 0, 7 ) );
              output_color("$Gw ");
              tt = (int) wall;
              break;
            }
            // p
            else if (key == 80 || key == 112)
            {
              set_cursor( command_line + Location( 0, 7 ) );
              output_color("$Gp ");
              tt = (int) plant;
              break;
            }
            // h
            else if (key == 72 || key == 104)
            {
              set_cursor( command_line + Location( 0, 7 ) );
              output_color("$Gh ");
              tt = (int) herbivore;
              break;
            }
            // c
            else if (key == 67 || key == 99)
            {
              set_cursor( command_line + Location( 0, 7 ) );
              output_color("$Gc ");
              tt = (int) carnivore;
              break;
            }
            else if (key == ENTER || key == BACKSPACE)
            {
              parsing = false;
              break;
            }
            else if (key == 0 || key == 224)
              getch(); // erase next key
          }
          if (!parsing)
            break;  
            
          while(1)
          {
            // memory ($C)
            key = getch();
            // F
            if (key == 70 || key == 102)
            {
              set_cursor( command_line + Location( 0, 9 ) );
              output_color("$CF");
              tm = (int) move_forward;
              break;
            }
            // B
            else if (key == 66 || key == 98)
            {
              set_cursor( command_line + Location( 0, 9 ) );
              output_color("$CB");
              tm = (int) move_backward;
              break;
            }
            // L
            else if (key == 76 || key == 108)
            {
              set_cursor( command_line + Location( 0, 9 ) );
              output_color("$CL");
              tm = (int) turn_left;
              break;
            }
            // R
            else if (key == 82 || key == 114)
            {
              set_cursor( command_line + Location( 0, 9 ) );
              output_color("$CR");
              tm = (int) turn_right;
              break;
            }
            // S
            else if (key == 83 || key == 115)
            {
              set_cursor( command_line + Location( 0, 9 ) );
              output_color("$CS");
              tm = (int) change_state;
              break;
            }
            else if (key == ENTER || key == BACKSPACE)
            {
              parsing = false;
              break;
            }
            else if (key == 0 || key == 224)
              getch(); // erase next key
          }
          if (!parsing)
            break;

          // ENTER
          while(1)
          {
            if (ts < 0 || td < 0 || tt < 0 || tm < 0)
            {
              parsing = false;
              break;
            }
            
            key = getch();
            if (key == ENTER)
            {
              s = ts - 1; d = td; t = tt; m = tm;
              // draw the old location back in
              set_cursor( gene_cursor );
              switch( organism->dna[gene_index].next_action )
              {
                case( move_forward ) : output_color("$yF"); break;
                case( move_backward ): output_color("$gB"); break;
                case( turn_left )    : output_color("$bL"); break;
                case( turn_right )   : output_color("$rR"); break;
              }      
              gene_cursor.row = s + top_row;
              gene_cursor.col = d * (COUNT_ACTOR_TYPES * COUNT_MEMORIES) + t * COUNT_MEMORIES + m + left_col;
              parsing = false;
              break;
            }
            else if (key == BACKSPACE)
            {
              parsing = false;
              break;
            }
            else if (key == 0 || key == 224)
              getch(); // erase next key
          }
        break;
        
        // [][][][]
        case(224):
          key = (key * 100) + getch();
          // draw the old location back in
          set_cursor( gene_cursor );
          switch( organism->dna[gene_index].next_action )
          {
            case( move_forward ) : output_color("$yF"); break;
            case( move_backward ): output_color("$gB"); break;
            case( turn_left )    : output_color("$bL"); break;
            case( turn_right )   : output_color("$rR"); break;
          }      
          // []
          if (key == ARROW_UP)
          {
            if (gene_cursor.row > top_row)
            {
              gene_cursor.row--;
              s--;
            }
          }
          // []
          else if (key == ARROW_RT)
          {
            if (gene_cursor.col < right_col)
            {
              gene_cursor.col++;
              m++;
            }
          }
          // []
          else if (key == ARROW_DN)
          {
            if (gene_cursor.row < bottom_row)
            {
              gene_cursor.row++;
              s++;
            }
          }
          // []
          else if (key == ARROW_LF)
          {
            if (gene_cursor.col > left_col)
            {
              gene_cursor.col--;
              m--;
            }
          }
          // no matter what happened, command is done
          parsing = false;
        break;
        
        // E
        case( 69):case(101):
          output_color("$We");
          key = getch();
          // X
          if (key == 88 || key == 120)
          {
            output_color("x");
            key = getch();
            // I
            if (key == 73 || key == 105 )
            {
              output_color("i");
              key = getch();
              // T
              if (key == 84 || key == 116 )
              {
                output_color("t");
                key = getch();
                if (key == ENTER)
                {
                  // EXIT
                  done = true;
                  system("cls");
                }
                parsing = false;
              }
            }
          }
          parsing = false;
        break;
      }
    }
    // clear kbhit() buffer
    while( kbhit() )
    {
      // take care of those nasty two-char codes
      key = getch();
      if (key == 0)
        getch(); // getch again
    }
  }
}

//------------------------------------------------------------------------------

void kbot()
{
  output_color(
    string("$W") +
    string(" Û ÛÛÛÛÛÛÛÛÛÛ Û\n") +
    string(" Ü ÜÜÜ   ÜÜÜÜ Ü\n") +
    string(" Û ÛÛÛ ÜÛÛÛß  Û\n") +
    string(" Û ÛÛÛÛÛÛß    Û\n") +
    string(" Û ÛÛÛÛß      Û\n") +
    string(" Û ÛÛÛÛÜ      Û\n") +
    string(" Û ÛÛÛÛÛÛÜ    Û\n") +
    string(" Û ÛÛÛ ßÛÛÛÜ  Û\n") +
    string(" Û ßßß   ßßßß Û\n") +
    string(" Û ÛßİÛßİßÛß  Û\n") +
    string(" Û ÛßİÛ İ Û Û Û\n") +
    string(" ß ßß ßß  ß   ß\n") +
    string(" Û ÛÛÛÛÛÛÛÛÛÛ Û\n") +
    string("\n$w")
  );
  wait( 1.0 );
}

void firelord()
{
  output_color(
    string("                $YÛ      \n") +
    string("         $YÛ      $YÛ$YÛ     \n") +
    string("        $YÛ$YÛ     $YÛ$YÛ$YÛ     \n") +
    string("        $YÛ$YÛ$YÛ   $YÛ$YÛ$YÛ$YÛ     \n") +
    string("       $YÛ$YÛ$YÛ$YÛ$YÛ$YÛ $YÛ$YÛ$YÛ$YÛ$YÛ    \n") +
    string("     $YÛ$YÛ$YÛ$YÛ$RÛ$YÛ$YÛ$YÛ$YÛ$YÛ$YÛ$RÛ$YÛ$YÛ    \n") +
    string("    $YÛ$YÛ$YÛ$YÛ$RÛ$RÛ$RÛ$YÛ$YÛ$YÛ$YÛ$YÛ$RÛ$YÛ$YÛ$YÛ   \n") +
    string("   $YÛ$YÛ$YÛ$YÛ$RÛ$RÛ$RÛ$RÛ$RÛ$YÛ$YÛ$YÛ$RÛ$RÛ$YÛ$YÛ$YÛ   \n") +
    string("  $YÛ$YÛ$YÛ$YÛ$RÛ$RÛ$RÛ$rÛ$RÛ$RÛ$RÛ$RÛ$RÛ$RÛ$RÛ$YÛ$YÛ$YÛ$YÛ  \n") +
    string("  $YÛ$YÛ$YÛ$YÛ$RÛ$RÛ$rÛ$rÛ$rÛ$RÛ$RÛ$RÛ$rÛ$RÛ$RÛ$YÛ$YÛ$YÛ$YÛ  \n") +
    string("  $YÛ$YÛ$YÛ$YÛ$RÛ$RÛ$RÛ$rÛ$rÛ$rÛ$rÛ$rÛ$rÛ$RÛ$RÛ$YÛ$YÛ$YÛ$YÛ  \n") +
    string("  $YÛ$YÛ$YÛ$YÛ$YÛ$RÛ$RÛ$RÛ$RÛ$rÛ$rÛ$RÛ$RÛ$RÛ$YÛ$YÛ$YÛ$YÛ$YÛ  \n") +
    string("   $YÛ$YÛ$YÛ$YÛ$YÛ$YÛ$RÛ$RÛ$RÛ$RÛ$RÛ$RÛ$YÛ$YÛ$YÛ$YÛ$YÛ   \n") +
    string("      $YÛ$YÛ$YÛ$YÛ$YÛ$YÛ$YÛ$YÛ$YÛ$YÛ$YÛ      %k$w\n")
  );
  wait( 1.0 );
}

//------------------------------------------------------------------------------

void pong()
{
  // clear out input buffer
  while (kbhit())
    getch();system("cls");
  
  string arena = 
    string("                    $w(E,C) $RP1   $BP2 $w(O,M)\n")                + // 0
    string("ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÒÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿\n") + // 1
    string("³                   ³      0 º 0      ³                      ³\n") + // 2
    string("ÃÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÄĞÄÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ´\n") + // 3
    string("³                            °                               ³\n") + // 4
    string("³                            °                               ³\n") + // 5
    string("³                            °                               ³\n") + // 6
    string("³                            °                               ³\n") + // 7
    string("³                            °                               ³\n") + // 8
    string("³                            °                               ³\n") + // 9
    string("³                            °                               ³\n") + // 10
    string("³                            °                               ³\n") + // 11
    string("³                            °                               ³\n") + // 12
    string("³                            °                               ³\n") + // 13
    string("³                            °                               ³\n") + // 14
    string("³                            °                               ³\n") + // 15
    string("³                            °                               ³\n") + // 16
    string("³                            °                               ³\n") + // 17
    string("³                            °                               ³\n") + // 18
    string("ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ\n");  // 19
    //      00000000001111111111222222222233333333334444444444555555555566
    //      01234567890123456789012345678901234567890123456789012345678901
  
  
  output_color( arena );
  output_color("$W");
  double       wait_time = 0.150,
               wait_min = 0.030,
               delta_wait = 0.010;
  Location     bounds( 19, 61 );
  int          sw = 6; // score width
  unsigned int sc1 = 0, // scores for player 1 and player 2
               sc2 = 0,
               win = 20;
  Location     sc1P( 2, 29 - (sw + 1) ), // score drawing locations
               sc2P( 2, 29 + 2 );
  unsigned int p1 = 10, // paddle rows for player 1 and player 2
               p2 = 10;
  int          psize = 3;
  unsigned int upperb = 4,
               lowerb = 18;
  Location     bv( (random(0,1)?-1:1), (random(0,1)?-1:1) );
  Location     ball_init( 11, 29 );
  Location     b = ball_init;
  int i;
  bool done = false;
  
  // draw ball ù
  set_cursor(b);
  output_color("ù");
    
  // draw paddles Û
  for (i = 0; i < psize; i++)
  {
    set_cursor( Location( p1 + i, 2 ));
    output_color("Û");
  }
  for (i = 0; i < psize; i++)
  {
    set_cursor( Location( p2 + i, 59 ));
    output_color("Û");
  }
  
  while (!done)
  {
    // draw ball ù
    set_cursor(b);
    output_color("ù");
    
    // wait for next frame
    wait( wait_time );

    // erase ball ù
    set_cursor(b);
    if (b.col == 29)
      output_color("$w°$W");
    else
      output_color(" ");
    
    // check for input and move paddles if necessary
    while (kbhit()) // input char waiting
    {
      // erase paddles Û
      for (i = 0; i < psize; i++)
      {
        set_cursor( Location( p1 + i, 2 ));
        output_color(" ");
      }
      for (i = 0; i < psize; i++)
      {
        set_cursor( Location( p2 + i, 59 ));
        output_color(" ");
      }
      
      int temp = getch();
      switch( temp )
      {
        case('e'): case('E'): if (p1 > upperb)               p1--; break;
        case('c'): case('C'): if (p1 < lowerb - (psize - 1)) p1++; break;
        case('o'): case('O'): if (p2 > upperb)               p2--; break;
        case('m'): case('M'): if (p2 < lowerb - (psize - 1)) p2++; break;
        default: done = true;
      }
      
      // draw paddles Û
      for (i = 0; i < psize; i++)
      {
        set_cursor( Location( p1 + i, 2 ));
        output_color("Û");
      }
      for (i = 0; i < psize; i++)
      {
        set_cursor( Location( p2 + i, 59 ));
        output_color("Û");
      }
    }
    
    // move ball
    b = b + bv;
    
    // check for hitting top or bottom wall
    if (b.row < upperb)
    {
      bv.row = 1;
      b.row += 2;
    }
    if (b.row > lowerb)
    {
      bv.row = -1;
      b.row += -2;
    }
    
    // check for hitting a paddle
    if (b.col == 2)
    for (i = 0; i < psize; i++)
    if (b.row == p1 + i)
    {
      bv.col = 1;
      b.col += 2;
    }
    if (b.col == 59)
    for (i = 0; i < psize; i++)
    if (b.row == p2 + i)
    {
      bv.col = -1;
      b.col += -2;
    }
    
    // check for point (left or right wall); if point, respawn ball
    static bool scored;
    scored = false;
    if (b.col == 0)
    {
      sc2++;
      b = ball_init;
      bv.set( (random(0,1)?-1:1), -1 );
      scored = true;
    }
    if (b.col == 61)
    {
      sc1++;
      b = ball_init;
      bv.set( (random(0,1)?-1:1),  1 );
      scored = true;
    }
    if (scored)
    {
      scored = false;
      // draw scores
      set_cursor(sc1P);
      output_color(string( (sc1>sc2)?"$R":"$w" ) + to_string(sc1,sw,'R'));
      set_cursor(sc2P);
      output_color(string( (sc2>sc1)?"$B":"$w" ) + to_string(sc2,sw,'L'));
      output_color("$w");
      // up the speed
      wait_time -= delta_wait;
      if (wait_time < wait_min)
        wait_time = wait_min;
    }
    if (sc1 == win)
    {
      string g1[8] =
      {
        "  $rÛÛÜ  Û     ",
        "  Û Û ßÛ     ",
        "  ÛÛß  Û     ",
        "  Û   ÜÛÜ    ",
        "$w            Ü",
        "Û Ü Û Û ÛÜ  Û",
        "Û Û Û Û ÛßÛ ß",
        "ßÛßÛß Û Û Û Û"
      };      
      Location cursor( 6, 6 );
      for (int j = 0; j < 8; j++)
      {
        set_cursor(cursor);
        output_color( g1[j] );
        cursor.row++;
      }      
      // wait for next frame
      wait( 2.5 );
      done = true;
    }
    if (sc2 == win)
    {
      string g2[8] =
      {
        "  $bÛÛÜ ÜÛÛÜ   ",
        "  Û Û ß ÜÛ   ",
        "  ÛÛß ÜÛß    ",
        "  Û   ÛÜÜÛ   ",
        "$w            Ü",
        "Û Ü Û Û ÛÜ  Û",
        "Û Û Û Û ÛßÛ ß",
        "ßÛßÛß Û Û Û Û"
      };      
      Location cursor( 6, 41 );
      for (int j = 0; j < 8; j++)
      {
        set_cursor(cursor);
        output_color( g2[j] );
        cursor.row++;
      }
      // wait for next frame
      wait( 2.5 );
      done = true;
    }
  }
  system("cls");
  output_color("$w");
}

//------------------------------------------------------------------------------

void virus()
{
  timer t; t.restart();
  output_color("%k$R"); // setting up the CANVAS
  while (t.elapsed_time() < 3.0)
  {
    static int H = 24, W = 75;
    set_cursor( Location(random(0,H),random(0,W)) );
    cout << ( (random(0,1))?(""):("") ); // smilies!
  }
  while (t.elapsed_time() < 6.0)
  {
    static string virus[24] =
    {
      "                        ",
      "  ÛÛ                ÛÛ  ",
      " ÛÛÛÛ              ÛÛÛÛ ",
      " ÛÛÛÛ   ÛÛÛÛÛÛÛ    ÛÛÛÛ ",
      "  ÛÛÛÛ ÛÛÛÛÛÛÛÛÛÛ ÛÛÛÛ  ",
      "    ÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛ    ",
      "     ÛÛÛÛÛÛÛÛÛÛÛÛÛÛ     ",
      "    ÛÛ  ÛÛÛÛÛÛÛÛ  ÛÛ    ",
      "   ÛÛ      ÛÛ      ÛÛ   ",
      "   ÛÛ     ÛÛÛÛ     ÛÛ   ",
      "   ÛÛ    ÛÛÛÛÛÛ    ÛÛ   ",
      "   ÛÛ    ÛÛ  ÛÛ    ÛÛ   ",
      "   ÛÛ   ÛÛÛ  ÛÛÛ   ÛÛ   ",
      "   ÛÛÛÛÛÛÛ    ÛÛÛÛÛÛÛ   ",
      "    ÛÛÛÛÛÛ    ÛÛÛÛÛÛ    ",
      "     ÛÛÛÛÛ ÛÛ ÛÛÛÛÛ     ",
      "    ÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛ    ",
      "  ÛÛÛÛ ÛÛÛÛÛÛÛÛÛÛ ÛÛÛÛ  ",
      " ÛÛÛÛ  ÛÛÛÛÛÛÛÛÛÛ  ÛÛÛÛ ",
      " ÛÛÛÛ  ÛÛ  ÛÛ  ÛÛ  ÛÛÛÛ ",
      "  ÛÛ   ÛÛ  ÛÛ  ÛÛ   ÛÛ  ",
      "       Û   ÛÛ  ÛÛ       ",
      "           ÛÛ  Û        ",
      "                        "
    };
    static int row, col;
    row = random(0,23); col = random(0,23);
    if ( virus[row][col] == 'Û')
      output_color("%k$k"); // drawing the SKULL
    else // virus[row][col] == ' '
      output_color("%k$R"); // drawing area AROUND it
    
    set_cursor( Location(row,col+25) );
    output_color( ( random(0,1) )? ("") : ("") ); // smilies!
    
    output_color("%k$R"); // drawing area AROUND it
    if (random(0,1))
      set_cursor( Location(random(0,23), random(0,23) ) );
    else
      set_cursor( Location(random(0,23), random(51,74) ) );
    output_color( ( random(0,1) )? ("") : ("") ); // smilies!
  }
  t.stop();
  output_color("%k$w");
  // hahahaha that was fun :D
  
  system("cls");
  set_cursor(Location(0,0));
}

//------------------------------------------------------------------------------

void meteor( Location impact, Location maxBR )
{
  // if undisplayable
  Location maxTL( 0, 0 );
  if ( ( maxBR.row <= maxTL.row     || maxBR.col <= maxTL.col ) ||
       ( impact.row < maxTL.row - 7 || impact.row > maxBR.row + 7 ) ||
       ( impact.col < maxTL.col - 7 || impact.col > maxBR.col + 7 ) )
    return;  
  
  double frame[10] = { 0.05, 0.05, 0.05, 0.05, 0.05, 0.1, 0.1, 0.1, 0.05, 0.05 };
  string rock [10][15] =
  {
    {
      "               ",
      "               ",
      "               ",
      "               ",
      "               ",
      "               ",
      "               ",
      "       °       ",
      "               ",
      "               ",
      "               ",
      "               ",
      "               ",
      "               ",
      "               "
    },
    {
      "               ",
      "               ",
      "               ",
      "               ",
      "               ",
      "               ",
      "       °       ",
      "      °±°      ",
      "       °       ",
      "               ",
      "               ",
      "               ",
      "               ",
      "               ",
      "               "
    },
    {
      "               ",
      "               ",
      "               ",
      "               ",
      "               ",
      "      °°°      ",
      "     °°±°°     ",
      "     °±²±°     ",
      "     °°±°°     ",
      "      °°°      ",
      "               ",
      "               ",
      "               ",
      "               ",
      "               "
    },
    {
      "               ",
      "               ",
      "               ",
      "               ",
      "      °°°      ",
      "     °°±°°     ",
      "    °°±²±°°    ",
      "    °±²²²±°    ",
      "    °°±²±°°    ",
      "     °°±°°     ",
      "      °°°      ",
      "               ",
      "               ",
      "               ",
      "               "
    },
    {
      "               ",
      "               ",
      "      °°°      ",
      "    °°°°°°°    ",
      "   °°°±±±°°°   ",
      "   °°±²²²±°°   ",
      "  °°±²ùÜù²±°°  ",
      "  °°±²ŞÛİ²±°°  ",
      "  °°±²ùßù²±°°  ",
      "   °°±²²²±°°   ",
      "   °°°±±±°°°   ",
      "    °°°°°°°    ",
      "      °°°      ",
      "               ",
      "               "
    },
    {
      "     °°°°°     ",
      "   °°±±±±±°°   ",
      "  °±±±±±±±±±°  ",
      " °±±±²²²²²±±±° ",
      " °±±²²ùùù²²±±° ",
      "°±±²²ùÜÜÜù²²±±°",
      "°±±²ùŞÛÛÛİù²±±°",
      "°±±²ùŞÛÛÛİù²±±°",
      "°±±²ùŞÛÛÛİù²±±°",
      "°±±²²ùßßßù²²±±°",
      " °±±²²ùùù²²±±° ",
      " °±±±²²²²²±±±° ",
      "  °±±±±±±±±±°  ",
      "   °°±±±±±°°   ",
      "     °°°°°     "
    },
    {
      "     XXXXX     ",
      "   XX°°°°°XX   ",
      "  X°°°°°°°°°X  ",
      " X°°°±±±±±°°°X ",
      " X°°±±ùùù±±°°X ",
      "X°°±±ùÜÜÜù±±°°X",
      "X°°±ùŞÛÛÛİù±°°X",
      "X°°±ùŞÛÛÛİù±°°X",
      "X°°±ùŞÛÛÛİù±°°X",
      "X°°±±ùßßßù±±°°X",
      " X°°±±ùùù±±°°X ",
      " X°°°±±±±±°°°X ",
      "  X°°°°°°°°°X  ",
      "   XX°°°°°XX   ",
      "     XXXXX     "
    },
    {
      "               ",
      "     XXXXX     ",
      "   XXXXXXXXX   ",
      "  XXX°°°°°XXX  ",
      "  XX°°ùùù°°XX  ",
      " XX°°ùÜÜÜù°°XX ",
      " XX°ùŞÛÛÛİù°XX ",
      " XX°ùŞÛÛÛİù°XX ",
      " XX°ùŞÛÛÛİù°XX ",
      " XX°°ùßßßù°°XX ",
      "  XX°°ùùù°°XX  ",
      "  XXX°°°°°XXX  ",
      "   XXXXXXXXX   ",
      "     XXXXX     ",
      "               "
    },
    {
      "               ",
      "               ",
      "               ",
      "     XXXXX     ",
      "    XXùùùXX    ",
      "   XXùÜÜÜùXX   ",
      "   XùŞÛÛÛİùX   ",
      "   XùŞÛÛÛİùX   ",
      "   XùŞÛÛÛİùX   ",
      "   XXùßßßùXX   ",
      "    XXùùùXX    ",
      "     XXXXX     ",
      "               ",
      "               ",
      "               "
    },
    {
      "               ",
      "               ",
      "               ",
      "               ",
      "      XXX      ",
      "     XÜÜÜX     ",
      "    XŞÛÛÛİX    ",
      "    XŞÛÛÛİX    ",
      "    XŞÛÛÛİX    ",
      "     XßßßX     ",
      "      XXX      ",
      "               ",
      "               ",
      "               ",
      "               "
    }
  };
  
  hide_cursor();
  cout << '\7'; // audible bell
  for (int rock_index = 0; rock_index < 10; rock_index++)
  {  
    Location cursor = impact;
    Location rock_ptr( 7, 7 );
    int dr, dc;
    int length = 0;
    
    // draw center
    meteor_sub( rock, rock_index, cursor, rock_ptr, maxBR );
    
    while ( (rock_ptr.row >= 0 && rock_ptr.row < 15) &&
            (rock_ptr.col >= 0 && rock_ptr.col < 15) )
    {
      length++;
      // down
      for (dr = 0; dr < length; dr++)
      {
        cursor.row++; rock_ptr.row++;
        meteor_sub( rock, rock_index, cursor, rock_ptr, maxBR );
      }
      
      if (rock_ptr.row == 15 || rock_ptr.col == 15)
        break;
      
      // right
      for (dc = 0; dc < length; dc++)
      {
        cursor.col++; rock_ptr.col++;
        meteor_sub( rock, rock_index, cursor, rock_ptr, maxBR );
      }
      
      length++;
      // up
      for (dr = 0; dr < length; dr++)
      {
        cursor.row--; rock_ptr.row--;
        meteor_sub( rock, rock_index, cursor, rock_ptr, maxBR );
      }
      // left
      for (dc = 0; dc < length; dc++)
      {
        cursor.col--; rock_ptr.col--;
        meteor_sub( rock, rock_index, cursor, rock_ptr, maxBR );
      }
    }
    
    // wait
    wait( frame[rock_index] );
  }
  output_color("%k$w");
  set_cursor( Location( maxBR.row + 1, 0 ));
  show_cursor();
}

void meteor_sub( string rock[10][15], int& rock_index, Location& cursor, Location& rock_ptr, Location& maxBR )
{
  // if in_bounds
  if ( (cursor.row > 0 && cursor.row < maxBR.row) &&
       (cursor.col > 0 && cursor.col < maxBR.col) )
  {
    set_cursor( cursor );
    static string token = "";
    switch( rock[rock_index][rock_ptr.row][rock_ptr.col] )
    {
      case(' '): token = "%k$w";      break;
      case('°'): token = "%k$w°"; break;
      case('±'): token = "%k$w±"; break;
      case('²'): token = "%k$w²"; break;
      case('ù'): token = "%Y$R ";   break;
      case('Û'): token = "%Y$RÛ";   break;
      case('Ü'): token = "%Y$RÜ"; break;
      case('İ'): token = "%Y$Rİ"; break;
      case('ß'): token = "%Y$Rß"; break;
      case('Ş'): token = "%Y$RŞ"; break;
      case('X'): token = "%k$w ";   break;
    }
    output_color( token );
  }
}

// end of file
