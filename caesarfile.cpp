#include <iostream>
#include <fstream>
using namespace std;

int main() {
	setlocale(LC_ALL, "RUSSIAN");
	system("chcp 1251");
	system("cls");
	int pwd;
	int menu;
	ifstream readFile;
	ofstream writeFile;
	char name[255];
	do {
		system("cls");
		cout << "1 - Encryption\n2 - Decryption\n0 - Exit\n\t";	
                cin >> menu;
		cin.get();
		if (menu == 1) {
			cout << "Enter file name for encryption: ";
			cin.getline(name, 255);
			readFile.open(name, ios::binary);
			if (readFile) {
				readFile.seekg(0, ios::end);
				unsigned int size = readFile.tellg();
				readFile.seekg(0);
				char *file = new char[size];
				if (file) {
					readFile.read(file, size);
					readFile.close();
					cout << "Enter a key (number): ";
					cin >> pwd;
					for (unsigned int i = 0; i < size; i++) {
						file[i] += pwd;
					}
					writeFile.open(name, ios::binary);
					writeFile.write(file, size);
					writeFile.close();
				}
				else
					readFile.close();
			}
			else
				cout << "Error open file!";

		}
		else if (menu == 2) {
			cout << "Enter file name for decryption: ";
			cin.getline(name, 255);
			readFile.open(name, ios::binary);
			if (readFile) {
				readFile.seekg(0, ios::end);
				unsigned int size = readFile.tellg();
				readFile.seekg(0);
				char *file = new char[size];
				if (file) {
					readFile.read(file, size);
					readFile.close();
					cout << "Enter a key (number): ";
					cin >> pwd;
					for (unsigned int i = 0; i < size; i++) {
						file[i] -= pwd;
					}
					writeFile.open(name, ios::binary);
					writeFile.write(file, size);
					writeFile.close();
				}
				else
					readFile.close();
			}
			else
				cout << "Error open file!";
		}
	} while (menu);
}

