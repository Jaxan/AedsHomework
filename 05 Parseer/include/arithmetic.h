// Nick Overdijk	3029832
// Joshua Moerman	3009408

#ifndef ARITHMETIC_H
#define ARITHMETIC_H

/**
 
 Abstractie, het special getal 0 en 1 voor willekeurig type (gebruiken we in logic.h voor algemene logica)
 
 */

namespace JN{

template <typename T>
T one() { static_assert(sizeof(T)==0, "You didn't specialise your own one value"); }

template <typename T>
T zero() { static_assert(sizeof(T)==0, "You didn't specialise your own zero value"); }


template <>
bool one<bool>() { return true; }
template <>
bool zero<bool>() { return false; }

}

#endif // ARITHMETIC_H
