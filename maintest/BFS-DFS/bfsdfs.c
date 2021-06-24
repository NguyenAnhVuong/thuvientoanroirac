#include "bfsdfs.h"
Graph creatGraph(){
    Graph g = make_jrb();
    return g;
}

void addEdge(Graph g, int v1, int v2){
    Graph tmp = jrb_find_int(g, v1);
    Graph tree;

    if(tmp == NULL){
        tree = make_jrb();
        jrb_insert_int(g, v1, new_jval_v(tree));
        jrb_insert_int(tree, v2, new_jval_i(1));
    }
    else{
        tmp = (JRB)tmp->val.v;
        jrb_insert_int(tmp, v2, new_jval_i(1));
    }

    tmp = jrb_find_int(g, v2);
    if(tmp == NULL){
        tree = make_jrb();
        jrb_insert_int(g, v2, new_jval_i(tree));
        jrb_insert_int(tree, v1, new_jval_i(1));
    }
    else{
        tmp = (JRB)tmp->val.v;
        jrb_insert_int(tmp, v1, new_jval_i(1));
    }
}

int adjacent(Graph g, int v1, int v2){ // kiem tra v2 co la hang xom cua v1
    Graph tmp = jrb_find_int(g, v1);
    tmp = (JRB)tmp->val.v;
    JRB tmp1;
    jrb_traverse(tmp1, tmp){
        if(tmp1->key.i == v2) return 1; //co
    }
    return 0;//khong
}

int getAdjacentVertices(Graph g, int v, int *output)//lay tap dinh ke
{
    Graph tmp = jrb_find_int(g, v);
    tmp = (JRB)tmp->val.v;
    Graph tmp1;
    int n = 0;
    jrb_traverse(tmp1, tmp)
    {
        output[n++] = tmp1->key.i;
    }
    return n;
}

void dropGraph(Graph g)// xoa do thi
{
    JRB tmp;
    jrb_traverse(tmp, g)
    {
        jrb_free_tree((JRB)tmp->val.v);
    }
    jrb_free_tree(g);
}

int BFS(Graph g, int v[]){
    Queue q;
    Graph tmp;
    int n = 0, count = 0;
    jrb_traverse(tmp, g){
        n++;
    }
    int *visited = (int *)calloc(n + 1, sizeof(int));
    makeNullQueue(&q);
    enQueue(&q, 1);
    int u;
    int output[100];
    while(!isEmpty(q)){
        deQueue(&q, &u);
        if(visited[u] == 0){
            n =  getAdjacentVertices(g, u, output);
            printf("%d ", u);
            v[count] = u;
            for(int i = 0; i < n; i++){
                enQueue(&q, output[i]);
            }
            count++;
            visited[u] = 1;
        }
    }
    // printf("%d ",count);
    return count;
}

int DFS(Graph g, int v[])
{
    Graph tmp;
    int n = 0, count = 0;
    jrb_traverse(tmp, g)
    {
        n++;
    }
    int *visited =(int *)calloc(n + 1, sizeof(int));
    Stack st = NULL;
    st = push(st, 1);
    int u;
    int output[100];
    while(st != NULL)
    {
        st = pop(st, &u);
        if(visited[u] == 0)
        {
            n = getAdjacentVertices(g, u, output);
            printf("%d ", u);
            v[count] = u;
            for(int i = 0; i < n; i++)
            {
                st = push(st, output[i]);
            }
            count++;
            visited[u] = 1;
        }
    }
    return count;
}

void fileOriginal(Graph g){
    FILE *fp = fopen("graphoriginal.dot", "w");
    Graph tree;
    int output[100];
    int n;
    // int test[100];

    if(fp == NULL){
        printf("Khong mo duoc file!!!\n");
        return;
    }
    else{
        tree = make_jrb();
        fprintf(fp, "graph bfs\n{\n");
        jrb_traverse(tree, g){
            fprintf(fp, "%d [fillcolor = white, style = filled];\n", tree->key.i);

        }
        jrb_traverse(tree, g){
            int n = getAdjacentVertices(g, tree->key.i, output);
            for(int i = 0; i < n; i++){
                if(tree->key.i < output[i]){
                    fprintf(fp, "%d -- %d;\n", tree->key.i, output[i]);
                }
            }
        }
        fprintf(fp, "}");
    }
    fclose(fp);

}

void xuatFilebfs(int v[], int count){
    FILE *fp = fopen("bfs.dot", "w");

    if(fp == NULL){
        printf("Khong mo duoc file!!!\n");
        return;
    }
    else{
        fprintf(fp, "graph bfs\n{\n");
        for(int i = 0; i < count; i++){
            fprintf(fp, "%d [fillcolor = white, style = filled];\n",v[i]);
        }
        for(int i = 0; i < count - 1; i++){
            fprintf(fp, "%d -- %d;\n",v[i],v[i+1]);
        }
        fprintf(fp, "}");
    }
    fclose(fp);
}

void xuatFiledfs(int v[], int count){
    FILE *fp = fopen("dfs.dot", "w");

    if(fp == NULL){
        printf("Khong mo duoc file!!!\n");
        return;
    }
    else{
        fprintf(fp, "graph dfs\n{\n");
        for(int i = 0; i < count; i++){
            fprintf(fp, "%d [fillcolor = white, style = filled];\n",v[i]);
        }
        for(int i = 0; i < count - 1; i++){
            fprintf(fp, "%d -- %d;\n",v[i],v[i+1]);
        }
        fprintf(fp, "}");
    }
    fclose(fp);
}
