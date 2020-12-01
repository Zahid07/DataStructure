#include<iostream>
#include"Ast1_DES.h"
using namespace std;


// This is the main function.


int main()
{
	//////////// sub keys generated ///////////////////
	string k = "133457799BBCDFF1"; // Key input
	string k_t = "";// permutated key
	string binary = "";// Binary of key
	string firsthalf = "";// First half of key
	string secondhalf = "";//second half of key
	int round_shifts[16] = { 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 };
	string FIRST_SECOND[16];// First Half and Second half keys saved for further use
	string permutated_Keys[16];// Permutated keys of 16 rounds
	binary = convert_Binary(k);
	
	k_t = initKeyPermutation(k);
	// Splitting First half and Second Half
	for (int i = 0; i < 56; i++) {
		if (i < 28) {
			firsthalf = firsthalf + k_t[i];
		}
		else {
			secondhalf = secondhalf + k_t[i];
		}
	}
	
	//Saving the keys in FIRST_SECOND[16] after each offset
	for (int i = 0; i < 16; i++) {
		firsthalf = offset(round_shifts[i], firsthalf);
		secondhalf = offset(round_shifts[i], secondhalf);
		FIRST_SECOND[i] = firsthalf + secondhalf;
	}

	//Applying PC2 here
	for (int j = 0; j < 16; j++) {

		permutated_Keys[j] = roundPermutation(FIRST_SECOND[j]);
		
	}



	///////////////////// plain text ///////////////////

	string m = "0123456789ABCDEF"; // Plain Text input
	string m_Binary = ""; // Plain text binary
	string IP = ""; //Initial Permutation text
	string Ln = "";// Left part of text
	string Rn = "";//right part of text
	int IPT[64] = { 58 , 50 , 42 , 34 , 26 , 18 , 10 , 2,60 , 52 , 44 , 36 , 28 , 20 , 12, 4,62 , 54, 46, 38, 30 , 22 , 14 , 6,64 , 56 , 48 , 40 , 32 , 24 , 16 , 8,57 , 49, 41, 33 , 25 , 17 , 9, 1,
		59 , 51 , 43, 35 , 27 , 19 , 11 ,3,
		61 , 53 , 45, 37 , 29 ,21 , 13 , 5,
		63 , 55 , 47 , 39 , 31, 23 , 15 ,7 };

	m_Binary = convert_Binary(m);

	IP = initTextPermutation(m);

	//Turning text binary to right half and left half
	for (int i = 0; i < 64; i++) {
		if (i < 32) {
			Ln = Ln + IP[i];
		}
		else {
			Rn = Rn + IP[i];
		}

	}
	for (int i = 0; i < 16; i++) {
		string temp = func(Rn, permutated_Keys[i]);
		string t = Ln;
		Ln = Rn;
		Rn = XOR(t, temp);		
	}
	IP = "";
	IP = Rn + Ln;
	//cout << "Ip is = " << IP << endl;
	IP = reverse_perm(IP);
	//cout << "Last answer is = ----------------- " << IP << endl;
	cout << "Encrypted text is = " << answer(IP);


}
