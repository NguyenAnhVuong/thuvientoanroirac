#include "kruskal.h"
void docfile(char *filename)
{
    FILE  *fp = fopen(filename, "r");

    if(fp == NULL)
    {
        printf("Co loi khi mo file!\n");
        exit(0);
    }
    else
    {
        fscanf(fp, "%d", &n);
        cost = (int **)malloc(sizeof(int *) * n);
        for(int i = 0; i < n; i++)
        {
            cost[i] = (int *)malloc(n * sizeof(int));
        }
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++)
            {
                cost[i][j] = 0;
            }
        }
        int x, y, z;
        while(fscanf(fp, "%d %d %d", &x, &y, &z) != EOF)
        {
            cost[x - 1][y - 1] = z;
            cost[y - 1][x - 1] = z;
        }
    }
    fclose(fp);
}
void printMTS(int a[], int b[], int weight[])  //in cay MTS
{
    int minweight = 0;
    for (int i = 0; i < n - 1; i++)
    {
        printf("canh: %d - %d ", a[i], b[i]);
        printf("trong so: %d\n", weight[i]);
        minweight += weight[i];
    }
    printf("trong so nho nhat la: %d\n", minweight);
}

int findparent(int node)
{
    while(parent[node] >= 0)
    {
        node = parent[node];
    }
    return node;
}

// int findparentpathcompression(int node){
//     if(node == parent[node]) return node;
//     return parent[node] = findparentpathcompression(parent[node]);
// }

void fill_n(int a[], int location, int total, int val)
{
    int i;
    for(i = location; i < location + total; i++)
    {
        a[i] = val;
    }

}

void xuatkruskal(int a[], int b[], int weight[])
{
    FILE *fp = fopen("dothikruskal.dot", "w");

    if(fp == NULL)
    {
        printf("Mo file that bai!!!\n");
        return;
    }
    else
    {
        fprintf(fp, "graph kruskal\n{\n");
        for(int i = 0; i < n; i++)
        {
            fprintf(fp, "%d [fillcolor = white, style = filled];\n", i);
        }
        for(int i = 0; i < n - 1; i++)
        {
            fprintf(fp, "%d -- %d [weight = %d] [label = %d];\n", a[i], b[i],weight[i], weight[i]);
        }
        fprintf(fp, "}");
    }
    fclose(fp);
}

void kruskal()
{
    parent = (int *)malloc(10001 *sizeof(int));
    fill_n(parent, 0, n, -1);
    int u, v, k = 0, count = 0;
    int fisrtnode, secondnode;
    int a[n], b[n];
    int weight[n];
    int min;

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(cost[i][j] == 0) cost[i][j] = int_max;
        }
    }

    while(count < n - 1 )
    {
        min = int_max;

        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++)
            {
                if(cost[i][j] < min)
                {
                    min = cost[i][j];
                    fisrtnode = i; // i = 1
                    secondnode = j; // j = 2
                }
            }
        }

        u = findparent(fisrtnode); // u =1
        v = findparent(secondnode); // v =2

        if( u != v)
        {
            parent[v]  = u;
            a[k] = fisrtnode;
            b[k] = secondnode;
            weight[k] = cost[fisrtnode][secondnode];
            count++;
            k++;
        }

        cost[fisrtnode][secondnode] = cost[secondnode][fisrtnode] = int_max;
    }

    xuatkruskal(a, b, weight);
    printMTS(a, b, weight);
}

void xuatfile()
{
    FILE *fp = fopen("dothimau.dot", "w");
    int w, e;
    if(fp == NULL)
    {
        printf("Khong mo duoc file!!!\n");
        return;
    }

    else
    {
        fprintf(fp,"graph dothi\n{\n");
        for(int i = 0; i < n; i++)
        {
            fprintf(fp, "%d [fillcolor = white, style = filled];\n", i);
        }
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++)
            {
                if(i < j && cost[i][j] != 0)
                {
                    fprintf(fp, "%d -- %d [label = %d];\n", i, j,cost[i][j]);
                }
            }
        }
        fprintf(fp, "}");
    }
    fclose(fp);
}
