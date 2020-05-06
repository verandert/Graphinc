/*
 * @Author: verandert
 * @Date: 2020-05-03 13:53:58
 * @LastEditTime: 2020-05-06 13:43:13
 * @Description: main function
 */
#include "./include/graph.h"

int main(){
    VerType ver[] = {1,2,3,4,5,6}, arc[][2] = {{1,2}, {1,3}, {2, 4}, {3, 2}, {3, 4}, {4, 1}, {5, 6}};
    enum bool visited[6];
    for (int i = 0; i < 6; i++)
    {
        visited[i] = false;
    }
    //boolean visited[4];
    OrtGraph G;
    OrtGraph Gr;
    G.arcnum = 7; G.vernum = 6;
    Gr.arcnum = 7; Gr.vernum = 6;
    CreateOG(&G, ver, arc);
    CreateReverseOG(&Gr, ver, arc);
    FSCCbyKosaraju(&G, &Gr, visited);
    //DFSForest(&G, visited, &p);
    //DFSTraverse(&G, visited);
    //BFSTraverse(&G, visited);
    //DFSTraverseFSCC(&G, visited);
    //ReverseDFSTraverse(&G, visited);
    return 0;
}