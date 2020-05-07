/*
 * @Author: verandert
 * @Date: 2020-05-03 13:53:58
 * @LastEditTime: 2020-05-08 01:12:50
 * @Description: main function
 */
#include "./include/graph.h"

int main(){
    VerType ver[] = {1,2,3,4,5.6,7.9}, arc[][3] = {{1, 2, 6}, {2, 1, 6}, {2, 3, 2}, {3, 2, 2}, {3, 4, 4}, {4, 3, 4}};
    int udarc[][3] = {{0,1,6}, {0,2,1}, {0,3,5}, {1,2,5}, {1,4,3}, {2,4,6}, {2,3,5}, {2,5,4}, {3,5,2}, {4,5,6}};
    enum bool visited[6];
    int len = 10, num = 6;;
    TNode tn[6];
    for (int i = 0; i < num; i++)
    {
        visited[i] = false;
    }
    Heap heap;
    //boolean visited[4];
    // OrtGraph G;
    // OrtGraph Gr;
    // G.arcnum = 6; G.vernum = 4;
    // Gr.arcnum = 6; Gr.vernum = 4;
    //CreateOG(&G, ver, arc);
    //MSTByPrim(&G);
    //CreateReverseOG(&Gr, ver, arc);
    //FSCCbyKosaraju(&G, &Gr, visited); 
    //DFSForest(&G, visited, &p);
    //DFSTraverse(&G, visited);
    //BFSTraverse(&G, visited);
    //DFSTraverseFSCC(&G, visited);
    InitHeap(heap, udarc, len);
    MSTbyKruskal(ver, heap, num, len, visited, tn);
    return 0;
}