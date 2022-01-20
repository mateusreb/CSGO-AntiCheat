#include "Decrypter.h"

Decrypter :: Decrypter () : n (0), d (0)
{
}

Decrypter :: Decrypter (const Uint & n, const Uint & d) : n (n), d (d)
{
}

std :: string Decrypter :: decrypt (const std :: vector < Uint > & enc)
{
  Uint k;
  Uint c;

  std :: string msg;

  for (const auto & l : enc)
  {
    k = static_cast < Uint >(1);
    c = static_cast < Uint >(l);

    for (Uint j = 0; j < this->d; ++j)
      k = (k * c) % this->n;

    msg.push_back(static_cast < char >(k));
  }

  return msg;
}