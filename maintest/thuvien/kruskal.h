#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define int_max 2147483647
int **cost;
int *parent;
int n;
void docfile(char *filename);
void printMTS(int a[], int b[], int weight[]);
int findparent(int node);
void fill_n(int a[], int location, int total, int val);
void xuatkruskal(int a[], int b[], int weight[]);
void kruskal();
void xuatfile();
