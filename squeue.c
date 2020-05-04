/*
 * @Author: verandert
 * @Date: 2020-05-03 13:39:42
 * @LastEditTime: 2020-05-03 17:15:46
 * @Description: 
 */

//循环队列---顺序表示和实现
#include "./include/graph.h"


//初始化队列,队列的最大长度为249
void InitQueue(SqQueue *Q)
{
    Q->base = (SqElemtype *)malloc(MAXSIZE*sizeof(SqElemtype));
    if(!Q->base) exit(-1);
    Q->front = Q->rear = 0;
}

//返回队列长度
int QueueLength(SqQueue *Q)
{
    return (Q->rear - Q->front + MAXSIZE) % MAXSIZE;
}

//队列不满, 进队列;
void EnQueue(SqQueue *Q, SqElemtype data)
{
    if((Q->rear + 1)%MAXSIZE == Q->front) {printf("队列已满"); exit(-1);}
    Q->base[Q->rear] = data;
    Q->rear = (Q->rear + 1) % MAXSIZE;
}

//队列不空， 删除队列头元素;
SqElemtype DeQueue(SqQueue *Q)
{
    SqElemtype data;
    if(Q->front == Q->rear) {printf("删除空队列"); exit(-1);}
    data = Q->base[Q->front];
    Q->front = (Q->front + 1) % MAXSIZE;
    return data;
}

//判断队列是否为空
enum bool IsQueueEmpty(SqQueue *Q)
{
   if(Q->front == Q->rear) return true;
   return false; 
}

//返回队列头元素的值，但不出队列；
SqElemtype GetQueueHead(SqQueue *Q)
{
    if(IsQueueEmpty(Q)) {printf("取空队列头节点"); exit(-1);}
    return Q->base[Q->front];
}

void DestroyQueue(SqQueue *Q){
    
}