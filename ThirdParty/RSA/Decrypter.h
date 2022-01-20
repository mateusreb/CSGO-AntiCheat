#ifndef __decrypter_h__
#define __decrypter_h__

#include <vector>
#include <string>

using Uint = long unsigned int;

class Decrypter
{
  Uint n;
  Uint d;

public:

  Decrypter ();
  Decrypter (const Uint & n, const Uint & d);
  ~Decrypter () = default;

  // members

  std :: string decrypt (const std :: vector < Uint > & enc);
};

#endif // __decrypter_h__
