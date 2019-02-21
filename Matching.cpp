#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<stdlib.h>
#include"Matching.h"

using namespace std;

const int v=262111;
const int e=1234877;

int degree[v] = { 0 };
int offset[v] = { 0 };
int index[e];
double weight[e];
int root1[v] = { 0 };
int Number = 0;

template <class Type>
Type stringToNum(const string& str)
{
	istringstream iss(str);
	Type num;
	iss >> num;
	return num;
}
matching::matching() {

}

void matching::readFile() {
	string s;
	int l = 0;
	int i = 1;
	int position;
	int lines=0;
	int row, col;
	rFile.open("amazon.mtx");

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
				weight[lines] = rand() % 600;
				lines++;
				
			}
			/*else if (i % 3 == 0) {
				weight[lines] = stringToNum<double>(s);
				lines++;
			}*/
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
	
	/*
	//test the result;
	cout << "degree" << endl;
	for (int i = 0; i < v; i++) {
		cout << degree[i] << " ";
	}
	cout << endl;
	cout << "offset" << endl;
	for (int i = 0; i < v; i++) {
		cout << offset[i] << " ";
	}
	cout << endl;
	cout << "index" << endl;
	for (int i = 0; i < e; i++) {
		cout << index[i] << " ";
	}
	cout << endl;
	cout << "weight" << endl;
	for (int i = 0; i < e; i++) {
		cout << weight[i] << " ";
	}//end test;
	cout << endl;
	*/
}
//int newDegree[v];
int newIndex[v];
double newWeight[v];

void matching::pre() {
	for (int i = 0; i < v; i++) {//traverse each vertex;
		int position = -1;
		int temp = -1;
		int max = -1;
		temp = offset[i];//start point of the vertex;

		for (int j = 0; j < degree[i]; j++) {//edge of the vertex;
			if (max < weight[temp]) {
				position = index[temp];//update the max end point;
				max = weight[temp];//update the max edge;
			}
			temp++;
		}

		for (int j = 0; j < e; j++) {//find the other possible vertex;
			if (index[j] != i)continue;
			else {
				if (max < weight[j]) {
					max = weight[j];
					for (int k = 0; k < v; k++) {//update the position
						if (offset[k] > j) {
							position = k-1;//update finished
							break;
					   }
					}
				}
			}
		}

		//store the index and the weight;
		newIndex[i] = position;
		newWeight[i] = max;
		
	}
	/*
	//verify the result;
	cout << "index" << endl;
	for (int i = 0; i < v; i++) {
		cout << newIndex[i] << " ";
	}
	cout << endl;
	cout << "weight" << endl;
	for (int i = 0; i < v; i++) {
		cout << newWeight[i] << " ";
	}
	cout << endl;
	//end test;
	*/
}

void matching::verify() {
	for (int i = 0; i < v; i++) {
		findRoot(i, -1);
	}
	/*
	//verify the result
	for (int i = 0; i < v; i++) {
		cout << root1[i] << endl;
	}*/
}

void matching::findRoot(int j,int k) {
	if (root1[newIndex[j]] != 0) {
		root1[j] = root1[newIndex[j]];
		return;
	 }

	if (root1[newIndex[j]] == 0 && newIndex[j] != k) {
		//cout << "Run" << endl;
		findRoot(newIndex[j],j);
		root1[j] = root1[newIndex[j]];
	}
	else {
		if (newIndex[j] == k) {
			root1[j] = ++Number;
		}
		//root1[j] = root1[newIndex[j]];
		return;
	}
}


int maxEdge[v] = { 0 };
void matching::maxWeight() {
	
	for (int i = 0; i < v; i++) {//find the max adjacent vertex for each vertex;
		int position = -1;
		int max = -1;
		int temp = -1;
		temp = offset[i];//start point of the vertex;
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
				position = index[temp];//update the max end point;
				max = weight[temp];//update the max edge;
			}
			temp++;
		}

		for (int j = 0; j < e; j++) {//find the other possible vertex;
			if (index[j] != i)continue;
			else {
				if (max < weight[j]) {
					max = weight[j];
					for (int k = 0; k < v; k++) {//update the position
						if (offset[k] > j) {
							position = k - 1;//update finished
							break;
						}
					}
				}
			}
		}

		maxEdge[i] = position;
	}
	/*
	//verify
	for (int i = 0; i < e; i++) {
		cout << index[i] << " ";
	}
	cout << endl;
	for (int i = 0; i < v; i++) {
		cout << maxEdge[i] << " ";
	}
	cout << endl;
	*/
}


void matching::matchWeight() {
	int count = 0;
	for (int i = 0; i < v; i++) {
		if (i == maxEdge[maxEdge[i]]) {//matched
			deleteWeight(i, maxEdge[i]);
			count++;
		}
	}
	//cout << "match time is " << count / 2 << endl;
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

	for (int i = 0; i < e; i++) {
		if (index[i] == j || index[i] == k) {
			index[i] = -1;
			weight[i] = -1;
		}
	}
}

int level[v] = { 0 };
int depth = 0;
void matching::treeDepth() {
	for (int i = 0; i < v; i++) {
		findLevel(i, -1);
	}
	/*
	cout << "The level for each node are :" << endl;
	for (int i = 0; i < v; i++) {
		cout << level[i] << endl;
	}*/
}

void matching::findLevel(int j,int k) {
	if (level[j] != 0)return;
	if (level[newIndex[j]] != 0) {
		level[j] = level[newIndex[j]]+1;
		return;
	}

	if (level[newIndex[j]] == 0 && newIndex[j] != k) {
		//cout << "Run" << endl;
		findLevel(newIndex[j], j);
		level[j] =level[newIndex[j]]+1;
	}
	else {
		if (newIndex[j] == k) {
			level[j] = 1;
		}
		//root1[j] = root1[newIndex[j]];
		return;
	}
}


void matching::counting() {
	int amount[v] = {0};
	int amountOfTree = 0;
	double averageTreeSize = 0;
	double maxTree = 0;
	double sum = 0;
	double sumDeepth = 0;
	double averageTreeDepth = 0;
	double deepestTree = 0;
	int treeDepth[v] = { 0 };


	for (int i = 0; i < v; i++) {
		amount[root1[i]-1]++;
	}//counting every tree

	for (int i = 0; i < v; i++) {
		if (amount[i] != 0) {
			amountOfTree++;
		}
	}

	for (int i = 0; i < v; i++) {
		if (maxTree < amount[i]) {
			maxTree = amount[i];
		}
	}//find the max size tree

	for (int i = 0; i < v; i++) {
		int temp = root1[i];
		if (treeDepth[temp] < level[i]) {
			treeDepth[temp] = level[i];
		}
	}//find the depth for each tree
	for (int i = 0; i < v; i++) {
		sumDeepth += treeDepth[i];
	}
	averageTreeDepth = sumDeepth / amountOfTree;

	for (int i = 0; i < v; i++) {
		sum += amount[i];
	}
	averageTreeSize = sum / amountOfTree;//find the average tree size

	for (int i = 0; i < v; i++) {
		if (deepestTree < level[i]) {
			deepestTree = level[i];
		}
	}//find the deepest tree level

	


	cout << "There are " << amountOfTree << " trees in the graph" << endl;
	cout << "The average tree size is " << averageTreeSize << endl;
	cout << "The max tree size is " <<maxTree<< endl;
	cout << "The deepest tree depth is " << deepestTree << endl;
	cout << "The average tree depth is " << averageTreeDepth << endl;
	/*for (int i = 0; i < amountOfTree; i++) {
		cout << "The " << i+1 << " tree has " << amount[i] << " node" << endl;
	}*/

}
