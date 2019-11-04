
//#include"readFile.h"
#include"Matching.h"
#include<iostream>
#include<fstream>
#include<string>
#include<stdlib.h>
using namespace std;
int  main(int arc,char *arv[] ) {
	
	int choice;
 	int i=1;
	char *inputFile;
 	inputFile=arv[i];
	matching test(inputFile);
	//match test1;
	
	test.readFile(inputFile);
	//test.writeFile();
	//test.reReadFile();
	//cout << "Doing pre now " << endl;
//	test.pre();
        test.handShaking(inputFile);
	//cout << "Doing verify now " << endl;
	
	//test1.tree();
	//test.treeDepth();
	//test.counting(inputFile);
	/*for (int i = 0; i < 50; i++) {
		test.maxWeight();
		test.matchWeight();
	}*/
	//test.deleteWeight();
	//test.maxWeight();
	//test.matchWeight();
	//system("pause");
	return 0;
}
