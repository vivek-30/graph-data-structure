#include<iostream>
#include<list>
#include<set>
using namespace std;

class graph{

	list<pair<int,int> > *adjlist;
	int vertex;

public:
	graph(int v){
		vertex=v;
		adjlist=new list<pair<int ,int> >[v];
	}
	void insert(int,int,int,bool);
	void printlist();
	void bfs(int);
	void dfs(int,bool*);
	void dfs_util(int);
	void topological_sort(int,bool*,list<int>&);
	void topological_sort_util(int);
	void dijkstra_util(int);
	void dijkstra(int,int*);
	void bellman_ford(int);
	void kruskal(int);
	void prims(int);
	int* indegree(int);
	void kahn(int);
	void genode(list<int>&,int*,int,int,bool*);
	void kosaraju_util(int);
	list<pair<int,int> >* transpose_graph(int);
	void shortest_path_bfs_util(int,int);
	bool shortest_path_bfs(int,int,int*,bool*,int&);
	bool is_cyclic_directed(int,bool*);
	void is_cyclic_undirected_util(int);
	bool is_cyclic_undirected(int,int,bool*);
};

class graph_node{
public:
	int source;
	int destination;
	int weight;

	graph_node(){
		source=destination=weight=0;
	}
};

class union_find{

	int* parent;
public:
	union_find(int size){
		parent=new int[size];
		for(int i=0;i<size;i++)
			parent[i]=-1;

	}
	int search(int);
	bool combine(int,int);
};

int union_find::search(int vertex){
	if(vertex<0)
		return -1;

	if(parent[vertex]<0)
		return vertex;

	int store=search(parent[vertex]);
	parent[vertex]=store;
	return store;
}

bool union_find::combine(int vertex1,int vertex2){
	if(vertex1<0 || vertex2<0)
		return false;

	int parent1=search(vertex1);
	int parent2=search(vertex2);
	if(parent1==parent2)
		return false;

	if(parent1<=parent2){
		parent[parent1]+=parent[parent2];
		parent[parent2]=parent1;
	}
	else{
		parent[parent2]+=parent[parent1];
		parent[parent1]=parent2;
		}

		return true;
}

void graph::insert(int first,int second,int weight=1,bool is_undirected=false){

		adjlist[first].push_back(make_pair(second,weight));
		if(is_undirected)
			adjlist[second].push_back(make_pair(first,weight));
}

void graph::printlist(){

	for(int i=0;i<vertex;i++){
		cout<<i<<" -> ";
		list<pair<int ,int> >::iterator it=adjlist[i].begin();
		for(;it!=adjlist[i].end();it++){
			cout<<it->first<<"("<<it->second<<"),";
		}
		cout<<"\n";
	}
}

void graph::dijkstra(int start,int distance[]){

	multiset<pair<int,int> > s;
	multiset<pair<int,int> >::iterator it;
	list<pair<int,int> >::iterator u;
		s.insert(make_pair(distance[start],start));
	for(int i=start;i<vertex;i++){
	it=s.begin();
	int min_vertex= it->second;
	s.erase(it);
	for(u=adjlist[min_vertex].begin();u!=adjlist[min_vertex].end();u++){
		if((distance[u->first]>distance[min_vertex]+u->second) and distance[min_vertex]!=INT_MAX){
			distance[u->first]=distance[min_vertex]+u->second;
			s.insert(make_pair(distance[u->first],u->first));
			}
		}
	}
}

void graph::dijkstra_util(int start){

	int *distance=new int[vertex];
	for(int i=0;i<vertex;i++)
		distance[i]=INT_MAX;
	distance[start]=0;

	dijkstra(start,distance);
	cout<<"shortest path is :\n";
	for(int i=start;i<vertex;i++)
		cout<<start<<" -> "<<i<<" => "<<distance[i]<<endl;

	delete[] distance;
}

void graph::bfs(int starting_vertex){

	bool visited[vertex];
	for(int i=0;i<vertex;i++)
		visited[i]=false;
	list<int> queue;
	int s;
	list<pair<int,int> >::iterator it;

	queue.push_back(starting_vertex);
	while(!queue.empty()){
		s=queue.front();
		queue.pop_front();
		cout<<s<<" ";
		visited[s]=true;
		it=adjlist[s].begin();
		while(it!=adjlist[s].end()){
			if(!visited[it->first]){
			queue.push_back(it->first);
			visited[it->first]=true;
			}
			it++;
		}
	}
}

void  graph::dfs(int vertex,bool isvisited[]){

		isvisited[vertex]=true;
		cout<<vertex<<" ";

		list<pair<int,int> >::iterator it;
		for(it=adjlist[vertex].begin();it!=adjlist[vertex].end();it++){
			if(!isvisited[it->first])
				dfs(it->first,isvisited);
		}
	}

void graph::dfs_util(int start){

	bool* isvisited=new bool[vertex];
	for(int i=0;i<vertex;i++){
		isvisited[i]=false;
	}

	// for(int i=start;i<vertex;i++)
	// 	if(!isvisited[i]){
	// 		cout<<endl;
			// dfs(i,isvisited); only for dfs

			// for cycle detection
			if(is_cyclic_directed(start,isvisited))
				cout<<"yes graph contains a cycle\n";
			else
				cout<<"No graph do not contain a cycle\n";
		// }	

	delete[] isvisited;
}

	int* graph::indegree(int start){
		int *degree=new int[vertex];
		for(int i=0;i<vertex;i++){
			degree[i]=0;
		}

		list<pair<int,int> >::iterator it;
		for(int i=start;i<vertex;i++){
			for(it=adjlist[i].begin();it!=adjlist[i].end();it++){
				degree[it->first]++;
			}
		}
		return degree;
	}

	void getnode(list<int>& queue,int *indegree,int vertex,int start,bool *is_visited){
			for(int i=start;i<vertex;i++)
				if(indegree[i]==0 and is_visited[i]==false){
					queue.push_back(i);
					is_visited[i]=true;
				}
	}

	void graph::kahn(int start){

		int* degree=indegree(start);

		bool *visited=new bool[vertex];
		for(int i=0;i<vertex;i++)
			visited[i]=false;
		list<int> queue;
		int count=0,temp;
		int* sol=new int[vertex];
		getnode(queue,degree,vertex,start,visited);

		list<pair<int,int> >::iterator it;
		while(not queue.empty()){
			temp=queue.front();
			queue.pop_front();
			sol[count++]=temp;
			for(it=adjlist[temp].begin();it!=adjlist[temp].end();it++)
				if(degree[it->first])
					degree[it->first]--;
			getnode(queue,degree,vertex,start,visited);
		}

		if(count==vertex-1){
		cout<<"topological sort: ";
			for(int i=0;i<vertex-1;i++)
				cout<<sol[i]<<" ";
			cout<<endl;
		}
		else
			cout<<"given graph contains a cycle\n";
		delete [] sol;
		delete [] visited;
		delete [] degree;
		return;
	}

	void graph::topological_sort(int start,bool *isvisited,list<int>& stack){

		isvisited[start]=true;

		list<pair<int,int> >::iterator it=adjlist[start].begin();
		for(;it!=adjlist[start].end();it++){
			if(!isvisited[it->first])
				topological_sort(it->first,isvisited,stack);

		}
		stack.push_front(start);
	}


	void graph::topological_sort_util(int start){

	bool* isvisited=new bool[vertex];
	for(int i=0;i<vertex;i++){
		isvisited[i]=false;
	}
	list<int> stack;

	for(int i=start;i<vertex;i++)
		if(!isvisited[i])
			topological_sort(i,isvisited,stack);

	while(!stack.empty()){
		cout<<stack.front()<<" ";
		stack.pop_front();
	}
	cout<<endl;

	delete[] isvisited;

	}


	void graph::kruskal(int start){

	multiset<pair<int,pair<int,int> > > s;
	multiset<pair<int,pair<int,int> > >::iterator it;
	list<pair<int,int > >::iterator ll;
	graph_node* arr=new graph_node[vertex-1];
	union_find *uf=new union_find(vertex);
	for(int i=start;i<vertex;i++){
		for(ll=adjlist[i].begin();ll!=adjlist[i].end();ll++){
		s.insert(make_pair(ll->second,make_pair(i,ll->first)));
		}
	}
	int j=0;
	while(not s.empty() and j<vertex-1){
		it=s.begin();
		if(uf->combine(it->second.first,it->second.second)){
			arr[j].source=it->second.first;
			arr[j].destination=it->second.second;
			arr[j].weight=it->first;
			j++;
		}
		s.erase(it);
	}

	cout<<"source\t  destination\t   weight\n";
	for(int i=0;i<vertex-1;i++){
		cout<<arr[i].source<<"\t\t"<<arr[i].destination<<"\t\t"<<arr[i].weight<<endl;
	}

	delete[] arr;
	delete uf;
	}

	void graph::prims(int start){

	graph_node* arr=new graph_node[vertex];
	bool *isvisited = new bool[vertex];
	int *distance = new int[vertex];
	for(int i=0;i<vertex;i++){
		distance[i]=INT_MAX;
		isvisited[i]=false;
	}
	distance[start]=0;
	multiset<pair<int,pair<int,int> > > s;
	multiset<pair<int,pair<int,int> > >::iterator it;
	s.insert(make_pair(distance[start],make_pair(-1,start)));
	list<pair<int,int> >::iterator ll;
	int j=0;

	for(int i=start;i<vertex;i++){
		it=s.begin();
				arr[j].source=it->second.first;
				arr[j].destination=it->second.second;
				arr[j].weight=it->first;
				j++;
		isvisited[it->second.second]=true;
	for(ll=adjlist[it->second.second].begin();ll!=adjlist[it->second.second].end();ll++){

			if(distance[ll->first]>ll->second and not isvisited[ll->first]){
				distance[ll->first]=ll->second;
				s.insert(make_pair(distance[ll->first],make_pair(it->second.second,ll->first)));
			}
		}
		s.erase(it);
	}

	cout<<"parent\t  destination\t   weight\n";
	for(int i=1;i<vertex;i++){
		cout<<arr[i].source<<"\t\t"<<arr[i].destination<<"\t\t"<<arr[i].weight<<endl;
	}

	delete[] isvisited;
	delete[] distance;
	delete[] arr;
	}

	void graph::bellman_ford(int start){

	int *dist=new int[vertex];
	for(int i=0;i<vertex;i++)
		dist[i]=INT_MAX;
	dist[start]=0;
	list<pair<int,int> >::iterator ll;
	multiset<pair<int,int> > s;
	multiset<pair<int,int> >::iterator it;
	s.insert(make_pair(dist[start],start));
	bool flag=false;

	// we only have traversse all the given edges (in any order) for |V|-1 times but in dijkstra algorithm
	// the order of edges/vertex matters there we select vertex with minimum weight and here we only operate on 
	// edges and not on vertex.
	 for(int count=start;count<=vertex-1;count++){
			for(int i=start;i<vertex;i++){
				for(ll=adjlist[i].begin();ll!=adjlist[i].end();ll++){
					if((dist[ll->first]>dist[i]+ll->second) and dist[i]!=INT_MAX){
						dist[ll->first]=dist[i]+ll->second;
						}
					}	
				}
			 }

	for(int i=start;i<vertex;i++){
		ll=adjlist[i].begin();
		while(ll!=adjlist[i].end()){
				if((dist[ll->first]>dist[i]+ll->second) and dist[i]!=INT_MAX){
					flag=true;
					break;
					}
					ll++;
				}
				if(flag)
					break;
	}

	if(flag){
		cout<<"graph contains a negative weight cycle\n";
	}
	else{
		cout<<"shortest path is :\n";
		for(int i=start;i<vertex;i++)
			cout<<start<<" -> "<<i<<" => "<<dist[i]<<endl;
		}
	delete[] dist;

	}

	list<pair<int,int> >* graph::transpose_graph(int start){

		list<pair<int,int> >* rev_graph=new list<pair<int,int> >[vertex];
		list<pair<int,int> >::iterator it;

		for(int i=start;i<vertex;i++){
			it=adjlist[i].begin();

			while(it!=adjlist[i].end()){
				rev_graph[it->first].push_back(make_pair(i,it->second));
				it++;
			}
		}
		return rev_graph;
	}

    void dfs_for_kosaraju(list<pair<int,int> >* graph,int vertex,bool isvisited[]){
		isvisited[vertex]=true;
			cout<<vertex<<" ";

		list<pair<int,int> >::iterator it;
		for(it=graph[vertex].begin();it!=graph[vertex].end();it++){
			if(!isvisited[it->first])
				dfs_for_kosaraju(graph,it->first,isvisited);
		}
	}

	void graph::kosaraju_util(int start){

		bool* isvisited=new bool[vertex];
		for(int i=0;i<vertex;i++)
			isvisited[i]=false;
		list<int> stack;

		for(int i=start;i<vertex;i++){
			if(!isvisited[i]){
			topological_sort(i,isvisited,stack);
			}
		}
		
		list<pair<int,int> >* rev_graph=transpose_graph(start);

		for(int i=0;i<vertex;i++)
			isvisited[i]=false;

		int node,count=0;
		cout<<"strongly connected components are";
		while(!stack.empty()){
			node=stack.front();
			stack.pop_front();
			if(not isvisited[node]){
			cout<<endl<<++count<<". ";
			dfs_for_kosaraju(rev_graph,node,isvisited);
			}
		}

		cout<<endl;
		// delete reversed graph
		for(int i=start;i<vertex;i++){
			while(not rev_graph[i].empty()){
				rev_graph[i].pop_back();
			}
		}

		delete[] rev_graph;
		delete[] isvisited;
	}

	bool graph::shortest_path_bfs(int node,int dest,int path[],bool isvisited[],int& i){

		// base case when we reach our destination vertex.
		if(node==dest){
			return true;
		}

		isvisited[node]=true;
		list<pair<int,int> >::iterator it;
		for(it=adjlist[node].begin();it!=adjlist[node].end();it++){
			if(!isvisited[it->first]){
				if(shortest_path_bfs(it->first,dest,path,isvisited,i)){
				path[i++]=it->first;
				return true;
				}
			}
		}

		return false;
	}

	void graph::shortest_path_bfs_util(int node,int dest){

		if(dest<0 or dest>=vertex or node<0 or node>=vertex)
			return;
		int J=0;
		bool* isvisited=new bool[vertex];
		for(int i=0;i<vertex;i++)
			isvisited[i]=false;
		int *path=new int[vertex];
		for(int i=0;i<vertex;i++)
			path[i]=-1;

		if(shortest_path_bfs(node,dest,path,isvisited,J)){
		cout<<"required path is :\n";
		path[J]=node;
		for(;J>=0;J--)
			cout<<path[J]<<" -> ";
		cout<<endl;
		}
		else 
			cout<<"path doesnot exists\n";

		delete[] isvisited;
		delete[] path;
	}

	bool graph::is_cyclic_directed(int node,bool* isvisited){

		if(isvisited[node])
			return true;

		isvisited[node]=true;
		list<pair<int,int> >::iterator it;
		for(it=adjlist[node].begin();it!=adjlist[node].end();it++){
				if(is_cyclic_directed(it->first,isvisited))
					return true;
				isvisited[it->first]=false;
		}
		
		return false;
	}

	void graph::is_cyclic_undirected_util(int node){

	bool* isvisited =new bool[vertex];
		for(int i=0;i<vertex;i++){
		isvisited[i]=false;
		}

		int parent=-1;

		if(is_cyclic_undirected(node,parent,isvisited))
			cout<<"yes cycle exists\n";
		else 
			cout<<"No cycle doesnot exist\n";

		delete[] isvisited;

	}

	bool graph::is_cyclic_undirected(int node,int parent,bool isvisited[]){

		isvisited[node]=true;

		list<pair<int,int> >::iterator it;
		for(it=adjlist[node].begin();it!=adjlist[node].end();it++){
			if(not isvisited[it->first]){
				if(is_cyclic_undirected(it->first,node,isvisited))
					return true;
			}
			else if(it->first!=parent)
				return true;
		}
			return false;
	}

	int main(){

	int weight=1,first,second,edges,choice,start,vertices,dest;
	bool is_directed=false,is_weighted=false;
	cout<<"enter 1 for undirected graph else 0 for directed graph\n";
	cin>>is_directed;
	cout<<"enter 1 for weighted graph else 0 for unweighted graph\n";
	cin>>is_weighted;
	cout<<"enter total no of  vertices and edges\n";
	cin>>vertices>>edges;
	graph *adjlist=new graph(vertices);
	cout<<"	Enter your choice\n0.Exit\n1.build a graph\n2.print a graph\n3.BFS traversal\n4.DFS traversal\n5.topological sorting"<<endl;
	cout<<"6.shortest path(dijkstra's algorithm)\n7.detect cycle\n7.kruskal's algorithm\n8.prim's algorithm\n9.bellman ford\n10.kahn algorithm\n";
	cout<<"11.kosaraju algorithm\n12.shortest path using BFS\n13.detect cycle in directed graph \n14.detect cycle in undirected graph\n";
	cin>>choice;
	while(choice){
	switch(choice){
		case 0: return 0;
		case 1: 
					 cout<<"enter 2 vertices that represents a edge\n";
					for(int i=0;i<edges;i++){
						cout<<"enter "<<i+1<<"th edge\n";
						cin>>first>>second;
						if(is_weighted){
							cout<<"enter weight\n";
							cin>>weight;
						}
						adjlist->insert(first,second,weight,is_directed);
						}
					break;
		 case 2: adjlist->printlist();
		 break;
		 case 3:
		 cout<<"enter starting vertex\n";
		 cin>>start;
		 adjlist->bfs(start);
		 break;
		 case 4:
		 cout<<"enter starting vertex\n";
		 cin>>start;
		 adjlist->dfs_util(start);
		 break;
		 case 5:
		 cout<<"enter starting vertex\n";
		 cin>>start;
		 adjlist->topological_sort_util(start);
		 break;
		 case 6: cout<<"enter starting node\n";
		 cin>>start;
		 adjlist->dijkstra_util(start);
		 break;
		 case 7:  cout<<"enter starting vertex\n";
		 cin>>start;
		 adjlist->kruskal(start);
		 break;
		 case 8: cout<<"enter starting vertex\n";
		 cin>>start;
		 adjlist->prims(start);
		 break;
		 case 9:cout<<"enter starting vertex\n";
		 cin>>start;
		 adjlist->bellman_ford(start);
		 break;
		case 10:cout<<"enter starting vertex\n";
		 cin>>start;
		 adjlist->kahn(start);
		 break;
		 case 11:cout<<"enter starting vertex\n";
		 cin>>start;
		 adjlist->kosaraju_util(start);
		 break;
		 case 12:cout<<"enter source and destination vertex\n";
		 cin>>start>>dest;
		 adjlist->shortest_path_bfs_util(start,dest);
		 break;
		 case 13:cout<<"enter starting vertex\n";
		 cin>>start;
		 adjlist->dfs_util(start);
		 break;
		 case 14:cout<<"enter starting vertex\n";
		 cin>>start;
		 adjlist->is_cyclic_undirected_util(start);
		 break;

		default: cout<<"enter right choice\n";
		}
		cout<<"enter your choice\n";
		cin>>choice;
	}
	return 0;

	}