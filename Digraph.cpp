//有向图的相关算法

#include<vector>
#include<stack>

using namespace std;

//有向图的表示,为了算法描述便利
class Digraph
{
public:
	Digraph(int V);
	int V();
	int E();
	void addEdge(int v, int w);
	std::vector<int> adj(int v);
  Digraph reverse();
	~Digraph();
private:
	int V;
	int E;
	vector<vector<int>> adj;
};

//有向环的判断
class DirectedCycle {
private:
  vector<bool> marked;
  std::vector<int> edgeTo;
  std::vector<int> cycle;
  std::vector<bool> onStack;
public:
  DirectedCycle(Digraph& G)
  {
    int V = G.V();
    marked.resize(V,false);
    edgeTo.resize(V,0);
    onStack.resize(V,false);
    for (int v = 0; v < V; ++v) {
      if (!marked[v])
        dfs(G,v);
    }
  }
  bool hasCycle() {
    return (cycle.size() != 0);
  }
  std::vector<int> cycle() {
    return cycle;
  }
private:
  void dfs(Digraph& G, int v) {
    onStack[v] = true;
    marked[v] = true;
    std::vector<int> vs = G.adj(v);
    for (size_t i = 0; i < vs.size(); i++) {
      int w = vs[i];
      if (!marked[w]) {
        edgeTo[w] = v;
        dfs(G, w);
      }
      else if (onStack[w]) {
        for (int x = v; x != w; x = edgeTo[x]) {
          cycle.push_back(x);
        }
        cycle.push_back(w);
        cycle.push_back(v);
      }
    }
    onStack[v] = false;
  }
};

//图的前序遍历，后序遍历，逆后序遍历
class DepthFirstOrder {
private:
  vector<bool> marked;
  vector<int> pre;
  vector<int> post;
  stack<int> reversePost;
public:
  DepthFirstOrder(Digraph& G) {
    marked.resize(G.V(),false);
    for (int v = 0; v < G.V(); ++v) 
      if (!marked[i])
        dfs(G,v);
  }
  std::vector<int> pre() {
    return pre;
  }
  std::vector<int> post() {
    return post;
  }
  stack<int> reversePost() {
    return reversePost;
  }
private:
  void dfs(Digraph& G, int v) {
    marked[v] = true;
    pre.push_back(v);
    
    vector<int> vs = G.adj(v);
    for(size_t i = 0; i<vs.size; ++i) {
      int w = vs[i];
      if (!marked[w]) {
        dfs(G,w);
      }
    }

    post.push_back(v);
    reversePost.push(v)；
  }  
};

//有向无环图的拓扑排序
class Topological {
private:
  std::vector<int> order;
public:
  Topological(Digraph& G) {
    DirectedCycle cyclefinder(G);
    if (!cyclefinder.hasCycle()) {
      DepthFirstOrder dfs(G);
      stack<int> tmp = dfs.reversePost();
      while(!tmp.empty()) {
        order.push_back(tmp.top());
        tmp.pop();
      }
    }
  }
  std::vector<int> order() {
    return order;
  }
  bool isDAG() {
    return (order.size() != 0);
  }
};

//计算强连通分量的 Kosaraju 算法
class Kosaraju {
private:
  vector<bool> marked;
  vector<int> id;
  int count;
public:
  Kosaraju(Digraph& G) {
    int V = G.V();
    count = 0;
    marked.resize(V,false);
    id.resize(V,-1);
    Topological topo_order(G.reverse());
    vector<int> order = topo_order.order();
    for (int i = 0; i < V; ++i) {
      int v = order[i];
      if (!marked[v]) {
        dfs(G,v);
        count++;
      }
    }
  }
  bool stronglyConnected(int v, int w) {
    return id[v] == id[w];
  }
  int id(int v) {
    return id[v];
  }
  int count() {
    return count;
  }
private:
  void dfs(Digraph& G, int v) {
    marked[v] = true;
    id[v] = count;
    vector<int> vs = G.adj(v);
    for (size_t i = 0; i<vs.size(); ++i) {
      int w = vs[i];
      if (!marked[w]) {
        dfs(G,w);
      }
    }
  }
};

//最小生成树 Prim即时版本的算法

