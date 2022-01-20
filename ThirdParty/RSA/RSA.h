#ifndef __RSA_h__
#define __RSA_h__

#include <iostream>
#include <string>
#include <cmath>
#include <stdexcept>

using Uint = long unsigned int;

class RSA
{
  Uint p;
  Uint q;

  bool is_prime (const Uint & n);

public:

  Uint n;
  Uint phi;
  Uint e;
  Uint d;

  RSA ();
  RSA (const Uint & p, const Uint & q);

  ~RSA () = default;

  // members

private:

  void compute_public_key (const Uint & phi);
  void compute_private_key (const Uint & phi, const Uint & e);
};

#endif // __RSA_h__
