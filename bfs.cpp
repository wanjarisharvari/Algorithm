#include <iostream>
#include <list>
#include <bits/stdc++.h>
using namespace std;

class graph{
    int v;
    vector <list <int>> adj;
    //bool* visited;

    public:
    graph(int v);
    void addedge(int v, int w);
    void bfs(int s);
};

graph::graph(int v){
    this->v=v;
    adj.resize(v);
}

void graph::addedge(int v,int w){
    adj[v].push_back(w);
}

void graph::bfs(int s){
    vector<bool> visited;
    visited.resize(v,false);
    list<int>queue;
    visited[s]=true;
    queue.push_back(s);
    while(!queue.empty()){

        s=queue.front();
        cout<< s << " ";
        queue.pop_front();

        for(auto adjacent : adj[s]){
            if(!visited[adjacent]){
                visited[adjacent] = true;
                queue.push_back(adjacent);
            }
        }
    }
}
int main(){
    graph g(4);
    g.addedge(0,1);
    g.addedge(0,2);
    g.addedge(1,2);
    g.addedge(2,0);
    g.addedge(2,3);
    g.addedge(3,3);
    cout<<"bfs : ";
    g.bfs(1);
    return 0;
}
