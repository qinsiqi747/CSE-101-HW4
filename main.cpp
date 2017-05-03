#include <iostream>
#include <cstdlib>
#include <random>
#include <queue>
#include <vector>
#include <unordered_set>
// Use AdjList to find a set of node

using namespace std;

struct AdjListNode
{
    int dest;
    struct AdjListNode* next;
};

struct AdjList
{
    struct AdjListNode *head;
};

class Graph
{
    private:
        int V;
    public:
        vector<int> neighbors;
        struct AdjList* array;
        Graph(int V)
        {
            this->V = V;
            array = new AdjList [V];
            for (int i = 0; i < V; ++i)
            {
                array[i].head = NULL;
                neighbors.push_back(0);
            }
        }
/*
       * Creating New Adjacency List Node        */
        AdjListNode* newAdjListNode(int dest)
        {
            AdjListNode* newNode = new AdjListNode;
            newNode->dest = dest;
            newNode->next = NULL;
            return newNode;
        }
        /*
        * Adding Edge to Graph
       */
        void addEdge(int src, int dest)
        {
            AdjListNode* newNode = newAdjListNode(dest);
            newNode->next = array[src].head;
            array[src].head = newNode;
/*            newNode = newAdjListNode(src);
            newNode->next = array[dest].head;
            array[dest].head = newNode;
            */
            neighbors[src]++;
        }
        /*
      * Print the graph
       */
        void printGraph()
        {
            int v;
            for (v = 0; v < V; ++v)
            {
                AdjListNode* pCrawl = array[v].head;
                cout<<"\n Adjacency list of vertex "<<v<<"\n head ";
                while (pCrawl)
                {
                    cout<<"-> "<<pCrawl->dest;
                    pCrawl = pCrawl->next;
                }
                cout<<endl;
            }
        }
};

int main()
{
    int N = 2048;
    Graph gh(N);
    for(int i = 0;i < N;i++)
        for(int j = i+1;j < N;j++)
            if(rand()%2)
            {
                gh.addEdge(i,j);
                gh.addEdge(j,i);
                //cout<<i<<" "<<j<<endl;
                //cout<<gh.neighbors[i]<<" "<<gh.neighbors[j]<<endl;
                //cout<<endl;
            }

    //cout<<endl;
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> p;
    pair<int,int> a;
    for(int i = 0;i < N; i++)
    {
        a = make_pair(gh.neighbors[i],i);
        p.push(a);
        //cout<<i<<" "<<gh.neighbors[i]<<endl;
    }
    //cout<<endl;
    unordered_set<int> visited;
    vector<int> I;
    while(p.size())
    {
        a = p.top();
        if(visited.find(a.second) != visited.end())
            p.pop();
        else{
            I.push_back(a.second);
            for(AdjListNode* x = gh.array[a.second].head;x!=nullptr;x = x->next)
                visited.insert(x->dest);
            p.pop();
        }
    }
    //for(int i = 0;i < I.size();i++)
        //cout<<I[i]<<endl;

    cout << N <<" "<<I.size()<<endl;
    return 0;
}
