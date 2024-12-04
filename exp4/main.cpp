#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

// 图数据结构类
class Graph {
private:
    int numVertices;
    vector<vector<int>> adjMatrix;

public:
    Graph(int vertices) : numVertices(vertices), adjMatrix(vertices, vector<int>(vertices, 0)) {}

    // 添加边
    void addEdge(int src, int dest, int weight = 1) {
        adjMatrix[src][dest] = weight;
        adjMatrix[dest][src] = weight;  // 对于无向图，对称添加
    }

    int getNumVertices() const {
        return numVertices;
    }

    const vector<vector<int>>& getAdjMatrix() const {
        return adjMatrix;
    }
};

// 广度优先搜索（BFS）算法实现
void BFS(const Graph& graph, int startVertex) {
    int numVertices = graph.getNumVertices();
    vector<bool> visited(numVertices, false);
    queue<int> q;

    visited[startVertex] = true;
    q.push(startVertex);

    while (!q.empty()) {
        int currentVertex = q.front();
        q.pop();
        cout << currentVertex << " ";

        const vector<int>& neighbors = graph.getAdjMatrix()[currentVertex];
        for (int i = 0; i < numVertices; ++i) {
            if (neighbors[i] > 0 &&!visited[i]) {
                visited[i] = true;
                q.push(i);
            }
        }
    }
    cout << endl;
}

// 深度优先搜索（DFS）算法实现
void DFSUtil(const Graph& graph, int vertex, vector<bool>& visited) {
    visited[vertex] = true;
    cout << vertex << " ";

    const vector<int>& neighbors = graph.getAdjMatrix()[vertex];
    for (int i = 0; i < graph.getNumVertices(); ++i) {
        if (neighbors[i] > 0 &&!visited[i]) {
            DFSUtil(graph, i, visited);
        }
    }
}

// DFS接口函数
void DFS(const Graph& graph, int startVertex) {
    vector<bool> visited(graph.getNumVertices(), false);
    DFSUtil(graph, startVertex, visited);
    cout << endl;
}

// 迪杰斯特拉算法实现（最短路径）
vector<int> dijkstra(const Graph& graph, int startVertex) {
    int numVertices = graph.getNumVertices();
    vector<int> dist(numVertices, INT_MAX);
    vector<bool> finalized(numVertices, false);

    dist[startVertex] = 0;

    for (int count = 0; count < numVertices - 1; ++count) {
        int minDist = INT_MAX, minIndex = -1;

        // 找到未确定最短路径且距离最小的顶点
        for (int v = 0; v < numVertices; ++v) {
            if (!finalized[v] && dist[v] <= minDist) {
                minDist = dist[v];
                minIndex = v;
            }
        }

        finalized[minIndex] = true;

        // 更新相邻顶点的距离
        const vector<int>& neighbors = graph.getAdjMatrix()[minIndex];
        for (int i = 0; i < numVertices; ++i) {
            if (neighbors[i] > 0 &&!finalized[i] && dist[minIndex]!= INT_MAX 
                && dist[minIndex] + neighbors[i] < dist[i]) {
                dist[i] = dist[minIndex] + neighbors[i];
            }
        }
    }

    return dist;
}

// 普里姆算法实现（最小支撑树）
Graph primMST(const Graph& graph) {
    int numVertices = graph.getNumVertices();
    vector<bool> inMST(numVertices, false);
    Graph mst(numVertices);

    // 从第一个顶点开始
    inMST[0] = true;

    for (int edgeCount = 0; edgeCount < numVertices - 1; ++edgeCount) {
        int minWeight = INT_MAX, start = -1, end = -1;
        for (int i = 0; i < numVertices; ++i) {
            if (inMST[i]) {
                const vector<int>& neighbors = graph.getAdjMatrix()[i];
                for (int j = 0; j < numVertices; ++j) {
                    if (!inMST[j] && neighbors[j] > 0 && neighbors[j] < minWeight) {
                        minWeight = neighbors[j];
                        start = i;
                        end = j;
                    }
                }
            }
        }

        mst.addEdge(start, end, minWeight);
        inMST[end] = true;
    }

    return mst;
}

// BFS测试案例
void testBFS() {
    Graph g(6);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 4);
    g.addEdge(3, 5);
    g.addEdge(4, 5);

    cout << "BFS starting from vertex 0: ";
    BFS(g, 0);
}

// DFS测试案例
void testDFS() {
    Graph g(6);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 4);
    g.addEdge(3, 5);
    g.addEdge(4, 5);

    cout << "DFS starting from vertex 0: ";
    DFS(g, 0);
}

// 最短路径（迪杰斯特拉算法）测试案例
void testDijkstra() {
    Graph g(5);
    g.addEdge(0, 1, 4);
    g.addEdge(0, 2, 2);
    g.addEdge(1, 3, 5);
    g.addEdge(2, 1, 1);
    g.addEdge(2, 3, 8);
    g.addEdge(2, 4, 10);
    g.addEdge(3, 4, 2);

    vector<int> distances = dijkstra(g, 0);
    cout << "Shortest distances from vertex 0: ";
    for (int i = 0; i < distances.size(); ++i) {
        cout << distances[i] << " ";
    }
    cout << endl;
}

// 最小支撑树（普里姆算法）测试案例
void testPrimMST() {
    Graph g(5);
    g.addEdge(0, 1, 2);
    g.addEdge(0, 3, 6);
    g.addEdge(1, 2, 3);
    g.addEdge(1, 3, 8);
    g.addEdge(1, 4, 5);
    g.addEdge(2, 4, 7);
    g.addEdge(3, 4, 9);

    Graph mst = primMST(g);
    cout << "Minimum Spanning Tree edges: " << endl;
    const vector<vector<int>>& adjMatrix = mst.getAdjMatrix();
    for (int i = 0; i < g.getNumVertices(); i++) {
        for (int j = i + 1; j < g.getNumVertices(); j++) {
            if (adjMatrix[i][j] > 0) {
                cout << i << " - " << j << " : " << adjMatrix[i][j] << endl;
            }
        }
    }
}

int main() {
    testBFS();
    testDFS();
    testDijkstra();
    testPrimMST();
    //getchar();
    return 0;
}