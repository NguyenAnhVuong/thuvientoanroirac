#include <stdio.h>
#include <stdlib.h>
#include "jrb.h"
#include <string.h>
#include "queue.h"
char *tmpx;
typedef struct
{
    JRB edges;
    JRB vertices;
} Graph;
typedef int elementtype;
struct linkedlist
{
    elementtype data;
    int c;
    struct linkedlist *next;
};
typedef struct linkedlist *node;
typedef struct
{
    Graph graph;
    JRB root;
}HuffmanTree;
typedef struct
{
    int size;
    char bits[200];
}Coding;
Graph createGraph();
void addVertex(Graph g, int id, char *name);
char *getVertex(Graph g, int id);
void addEdge(Graph g, int v1, int v2, int kc);
int hasEdge(Graph g, int v1, int v2);
int indegree(Graph g, int v, int* output);
int outdegree(Graph g, int v, int* output);
void timDuong(Graph g, int diemtruoc[],int diemdau, int diemcuoi, char *duong);
void edgesDijkstra(Graph g, int diemdau, int diemcuoi, char *duong);
node createNode(int c, elementtype value);
node insertNode(node head,int c, elementtype value, int index);
node delHead(node head);
elementtype getNode(node head, int index);
void printList(node head);
void sortLinkedList(node head);
node insert1(node head, int c, int dem);
int demsokitu(char *s, char c);
HuffmanTree makeHuffman (char *buffer);
void createHuffmanTable(HuffmanTree h, Coding *huffmanTable, char *buffer);

