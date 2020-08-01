#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
	ifstream file;
	ofstream file_out;
	int size = 0;
	if(argc != 4){
		cout << "Error! Example: program | way | key(0-255) | enc/dec" << endl;
	}
	file.open(argv[1], ios_base::in | ios_base::binary);
	if (file.is_open()) {
		file.seekg(0, ios::end);
		size = file.tellg();
		file.seekg(0, ios::beg);
		char *str = new char[size];
		file.read(str, size);
		file.close();
		if(argv[3] == "enc" || argv[3] == "dec"){
		int key = atoi(argv[2]);
		char key1 = (char) key;
		for (int i = 0; i < size; i++) {
			str[i] += key1;
		}
	}
		file_out.open(argv[1], ios_base::out | ios_base::binary);
		if (file_out.is_open()) {
			file_out.write(str, size);
			file_out.close();
		}
	}
	else
		cout << "Error! File not found!" << endl;
}