# satohash
Satohash - cryptographic key derivation function
THIS IS AN UPDATED VERSION (THAT ACTUALLY WORKS) OF movedon2otherthings REPO


This version includes an updated hash.h header file that has matching declarations for all definitions.


# build

Tested on Ubuntu 16.04

1. clone the repo

2. cd to repo

3. gcc satohash.c hash.h -o run

4. *NOTE* on step three, just name the output anything you want. I chose "run" as you can see in instructions.

# usage

The function takes 256bit input (for example a password) and returns a 256bit output (for example a bitcoin private key)

This function can be used as a key derivation function. You only remember the password to your funds.

Another purpose the function can be used for hashing, like when combined with sha256 or any other function like this satohash(sha256(input file))

Code:
$ sha256sum hash.h | ./run
d590e41a6cb9ea0b1952565d29c40d3e09fe3c0d07acf42c089b9c009775d71d

The function also can be mined to create proof of work like bitcoin. But must be again chained with arbitrary input hash function like sha256

There is also a command line code that hashes stdin or the first argument

# Examples:

*empty input (all zeros)

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

*Demonstrate the avalanche effect, changing one letter changes whole output

Code:
$ ./run Satohash
2b4f3c56fd7f93d8d2730cc79f6e0f492dcff1e4784cef58f4a1b24554b11b06

# so how do i turn turn the sha256 result into a bitcoin private key????????

Here is an example:

1.) Take a private key (Below is the HEX representation of binary value--this is the sha256 hash returned from satohash)

f3bc5e754c621ed5f7a77566cd5ec425a395bedfefe5ef342412cb6ce7e51505

2.) Add a 0x80 byte in front of it

80f3bc5e754c621ed5f7a77566cd5ec425a395bedfefe5ef342412cb6ce7e51505

3.) Perform SHA-256 hash on the extended key

echo -n '80f3bc5e754c621ed5f7a77566cd5ec425a395bedfefe5ef342412cb6ce7e51505' | xxd -r -p | sha256sum -b

76d79e77bcf6e323cfa2fd256e51378734cf1b149355d2236c27a2a71045b96b

4.) Perform SHA-256 hash on result of SHA-256 hash

echo -n '76d79e77bcf6e323cfa2fd256e51378734cf1b149355d2236c27a2a71045b96b' | xxd -r -p | sha256sum -b

36f8dee4526fd10ec69f67bc097ff6c667298438aa5fa5bdc41b1b4a34a9d784

5.) Take the first 4 bytes of the second SHA-256 hash, this is the checksum

36f8dee4 

6.) Add the 4 checksum bytes from point 5 at the end of the extended key from point 2

80f3bc5e754c621ed5f7a77566cd5ec425a395bedfefe5ef342412cb6ce7e5150536f8dee4

7.) Convert the result from a byte string into Base58 to get it into the Base58Check format. This is also known as the Wallet Import Format; I recommend this tool: http://gobittest.appspot.com/PrivateKey

Simply input the sha256 hash of the private key where necessary and press send. This converts to WIF (wallet import format) which is an importable private key
