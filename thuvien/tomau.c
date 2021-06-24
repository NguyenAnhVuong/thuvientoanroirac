#include "tomau.h"
void docfile(char *filename)
{
    FILE  *fp = fopen(filename, "r");
    dinh = (int *)malloc(10001 * sizeof(int));
    mau = (int *)malloc(10001 * sizeof(int));
    matran = (int **)malloc(sizeof(int *) * 10001);
    for(int i = 0; i < 10001; i++)
    {
        matran[i] = (int *)malloc(10001 * sizeof(int));
    }
    if(fp == NULL)
    {
        printf("Co loi khi mo file!\n");
        exit(0);
    }
    else
    {
        fscanf(fp, "%d %d", &sodinh, &socanh);
        for(int i = 0; i < sodinh; i++)
        {
            for(int j = 0; j < sodinh; j++)
            {
                matran[i][j] = 0;
            }
            mau[i] = 0;
        }
        int x, y;
        while(fscanf(fp, "%d %d", &x, &y) != EOF)
        {
            matran[x - 1][y - 1] = 1;
            matran[y - 1][x - 1] = 1;
        }
    }
    fclose(fp);
}
void tomau()
{
    for(int i = 0; i < sodinh; i++)
    {
        int *mautrung = (int *)calloc(100, sizeof(int));
        int x = 0;
        for(int j = 0; j < sodinh; j++)
        {
            if(matran[i][j] == 1 && j != i)
            {
                mautrung[x++] = mau[j];
            }
        }
        for(int k = 1; k <= 10; k++)
        {
            int y = 1;
            for(int l = 0; l < x; l++)
            {
                if(k == mautrung[l])
                {
                    y = 0;
                    break;
                }
            }
            if(y == 1)
            {
                mau[i] = k;
                break;
            }
        }
    }
}
void xuatfile(char *filein, char *fileout)
{
    FILE *fp = fopen(fileout, "w");
    FILE *fp1 = fopen(filein, "r");
    char color[20][20] = {"red", "green", "blue","yellow","orange","purple","gray","pink","brown", "white"};
    int w,e;
    if(fp == NULL)
    {
        printf("Co loi khi mo file!!!\n");
        exit(0);
    }
    else
    {
        fprintf(fp,"graph dothi\n{\n");
        for(int i = 0; i < sodinh; i++)
        {
            fprintf(fp, "%d [fillcolor=%s, style=filled];\n", i + 1, color[mau[i] - 1]);
        }
        fscanf(fp1, "%d %d", &w, &e);
        for(int i = 0; i < socanh; i++)
        {
            fscanf(fp1, "%d %d", &w, &e);
            fprintf(fp, "%d -- %d;\n", w, e);
        }
        fprintf(fp,"}");
    }
    fclose(fp);
    fclose(fp1);
}
