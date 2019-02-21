
//#include"readFile.h"
#include"Matching.h"
#include<iostream>
#include<fstream>
#include<string>
#include<stdlib.h>
using namespace std;
int  main() {
	
	int choice;
	matching test;
	//match test1;
	
	test.readFile();
	test.pre();
	test.verify();
	//test1.tree();
	test.treeDepth();
	test.counting();
	//for (int i = 0; i < 50; i++) {
	//	test.maxWeight();
	//	test.matchWeight();
	//}
	//test.deleteWeight();
	//test.maxWeight();
	//test.matchWeight();
	//system("pause");
	return 0;
}
