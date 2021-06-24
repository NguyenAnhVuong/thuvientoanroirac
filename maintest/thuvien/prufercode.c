#include "prufercode.h"
void prufercode()
{
    scanf("%d", &n);
    arr = (int **)malloc(10001 * sizeof(int *));
    for(int i = 0; i < 10001; i ++)
    {
        arr[i] = (int *)calloc(10001, sizeof(int));
    }
    int a, b;
    for(int i = 0; i < n; i++)
    {
        scanf("%d%d",&a,&b);
        arr[a][b]++;
        arr[b][a]++;
    }
    int *op = (int *)malloc((n - 1) * sizeof(int));
    int x = 0;
    int *bac = (int *)calloc((n + 1), sizeof(int));
    for(int i = 0; i < n + 1; i++)
    {
        for(int j = 0; j < n + 1; j++)
        {
            if(arr[i][j] == 1)bac[i]++;
        }
    }
    for(int i = 1; i <= n; i++)
    {
        if(bac[i] == 1)
        {
            for(int j = 0; j < n + 1; j++)
            {
                if(arr[i][j] != 0)
                {
                    bac[j]--;
                    arr[j][i] = 0;
                    op[x++] = j;
                }
            }
        }
    }
    printf("prufercode: ");
    for(int i = 0; i < x; i++)
    {
        printf("%d ", op[i]);
    }
}
void xuatFile(char *filename)
{
    FILE *fp = fopen(filename, "w");//printf("1111\n");
    if(fp == NULL)
    {
        printf("Co loi khi mo file!\n");
        exit(0);
    }
    fprintf(fp, "graph dothi\n{\n");
    int *xx = (int *)malloc(10001 * sizeof(int));
    int nn = 0;

    for(int i = 0; i < 10001; i++)
    {
        for(int j = 0; j < 10001; j++)
        {
            if(arr[i][j] != 0)
            {
                int checki = 1;
                int checkj = 1;
                for(int k = 0; k < nn; k++)
                {
                    if(i == xx[k])
                    {
                        checki = 0;

                    }
                    if(j == xx[k])checkj = 0;
                }
                if(checki == 1)
                {
                    xx[nn++] = i;
                }
                if(checkj == 1)
                {
                    xx[nn++] = j;
                }

            }
        }
    }
    for(int i = 0; i < nn; i++)
    {
        fprintf(fp, "%d [fillcolor=white, style=filled];\n", xx[i]);
    }
    int *zz = (int *)malloc(10001 * sizeof(int));
    int nnn = 0;
    for(int i = 0; i < nn; i++)
    {
        for(int j = 0; j < nn; j++)
        {
            if(arr[i][j] != 0)
            {
                int check = 1;
                for(int k = 0; k < nnn; k++)
                {
                    if(zz[k] == i * nn + j)
                    {
                        check = 0;
                        break;
                    }
                }
                if(check == 1)
                {
                    fprintf(fp, "%d -- %d;\n", i, j);
                    zz[nnn++] = i * nn + j;
                    zz[nnn++] = j * nn + i;
                }
            }
        }
    }
    fprintf(fp, "}");
    fclose(fp);
}
