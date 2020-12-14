#include<iostream>
#include<vector>
using namespace std;

class node{
	int first_index;
	int weight;
	int last_index;
public:
	node(int firstVertex,int SecondVertex,int weight=1)
	{
		first_index=firstVertex;
		last_index=SecondVertex;
		this->weight=weight;
	}
	int put_first_index(){
		return first_index;
	}

	int put_second_index(){
		return last_index;
	}
};

class graph{

	int total_edges;
	int total_vertex;

	vector<string> vertex_list;
	vector<node*> edge_list;

public:
	graph(int vertex,int edges){
		total_vertex=vertex;
		total_edges=edges;
	}

	void getVertex(string);
	void getEdges(string,string);
	void insert_edge(int start_point,int end_point);
	void bfs_traversal();
};

void graph::insert_edge(int start_point,int end_point){
	
	node* temp=new node(start_point,end_point);
	edge_list.push_back(temp);
}

void graph::getVertex(string data){
		vertex_list.push_back(data);
	}

void graph::getEdges(string first_vertex,string second_vertex){
		int start_point=INT_MAX,end_point=INT_MAX;
		int i=0;
		while(start_point==INT_MAX || end_point==INT_MAX){
			if(first_vertex.compare(vertex_list[i])==0)
				start_point=i;
			if(second_vertex.compare(vertex_list[i])==0)
				end_point=i;
			i++;
		}
		insert_edge(start_point,end_point);
	}

	void graph::bfs_traversal(){	
	int i=0;
	// queue<int> q;
	bool visited[total_vertex];
	for(int i=0;i<total_vertex;i++)
		visited[i]=false;
	// q.push(i);
	node* temp=edge_list[i];
	while(i<total_edges){
		cout<<vertex_list[temp->put_first_index()]<<" -> ";
		cout<<vertex_list[temp->put_second_index()]<<" ";
		temp=edge_list[++i];
		cout<<"\n";
		}	
}		


int main(){
	int vertex,edges,choice=1,weight;
	string data,first_vertex,second_vertex;
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
			default: cout<<"enter right choice\n";
		case 2: g->bfs_traversal();
			break;
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