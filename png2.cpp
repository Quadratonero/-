#include "stdafx.h"
#include "iostream"
#include "conio.h"
#include <fstream>
#include <vector>
using namespace std;

void normalOutputForCRC(unsigned char* data) {
	cout << "CRC: 0x";
	for (int i = 0; i<4; i++) {
		cout << hex <<(int)data[i];
	}
	cout << endl << endl;
}

int main(int argc, char *argv[])
{
	if (argc != 2) { 
		cout << "Usage: png2.exe <filename>" << endl;
		return 1;
	}
	ifstream in(argv[1], ios::binary);
	if (!in.is_open()) {
		cout << "Can't open " << argv[1] << endl;
		return 2;
	}

	unsigned char signature[9] = { 0 };
	in.read((char*)signature, 8);

	if (strcmp((char*)signature, "\x89\x50\x4E\x47\x0D\x0A\x1A\x0A") == 0) {
		cout << "PNG signature - [CORRECT] " << endl << endl;
	}
	else {
		cout << "PNG signature - [WRONG]" << endl << endl;
	}

	unsigned char IHDRlength[4] = { 0 };
	in.read((char*)IHDRlength, 4);

	for (int i = 0; i < 2; i++) {
		swap(IHDRlength[i], IHDRlength[3 - i]);
	}

	unsigned int IHDRLengthLikeNumber = *((unsigned int*)IHDRlength);
	char IHDRname[5] = { 0 };
	unsigned char IHDRcrc[4] = { 0 };
	in.read((char *)IHDRname, 4);

	if (strcmp(IHDRname, "IHDR") == 0) {
		in.seekg(IHDRLengthLikeNumber, ios_base::cur);
		in.read((char *)IHDRcrc, 4);
		cout << "IHDR chunk - [CORRECT]" << endl;
		cout << "Length: " << dec <<IHDRLengthLikeNumber << endl;
		normalOutputForCRC(IHDRcrc);
	}
	else {
		cout << "IHDR chunk - [WRONG]" << endl << endl;

	}

	in.seekg(-12, ios_base::end);
	unsigned char IENDchunk[13] = { 0 };
	in.read((char *)IENDchunk, 12);
	if (strcmp((char*)IENDchunk, "\x00\x00\x00\x00\x49\x45\x4E\x44\xAE\x42\x60\x82") == 0) {
		cout << "IEND chunk - [CORRECT]" << endl << endl;
	}
	else {
		cout << "IEND chunk - [WRONG]" << endl << endl;
	}

	char IDATname[5] = { 0 };
	in.seekg((20 + IHDRLengthLikeNumber), ios_base::beg);
	bool thereIsOneIDAT = false;

	while (!in.eof()) {
		if (in.get() == 'I') {
			in.seekg(-1, ios_base::cur);
			in.read((char*)IDATname, 4);
			if (strcmp((char*)IDATname, "IDAT") == 0) {
				cout << "IDAT chunk" << endl;
				in.seekg(-8, ios_base::cur);
				cout << "Position: " << dec <<in.tellg() << endl;
				unsigned char tempIDAT[5] = { 0 };
				in.read((char *)tempIDAT, 4);
				for (int i = 0; i < 2; i++) {
					swap(tempIDAT[i], tempIDAT[3 - i]);
				}
				unsigned int IDATLengthLikeNumber = *((unsigned int*)tempIDAT);
				cout << "Length: " << dec<<IDATLengthLikeNumber << endl;
				in.seekg(4 + IDATLengthLikeNumber, ios_base::cur);
				in.read((char *)tempIDAT, 4);
				normalOutputForCRC(tempIDAT);
				thereIsOneIDAT = true;
			}
		}
	}

	if (!thereIsOneIDAT) {
		cout << "There is no IDAT chunks" << endl << endl;
	}
	else {
		cout << "[END]";
	}

	_getch();
}

