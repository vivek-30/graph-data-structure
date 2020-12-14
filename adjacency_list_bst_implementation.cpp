#include<iostream>
#include<vector>
#define Max_Size 20
using namespace std;

class BSTnode{

	int index;
	int weight;
	BSTnode* left;
	BSTnode* right;
public:
	BSTnode(int vertex)
	{
		index=vertex;
		weight=1;
		left=right=NULL;
	}
	void getleft(BSTnode* temp){
		left=temp;
	}

	BSTnode* putleft(){
		return left;
	}	

	void getright(BSTnode* temp){
		right=temp;
	}

	BSTnode* putright(){
		return right;
	}	

	void getweight(int weight){
		this->weight=weight;
	}
	int putindex(){
		return index;
	}
};

class graph{

	int total_edges;
	int total_vertex;

	vector<string> vertex_list;
	BSTnode **adjacency_list;

public:
	graph(int vertex,int edges){
		total_vertex=vertex;
		total_edges=edges;
		adjacency_list=new BSTnode*[vertex];
		for(int i=0;i<vertex;i++)
		adjacency_list[i]=0;
	}

	void getVertex(string);
	void getEdges(string,string,int);
	void insert_edge(int ,int,int);
	BSTnode* bst_insert(BSTnode*,int,int);
};

BSTnode* graph::bst_insert(BSTnode* first_vertex,int end_point,int weight=1){
	if(!first_vertex){
		BSTnode* temp=new BSTnode(end_point);
		temp->getweight(weight);
		return temp;
	}
	else
		if(first_vertex->putindex()>=end_point)
			first_vertex->getleft(bst_insert(first_vertex->putleft(),end_point,weight));
		else
			first_vertex->getright(bst_insert(first_vertex->putright(),end_point,weight));
		return first_vertex;
}


void graph::insert_edge(int start_point,int end_point,int weight){	
		BSTnode* temp;
		temp=adjacency_list[start_point];
		adjacency_list[start_point]=bst_insert(temp,end_point,weight);
	}

void graph::getVertex(string data){
		vertex_list.push_back(data);
	}

void graph::getEdges(string first_vertex,string second_vertex,int weight){
		int start_point=INT_MAX,end_point=INT_MAX;
		int i=0;
		while((start_point==INT_MAX || end_point==INT_MAX)&& !vertex_list.empty()){
			if(first_vertex.compare(vertex_list[i])==0)
				start_point=i;
			if(second_vertex.compare(vertex_list[i])==0)
				end_point=i;
			i++;
		}
		insert_edge(start_point,end_point,weight);
	}


int main(){
	int vertex,edges,choice=1,weight;
	string data,first_vertex,second_vertex;

	cout<<"	Enter your choice\n0.Exit\n1.build a graph\n2.traverse a graph\n3.find shortest find\n4.check if 2 vertex are connected or not\n";;
	cin>>choice;
	while(choice){

	switch(choice){
		case 0: return 0;
		case 1: 
		cout<<"if you wanted to add a weight to a edge then you are free to do that\n";
		cout<<"enter total number vertex and edges\n";
			cin>>vertex>>edges;
			graph *g=new graph(vertex,edges);
		 cout<<"enter string(data) of "<<vertex<<" vertices\n";
		for(int i=0;i<vertex;i++){
			cin>>data;
			g->getVertex(data);
			}
		cout<<"enter 2 vertex(strings) that represents an edge and also enter weight of the edge\n";
		for(int i=0;i<edges;i++){
			cin>>first_vertex>>second_vertex;
			cin>>weight;
			g->getEdges(first_vertex,second_vertex,weight);
			}
			break;
			// default: cout<<"enter right choice\n";
		// case 2: traverse();
			// break;
			// case 3: shortest_path();
			// break;
			// case 4: check_connection();
			// break;
			
		}
		cout<<"enter your choice\n";
		cin>>choice;
	}
	return 0;

}