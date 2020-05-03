/*
 * @Author: verandert
 * @Date: 2020-05-03 13:41:47
 * @LastEditTime: 2020-05-03 15:16:17
 * @Description: headfile for ortgraph
 */
#ifndef _GRAPH_H
#define _GRAPH_H
#include <stdio.h>
#include <stdlib.h>


#define MaxNum 20//max numbers of vertex
#define MAXSIZE 250//max numbers of squeue


enum bool{false, true};
typedef float VerType;//type of vertex

typedef char* InfoType;
typedef struct ArcNode
{
    int tailver, headver;
    InfoType info;
    struct ArcNode *hlink, *tlink;
   /**
    * @tailver:index of tailvertex
    * @headver:index of headvertex
    * @info:information of the arc
    * @hlink:link to next arc with same head vertex
    * @tlind:link to next arc with same tail vertex
    */
}ArcNode;

typedef struct
{
    VerType data;
    ArcNode *inarc, *outarc;
   /**
    * @inarc:link to first arc which regards data as head vertex
    * @outarc:link to first arc which regards data as tail vertex
    */
}VerNode;

typedef struct
{
    VerNode xlist[MaxNum];
    int arcnum, vernum;
}OrtGraph;

typedef ArcNode *SqElemtype;
typedef struct
{
    SqElemtype *base;
    int front, rear;
}SqQueue;

void CreateOG(OrtGraph *G, VerType ver[], VerType (*arc)[2]);
int locate(OrtGraph *G, VerType data);
void DFS(OrtGraph *G, int v, enum bool visited[]);
void DFSTraverse(OrtGraph *G, enum bool visited[]);
void BFSTraverse(OrtGraph *G, enum bool visited[]);

void InitQueue(SqQueue *Q);
int QueueLength(SqQueue *Q);
void EnQueue(SqQueue *Q, SqElemtype data);
SqElemtype DeQueue(SqQueue *Q);
enum bool IsQueueEmpty(SqQueue *Q);
SqElemtype GetQueueHead(SqQueue *Q);

#endif