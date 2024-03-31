#ifndef KK_H
#define KK_H
const bool kk[256]{
	false,// 00
	false,// 01
	false,// 02
	false,// 03
	false,// 04
	false,// 05
	false,// 06
	false,// 07
	false,// 08
	false,// 09
	false,// 0A
	false,// 0B
	false,// 0C
	false,// 0D
	false,// 0E
	false,// 0F
	false,// 10
	false,// 11
	false,// 12
	false,// 13
	false,// 14
	false,// 15
	false,// 16
	false,// 17
	false,// 18
	false,// 19
	false,// 1A
	false,// 1B
	false,// 1C
	false,// 1D
	false,// 1E
	false,// 1F
	false,// 20 ' '
	true ,// 21 '!'
	false,// 22 '"'
	true ,// 23 '#'
	true ,// 24 '$'
	true ,// 25 '%'
	false,// 26 '&'
	false,// 27 '''
	false,// 28 '('
	false,// 29 ')'
	true ,// 2A '*'
	true ,// 2B '+'
	false,// 2C ','
	true ,// 2D '-'
	true ,// 2E '.'
	true ,// 2F '/'
	true ,// 30 '0'
	true ,// 31 '1'
	true ,// 32 '2'
	true ,// 33 '3'
	true ,// 34 '4'
	true ,// 35 '5'
	true ,// 36 '6'
	true ,// 37 '7'
	true ,// 38 '8'
	true ,// 39 '9'
	false,// 3A ':'
	false,// 3B ';'
	true ,// 3C '<'
	true ,// 3D '='
	true ,// 3E '>'
	true ,// 3F '?'
	true ,// 40 '@'
	true ,// 41 'A'
	true ,// 42 'B'
	true ,// 43 'C'
	true ,// 44 'D'
	true ,// 45 'E'
	true ,// 46 'F'
	true ,// 47 'G'
	true ,// 48 'H'
	true ,// 49 'I'
	true ,// 4A 'J'
	true ,// 4B 'K'
	true ,// 4C 'L'
	true ,// 4D 'M'
	true ,// 4E 'N'
	true ,// 4F 'O'
	true ,// 50 'P'
	true ,// 51 'Q'
	true ,// 52 'R'
	true ,// 53 'S'
	true ,// 54 'T'
	true ,// 55 'U'
	true ,// 56 'V'
	true ,// 57 'W'
	true ,// 58 'X'
	true ,// 59 'Y'
	true ,// 5A 'Z'
	false,// 5B '['
	true ,// 5C '\'
	false,// 5D ']'
	false,// 5E ¡^'
	true ,// 5F '_'
	false,// 60 '`'
	true ,// 61 'a'
	true ,// 62 'b'
	true ,// 63 'c'
	true ,// 64 'd'
	true ,// 65 'e'
	true ,// 66 'f'
	true ,// 67 'g'
	true ,// 68 'h'
	true ,// 69 'i'
	true ,// 6A 'j'
	true ,// 6B 'k'
	true ,// 6C 'l'
	true ,// 6D 'm'
	true ,// 6E 'n'
	true ,// 6F 'o'
	true ,// 70 'p'
	true ,// 71 'q'
	true ,// 72 'r'
	true ,// 73 's'
	true ,// 74 't'
	true ,// 75 'u'
	true ,// 76 'v'
	true ,// 77 'w'
	true ,// 78 'x'
	true ,// 79 'y'
	true ,// 7A 'z'
	true ,// 7B '{'
	false,// 7C '|'
	true ,// 7D '}'
	false,// 7E '~'
	false,// 7F
	false,// 80
	false,// 81
	false,// 82
	false,// 83
	false,// 84
	false,// 85
	false,// 86
	false,// 87
	false,// 88
	false,// 89
	false,// 8A
	false,// 8B
	false,// 8C
	false,// 8D
	false,// 8E
	false,// 8F
	false,// 90
	false,// 91
	false,// 92
	false,// 93
	false,// 94
	false,// 95
	false,// 96
	false,// 97
	false,// 98
	false,// 99
	false,// 9A
	false,// 9B
	false,// 9C
	false,// 9D
	false,// 9E
	false,// 9F
	false,// A0
	false,// A1
	false,// A2
	false,// A3
	false,// A4
	false,// A5
	false,// A6
	false,// A7
	false,// A8
	false,// A9
	false,// AA
	false,// AB
	false,// AC
	false,// AD
	false,// AE
	false,// AF
	false,// B0
	false,// B1
	false,// B2
	false,// B3
	false,// B4
	false,// B5
	false,// B6
	false,// B7
	false,// B8
	false,// B9
	false,// BA
	false,// BB
	false,// BC
	false,// BD
	false,// BE
	false,// BF
	false,// C0
	false,// C1
	false,// C2
	false,// C3
	false,// C4
	false,// C5
	false,// C6
	false,// C7
	false,// C8
	false,// C9
	false,// CA
	false,// CB
	false,// CC
	false,// CD
	false,// CE
	false,// CF
	false,// D0
	false,// D1
	false,// D2
	false,// D3
	false,// D4
	false,// D5
	false,// D6
	false,// D7
	false,// D8
	false,// D9
	false,// DA
	false,// DB
	false,// DC
	false,// DD
	false,// DE
	false,// DF
	false,// E0
	false,// E1
	false,// E2
	false,// E3
	false,// E4
	false,// E5
	false,// E6
	false,// E7
	false,// E8
	false,// E9
	false,// EA
	false,// EB
	false,// EC
	false,// ED
	false,// EE
	false,// EF
	false,// F0
	false,// F1
	false,// F2
	false,// F3
	false,// F4
	false,// F5
	false,// F6
	false,// F7
	false,// F8
	false,// F9
	false,// FA
	false,// FB
	false,// FC
	false,// FD
	false,// FE
	false,// FF
};
#endif
