#include <iostream>
#include <cassert>
#include "header/biginteger.h"

using namespace std;

int main(int argc, char const *argv[])
{
    // Samples
    BigInteger bin("1011", 2);  // 11
    BigInteger oct("13", 8);    // 11
    BigInteger dec("255", 10);  // 255
    BigInteger hex("ff", 16);   // 255
    BigInteger num("123456789");

    cout << "1011 bin -> " << bin << endl;
    cout << "13 oct -> " << oct << endl;
    cout << "255 dec -> " << dec << endl;
    cout << "ff hex -> " << hex << endl;

    cout << "123456789" << " in [bin, ter, oct, dec, hex, b32]" << endl;
    cout << num.toString(2) << endl;
    cout << num.toString(3) << endl;
    cout << num.toString(8) << endl;
    cout << num.toString() << endl;
    cout << num.toString(16) << endl;
    cout << num.toString(32) << endl;
    
    // Check
    assert(bin.add(oct) == BigInteger("22"));
    assert(dec.substract(hex) == BigInteger::ZERO);
    assert(bin.multiply(hex) == BigInteger("2805"));
    assert(dec.pow(BigInteger::TEN) == BigInteger("1162523670191533212890625"));
    assert(hex.divide(oct) == BigInteger("23"));
    assert(hex.modulus(oct) == BigInteger("2"));
    assert(BigInteger(1024).toString(8) == "2000");

    return 0;
}
