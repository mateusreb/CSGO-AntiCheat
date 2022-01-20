#ifndef __encrypter_h__
#define __encrypter_h__

#include <vector>
#include <string>

using Uint = long unsigned int;

class Encrypter
{
  Uint n;
  Uint e;

public:

  Encrypter ();
  Encrypter (const Uint & n, const Uint & e);
  ~Encrypter () = default;

  // members

  std :: vector < Uint > encrypt (const std :: string & enc);
};

#endif // __encrypter_h__
