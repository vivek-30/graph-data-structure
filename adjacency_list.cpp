#include<iostream>
#include<vector>
#include<queue>
#define Max_Size 20
using namespace std;

class node{

	int index;
	int weight;
	node* next;
public:
	node(int vertex,int weight=1)
	{
		index=vertex;
		this->weight=weight;
		next=NULL;
	}
	void getNext(node* temp){
		next=temp;
	}

	node* putNext(){
		return next;
	}	
	int putindex(){
		return index;
	}
};

class graph{

	int total_edges;
	int total_vertex;

	vector<string> vertex_list;
	node **adjacency_list;

public:
	graph(int vertex,int edges){
		total_vertex=vertex;
		total_edges=edges;
		adjacency_list=new node*[vertex];
		for(int i=0;i<Max_Size;i++)
		adjacency_list[i]=0;
	}

	void getVertex(string);
	void getEdges(string,string);
	void insert_edge(int start_point,int end_point);
	void bfs_traversal();
};

void graph::insert_edge(int start_point,int end_point){
	if(!adjacency_list[start_point])
	adjacency_list[start_point]=new node(end_point);
	else{
		node* temp;
		temp=adjacency_list[start_point];
		while(temp->putNext()!=NULL){
			temp=temp->putNext();
		}
		temp->getNext(new node(end_point));
	}
}

void graph::bfs_traversal(){
	
	int i=0;
	queue<int> q;
	bool visited[total_vertex];
	for(int i=0;i<total_vertex;i++)
		visited[i]=false;
	q.push(i);
	node* temp=adjacency_list[i];
	while(i<total_vertex){
		cout<<vertex_list[i]<<" -> ";
		while(temp){
		cout<<vertex_list[temp->putindex()]<<" ";
		temp=temp->putNext();
		}
		temp=adjacency_list[++i];
		cout<<"\n";
		}	
}		

void graph::getVertex(string data){
		vertex_list.push_back(data);
	}

void graph::getEdges(string first_vertex,string second_vertex){
		int start_point=INT_MAX,end_point=INT_MAX;
		int i=0;
		while((start_point==INT_MAX || end_point==INT_MAX)&& !vertex_list.empty()){
			if(first_vertex.compare(vertex_list[i])==0)
				start_point=i;
			if(second_vertex.compare(vertex_list[i])==0)
				end_point=i;
			i++;
		}
		insert_edge(start_point,end_point);
	}


int main(){
	int vertex,edges,choice=1,weight;
	string data,first_vertex,second_vertex;
		// cout<<"if you wanted to add a weight to a edge then you are free to do that\n";
							cout<<"enter total number vertex and edges\n";
							cin>>vertex>>edges;
							graph *g=new graph(vertex,edges);
	cout<<"	Enter your choice\n0.Exit\n1.build a graph\n2.traverse a graph\n3.find shortest find\n4.check if 2 vertex are connected or not\n";;
	cin>>choice;
	while(choice){

	switch(choice){
		case 0: return 0;
		case 1: 
					 cout<<"enter string(data) of "<<vertex<<" vertices\n";
					for(int i=0;i<vertex;i++){
						cin>>data;
						g->getVertex(data);
						}
					cout<<"enter 2 vertex(strings) that represents an edge\n";
					for(int i=0;i<edges;i++){
						cin>>first_vertex>>second_vertex;
						g->getEdges(first_vertex,second_vertex);
						}
						break;
		 case 2: g->bfs_traversal();
		 break;
			// break;
			// case 3: shortest_path();
			// break;
			// case 4: check_connection();
			// break;
			// default: cout<<"enter right choice\n";
		}
		cout<<"enter your choice\n";
		cin>>choice;
	}
	return 0;

}