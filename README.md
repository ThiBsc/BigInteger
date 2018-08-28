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

From 2 to 16

### Arithmetic

- [x] add
- [x] substract
- [x] multiply
- [ ] divide
- [x] pow
- [ ] modulus

### Modification & Checking/Operator

- [x] compare
- [x] negate
- [x] swap
- [x] operator--, ++ (post, pre)
- [ ] operator+, operator-, operator*, operator/
- [ ] operator+=, operator-=, operator*=, operator/=
- [x] operator<, operator>, operator<=, operator>=
- [x] operator<<

## Code sample

```cpp
BigInteger bin("1011", 2); // 11
BigInteger oct("13", 8); // 11
BigInteger dec("255", 10); // 255
BigInteger hex("ff", 16); // 255
// Use with cout to print result
bin.add(oct); // 22
dec.substract(hex); // 0
bin.multiply(hex); // 2805
dec.pow(BigInteger::TEN); // 1 162 523 670 191 533 212 890 625
BigInteger("2").substract("-3"); // (2)-(-3) = 2+3 = 5
```

## Compile & Test

```shell
make bint
./build/bint
```

## Support development :+1:

- Star the project :star:
- Help to implement features
