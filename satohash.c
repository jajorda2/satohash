#include <stdio.h>
#include <string.h>

#include "hash.h"

void dump1(uint8_t* abcde) {
	for (int i = 0; i < 32; i++) {
		uint8_t value = abcde[i];
		printf("%02x", value);
	}
}

int main(int argc, char**argv) {

	uint8_t abcd [66] = {0};

	if (argc >= 2) {
		strncpy(&abcd[0], (uint8_t *)argv[1],65);
	} else {

		for (int i = 0; i < 65; i++) {
			int c = getchar();
			if (c == EOF) {
				break;
			}
			abcd[i] = (uint8_t)(c);
		}
	}

	if ((abcd[65] == 0) &&
		((abcd[64] == 0) || (abcd[64] == ' ') || (abcd[64] == '\n'))) {

		for (int i = 0; i < 64; i++) {
			switch (abcd[i]) {
			case '0':case '1':case '2':case '3':case '4':case '5':
			case '6':case '7':case '8':case '9':case 'a':case 'b':
			case 'c':case 'd':case 'e':case 'f':
				continue;
			}
			goto normalinput;
		}

		for (int i = 0; i < 64; i++) {
			if (abcd[i] >= 'a') {
				abcd[i] = abcd[i] + 10 - 'a';
			} else {
				abcd[i] -= '0';
			}
		}
		for (int i = 0; i < 32; i++) {
			abcd[i] = 16*abcd[2*i] + abcd[2*i+1];
		}

		for (int i = 32; i < 66; i++) {
			abcd[i] = 0;
		}
	}

	normalinput:

	satohash(&abcd[0], &abcd[0]);
	dump1(&abcd[0]);putchar('\n');

	return 0;
}
