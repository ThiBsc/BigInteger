# BigInteger
[![Build Status](https://travis-ci.org/thibDev/BigInteger.svg?branch=master)](https://travis-ci.org/thibDev/BigInteger) [![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT)  
BigInteger C++ implementation.

## Features
### Radix

From 2 to 16
```cpp
BigInteger bin("1011", 2);  // 11
BigInteger ter("121", 3);   // 16
BigInteger oct("13", 8);    // 11
BigInteger dec("255", 10);  // 255
BigInteger hex("ff", 16);   // 255
```

### Arithmetic

```cpp
BigInteger a(127), b(273), c(-597);
a.add(b);               // 400
a.add(c);               // -470
a.substract(b);         // -146
a.substract(c);         // 724
a.multiply(b);          // 34671
a.multiply(c);          // -75819
b.divide(c);            // 2
c.divide(a);            // -4
a.pow(BigInteger(12));  // 17605349516220764271966721
b.modulus(a);           // 19
```

### Modification & Checking/Operator

```cpp
BigInteger a(127), b(127), c(-597);
c.compare(a);           // -1
a.compare(b);           // 0
a.compare(c);           // 1
a.negate();             // -127
c.absolute();           // 597
a.swap(c);              // a=-597, c=127
(BigInteger::ONE << 8); // 256
```
#### Operator

- operator--, operator++ (prefix, postfix)
- operator+, operator-, operator*, operator/, operator%
- operator+=, operator-=, operator*=, operator/=
- operator==, operator!=, operator<, operator>, operator<=, operator>=
- operator<<

## Code sample

```cpp
#include <iostream>
#include <cassert>
#include "header/biginteger.h"

using namespace std;

int main(int argc, char const *argv[])
{
    BigInteger hex("aef8", 16), power(12);
    cout << hex << " ^ " << power << " = " << hex.pow(power) << endl;

    BigInteger payload("9444732987799592368290"), modulo = 31;
    while (!(payload == BigInteger::ZERO)) {
        BigInteger mod = payload.modulus(modulo);
        payload = payload.divide(modulo);
        cout << mod << " ";
    }
    cout << endl;
    assert(hex.pow(power) == BigInteger("65223703316636040602169485327930322370641440178266177536"));

    return 0;
}
```

## Compile & Test

```shell
make bint
./build/bint
```

## Support development :+1:

- Star the project :star:
- Help to implement features
