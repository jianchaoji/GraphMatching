#pragma once

#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<iomanip>
using namespace std;

class matching {

public:
	matching();
	void readFile();
	void verify();
	void pre();
	void treeDepth();
	void maxWeight();
	void matchWeight();
	void deleteWeight(int i,int j);
	void findRoot(int, int);
	void findLevel(int,int);
	void counting();
public:
	ifstream rFile;
};
