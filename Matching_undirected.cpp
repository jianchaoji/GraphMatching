#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<stdlib.h>
#include"Matching.h"

using namespace std;

int v;
int e;
//const int v=15;
//const int e=12;

//int *degree;
int *degree;

//int degree[v] = { 0 };
int *offset;
int *index;
double *weight;
int *root1;
int Number = 0;


int *newIndex;
double *newWeight;


int *amount;
int *treeDepthA;

int *maxEdge;
int *maxWeights;
int *level;

int *flag; //check if the vertex is matched

template <class Type>
Type stringToNum(const string& str)
{
	istringstream iss(str);
	Type num;
	iss >> num;
	return num;
}
matching::matching(char *inputFile) {
	string s;
	
	int l = 0;
	rFile.open(inputFile);
	while (rFile >> s) {
		if (l < 2) {
			l++;
			if (l == 1) {
				v = stringToNum<int>(s);
			}
			if (l == 2) {
				e = stringToNum<int>(s);
			}
			continue;
		}
		else {
			break;
		}
	}
	rFile.close();

	//initialize
	degree = (int*)malloc(v * sizeof(int));
	 offset = (int*)malloc(v * sizeof(int));
	 index = (int*)malloc(e * sizeof(int));
	 weight = (double*)malloc(e * sizeof(double));
	 root1  = (int*)malloc(v * sizeof(int));

	  newIndex = (int*)malloc(v * sizeof(int));
	  newWeight = (double*)malloc(v * sizeof(double));


	 amount=(int*)malloc(v * sizeof(int));
	 treeDepthA = (int*)malloc(v * sizeof(int));

	 maxEdge = (int*)malloc(v * sizeof(int));
	 maxWeights = (int*)malloc(v * sizeof(int));
	 level = (int*)malloc(v * sizeof(int));

         flag = (int*)malloc(v*sizeof(int));
	for (int i = 0; i < v; i++) {
		degree[i] = 0;
		offset[i] = 0;
		root1[i] = 0;
		newIndex[i] = 0;
		newWeight[i] = 0;
		amount[i] = 0;
		treeDepthA[i] = 0;
		maxEdge[i] = 0;
		maxWeights[i]=0;
		level[i] = 0;
		flag[i]=0;
	}

	for (int i = 0; i < e; i++) {
		index[i] = 0;
		weight[i] = 0;
	}
}

void matching::readFile(char *inputFile) {
	string s;
	int l = 0;
	int i = 1;
	int position;
	int lines=0;
	int row, col;
	rFile.open(inputFile);
	srand(time(NULL));
	

	//initialize the graph
	while (rFile >> s) {

		if (l < 2) {
			l++;
			continue;
		}
		else {
			if (i % 2 == 0) {
				position = stringToNum<int>(s)-1;
				degree[position]++;
			}
			else if (i % 2 == 1) {
				index[lines] = stringToNum<int>(s)-1;
				weight[lines] = rand() % 500;
				lines++;
				
			}
	//		else if (i % 3 == 0) {
	//			//weight[lines] = stringToNum<double>(s);
	//			lines++;
	//		}
			i++;
		}
	}

	for (int i = 1; i < v; i++) {
		offset[i] = offset[i - 1] + degree[i - 1];
	}
	
	
	for (int i = 0; i < v; i++) {//traverse each vertex;
		
		int temp = -1;
		
		temp = offset[i];//start point of the vertex;

		for (int j = 0; j < degree[i]; j++) {//edge of the vertex;
			if (i == index[temp]) {
				index[temp] = -1;
				weight[temp] = -1;	
			}
			temp++;
		}
	}
	
	
//	//test the result;
//	cout << "degree" << endl;
//	for (int i = 0; i < v; i++) {
//		cout << degree[i] << " ";
//	}
//	cout << endl;
//	cout << "offset" << endl;
//	for (int i = 0; i < v; i++) {
//		cout << offset[i] << " ";
//	}
//	cout << endl;
//	cout << "index" << endl;
//	for (int i = 0; i < e; i++) {
//		cout << index[i] << " ";
//	}
//	cout << endl;
//	cout << "weight" << endl;
//	for (int i = 0; i < e; i++) {
//		cout << weight[i] << " ";
//	}//end test;
//	cout << endl;
	
}








void matching::maxWeight() {
	
	for (int i = 0; i < v; i++) {//find the max adjacent vertex for each vertex;
		int position = -1;
		int max = maxWeights[i];
		int temp = -1;
		temp = offset[i];//start point of the vertex;
	//	if(temp==-1)continue;
		/*for (int j = 0; j < degree[i]; j++) {
			temp = offset[i] + j;//exactly position
			if (max < weight[temp]) {
				max = weight[temp];
				position = index[temp]-1;
			}
			
		}
		maxEdge[i] = position;*/
		for (int j = 0; j < degree[i]; j++) {//edge of the vertex;
			if (max < weight[temp]) {
	//			cout<<"start match vertex"<<i<<endl;
				if(flag[index[temp]]!=-1){
				position = index[temp];//update the max end point;
	//			cout<<"The position is : "<< position<<endl;
				max = weight[temp];//update the max edge;
				maxWeights[i]=max;
				maxEdge[i]=position;
				if(flag[position]!=-1){
	//				cout<<"start check destination vertex"<<endl;
					if(maxWeights[position]<max){
	//				cout<<"we should update the destination vertex"<<endl;
						maxWeights[position]=max;
						maxEdge[position]=i;
						}
					}
				}
			}
			temp++;
		}


	//	maxEdge[i] = position;
	}
	
	//verify
//	for (int i = 0; i < e; i++) {
//		cout << index[i] << " ";
//	}
//	cout << endl;
//	for (int i = 0; i < v; i++) {
//		cout << maxEdge[i] << " ";
//	}
//	cout << endl;
//	
}


int matching::matchWeight() {
	int count = 0;
	for (int i = 0; i < v; i++) {
		if (i == maxEdge[maxEdge[i]]) {//matched
			deleteWeight(i, maxEdge[i]);
			count++;
		}
	}
	cout << "match time is " << count / 2 << endl;
	return count;
}

void matching::deleteWeight(int j, int k) {
	for (int i = 0; i < degree[j]; i++) {//delete vertex j;
		int temp = offset[j] + i;
		index[temp] = -1;
		weight[temp] = -1;
	}
	for (int i = 0; i < degree[k]; i++) {//delete vertex k;
		int temp = offset[k] + i;
		index[temp] = -1;
		weight[temp] = -1;
	}
	flag[j]=-1;
//	cout<<"delete vertex :"<< j<<endl;
	flag[k]=-1;
//	cout<<"delete vertex :"<<k<<endl;
//	for (int i = 0; i < e; i++) {
//		if (index[i] == j || index[i] == k) {
//			index[i] = -1;
//			weight[i] = -1;
//		}
//	}
/*
   	for(int i=0;i<v;i++){
	if(i==j||i==k){
	offset[i]=-1;
		}
	}
*/
}




void matching::handShaking(char *inputFile){
     int *pairs;
     pairs=(int*)malloc(v*sizeof(int));
     for(int i=0 ; i<v;i++){
	pairs[i]=0;
	}
     int i=0;
     while(true){
 	maxWeight();
	pairs[i]=matchWeight()-1;
//	cout<<pairs[i]<<endl;
	if(pairs[i]<=0)break;
	i++;
	for(int k=0;k<v;k++){
		maxWeights[k]=-1;
		maxEdge[k]=-1;
		}
//	for(int k=0;k<v;k++){
//		cout<<flag[k]<<" ";
//		}
//	cout<<endl;
	//if(pairs[i-1]==0)return;
	}
	int iteration=0;
//     while(true){
//	if(pairs[iteration]!=0)iteration++;
//	else break;
//	}
//	oHandShaking.open("handShaking.txt",ios::app);
	oHandShaking<<"The name of the graph is "<< inputFile<<endl
		<<"There are "<<v<< " vertex "<< e <<" edges in the graph"<<endl
		<<"The iteration is "<<iteration<<endl<<endl;
        oHandShaking.close();

}

