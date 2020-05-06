/*
 * @Author: verandert
 * @Date: 2020-05-03 13:53:58
 * @LastEditTime: 2020-05-07 01:28:44
 * @Description: main function
 */
#include "./include/graph.h"

int main(){
    VerType ver[] = {1,2,3,4}, arc[][3] = {{1, 2, 6}, {2, 1, 6}, {2, 3, 2}, {3, 2, 2}, {3, 4, 4}, {4, 3, 4}};
    enum bool visited[4];
    for (int i = 0; i < 4; i++)
    {
        visited[i] = false;
    }
    //boolean visited[4];
    OrtGraph G;
    OrtGraph Gr;
    G.arcnum = 6; G.vernum = 4;
    Gr.arcnum = 6; Gr.vernum = 4;
    CreateOG(&G, ver, arc);
    MSTByPrim(&G);
    //CreateReverseOG(&Gr, ver, arc);
    //FSCCbyKosaraju(&G, &Gr, visited);
    //DFSForest(&G, visited, &p);
    //DFSTraverse(&G, visited);
    //BFSTraverse(&G, visited);
    //DFSTraverseFSCC(&G, visited);
    return 0;
}