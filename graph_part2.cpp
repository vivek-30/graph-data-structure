#include<iostream>
using namespace std;

#define INF INT_MAX
void print(int**,int);
void TSP(int**,int*,int,int,int&);

void floyd_warshall(int **graph,int V,int **distance){

	for(int i=0;i<V;i++)
		for(int j=0;j<V;j++)
			distance[i][j]=graph[i][j];

	for(int k=0;k<V;k++){
		for(int i=0;i<V;i++){
			for(int j=0;j<V;j++){
				if(distance[i][k]!=INF and distance[k][j]!=INF){
				if(distance[i][j]>distance[i][k]+distance[k][j])
					distance[i][j]=distance[i][k]+distance[k][j];
				}
			}
		}
	}

	return;
}

bool is_safe_color(int **graph,int *color,int v,int start,int pos,int colorCode){
	if(pos<0 or pos>=v)
		return false;

		for(int i=start;i<v;i++){
			if((graph[i][pos]==1 or graph[pos][i]==1) and (color[i]==colorCode))
				return false;
		}

		return true;
}

bool color_graph(int** graph,int v,int* color,int pos,int start,int maxColor){

	if(pos==v)
		return true;

	for(int shade=1;shade<v;shade++){
		if(is_safe_color(graph,color,v,start,pos,shade)){
				color[pos]=shade;
				if(color_graph(graph,v,color,pos+1,start,maxColor))
				return true;

				return false;
			}
		}
		return false;
}

bool is_safe_edge(int **graph,int* cycle,int V,int pos,int vertex){
	if(pos<0 || pos>=V)
		return false;

	int u,v;
	u=cycle[pos-1];
	v=vertex;
	
	for(int i=0;i<pos;i++)
		if(cycle[i]==vertex)
			return false;

	if(graph[u][v] or graph[v][u])
		return true;

	return false;
}

void find_hamiltonain_cycle(int **graph,int* cycle,int v,int start,int pos,int& min){
	if(pos==v){
		if(graph[cycle[pos-1]][start]){
			cycle[pos]=start;

		// only to print permutations

		// for(int node=start;node<v;node++){
		// 	cout<<cycle[node]<<" -> ";
		// 	}
		// 	cout<<cycle[v]<<endl;

			// for tsp problem
		  TSP(graph,cycle,start,v,min);
		}
		return;	
	}

	for(int node=start;node<v;node++){
		if(is_safe_edge(graph,cycle,v,pos,node)){
			cycle[pos]=node;
				find_hamiltonain_cycle(graph,cycle,v,start,pos+1,min);
		}
	}
	return;
}

void TSP(int **graph,int *cycle,int start,int v,int& min){

	int sum=0;
	int first,second;
	for(int i=start;i<v;i++){
		first=cycle[i];
		second=cycle[i+1];
		sum+=graph[first][second];
	}
	if(sum<min)
		min=sum;
}

int snake_ladder(int* board,int* path,int end){

	int min_steps=0,start=1,i=0,j,max=1;
	
	while(start<end){
		min_steps++;
		j=start;
		path[i++]=start;
		while(j<start+6 and j<end){
		if(board[j]>max)
				max=board[j];
			j++;
		}
		if(max==1)
			start=start+6;
		else
			start=max;
		if(start>=end){
			path[i]=start;
			return min_steps;
		}
		max=1;
	}
	path[i]=start;
	return min_steps;
}

void hamiltonain_cycle_util(int **graph,int v,int start){

	int* cycle=new int[v+1];
	int min=INF;

	for(int i=0;i<=v;i++)
		cycle[i]=0;

	cycle[start]=start;
	find_hamiltonain_cycle(graph,cycle,v,start,start+1,min);
	cout<<"minimum cost of travelling is : "<<min<<endl;
	delete[] cycle;
}

void graph_color_util(int** graph,int v,int start,int maxColor){

	int* color=new int[v];
	color[start]=1;

	if(color_graph(graph,v,color,start+1,start,maxColor)){
	cout<<"graph is colorable\n";
	for(int i=start;i<v;i++)
		cout<<color[i]<<" ";
	cout<<endl;
	}
	else
		cout<<"graph is not colorable\n";

	delete[] color;
}

void create(int **graph,int** distance,int v,int e,bool is_undirected,bool is_weighted,int weight=1){
	
	int first,second;
	cout<<"enter 2 vertices that representes an edge\n";
	for(int i=0;i<e;i++){
		cin>>first>>second;
			if(first>=v or second>=v)
				return;
			if(is_weighted){
				cout<<"enter weight\n";
				cin>>weight;
			}
			graph[first][second]=weight;
			if(is_undirected)
			graph[second][first]=weight;		
	}		
}

void print(int **graph,int V){
	for(int i=0;i<V;i++){
		for(int j=0;j<V;j++)
			if(graph[i][j]==INF)
				cout<<"INF\t";
			else
			cout<<graph[i][j]<<"\t";
		cout<<endl;
	}
}

int main()
{
int v,e,maxColor,start=0;
cout<<"enter total number of vertices and edges\n";
cin>>v>>e;

int **graph=new int*[v];
for(int i=0;i<v;i++)
graph[i]=new int[v];


// set all edges as -1 that is invalid
for(int i=0;i<v;i++){
	for(int j=0;j<v;j++){

	// for floyd warshall algorithm

	// 	if(i==j)
	// 	graph[i][j]=0;
	// else
	// 	graph[i][j]=INF;

		// for tsp problem
		graph[i][j]=0;
	}
}

int **distance=new int*[v];
for(int i=0;i<v;i++)
distance[i]=new int[v];

bool is_weighted,is_undirected=true;
cout<<"enter 1 for undirected graph and 0 directed\n";
cin>>is_undirected;
cout<<"enter 1 for weighted graph and 0 directed\n";
cin>>is_weighted;

create(graph,distance,v,e,is_undirected,is_weighted);
// cout<<"enter starting vertex\n";
// cin>>start;
// cout<<"enter total number of colors\n";
// cin>>maxColor;
// graph_color_util(graph,v,start,maxColor);
cout<<"enter starting vertex\n";
cin>>start;
hamiltonain_cycle_util(graph,v,start);

	/*
int* board=new int[36];
for(int i=0;i<36;i++)
	board[i]=1;
int* path=new int[36];
for(int i=0;i<36;i++)
	path[i]=1;


//ladder
board[2]=15;
board[9]=27;
board[25]=35;
board[5]=7;
board[18]=29;
//snake
board[34]=-22;
board[21]=-8;
board[17]=-13;
board[20]=-14; //1 15 29 30 36
board[32]=-2;
int total_steps=snake_ladder(board,path,36);
cout<<"min steps are : "<<total_steps<<endl;
for(int i=0;i<total_steps;i++)
	cout<<path[i]<<" ";
cout<<endl;
delete[] board;
board=NULL;
delete[] path;
path=NULL;
*/
// cout<<"adjacency matrix representation of graph is\n";
// print(graph,v);
// floyd_warshall(graph,v,distance);
// cout<<"shortest path for all pair of vertices are \n";
// print(distance,v);
return 0;
}