#pragma once

#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<iomanip>
using namespace std;

class matching {

public:
	matching(char *fileName);
	void readFile(char *fileName);
	void verify();
	void pre();
	void treeDepth();
	void maxWeight();
	int matchWeight();
	void deleteWeight(int i,int j);
	void findRoot(int, int);
	void findLevel(int,int);
	void counting(char *fileName);
	void writeFile();
	void reReadFile();
        void handShaking(char *fileName);
public:
	ifstream rFile;
	ofstream wFile;
	ofstream oResult;
 	ofstream oHandShaking;
};
