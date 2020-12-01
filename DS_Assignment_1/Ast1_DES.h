#pragma once
//#include <iostream>
#include <string>
#include <math.h>
using namespace std;
/*
If you want to know the encrypted text please uncomment main function and change the respective ket and text fields.
I190469.
Muhammad Zahid
CS-D
*/
string func(string, string);
string S_BOX(string);
string expand(string);
string convert_Binary(string);
// initial Permutation function


string initKeyPermutation(string key) {
	string binary = convert_Binary(key);
	string k_t = "";

	int PC1[56] = { 57, 49, 41, 33, 25, 17, 9, 1, 58, 50, 42, 34, 26, 18, 10, 2, 59, 51, 43, 35, 27, 19, 11, 3, 60, 52, 44, 36, 63, 55, 47, 39, 31, 23, 15, 7, 62, 54, 46, 38, 30, 22, 14, 6, 61, 53, 45, 37, 29, 21, 13, 5, 28, 20, 12, 4 };

	for (int i = 0; i < 56; i++) {
		int index = PC1[i];
		index -= 1;
		k_t = k_t + binary[index];
	}
	
	return k_t;
	
}

//Converts ant integer to Binary and is used in combinatin with the function convert_Binary
string Binary(int to_binary) {

	string bin = "";
	for (int k = 0; to_binary > 0; k++) {
		bin = bin + to_string(to_binary % 2);
		to_binary = to_binary / 2;

	}
	if (bin.length() < 4) {
		int len = bin.length();
		len = 4 - len;
		for (int k = 0; k < len; k++) {
			bin = bin + "0";
		}
	}
	string temp = "";
	for (int k = 0; k < 4; k++) {
		temp = temp + bin[3 - k];

	}
	bin = temp;
	return bin;
}

// The Function for circular shift
string halfCircularShift(string firsthalf, int offset) {
	string first = "";
	string half = "";
	for (int k = 0; k < offset; k++) {
		first = first + firsthalf[k];
	}

	for (int i = 0; i < (28 - offset); i++) {
		half = half + firsthalf[i + offset];
	}

	string temp = "";
	for (int i = 0; i < offset; i++) {
		temp = temp + first[(offset - 1) - i];
	}
	half = half + first;

	
	
	return half;
	
}

//Does the same work as circular shift
string offset(int offset, string firsthalf) {
	string first = "";
	string half = "";
	for (int k = 0; k < offset; k++) {
		first = first + firsthalf[k];
	}

	for (int i = 0; i < (28 - offset); i++) {
		half = half + firsthalf[i + offset];
	}

	string temp = "";
	for (int i = 0; i < offset; i++) {
		temp = temp + first[(offset - 1) - i];
	}
	half = half + first;





	return half;
}

//Converts any string k to binary, here K is hexa deciaml number
string convert_Binary(string k) {
	char temp_num = '1';
	string binary = "";
	int to_binary = 0;
	for (int i = 0; i < k.length(); i++) {
		temp_num = '1';
		to_binary = 0;
		if (k[i] >= '1' && k[i] <= '9') {
			string bin = "";
			for (int j = 0; j < 9; j++) {
				if (temp_num == k[i]) {
					to_binary = j + 1;
					break;
				}
				temp_num += 1;
			}
			bin = Binary(to_binary);
			binary = binary + bin;

		}
		else {
			string bin = "";
			temp_num = 'A';
			for (int j = 0; j < 7; j++) {
				if (temp_num == k[i]) {
					to_binary = j + 10;
					break;
				}
				temp_num += 1;
			}
			bin = Binary(to_binary);
			binary = binary + bin;
		}
		binary = binary;
	}
	return binary;
}

// This function takes the XOR and return the value
string XOR(string Rn, string F) {
	string temp = "";
	//cout << F.length() << endl;
	for (int i = 0; i < Rn.length(); i++) {
		if ((Rn[i] == '1' && F[i] == '1') || (Rn[i] == '0' && F[i] == '0')) {
			temp = temp + '0';
		}
		else {
			temp = temp + '1';
		}
	}
	
	return temp;
}

// This function is for reverse permutation of the key after 16 rounds
string reverse_perm(string key) {
	string answer;
	//cout << "key is = " << key << endl;
	int inverse[64] = { 40 , 8 , 48 , 16, 56, 24 , 64 , 32,

		39 , 7 , 47 , 15 , 55 , 23 , 63 , 31,
		38 , 6 , 46 , 14, 54, 22 , 62, 30,
		37 , 5 , 45 , 13 , 53, 21 , 61 , 29,
		36 , 4, 44 , 12 , 52 , 20 , 60 , 28,
		35 , 3 , 43 , 11 , 51 , 19, 59 , 27,
		34 , 2 , 42 , 10 , 50, 18 , 58 , 26,
		33 , 1 , 41 , 9 , 49, 17 , 57 , 25 };
	int j = 1;
	for (int i = 0; i < 64; i++) {
		int index = inverse[i];
		index -= 1;
		answer = answer + key[index];
		j += 1;
		if (j == 5) {
			j = 1;
			answer = answer;
		}
	}
	return answer;

}

// Expands the 32 to 48 bits
string expandHalfText(string Rn) {
	int EXPANSION_TABLE[48] = { 32, 1, 2, 3, 4, 5, 4, 5, 6, 7, 8, 9, 8, 9, 10, 11, 12, 13, 12, 13, 14, 15, 16, 17,
		16, 17, 18, 19, 20, 21, 20, 21, 22, 23, 24, 25, 24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32, 1 };

	string answer = "";
	for (int i = 0; i < 48; i++) {
		int index = EXPANSION_TABLE[i];
		index -= 1;
		answer = answer + Rn[index];


	}
	
	return answer;

}

// same function as the above function
string expand(string Rn) {
	int EXPANSION_TABLE[48] = { 32, 1, 2, 3, 4, 5, 4, 5, 6, 7, 8, 9, 8, 9, 10, 11, 12, 13, 12, 13, 14, 15, 16, 17,
		16, 17, 18, 19, 20, 21, 20, 21, 22, 23, 24, 25, 24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32, 1 };

	string answer = "";
	for (int i = 0; i < 48; i++) {
		int index = EXPANSION_TABLE[i];
		index -= 1;
		answer = answer + Rn[index];


	}

	return answer;

}

// This function performs the round permutation 

string roundPermutation(string FIRST_SECOND) {
	int PC2[48] = { 14, 17, 11, 24, 1, 5, 3, 28, 15, 6, 21, 10, 23, 19, 12, 4, 26, 8, 16, 7, 27, 20, 13, 2,	41, 52, 31, 37, 47, 55, 30, 40, 51, 45, 33, 48, 44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32 };

	string first = FIRST_SECOND;
	string temp = "";
	for (int i = 0; i < 48; i++) {
		int index = PC2[i];
		index -= 1;

		temp = temp + first[index];
	}
	
	return temp;
	
}


// This is for text permutation
string initTextPermutation(string m) {
	string IP = "";
	int IPT[64] = { 58 , 50 , 42 , 34 , 26 , 18 , 10 , 2,60 , 52 , 44 , 36 , 28 , 20 , 12, 4,62 , 54, 46, 38, 30 , 22 , 14 , 6,64 , 56 , 48 , 40 , 32 , 24 , 16 , 8,57 , 49, 41, 33 , 25 , 17 , 9, 1,
			59 , 51 , 43, 35 , 27 , 19 , 11 ,3,
			61 , 53 , 45, 37 , 29 ,21 , 13 , 5,
			63 , 55 , 47 , 39 , 31, 23 , 15 ,7 };

	string m_Binary = convert_Binary(m);


	for (int i = 0; i < 64; i++) {
		int index = IPT[i];
		index -= 1;

		IP = IP + m_Binary[index];
	}
	
	return IP;
}

// this converts the binary after inverse permutation to hexa
string answer(string IP) {
	string temp = "";
	string a = "";
	string ans = "";
	//cout << endl;
	//cout << " ";
	for (int i = 0; i < IP.length(); i++) {
		int t = 0;
		temp = temp + IP[i];
		if (((i + 1) % 4) == 0) {

			for (int i = 0; i < 16; i++) {
				if (temp == Binary(t)) {
					if (t < 10) {
						ans = ans + to_string(t);
					}
					else {
						if (t == 10) {
							ans = ans + 'A';
						}
						else if (t == 11) {
							ans = ans + 'B';
						}
						else if (t == 12) {
							ans = ans + 'C';
						}
						else if (t == 13) {
							ans = ans + 'D';
						}
						else if (t == 14) {
							ans = ans + 'E';
						}
						else if (t == 15) {
							ans = ans + 'F';
						}
					}
					t = 0;
					break;
				}
				t += 1;
			}
			temp = "";
			a = "";
		}


	}

	return ans;

}


// This returns the respectivr S BOX value
string return_S(int num, int row, int col) {

	int S[8][64] = { {14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7,0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8,4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0,15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13 },
					{15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10,3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5,0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15,13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9 },
					{10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8,13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1,13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7,1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12},
					{7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15,13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9,10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4,3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14 },
					{2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9,14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6,4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14,11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3 },
					{12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11,10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8,9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6,4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13},
					{4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1,13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6,1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2,6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12},
					{13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7,1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2,7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8,2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11} };


	int temp1[4][16];
	int k = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 16; j++) {
			temp1[i][j] = S[num][k];
			k += 1;
		}

	}
	int to_binary = temp1[row][col];
	string bin = "";
	for (int k = 0; to_binary > 0; k++) {
		bin = bin + to_string(to_binary % 2);
		to_binary = to_binary / 2;

	}

	string temp;
	while (bin.length() < 4) {
		bin = bin + '0';
	}
	for (int i = 0; i < 4; i++) {
		temp = temp + bin[3 - i];
	}
	return temp;
}

// This summons the abovr function. This sends which row and sbox to use
string calcSBox(string key) {
	int j = 0;
	string answer = "";
	string temp = "";
	for (int i = 0; i < 48; i++) {
		temp = temp + key[i];
		if ((i + 1) % 6 == 0) {
			int row = (2 * (temp[0] - '0')) + (1 * (temp[5] - '0'));
			int col = (8 * (temp[1] - '0')) + (4 * (temp[2] - '0')) + (2 * (temp[3] - '0')) + (1 * (temp[4] - '0'));
			answer = answer + return_S(j, row, col);
			temp = "";
			j += 1;
		}

	}

	return answer;
}/*
string S_BOX(string key) {
	//key = expand(key);

	//cout << "kry length is = " << key.length() << endl;
	int j = 0;
	string answer = "";
	string temp = "";
	for (int i = 0; i < 48; i++) {
		temp = temp + key[i];
		if ((i + 1) % 6 == 0) {
			//cout << " = " << temp << endl;;
			//temp = "011011";
			//for (int i = 0; i < 6; i++) {
				//cout << temp[i] << " ";
			//}cout << endl;
			int row = (2 * (temp[0] - '0')) + (1 * (temp[5] - '0'));

			int col = (8 * (temp[1] - '0')) + (4 * (temp[2] - '0')) + (2 * (temp[3] - '0')) + (1 * (temp[4] - '0'));


			//cout << "j is = " << j << endl;
			answer = answer + return_S(j, row, col);
			//cout << endl;
			temp = "";
			j += 1;
		}

	}
	//cout << "aaa = " << answer << endl;
	return answer;
}*/

// This function performs expansion and permutation for 32 to 32 bit conversion ans returns the value.
string func(string Rn, string permutated_Key) {
	int EXPANSION_TABLE[48] = { 32, 1, 2, 3, 4, 5, 4, 5, 6, 7, 8, 9, 8, 9, 10, 11, 12, 13, 12, 13, 14, 15, 16, 17,
		16, 17, 18, 19, 20, 21, 20, 21, 22, 23, 24, 25, 24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32, 1 };

	string temp = "";
	string answer = "";


	int j = 0;
	for (int i = 0; i < 48; i++) {
		int index = EXPANSION_TABLE[i];
		index -= 1;
		if ((Rn[index] == '1' && permutated_Key[i] == '1') || (Rn[index] == '0' && permutated_Key[i] == '0')) {
			temp = temp + '0';
		}
		else {
			temp = temp + '1';
		}
		if ((i + 1) % 6 == 0) {
			int row = (2 * (temp[0] - '0')) + (1 * (temp[5] - '0'));
			int col = (8 * (temp[1] - '0')) + (4 * (temp[2] - '0')) + (2 * (temp[3] - '0')) + (1 * (temp[4] - '0'));
			answer = answer + return_S(j, row, col);
			temp = "";
			j += 1;
		}

	}
	int P[32] = { 16,   7,  20,  21,	29 , 12,  28 , 17,1 , 15 , 23,  26,5 , 18 , 31,  10,2  , 8  ,24,  14,32 , 27  , 3 ,  9,	19 , 13 , 30  , 6,22 , 11,   4 , 25 };
	string ans = "";
	for (int i = 0; i < 32; i++) {
		int index = P[i];
		index -= 1;
		ans = ans + answer[index];
	}
	return ans;

}





