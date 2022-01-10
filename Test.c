#include "Gragh.h"
#include <stdio.h>

void menu();

int main()
{
    int VertexNum, edgeNum;
    int i, o, indegree[MaxVertexNum] = {0};
    PtrToMatrixGragh MG;
    PtrToListGragh LG;
    while (1)
    {
        menu();
        printf("Please input the number of vertex and edges\n>");
        scanf("%d %d", &VertexNum, &edgeNum);
        if (edgeNum > VertexNum * 2)// If edgeNum bigger than vertexNum then use adjacency matrix,else use adjacency list
        {
            MG = MatrixConstruct(VertexNum, edgeNum);
            Mjudge(MG);
        }
        else
        {
            LG = ListConstruct(VertexNum, edgeNum);
            Ljudge(LG);
        }
        puts("");
    }
    return 0;
}

void menu()
{
    printf("Is it an acyclic graph?\n");
}