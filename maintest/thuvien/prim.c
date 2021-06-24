#include "prim.h"
Graph createGraph()
{
    Graph g;
    g.edges = make_jrb();
    g.vertices = make_jrb();
    return g;
}
void addVertex(Graph g, int id, char *name)
{
    JRB tmp = jrb_find_int(g.vertices, id);
    if(tmp == NULL)
    {
        jrb_insert_int(g.vertices, id, new_jval_s(strdup(name)));
    }
    else
    {
        strcpy(tmp->val.s, name);
    }
}
char *getVertex(Graph g, int id)
{
    JRB tmp = jrb_find_int(g.vertices, id);
    return tmp->val.s;
}
void addEdge(Graph g, int v1, int v2, int kc)
{
    JRB tree = make_jrb();
    JRB tmp = jrb_find_int(g.edges, v1);
    if(tmp == NULL)
    {
        jrb_insert_int(g.edges, v1, new_jval_v(tree));
        jrb_insert_int(tree, v2, new_jval_i(kc));
    }
    else
    {
        tmp = (JRB)tmp->val.v;
        JRB tmp1 = jrb_find_int(tmp, v2);
        if(tmp1 == NULL)jrb_insert_int(tmp, v2, new_jval_i(kc));
    }
}
int hasEdge(Graph g, int v1, int v2)
{
    JRB tmp = jrb_find_int(g.edges, v1);
    if(tmp == NULL)
    {
        return 0;
    }
    else
    {
        tmp =  (JRB)tmp->val.v;
        JRB tmp1 = jrb_find_int(tmp, v2);
        if(tmp1 != NULL)return 1;
        return 0;
    }
}
int indegree(Graph g, int v, int* output)
{
    JRB tmp;
    JRB tmp1;
    JRB tmp2;
    int count = 0;
    int a;
    jrb_traverse(tmp, g.edges)
    {

        if(tmp->key.i != v)
        {
            a = tmp->key.i;
            tmp2 = (JRB)tmp->val.v;
            tmp1 = jrb_find_int(tmp2, v);
            if(tmp1 != NULL)
            {
                output[count++] = a;
            }
        }
    }
    return count;
}
int outdegree(Graph g, int v, int* output)
{
    JRB tmp = jrb_find_int(g.edges, v);
    int count = 0;
    JRB tmp1;
    if(tmp != NULL)
    {
        tmp = (JRB)tmp->val.v;
        jrb_traverse(tmp1, tmp)
        {
            output[count++] = tmp1->key.i;
        }
    }
    return count;
}
Graph Prim(Graph g, Graph g1, int diemdau)
{
    int sodinh = 10001;
    int *d = (int *)malloc(sodinh * sizeof(int));
    for(int i = 0; i < sodinh; i++)
    {
        d[i] = 1000;
    }
    d[diemdau] = 0;
    int *diemtruoc = (int *)malloc(10001 *sizeof(int));;
    for(int i = 0; i < 10001; i++)
    {
        diemtruoc[i] = -1;
    }
    int *check = (int *)calloc(sodinh, sizeof(int)); //visited
    Queue q;
    makeNullQueue(&q);
    enQueue(&q, diemdau);
    int u;
    int n;
    int *output = (int *)malloc(10001 *sizeof(int));
    JRB tmp, tmp1, tmp2, tmp4;
    int *xx = (int *)malloc(10001 *sizeof(int));
    int nn = 0;
    int min;
    xx[nn++] = diemdau;
    while(!isEmpty(q))
    {
        deQueue(&q, &u);
        n = outdegree(g, u, output);
        tmp = jrb_find_int(g.edges, u);
        if(check[u] == 0)
        {
            for(int i = 0; i < n; i++)
            {
                //enQueue(&q, output[i]);
                tmp1 = (JRB)tmp->val.v;
                tmp2 = jrb_find_int(tmp1, output[i]);
                if(d[output[i]] == 1000)
                {
                    d[output[i]] = tmp2->val.i;
                    diemtruoc[output[i]] = u;
                }
                else if(tmp2->val.i < d[output[i]])
                {
                    int check = 1;
                    for(int j = 0; j < nn; j++)
                    {
                        if(output[i] == xx[j])
                        {
                            check = 0;
                            break;
                        }
                    }
                    if(check == 1)
                    {
                        d[output[i]] = tmp2->val.i;
                        diemtruoc[output[i]] = u;
                    }

                }
            }
            int zz = 0;
            jrb_traverse(tmp4, g.vertices)
            {
                int check = 1;
                for(int i = 0; i < nn; i++)
                {
                    if(tmp4->key.i == xx[i])
                    {
                        check = 0;
                        break;
                    }
                }
                if(check == 1)
                {
                    if(zz == 0)
                    {
                        min = tmp4->key.i;
                        zz++;
                    }
                    else
                    {
                        if(d[min] > d[tmp4->key.i])min = tmp4->key.i;
                    }
                }
            }
            //printf("**%d\n", d[3]);
            enQueue(&q, min);
            //printf("***%d\n", min);
            xx[nn++] = min;
        }
        check[u] = 1;
    }
    JRB tmp3;
    jrb_traverse(tmp, g.vertices)
    {
        addVertex(g1, tmp->key.i, tmp->val.s);
        if(diemtruoc[tmp->key.i] != -1)
        {
            tmp1 = jrb_find_int(g.edges, tmp->key.i);
            tmp2 = (JRB)tmp1->val.v;
            tmp3 = jrb_find_int(tmp2, diemtruoc[tmp->key.i]);
            addEdge(g1, tmp->key.i, diemtruoc[tmp->key.i], tmp3->val.i);
            //printf("//%d %d\n", tmp->key.i, diemtruoc[tmp->key.i]);
            addEdge(g1, diemtruoc[tmp->key.i], tmp->key.i, tmp3->val.i);
        }
    }
    free(xx);
    free(output);
    free(d);
    free(check);
    free(diemtruoc);
    return g1;
}
void xuatFile(char filename[100], Graph g)
{
    FILE *fp = fopen(filename, "w");
    if(fp == NULL)
    {
        printf("Co loi khi mo file!");
        exit(0);
    }
    fprintf(fp, "graph dothi\n");
    fprintf(fp, "{\n");
    JRB tmp;
    int n = 0;
    int xx[1000];
    int nn = 0;
    jrb_traverse(tmp, g.vertices)
    {
        fprintf(fp, "%d [fillcolor=white, style=filled];\n", tmp->key.i);
        n++;
    }
    JRB tmp1, tmp2;
    jrb_traverse(tmp, g.edges)
    {
        tmp1 = (JRB)tmp->val.v;
        jrb_traverse(tmp2, tmp1)
        {
            int check = 1;
            for(int i = 0; i < nn; i++)
            {
                if(tmp2->key.i * n + tmp->key.i == xx[i])
                {
                    check = 0;
                    break;
                }
            }
            if(check == 1)
            {
                fprintf(fp, "%d -- %d [weight = %d] [label = %d];\n", tmp2->key.i, tmp->key.i, tmp2->val.i, tmp2->val.i);
                xx[nn++] = tmp2->key.i * n + tmp->key.i;
                xx[nn++] = tmp->key.i *n + tmp2->key.i;
            }
        }
    }
    fprintf(fp, "}");
    fclose(fp);
}
