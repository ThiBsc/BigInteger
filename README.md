# BigInteger
BigInteger C++ implementation. [![Build Status](https://travis-ci.org/thibDev/BigInteger.svg?branch=master)](https://travis-ci.org/thibDev/BigInteger) [![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT)

- [BigInteger](#biginteger)
    - [Features](#features)
        - [Radix](#radix)
        - [Arithmetic](#arithmetic)
        - [Modification & Checking/Operator](#modification--checkingoperator)
    - [Code sample](#code-sample)
    - [Compile & Test](#compile--test)
    - [Support development :+1:](#support-development-1)

## Features
### Radix

- [ ] 2
- [x] 10
- [ ] 16

### Arithmetic

- [x] add
- [x] substract
- [x] multiply
- [ ] divide
- [ ] pow
- [ ] modulus

### Modification & Checking/Operator

- [x] compare
- [x] negate
- [x] swap
- [ ] operator+, operator-, operator*, operator/
- [ ] operator+=, operator-=, operator*=, operator/=
- [x] operator<, operator>, operator<=, operator>=
- [x] operator<<

## Code sample

```cpp
BigInteger a("12"), b("13");
// Use with cout to print result
a.add(b); // 25
a.substract(b); // -1
a.multiply(b); // 156
(a<b); // True
(a>b); // False
(a==b); // False
```

## Compile & Test

```shell
make bint
./build/bint
```

## Support development :+1:

- Star the project :star:
- Help to implement features
