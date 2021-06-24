#include "huffman.h"
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
        jrb_insert_int(tmp, v2, new_jval_i(kc));
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
int DAG(Graph g)
{

    int u;
    int output[100];
    JRB tmp;
    int n;
    Queue q;
    jrb_traverse(tmp, g.edges)
    {
        int *visited = (int *)calloc(1000, sizeof(int));
        makeNullQueue(&q);
        enQueue(&q, tmp->key.i);
        while(!isEmpty(q))
        {
            deQueue(&q, &u);
            if(visited[u] == 0)
            {
                n = outdegree(g, u, output);

                for(int i = 0; i < n; i++)
                {
                    enQueue(&q, output[i]);
                    if(output[i] == tmp->key.i)return 0;

                }
            }
            visited[u] = 1;
        }

    }
    return 1;
}
void topologicalSort(Graph g,int *output,int *n)
{
    JRB tmp;
    int *dk = (int *)calloc(1000, sizeof(int));
    int out[100];
    Queue q;
    makeNullQueue(&q);
    int u, m;
    *n = 0;
    jrb_traverse(tmp, g.vertices)
    {
        dk[tmp->key.i] = indegree(g, tmp->key.i, out);
        if(dk[tmp->key.i] == 0)enQueue(&q, tmp->key.i);

    }
    while(!isEmpty(q))
    {
        deQueue(&q, &u);
        output[(*n)++] = u;
        m = outdegree(g, u, out);
        for(int i = 0; i < m; i++)
        {
            dk[out[i]]--;
            if(dk[out[i]] == 0)enQueue(&q, out[i]);
        }

    }
}
void timDuong(Graph g, int diemtruoc[],int diemdau, int diemcuoi, char *duong)
{
    if(diemdau == diemcuoi){
        strcat(duong, getVertex(g, diemcuoi));
        return;
    }
    timDuong(g, diemtruoc, diemdau,diemtruoc[diemcuoi], duong);
    strcat(duong, getVertex(g, diemcuoi));
}
void edgesDijkstra(Graph g, int diemdau, int diemcuoi, char *duong)
{
    int *d = (int *)malloc(10000 * sizeof(int));
    for(int i = 0; i < 10000; i++)
    {
        d[i] = 1000;
    }
    d[diemdau] = 0;
    int *diemtruoc = (int *)malloc(10000 * sizeof(int));
    int *check = (int *)calloc(10000, sizeof(int));
    Queue q;
    makeNullQueue(&q);
    enQueue(&q, diemdau);
    int u;
    int n;
    int output[1000];
    JRB tmp, tmp1, tmp2;

    while(!isEmpty(q))
    {
        deQueue(&q, &u);
        n = outdegree(g, u, output);
        tmp = jrb_find_int(g.edges, u);
        if(check[u] == 0)
        {
            for(int i = 0; i < n; i++)
            {
                enQueue(&q, output[i]);
                tmp1 = (JRB)tmp->val.v;
                tmp2 = jrb_find_int(tmp1, output[i]);
                if(d[output[i]] == 1000)
                {
                    d[output[i]] = tmp2->val.i + d[u];
                    diemtruoc[output[i]] = u;
                }
                else if(tmp2->val.i + d[u] < d[output[i]])
                {
                    d[output[i]] = tmp2->val.i + d[u];
                    diemtruoc[output[i]] = u;
                }

            }
        }
        check[u] = 1;
    }

    timDuong(g, diemtruoc, diemdau, diemcuoi, duong);
}
node createNode(int c, elementtype value) //Tạo node
{
    node tmp;
    tmp = (node)malloc(sizeof(struct linkedlist));
    tmp->c = c;
    tmp->data = value;
    tmp->next = NULL;
    return tmp;
}
node insertNode(node head,int c, elementtype value, int index)//Chèn vào vị trí index
{
    if(index == 0 || head == NULL)
    {
        head = createNode(c, value);
    }
    else
    {
        node tmp = head;
        while(head->next != NULL && index != 1)
        {
            index--;
            tmp = tmp->next;
        }
        node tmp1 = createNode(c, value);
        tmp1->next = tmp->next;
        tmp->next = tmp1;
    }
    return head;
}
node delHead(node head)//Xóa node đầu
{
    if(head == NULL)
    {
        printf("Khong co gi de xoa het!\n");
    }
    else
    {
        node tmp = head;
        head = head->next;
        free(tmp);
    }
    return head;
}
elementtype getNode(node head, int index)//Trả về giá trị của node ở vị trí index
{
    while(head->next != NULL && index != 0)
    {
        index--;
        head = head->next;
    }
    return head->data;
}
void printList(node head)//In danh sách
{
    while(head != NULL)
    {
        printf("%c %d\n",head->c, head->data);
        head = head->next;
    }
    printf("\n");
}
void sortLinkedList(node head)// Sắp xếp danh sách
{
    node tmp, tmp1;
    elementtype a;
    node b = head;
    char c;
    while(head->next != NULL)
    {
        tmp = head;
        tmp1 = head->next;
        while(tmp1 != NULL)
        {
            if(tmp->data > tmp1->data)
            {
                a = tmp->data;
                tmp->data = tmp1->data;
                tmp1->data = a;
                c = tmp->c;
                tmp->c = tmp1->c;
                tmp1->c = c;
            }
            tmp1 = tmp1->next;
        }
        head = head->next;
    }
    while(b->next != NULL)
    {
        tmp = b;
        tmp1 = b->next;
        while(tmp1 != NULL)
        {
            if(tmp->c < tmp1->c && tmp->data == tmp1->data)
            {
                a = tmp->c;
                tmp->c = tmp1->c;
                tmp1->c = a;
            }
            tmp1 = tmp1->next;
        }
        b = b->next;
    }
}
node insert1(node head, int c, int dem)
{
    node tmp = head;
    while(tmp->next != NULL && tmp->next->data <= dem)
    {
        tmp = tmp->next;
    }
    node tmp1 = createNode(c, dem);
    tmp1->next = tmp->next;
    tmp->next = tmp1;
    return head;
}


int demsokitu(char *s, char c)
{
    int count = 0;
    for(int i = 0; i < strlen(s); i++)
    {
        if(s[i] == c)count++;
    }
    return count;
}

HuffmanTree makeHuffman (char *buffer)
{
    tmpx = (char *)malloc(10001);
    strcpy(tmpx, "");
    node head = NULL;

    for(int i = 0; i < strlen(buffer); i++)
    {
        int check = 1;
        for(int j = 0; j < strlen(tmpx); j++)
        {
            if(buffer[i] == tmpx[j])
            {
                check = 0;
                break;
            }
        }
        if(check == 1)
        {
            strncat(tmpx, &buffer[i], 1);
            tmpx[strlen(tmpx)] = '\0';
        }
    }
    for(int i = 0; i < strlen(tmpx); i++)
    {
        head = insertNode(head, tmpx[i], demsokitu(buffer, tmpx[i]), i);
    }
    sortLinkedList(head);
    printList(head);
    int c = 1000;
    HuffmanTree h;
    h.graph = createGraph();
    while(head->next != NULL)
    {
        head = insert1(head, c, head->data + head->next->data);
        addVertex(h.graph, head->c, "0");
        addVertex(h.graph, head->next->c, "1");
        addVertex(h.graph, c, "");
        addEdge(h.graph, c, head->c, 1);
        addEdge(h.graph, c, head->next->c, 1);
        //printf("a: %d, b: %d, c: %d\n", head->c, head->next->c, c);
        head = delHead(head);
        head = delHead(head);
        c++;
    }
    h.root = jrb_find_int(h.graph.edges, --c);
    FILE *fp = fopen("huffman.dot", "w");
    if(fp == NULL)
    {
        printf("Co loi khi mo file!!!\n");
        exit(0);
    }
    fprintf(fp, "digraph dothi\n{\n");
    JRB tmp;
    jrb_traverse(tmp, h.graph.vertices)
    {
        if(tmp->key.i < 1000)
        {
            fprintf(fp, "%d [fillcolor=white, style=filled, label=\"%c\"];\n", tmp->key.i, tmp->key.i);
        }
        else
        {
            fprintf(fp, "%d [fillcolor=white, style=filled];\n", tmp->key.i);
        }
    }
    JRB tmp1, tmp2;
    jrb_traverse(tmp, h.graph.edges)
    {
        tmp1 = (JRB)tmp->val.v;
        jrb_traverse(tmp2, tmp1)
        {
            fprintf(fp, "%d -> %d [label = %s];\n", tmp->key.i, tmp2->key.i, getVertex(h.graph, tmp2->key.i));
        }
    }
    fprintf(fp, "}");
    fclose(fp);
    return h;
}


void createHuffmanTable(HuffmanTree h, Coding *huffmanTable, char *buffer)
{
    char bits1[1000];
    for(int i = 0; i <= 256; i++)
    {
        huffmanTable[i].size = 0;
    }
    for(int i = 0; i < strlen(tmpx); i++)
    {
        strcpy(bits1, "");
        edgesDijkstra(h.graph, h.root->key.i, tmpx[i], bits1);
        strcpy(huffmanTable[tmpx[i]].bits, bits1);
        huffmanTable[tmpx[i]].size = strlen(bits1);
        //printf("%c: %s\n", tmpx[i], huffmanTable[tmpx[i]].bits);
    }

}
