// Tyler Cole
// EVO Project Module Implementation
// settings.cpp

#include "settings.h"
using namespace std;

string read_ini()
{
  ifstream ini;
  bool file_is_hot = false;
  
  ini.open( "evo.ini" );
  if (!ini)
  {
    output_color( "$yWarning$w: file [$Wevo.ini$w] not found.\n" );
    ini.close(); ini.clear();
    file_is_hot = true;
    write_ini( "defaults" );
    ini.open( "evo.ini" );
  }
  
  while (ini.peek() == ';')
  { // while caret is positioned at a comment character,
    // throw away characters until newline
    ini.ignore( 1024, '\n' );
  }
  
  string filename;
  ini >> filename;
  
  if (filename == "defaults")
  {
    if (!file_is_hot)
      output_color("$yWarning$w: file [$Wevo.ini$w] did not specify a settings file.\n");
    // ask if they'd like to specify a settings file to use in the future
    output_color("Do you have a settings file you'd like to use? ($WY$w/$WN$w) ");
    
    string line;
    vector<string> token;
    
    getline(cin, line);
    line = to_upper(line);
    token = tokenize( line );
    
    if (token[0][0] == 'Y')
    { // user typed a line where the first token begins with Y; assume YES
      // so get the filename
      output_color("What's the name of the file? (must end in '$W.dat$w') ");

      getline(cin, line);
      line = to_lower( line );
      token = tokenize( line );
      filename = token[0];
      
      // validate extension
      if (!file_extension( filename, "dat" ))
      {
        output_color( string("$RError$w: file [$W") + filename + string("$w] is not a '$W.dat$w' file.\n") );
        return "defaults";
      }
      // validate filename
      else if (!file_exist( filename ))
      {
        output_color( string("$RError$w: file [$W") + filename + string("$w] not found.\n") );
        return "defaults";
      }
      else
      {
        init_settings_external( filename );
        return filename;
      }      
    }
    else
    { // user typed something else; assume NO
      init_settings_defaults();
      return "defaults";
    }
  }
  else
  {
    if ( init_settings_external( filename ))
      return filename;
    else
      return "defaults";
  }
}

//------------------------------------------------------------------------------

bool init_settings_external( string filename )
{
  // validate extension
  if (!file_extension( filename, "dat" ))
  {
    output_color( string("$RError$w: file [$W") + filename + string("$w] is not a '$W.dat$w' file.\n") );
    init_settings_defaults();
    return false;
  }
  // validate existence
  else if (!file_exist( filename ))
  {
    output_color( string("$RError$w: file [$W") + filename + string("$w] not found.\n") );
    init_settings_defaults();
    return false;
  }
  
  ifstream data;
  data.open( filename.c_str() );

  // found the file, reading in external settings
  string k; int v; int vars_read = 0;
  while (data)
  {
    while (data.peek() == ';')
    { // while caret is positioned at a comment character,
      // throw away characters until newline
      data.ignore( 1024, '\n' );
    }
    
    if (data.peek() == EOF)
    { // if end of file reached
      if (vars_read < COUNT_GLOBALS)
      { // not enough data found in [settings.dat]
        output_color( string("$RError$w: file [$W") + filename + string("$w] did not contain enough registered values.\n") );
        init_settings_defaults();
        data.close();
        return false;
      }
      else if ( /*total size*/(global("WORLDMAP_HEIGHT") * global("WORLDMAP_WIDTH")) - /*outer walls*/((2 * global("WORLDMAP_HEIGHT")) + (2 * global("WORLDMAP_WIDTH")) - 4) <= /*total population*/(global("PLANT_POPULATION") + global("HERBIVORE_POPULATION") + global("CARNIVORE_POPULATION")) )
      { // world map is not big enough to support given populations
        output_color( string("$RError$w: file [$W") + filename + string("$w] did not provide an adequately sized worldmap.\n") );
        init_settings_defaults();
        data.close();
        return false;
      }
      else
      { // found enough data
        output_color( string("$WSuccessfully$w read in settings from file [$W") + filename + string("$w]\n") );
        data.close();
        return true;
      }
    }
    
    // then, read in a key/value pair and check its validity
    data >> k >> v;
    switch( set_global( k, v ) )
    {
      case( 1 ): vars_read++; break;
      case( 2 ): output_color( string("$yWarning$w: attempt to set key [$W") + k + string("$w] out of bounds rejected.\n") ); break;
      case( 3 ): output_color( string("$RError$w: key [$W") + k + string("$w] is not a registered volatile global variable.\n") ); break;
    }

    // eat any trailing whitespace in preparation for peek()
    while (isspace( data.peek() ))
    { // while caret is positioned at any of the following characters:
      // space, horiz. tab, vert. tab, formfeed, carriage return, newline
      // throw that single character away
      data.get();
    }
  }
  
  return false;
}

//------------------------------------------------------------------------------

void init_settings_defaults()
{
  output_color( "Using $Wdefault$w settings.\n" );// internal default settings assigned
  int i;
  for (i = 0; i < COUNT_GLOBALS; i++)
  {
    set_global( key[i][0], global_default( key[i][0] ));
  }
}

//------------------------------------------------------------------------------

void write_settings( string filename )
{
  if (filename == "defaults")
  {
    output_color("Would you like to export default settings? ($WY$w/$WN$w) ");
    
    string line;
    vector<string> token;

    while(1)
    {
      getline(cin, line);
      line = to_upper(line);
      token = tokenize( line );
      
      if (token[0][0] == 'Y')
      {
        output_color("Name the file. (must end in '$W.dat$w') ");

        getline(cin, line);
        line = to_lower( line );
        token = tokenize( line );
        
        // validate extension
        if (!file_extension( token[0], "dat" ))
        {
          output_color( string("$RError$w: file [$W") + token[0] + string("$w] is not a '$W.dat$w' file.\n") );
          continue;
        }
        else
        {
          filename = token[0];
          break;
        }
      }
      else
      {
        return;
      }
    }
  }
  
  ofstream data;
  data.open( filename.c_str() );
  if (!data) // if the file couldn't be opened for writing
  {
    output_color( string("$yWarning$w: file [$W") + filename + string("$w] could not be written to.\n") );
    data.close();
    return;
  }
  
  // header
  data << "; Tyler Cole" << endl;
  data << "; EVO Project Settings" << endl;
  data << "; " << filename << endl;
  data << endl;
  
  // individual name, value, and description
  int i;
  for (i = 0; i < COUNT_GLOBALS; i++)
  {
    
    data.width(25);
    data << right;
    data << key[i][0];
    
    data << " ";
    data.width(8);
    data << left;
    data << value[i][0] << " ";
    
    data << key[i][1] << "\n";
  }
  
  data.close();  
  output_color( string("$WSuccessfully$w wrote current settings to file [$W") + filename + string("$w].\n") );
  
  write_ini( filename );
}

//------------------------------------------------------------------------------

void write_ini( string filename )
{
  ofstream ini;
  ini.open( "evo.ini" );
  if (!ini)
  {
    output_color( "$yWarning$w: file [$Wevo.ini$w] could not be written to.\n" );
    ini.close();
    return;
  }
  
  ini << "; Tyler Cole" << endl;
  ini << "; EVO Project Initialization File" << endl;
  ini << "; evo.ini" << endl << endl;
  ini << filename;
  ini.close();
  
  if (filename == "defaults")
  {
    output_color("$WNotice$w: wrote a default [$Wevo.ini$w] file to disk.\n");
  }
  else
  {
    output_color("Wrote that filename to [$Wevo.ini$w].\n");
  }
}

//------------------------------------------------------------------------------

string global_name( int i )
{
  return key[i][0];
}

//------------------------------------------------------------------------------

string global_desc( int i )
{
  return key[i][1];
}

//------------------------------------------------------------------------------

int global( string k )
{
  int i;
  for (i = 0; i < COUNT_GLOBALS; i++)
  {
    if ( k == key[i][0] )
    {
      return value[i][0]; // return the volatile value
    }
  }
  return -1;
}

//------------------------------------------------------------------------------

int global_default( string k )
{
  int i;
  for (i = 0; i < COUNT_GLOBALS; i++)
  {
    if ( k == key[i][0] )
    {
      return value[i][3]; // return the default value
    }
  }
  return -1;
}

//------------------------------------------------------------------------------

int set_global( string k, int v )
{
  int i;
  for (i = 0; i < COUNT_GLOBALS; i++)
  {
    if ( k == key[i][0] )
    {
      // bounds checking
      if ( v >= value[i][1] && v <= value[i][2] )
      {
        value[i][0] = v; // set the volatile value
        return 1; // success
      }
      else
      {
        return 2; // failed bounds check
      }
    }
  }
  return 3; // failed; did not find key
}

// end of file
