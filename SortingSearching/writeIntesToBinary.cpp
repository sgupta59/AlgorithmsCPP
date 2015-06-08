// Programmer: Graham Nedelka
// Output random numbers to file, read in via vector
//
#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>
#include <algorithm>
using namespace std;
static void readWrite()
{
	srand (time(NULL));
	ofstream myFile("C:\\temp\\data.dat");
	for (int i = 0; i < 1000000; i++)
		myFile << rand() % 10000 + 1 << endl;
	myFile.close();
	vector<int> newVector;
	ifstream myRead;
	myRead.open("C:\\temp\\data.dat");
	int x;
	while (!myRead.eof())
	{
		myRead >> x;
	newVector.push_back(x);
	}
	myRead.close();
	for (int i = 0; i < newVector.size(); i++)
		cout << newVector[i] << endl;
	sort(newVector.begin(), newVector.end());
	for (int i = 0; i < newVector.size(); i++)
		cout << newVector[i] << endl;
	return ;
}
void readWrite1()
{
	FILE *fp = fopen("C:\\temp\\path_to_file.bin","wb");
    if(fp == NULL) {
    	printf("error creating file");
    	return ;
    }
    int val = 4;
    fwrite((const void*)&val,4,1,fp);
	val = 5;
	fwrite((const void*)&val,4,1,fp);
    fclose(fp);

	unsigned char buffer[10];
	FILE *ptr;
	ptr = fopen("C:\\temp\\path_to_file.bin","rb");  // r for read, b for binary
	fread(buffer,4,1,ptr);
	fread(buffer+4,4,1,ptr);
    return ;
}
int main () {
	readWrite();
}