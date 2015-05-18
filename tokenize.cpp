// Tyler Cole
// EVO Project Module Implementation
// tokenize.cpp

#include "tokenize.h"
using namespace std;

vector<string> tokenize( string s )
{
  // tokenize input
  // capitalize input if flag_caps == true
  
  vector<string> token;
  token.push_back("");
  if (s.empty())
    return token;
  
  unsigned int i, t;  
  bool in_token = false;
  
  if ( !isspace(s[0]) )
  {
    in_token = true;
  }  
  for (i = 0, t = 0; i < s.size(); i++)
  {
    if ( in_token )
    { 
      if ( isspace(s[i]))
        in_token = false;
      else
        token[t] += s[i];
    }
    else if ( !isspace(s[i])) 
    {
      in_token = true;
      token.push_back("");
      token[++t] += s[i];
    }
  }

  return token;
}

// end of file
