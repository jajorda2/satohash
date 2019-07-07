# satohash
Satohash - cryptographic key derivation function
THIS IS AN UPDATED VERSION (THAT ACTUALLY WORKS) OF movedon2otherthings REPO
This version includes an updated hash.h header file that has matching declarations for all definitions.


The function takes 256bit input (for example a password) and returns a 256bit output (for example a bitcoin private key)

This function can be used as a key derivation function. You only remember the password to your funds.

Another purpose the function can be used for hashing, like when combined with sha256 or any other function like this satohash(sha256(input file))

Code:
$ sha256sum hash.h | ./run
d590e41a6cb9ea0b1952565d29c40d3e09fe3c0d07acf42c089b9c009775d71d

The function also can be mined to create proof of work like bitcoin. But must be again chained with arbitrary input hash function like sha256

There is also a command line code that hashes stdin or the first argument

Examples:

empty input (all zeros)

Code:
$ ./run 0000000000000000000000000000000000000000000000000000000000000000
fe077f0af592477a82d8eb871615add4a53a489402dd9b5a09c4565c66db0814

$ echo -n "" | ./run 
fe077f0af592477a82d8eb871615add4a53a489402dd9b5a09c4565c66db0814
$ ./run ""
fe077f0af592477a82d8eb871615add4a53a489402dd9b5a09c4565c66db0814

hello world
Code:
$ ./run satohash
db63fef9f4805eac731877f36f653635865b0a2700aae8cf6af40cb12801ada2

Demonstrate the avalanche effect, changing one letter changes whole output

Code:
$ ./run Satohash
2b4f3c56fd7f93d8d2730cc79f6e0f492dcff1e4784cef58f4a1b24554b11b06
