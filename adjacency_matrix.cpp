#include<iostream>
#include<vector>

using namespace std;

class graph{

	int total_edges;
	int total_vertex;

	vector<string> vertex_list;
	int **matrix;
public:
	graph(int vertex,int edges){
		total_vertex=vertex;
		total_edges=edges;
		matrix=new int*[vertex];

		for(int i=0;i<vertex;i++)
			matrix[i]=new int[vertex];

		for(int i=0;i<vertex;i++)
			for(int j=0;j<vertex;j++)
				matrix[i][j]=INT_MIN;
	}

	void getVertex(string);
	void getEdges(string,string,int);
	void insert_edge(int,int,int);
	void traverse();
};

void graph::insert_edge(int start_point,int end_point,int weight=1){
	matrix[start_point][end_point]=weight;
	}


void graph::getVertex(string data){
		vertex_list.push_back(data);
	}

void graph::getEdges(string first_vertex,string second_vertex,int weight=1){
		int start_point=INT_MIN,end_point=INT_MIN;
		int i=0;
		while((start_point==INT_MIN|| end_point==INT_MIN)&& !vertex_list.empty()){
			if(first_vertex.compare(vertex_list[i])==0)
				start_point=i;
			if(second_vertex.compare(vertex_list[i])==0)
				end_point=i;
			i++;
		}
		insert_edge(start_point,end_point,weight);
	}

void graph::traverse(){
	for(int i=0;i<total_vertex;i++){
			cout<<vertex_list[i]<<" -> ";
		for(int j=0;j<total_vertex;j++){
			if(matrix[i][j]!=INT_MIN)
				cout<<vertex_list[j]<<" ("<<matrix[i][j]<<") "<<" ";
		}
		cout<<endl;
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
			cout<<"enter weight of the edge\n";
			cin>>weight;
			g->getEdges(first_vertex,second_vertex,weight);
			}
			break;
			default: cout<<"enter right choice\n";
		case 2: g->traverse();
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