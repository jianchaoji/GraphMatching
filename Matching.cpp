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

	

	//initialize the graph
	while (rFile >> s) {

		if (l < 2) {
			l++;
			continue;
		}
		else {
			if (i % 3 == 2) {
				position = stringToNum<int>(s)-1;
				degree[position]++;
			}
			else if (i % 3 == 1) {
				index[lines] = stringToNum<int>(s)-1;
				weight[lines] = rand() % 500;
			//	lines++;
				
			}
			else if (i % 3 == 0) {
				//weight[lines] = stringToNum<double>(s);
				lines++;
			}
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

void matching::writeFile() {
	wFile.open("temp.txt");
	int position = 0;
	for (int i = 0; i < e; i++) {//edges
		int temp = 0;
		if (position + 1 < v) {
			while (i >= offset[position + 1])position++;
		}
		wFile << index[i]+1 << " "<<position+1<<" "<<weight[i] << endl;
	}
}

void matching::reReadFile() {
	string s;
	int l = 0;
	int i = 1;
	int position;
	int lines = 0;
	int row, col;
	rFile.open("temp.txt");

	//initialize the graph
	while (rFile >> s) {

		
			if (i % 3 == 1) {
				position = stringToNum<int>(s) - 1;
				degree[position]++;
			}
			else if (i % 3 == 2) {
				index[lines] = stringToNum<int>(s) - 1;
				/*weight[lines] = rand() % 5000;
				lines++;*/

			}
			else if (i % 3 == 0) {
				weight[lines] = stringToNum<double>(s);
				lines++;
			}
			i++;		
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

/*
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
                                if(max==weight[j]){
                                  for(int k=0;k<v;k++){
                                  if(offset[k]>j){
                                   if(position>k-1)
                                   position=k-1;
                                   break;
                                      }
                                 }
                                  }
				if (max < weight[j]) {//make sure each vertex pick the adjacent with smaller label
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

      }
*/
void matching::verify() {
	for (int i = 0; i < v; i++) {
		//if(i==24619||i==34087||i==45450)continue;
                findRoot(i, -1);
                //cout<<"this is the "<<i<<" times"<<endl; 
	}
	/*
	//verify the result
	for (int i = 0; i < v; i++) {
		cout << root1[i] << endl;
	}*/
}

void matching::findRoot(int j,int k) {
	
        // cout<<"The j,k is"<<j<<" "<<k<<endl;
         /*if(j==24619||j==34087||j==45450){
              root1[j]=1;
              return;
            }*/ 

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



void matching::maxWeight() {
	
	for (int i = 0; i < v; i++) {//find the max adjacent vertex for each vertex;
		int position = -1;
		int max = -1;
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
			//	cout<<"start match vertex"<<i<<endl;
				if(flag[index[temp]]!=-1){
				position = index[temp];//update the max end point;
			//	cout<<"The position is : "<< position<<endl;
				max = weight[temp];//update the max edge;
				}
			}
			temp++;
		}

	//	for (int j = 0; j < e; j++) {//find the other possible vertex;
	//		if (index[j] != i)continue;
	//		else {
	//			if (max < weight[j]) {
	//				max = weight[j];
	//				for (int k = 0; k < v; k++) {//update the position
	//					if (offset[k] > j) {
	//						position = k - 1;//update finished
	//						break;
	//					}
	//				}
	//			}
	//		}
	//	}

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


void matching::counting(char *inputFile) {
	

	int amountOfTree = 0;
	double averageTreeSize = 0;
	double maxTree = 0;
	double sum = 0;
	double sumDeepth = 0;
	double averageTreeDepth = 0;
	double deepestTree = 0;



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
		if (treeDepthA[temp] < level[i]) {
			treeDepthA[temp] = level[i];
		}
	}//find the depth for each tree
	for (int i = 0; i < v; i++) {
		sumDeepth += treeDepthA[i];
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

	
	oResult.open("result.txt",ios::app);
	oResult<<"The name of the graph is "<< inputFile<<endl
		<<"There are "<<v<< " vertex "<< e <<" edges in the graph"<<endl
		<<"There are "<<amountOfTree<<" tree in the graph"<<endl
		<<"The average tree size is "<<averageTreeSize<<endl
		<<"The max tree size is "<<maxTree<<endl
		<<"The deepest tree depth is "<<deepestTree<<endl
		<<"The average tree depth is "<<averageTreeDepth<<endl<<endl<<endl<<endl;
	oResult.close();

	cout << "There are " << amountOfTree << " trees in the graph" << endl;
	cout << "The average tree size is " << averageTreeSize << endl;
	cout << "The max tree size is " <<maxTree<< endl;
	cout << "The deepest tree depth is " << deepestTree << endl;
	cout << "The average tree depth is " << averageTreeDepth << endl;
	/*for (int i = 0; i < amountOfTree; i++) {
		cout << "The " << i+1 << " tree has " << amount[i] << " node" << endl;
	}*/

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

