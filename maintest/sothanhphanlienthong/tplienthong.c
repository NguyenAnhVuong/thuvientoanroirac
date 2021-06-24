#include "tplienthong.h"
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
    JRB tmp1;
    if(tmp == NULL)
    {
        jrb_insert_int(g.edges, v1, new_jval_v(tree));
        jrb_insert_int(tree, v2, new_jval_i(kc));
    }
    else
    {
        tmp = (JRB)tmp->val.v;
        tmp1 = jrb_find_int(tmp, v2);
        if(tmp1 == NULL)jrb_insert_int(tmp, v2, new_jval_i(kc));
    }
    tmp = jrb_find_int(g.edges, v2);
    if(tmp == NULL)
    {
        tree = make_jrb();
        jrb_insert_int(g.edges, v2, new_jval_v(tree));
        jrb_insert_int(tree, v1, new_jval_i(kc));
    }
    else
    {
        tmp = (JRB)tmp->val.v;
        tmp1 = jrb_find_int(tmp, v1);
        if(tmp1 == NULL)jrb_insert_int(tmp, v1, new_jval_i(kc));
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
void sothanhphanlienthong(Graph g)
{
    char color[20][20] = {"red", "green", "blue","yellow","orange","purple","gray","pink","brown", "white"};
    Queue q;
    JRB tmp;
    int u;
    int n;
    int count = 0;
    int *output = (int *)malloc(10001 * sizeof(int));
    int *visited = (int *)calloc(10001, sizeof(int));
    JRB tmp1;
    FILE *fp = fopen("tplt.dot", "w");
    if(fp == NULL)
    {
        printf("Co loi khi mo file!\n");
        exit(0);
    }
    fprintf(fp, "graph dothi\n{\n");
    jrb_traverse(tmp, g.vertices)
    {
        if(visited[tmp->key.i] == 0)
        {
            count++;
            makeNullQueue(&q);
            enQueue(&q, tmp->key.i);
            while(!isEmpty(q))
            {
                deQueue(&q, &u);
                if(count < 11)fprintf(fp, "%d [fillcolor=%s, style=filled];\n", u, color[count - 1]);
		else fprintf(fp, "%d [fillcolor=white, style=filled];\n", u);
                if(visited[u] == 0)
                {
                    n = outdegree(g, u, output);
                    for(int i = 0; i < n; i++)
                    {
                        if(visited[output[i]] == 0)enQueue(&q, output[i]);
                    }
                    visited[u] = 1;
                }

            }
        }
    }
    int *xx = (int *)malloc(10001 * sizeof(int));
    int nn = 0;
    JRB tmp2;
    int sd = 0;
    jrb_traverse(tmp, g.vertices)
    {
        sd++;
    }
    jrb_traverse(tmp, g.edges)
    {
        tmp1 = (JRB)tmp->val.v;
        jrb_traverse(tmp2, tmp1)
        {
            int zxc = 1;
            for(int i = 0; i < nn; i++)
            {
                if(tmp2->key.i * sd + tmp->key.i == xx[i])
                {
                    zxc = 0;
                    break;
                }
            }
            if(zxc == 1)
            {
                fprintf(fp,"%d -- %d;\n", tmp2->key.i, tmp->key.i);
                xx[nn++] = tmp2->key.i * sd + tmp->key.i;
                xx[nn++] = tmp->key.i * sd + tmp2->key.i;
            }
        }
    }
    fprintf(fp, "}");
    fclose(fp);
    free(visited);
    free(output);
    free(xx);
    printf("So thanh phan lien thong: %d\n", count);
}
