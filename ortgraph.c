/*
 * @Author: verandert
 * @Date: 2020-04-30 22:56:41
 * @LastEditTime: 2020-05-08 01:10:14
 * @Description: create orthogonal list and define some functions about it
 */
#include "./include/graph.h"

/**
 * @description: create orthogonal list by @ver which includes all vertexs and @arc which includes all arcs of vertexs
 */
void CreateOG(OrtGraph *G, VerType ver[], VerType (*arc)[3]){
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
                p->info = *(*(arc+i)+2);
            }
        }
        G->xlist[k].inarc = G->xlist[j].outarc = p;
    }   
}
/**
 * @Description: creatre reverse graph
 */
void CreateReverseOG(OrtGraph *G, VerType ver[], VerType (*arc)[3]){
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
                p->tailver = k;
                p->headver = j;
                p->hlink = G->xlist[j].inarc;
                p->tlink = G->xlist[k].outarc;
                p->info = 0;
                G->xlist[j].inarc = G->xlist[k].outarc = p;
            }
        }
       
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
    for (int i = 0; i < G->vernum; i++) if(!visited[i]) DFS(G, i, visited);
}

void DFS(OrtGraph *G, int v, enum bool visited[]){
    ArcNode *p;
    if(visited[v]==false){
        visited[v] = true;
        printf("%.2f ", G->xlist[v].data);
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
/**
 * @Description:convert graph to child-brother trees.
 */
void DFSForest(OrtGraph *G, enum bool visited[], CBTree *T){
    CBTree p, q;
    for (int i = 0; i < G->vernum; i++)
    {
        if(visited[i] == false){
            printf("%.2f\n", G->xlist[i].data);
            visited[i] = true;
            if(i>0) {
                if((p = (CBNode*)malloc(sizeof(CBNode)))){
                    p->data = G->xlist[i].data;
                    p->firstchild = NULL;
                    p->nextbrother = NULL;
                    q = *T;
                    while (q->nextbrother) q = q->nextbrother;
                    q->nextbrother = p;
                    DFSTree(G, i, visited, p);
                }
            } else
            {
                if(!(*T)) *T = (CBNode*)malloc(sizeof(CBNode));
                if(!(*T)) exit(0);
                (*T)->data = G->xlist[0].data;
                (*T)->firstchild = NULL;
                (*T)->nextbrother = NULL;
                DFSTree(G, i, visited, *T);
            }
            
        }
    }
    
}
/**
 * @Description: fucntion for DFSforest
 */
void DFSTree(OrtGraph *G, int v, enum bool visited[], CBTree T){
    ArcNode *p;
    CBNode *t, *q;
    p = G->xlist[v].outarc;
    while (p)
    {
        if(visited[p->headver]==false){
            if((t = (CBNode*)malloc(sizeof(CBNode)))){
                visited[p->headver] = true;
                printf("%.2f\n", G->xlist[p->headver].data);
                t->data = G->xlist[p->headver].data;
                t->firstchild = NULL;
                t->nextbrother = NULL;
                if(!T->firstchild) T->firstchild = t;
                else
                {
                    q = T->firstchild;
                    while (q->nextbrother) q = q->nextbrother;
                    q->nextbrother = t;
                }
            }
            DFSTree(G, p->headver, visited, t);
        }
        p = p->tlink;
    }   
}

/**
 * @Description:find strongly connected components by kosaraju in graph which was implemented by orthogonal list
 */
void FSCCbyKosaraju(OrtGraph *G, OrtGraph *Gr, enum bool visited[]){
    int count, finished[G->vernum];
    enum bool reversevisited[G->vernum];
    for (int i = 0; i < G->vernum; i++)
    {
        if(reversevisited[i]!=false) reversevisited[i] = false;
    }
    for (int i = 0; i < G->vernum; i++)
    {
        if(visited[i] == false) {
            count = 0;
            FSCCDFS(G, i, visited, &count, finished);
            // printf("count: %d ", count);
            // for (int i = 0; i < count; i++)
            // {
            //     printf("%.2f ", G->xlist[finished[i]].data);
            // }
            //printf("\n");
            for (int i = count-1; i >= 0; i--)
            {
                if(!reversevisited[finished[i]]){
                    printf("强连通分量为:");
                    DFS(Gr, finished[i], reversevisited);
                    printf("\n");
                }
            }
        }
    }
}
/**
 * @Description: function for FSCCbyKosaraju
 */
void FSCCDFS(OrtGraph *G, int v, enum bool visited[], int *count, int finished[]){
    ArcNode *p;
    if(visited[v]==false){
        visited[v] = true;
        //printf("%.2f\n", G->xlist[v].data);
        p = G->xlist[v].outarc;
        while (p)
        {
            FSCCDFS(G, p->headver, visited, count, finished);
            p = p->tlink;
        }
        finished[(*count)++] = v;
    }
    
}

/**
 * @Description: Minimum Cost Spanning Tree by PRIM
 */
void MSTByPrim(OrtGraph *G){
    ArcNode *p;
    Closedge closedge[G->vernum+1];
    int start = 0, j;
    for (int i = 0; i <= G->vernum; i++)
    {
        closedge[i].adjvex = start;
        closedge[i].lowcost = Int_Max;
    }
    closedge[start].lowcost = 0;
    p = G->xlist[start].outarc;
    while (p)
    {
        closedge[p->headver].lowcost = p->info;
        p = p->tlink;
    }
    for (int i = 0; i < G->vernum - 1; i++)
    {
        start = G->vernum;
        for (j = 0; j < G->vernum; j++)
        {
            if(closedge[j].lowcost < closedge[start].lowcost && closedge[j].lowcost != 0) start = j;
        }
        printf("<%d, %d> ", closedge[start].adjvex, start);
        closedge[start].lowcost = 0;
        p = G->xlist[start].outarc;
        while (p)
        {
            if(p->info < closedge[p->headver].lowcost) {
                closedge[p->headver].lowcost = p->info;
                closedge[p->headver].adjvex = p->tailver;
            }
            p = p->tlink;
        }
    }
    printf("\n");
}
/**
 * @Description: heap for kruskal
 */
void InitHeap(Heap heap, int (*udarc)[3], int len){
    int index = 1, temp, parent;
    for (int i = 0; i < len; i++)
    {
        heap[index].data = *(*(udarc+i)+2);
        heap[index].ver1 = *(*(udarc+i)+0);
        heap[index].ver2 = *(*(udarc+i)+1);
        temp = index;
        while (temp > 1)
        {
            parent = temp / 2;
            if(heap[parent].data > heap[temp].data){
                swap(heap, temp, parent);
            }
            temp = parent;
        }
         index++;
    }
    
}

void swap(Heap heap, int index1, int index2){
    HEAP temp;
    temp = heap[index1];
    heap[index1] = heap[index2];
    heap[index2] = temp;
}
/**
 * @Description: Minimum Cost Spanning Tree by Kruskal
 */
void MSTbyKruskal(VerType ver[], Heap heap, int num, int len, enum bool visited[], TNode tn[]){
    int k, s, start, min;
    for (int i = 0; i < num; i++)
    {
        tn[i].data = ver[i];
        tn[i].parent = i;
    }
    for (int i = len; i >= 1; i--)
    {
        start = 1;
        k = heap[1].ver1; s = heap[1].ver2;
        //printf("(%d %d)", k, s);
        while (tn[k].parent != k)
        {
            k = tn[k].parent;
        }
        while (tn[s].parent != s)
        {
            s = tn[s].parent;
        }
        if(k != s){
            tn[k].parent = heap[1].ver1;
            tn[s].parent = heap[1].ver2;
            tn[heap[1].ver1].parent = heap[1].ver2;
            tn[heap[1].ver2].parent = heap[1].ver2;
        }
        heap[1] = heap[i];
        while (start < i)
        {
            if(2*start >= i) start = 2*start;
            else if(2*start + 1 >= i) {
                if(heap[start].data > heap[2*start].data) {
                    swap(heap, start, 2*start);
                }
                start = 2*start;
            }
            else
            {
                if(heap[2*start].data <= heap[2*start + 1].data) min = 2*start;
                else {min = 2*start + 1;}
                if(heap[start].data > heap[min].data) {swap(heap, start, min); start = min;}
                else break;
            }
        }
    }
}
