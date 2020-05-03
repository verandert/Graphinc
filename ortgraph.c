/*
 * @Author: verandert
 * @Date: 2020-04-30 22:56:41
 * @LastEditTime: 2020-05-03 15:57:04
 * @Description: create orthongonal list and define some functions about it
 */
#include "./include/graph.h"

/**
 * @description: create orthongonal list by @ver which includes all vertexs and @arc which includes all arcs of vertexs
 */
void CreateOG(OrtGraph *G, VerType ver[], VerType (*arc)[2]){
    ArcNode *p;
    int k, j;
    for (int i = 0; i < G->vernum; i++)
    {
        G->xlist[i].data = ver[i];
        G->xlist[i].inarc = NULL;
        G->xlist[i].outarc = NULL;
    }
    for (int i = 0; i < G->arcnum; i++)
    {
        j = locate(G, *(*(arc+i)+0));
        k = locate(G, *(*(arc+i)+1));
        if(j != -1 && k != -1){
            if((p = (ArcNode*)malloc(sizeof(ArcNode)))){
                p->tailver = j;
                p->headver = k;
                p->hlink = G->xlist[k].inarc;
                p->tlink = G->xlist[j].outarc;
                p->info = "this is a arc";
            }
        }
        G->xlist[k].inarc = G->xlist[j].outarc = p;
    }   
}

/**
 * @Description: if data was found in G, return index of data, else return -1;
 */
int locate(OrtGraph *G, VerType data){
    for (int i = 0; i < G->vernum; i++)
    {
        if(G->xlist[i].data == data) return i;
    }
    return -1;
}
/**
 * @Description: depth_first search
 */
void DFSTraverse(OrtGraph *G, enum bool visited[]){
    for (int i = 0; i < G->vernum; i++) DFS(G, i, visited);
    printf("\n");
}

void DFS(OrtGraph *G, int v, enum bool visited[]){
    ArcNode *p;
    if(visited[v]==false){
        visited[v] = true;
        printf("%.2f\n", G->xlist[v].data);
        p = G->xlist[v].outarc;
        while (p)
        {
            DFS(G, p->headver, visited);
            p = p->tlink;
        }
    }
}

/**
 * @Description: breadth_first search
 */
void BFSTraverse(OrtGraph *G, enum bool visited[]){
    ArcNode *p;
    SqQueue Q;
    InitQueue(&Q);
    for (int i = 0; i < G->vernum; i++)
    {
        if(visited[i] == false) {printf("%.2f\n", G->xlist[i].data); visited[i] = true;}
        p = G->xlist[i].outarc;
        while(p || !IsQueueEmpty(&Q))
        {
            while (p)
            {
                if(visited[p->headver] == false) {printf("%.2f\n", G->xlist[p->headver].data); visited[p->headver] = true;EnQueue(&Q, p);}
                p = p->tlink;
            }
            if(!IsQueueEmpty(&Q)) p = G->xlist[DeQueue(&Q)->headver].outarc;
        }
        
    }
}