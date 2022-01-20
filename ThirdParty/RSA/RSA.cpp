#include "RSA.h"

RSA :: RSA () : p (0), q (0), n (0), phi (0), e (0), d (0)
{
}

RSA :: RSA (const Uint & p, const Uint & q)
{
  this->p = p;
  this->q = q;

  if ( !this->is_prime (p) )
  {
    std :: cerr << "p is not prime. Please insert a prime number" << std :: endl;
    std :: exit(1);
  }

  if ( !this->is_prime (q) )
  {
    std :: cerr << "q is not prime. Please insert a prime number" << std :: endl;
    std :: exit(1);
  }

  this->n = this->p * this->q;

  if ( n < 255 )
    throw std :: runtime_error("n = " + std :: to_string(n) + " is too small to support full ASCII table");

  this->phi = (this->p - 1) * (this->q - 1);

  this->compute_public_key (this->phi);
  this->compute_private_key (this->phi, this->e);
}



bool RSA :: is_prime (const Uint & n)
{
  Uint j = static_cast < Uint >(std :: sqrt(n));

  for (Uint i = 2; i <= j; ++i)
    if (n % i == 0) return false;

  return true;
}

void RSA :: compute_public_key (const Uint & phi)
{
  Uint i = 2;

  while (true)
  {
    if (phi % i == 0)
    {
      ++i;
      continue;
    }
    if (this->is_prime (i))
    {
      this->e = i;
      break;
    }
    ++i;
  }
}

void RSA :: compute_private_key (const Uint & phi, const Uint & e)
{
  Uint k = 1;

  while (true)
  {
    k += phi;
    if (k % e == 0)
    {
      this->d = k / e;
      break;
    }
  }
}
