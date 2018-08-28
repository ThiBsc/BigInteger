#include <iostream>
#include <cassert>
#include "header/biginteger.h"

using namespace std;

int main(int argc, char const *argv[])
{
    // Samples
    BigInteger bin("1011", 2); // 11
    BigInteger oct("13", 8); // 11
    BigInteger dec("255", 10); // 255
    BigInteger hex("ff", 16); // 255

    cout << bin << endl;
    cout << oct << endl;
    cout << dec << endl;
    cout << hex << endl;
    
    // Check
    assert(bin.add(oct) == BigInteger("22"));
    assert(dec.substract(hex) == BigInteger::ZERO);
    assert(bin.multiply(hex) == BigInteger("2805"));
    assert(dec.pow(BigInteger::TEN) == BigInteger("1162523670191533212890625"));

    return 0;
}
