/*
 * @Author: verandert
 * @Date: 2020-05-03 13:53:58
 * @LastEditTime: 2020-05-04 17:34:56
 * @Description: main function
 */
#include "./include/graph.h"

int main(){
    VerType ver[] = {1,2,3,4,5,6}, arc[][2] = {{1,2}, {1,3}, {3,2}, {3, 4}, {4, 1}, {5, 6}};
    enum bool visited[6];
    //boolean visited[4];
    OrtGraph G;
    CBNode T, *p;
    p = &T;
    G.arcnum = 6; G.vernum = 6;
    CreateOG(&G, ver, arc);
    DFSForest(&G, visited, &p);
    //DFSTraverse(&G, visited);
    //BFSTraverse(&G, visited);
    return 0;
}