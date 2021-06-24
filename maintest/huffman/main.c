#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"
int main()
{
    char buffer[1000];
    Coding huffmanTable[256];
    printf("Nhap chuoi: ");
    gets(buffer);
    HuffmanTree h = makeHuffman(buffer);
    createHuffmanTable(h, huffmanTable, buffer);
    for(int i = 0; i <= 256; i++)
    {
        if(huffmanTable[i].size != 0)
        {
            printf("%c: %s\n", i, huffmanTable[i].bits);
        }
    }
    return 0;
}
