/*
 * @Author: verandert
 * @Date: 2020-05-03 13:53:58
 * @LastEditTime: 2020-05-03 15:56:04
 * @Description: main function
 */
#include "./include/graph.h"

int main(){
    VerType ver[] = {1,2,3,4}, arc[][2] = {{1,2}, {1,3}, {3,2}, {3, 4}, {4, 1}};
    enum bool visited[4];
    //boolean visited[4];
    OrtGraph G;
    G.arcnum = 5; G.vernum = 4;
    CreateOG(&G, ver, arc);
    //DFSTraverse(&G, visited);
    BFSTraverse(&G, visited);
    return 0;
}