#include "Gragh.h"
#include "Queue.h"
#include "Stack.h"
#include "fatal.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int LocateMatrixVertex(PtrToMatrixGragh MG, VertexType V)
{
    for (int i = 0; i < MG->VertexNum; i++)
        if (MG->vertex[i] == V)
            return i;
    Error("Fail,there isn't corresponding vertex\n");
}

PtrToMatrixGragh MatrixConstruct(int VertexNum, int edgeNum)
{
    int i;
    PtrToMatrixGragh G = (PtrToMatrixGragh)malloc(sizeof(struct MatrixGragh));
    memset(G->edge, 0, sizeof(G->edge));
    memset(G->vertex, 0, sizeof(G->vertex));
    G->VertexNum = VertexNum;
    G->edgeNum = edgeNum;
    printf("Please input each vertex\n>");
    for (i = 0; i < G->VertexNum; i++)
    {
        getchar();
        scanf("%c", &G->vertex[i]);
    }
    printf("Please input each edge\n>");
    for (i = 0; i < G->edgeNum; i++)
    {
        VertexType a, b;
        getchar();
        scanf("%c %c", &a, &b);
        G->edge[LocateMatrixVertex(G, a)][LocateMatrixVertex(G, b)] = 1;
    }
    return G;
}

Stack MFindCircle(VertexType V, PtrToMatrixGragh MG)
{
    int i, t;
    VertexType TmpVertex = V, Cur, Tmp;
    Stack Q1 = createStack(MaxVertexNum), nS = NULL;
    MakeEmpty(Q1);
    for (i = 0; i < MG->VertexNum; i++)
        if (MG->edge[LocateMatrixVertex(MG, TmpVertex)][i] == 1)
        {
            MG->edge[LocateMatrixVertex(MG, TmpVertex)][i] = 0;
            Cur = MG->vertex[i];
            break;
        }
    push(TmpVertex, Q1);
    while (Cur != TmpVertex)
    {
        push(Cur, Q1);
        t = -1;
        for (i = 0; i < MG->VertexNum; i++)
            if (MG->edge[LocateMatrixVertex(MG, Cur)][i] == 1)
            {
                MG->edge[LocateMatrixVertex(MG, Cur)][i] = 0;
                Cur = MG->vertex[i];
                t = i;
                break;
            }
        while (t == -1)
        {
            if (IsEmpty(Q1))
                return nS;
            Tmp = top(Q1);
            pop(Q1);
            t = -1;
            for (i = 0; i < MG->VertexNum; i++)
                if (MG->edge[LocateMatrixVertex(MG, Tmp)][i] == 1)
                {
                    MG->edge[LocateMatrixVertex(MG, Tmp)][i] = 0;
                    t = i;
                    break;
                }
            if (t != -1)
            {
                Cur = MG->vertex[t];
                push(Tmp, Q1);
            }
        }
    }
    return Q1;
}

int Mjudge(PtrToMatrixGragh MG) // Achive by Topological Sort
{
    int indegree[MaxVertexNum] = {0};
    int i, o;
    int visite = 0;
    PtrToMatrixGragh TMG = MG;
    VertexType TmpVertex;
    Stack S = createStack(MaxVertexNum);
    MakeEmpty(S);
    Queue Q = createQueue(MaxVertexNum);
    makeEmpty(Q);
    for (i = 0; i < MG->VertexNum; i++) // Culculating the indegree of every vertex
        for (o = 0; o < MG->VertexNum; o++)
            if (MG->edge[o][i] == 1)
                indegree[i]++;
    for (i = 0; i < MG->VertexNum; i++)
        if (indegree[i] == 0)
        {
            enqueue(MG->vertex[i], Q);
            visite++;
        }
    TmpVertex = MG->vertex[0];
    while (!isEmpty(Q))
    {
        int i;
        char Tmp = frontAndDequeue(Q);
        for (i = 0; i < MG->VertexNum; i++)
        {
            if (MG->edge[LocateMatrixVertex(MG, Tmp)][i] == 1)
            {
                indegree[i]--;
                if (indegree[i] == 0)
                {
                    visite++;
                    enqueue(MG->vertex[i], Q);
                }
                else
                {
                    for (int j = 0; j < MG->VertexNum; j++)
                    {
                        if (MG->edge[LocateMatrixVertex(MG, MG->vertex[i])][j] == 1)
                        {
                            TmpVertex = MG->vertex[i];
                            S = MFindCircle(TmpVertex, MG);
                            if (S != NULL)
                            {
                                printf("No it isn't an acyclic graph.\nThe cycle is :");
                                TmpVertex = top(S);
                                pop(S);
                                while (!IsEmpty(S))
                                {
                                    printf("%c-", top(S));
                                    pop(S);
                                }
                                printf("%c\n", TmpVertex);
                                disposeStack(S);
                                disposeQueue(Q);
                                return 0;
                            }
                            break;
                        }
                    }
                }
            }
        }
    }
    if (visite == MG->VertexNum)
    {
        printf("Yes it is an acyclic graph.\nThe indegree of each vertex is :\n");
        for (i = 0; i < MG->VertexNum; i++)
            printf("%c %d\n", MG->vertex[i], indegree[i]);
        disposeQueue(Q);
        disposeStack(S);
        return 1;
    }
    S = MFindCircle(TmpVertex, MG);
    if (S != NULL)
    {
        TmpVertex = top(S);
        pop(S);
        printf("No it isn't an acyclic graph.\nThe cycle is :\n");
        while (!IsEmpty(S))
        {
            printf("%c-", top(S));
            pop(S);
        }
        printf("%c\n", TmpVertex);
        disposeStack(S);
        disposeQueue(Q);
        return 0;
    }
    else
    {
        disposeStack(S);
        disposeQueue(Q);
        return 0;
    }
}

int LocateListVertex(PtrToListGragh LG, VertexType V)
{
    int i;
    for (i = 0; i < LG[0].size; i++)
    {
        if (V == LG[i].data)
            return i;
    }
    Error("Fail,there isn't corresponding vertex\n");
}

PtrToListGragh ListConstruct(int VertexNum, int edgeNum)
{
    int i;
    PtrToListGragh G = (PtrToListGragh)malloc(sizeof(struct ListVertexNode) * MaxVertexNum);
    PtrToListGraghEdge Tmp = NULL, Cur = NULL;
    if (VertexNum == 0)
        Error("No Vertex\n");
    printf("Please input each vertex\n>");
    for (i = 0; i < VertexNum; i++)
    {
        getchar();
        scanf("%c", &G[i].data);
        G[i].firstedge = NULL;
        G[i].size = VertexNum;
    }
    printf("Please input each edge\n>");
    for (i = 0; i < edgeNum; i++)
    {
        VertexType a, b;
        getchar();
        scanf("%c %c", &a, &b);
        for (int j = 0; j < VertexNum; j++)
        {
            if (G[j].data == a)
            {
                if (G[j].firstedge == NULL)
                {
                    G[j].firstedge = (PtrToListGraghEdge)malloc(sizeof(struct ListEdgeNode));
                    G[j].firstedge->Vertex = b;
                    G[j].firstedge->next = NULL;
                    Cur = G[j].firstedge;
                }
                else
                {
                    Tmp = (PtrToListGraghEdge)malloc(sizeof(struct ListEdgeNode));
                    Cur->next = Tmp;
                    Tmp->Vertex = b;
                    Tmp->next = NULL;
                    Cur = Tmp;
                }
            }
        }
    }
    return G;
}

Stack LFindCircle(VertexType V, PtrToListGragh LG)
{
    PtrToListGraghEdge Cur = NULL;
    PtrToListGragh Tmp2 = LG;
    VertexType TmpVertex1 = V;
    Stack S = NULL;
    Stack Q1 = createStack(MaxVertexNum);
    MakeEmpty(Q1);
    VertexType V1;
    Cur = Tmp2[LocateListVertex(LG, TmpVertex1)].firstedge;
    push(TmpVertex1, Q1);
    while (Cur != NULL && Cur->Vertex != TmpVertex1)
    {
        push(Cur->Vertex, Q1);
        Cur = Tmp2[LocateListVertex(LG, Cur->Vertex)].firstedge;
        while (Cur == NULL)
        {
            if (IsEmpty(Q1))
                return S;
            V1 = top(Q1);
            pop(Q1);
            if (Tmp2[LocateListVertex(LG, V1)].firstedge != NULL)
            {
                Cur = Tmp2[LocateListVertex(LG, V1)].firstedge->next;
                Tmp2[LocateListVertex(LG, V1)].firstedge = Cur;
            }
            if (Cur != NULL)
                push(V1, Q1);
        }
        if (Cur == NULL)
            return S;
    }
    VertexType FV = top(Q1);
    push(FV, Q1);
    return Q1;
}

int Ljudge(PtrToListGragh LG) // Achive by Topological Sort
{

    int indegree[MaxVertexNum];
    int size = LG[0].size;
    int indeg[MaxVertexNum];
    int visite = 0;
    Stack Q1 = createStack(MaxVertexNum);
    MakeEmpty(Q1);
    PtrToListGraghEdge Cur = NULL;
    Queue Q = createQueue(MaxVertexNum);
    makeEmpty(Q);
    VertexType TmpVertex, TmpVertex1;
    PtrToListGragh Tmp = LG, Tmp1 = LG;
    memset(indegree, 0, sizeof(indegree));
    int i;
    for (i = 0; i < size; i++) // Culculating the indegree of every vertex
    {
        Cur = Tmp[i].firstedge;
        while (Cur != NULL)
        {
            indegree[LocateListVertex(LG, Cur->Vertex)]++;
            Cur = Cur->next;
        }
    }
    for (i = 0; i < size; i++)
    {
        if (indegree[i] == 0)
        {
            enqueue(Tmp1[i].data, Q);
            visite++;
        }
        indeg[i] = indegree[i];
    }
    TmpVertex1 = LG[0].data;
    while (!isEmpty(Q))
    {
        TmpVertex = frontAndDequeue(Q);
        while (Tmp1[LocateListVertex(LG, TmpVertex)].firstedge != NULL)
        {
            indegree[LocateListVertex(LG, Tmp1[LocateListVertex(LG, TmpVertex)].firstedge->Vertex)]--;
            if (indegree[LocateListVertex(LG, Tmp1[LocateListVertex(LG, TmpVertex)].firstedge->Vertex)] == 0)
            {
                VertexType temp = Tmp1[LocateListVertex(LG, TmpVertex)].firstedge->Vertex;
                enqueue(Tmp1[LocateListVertex(LG, temp)].data, Q);
                visite++;
            }
            else
            {
                if (Tmp1[LocateListVertex(LG, Tmp1[LocateListVertex(LG, TmpVertex)].firstedge->Vertex)].firstedge != NULL)
                {
                    TmpVertex1 = Tmp1[LocateListVertex(LG, TmpVertex)].firstedge->Vertex;
                    Q1 = LFindCircle(TmpVertex1, LG);
                    if (Q1 != NULL)
                    {
                        printf("No it isn't an acyclic graph.\nThe cycle is :");
                        TmpVertex1 = top(Q1);
                        pop(Q1);
                        while (!IsEmpty(Q1))
                        {
                            printf("%c-", top(Q1));
                            pop(Q1);
                        }
                        printf("%c\n", TmpVertex1);
                        disposeStack(Q1);
                        return 0;
                    }
                }
            }
            Tmp1[LocateListVertex(LG, TmpVertex)].firstedge = Tmp1[LocateListVertex(LG, TmpVertex)].firstedge->next;
        }
    }
    if (visite == size)
    {
        printf("Yes it is an acyclic graph.\nThe indegree of each vertex is :\n");
        for (i = 0; i < LG[0].size; i++)
            printf("%c %d\n", LG[i].data, indeg[i]);
        return 1;
    }
    Q1 = LFindCircle(TmpVertex1, LG);
    if (Q1 != NULL)
    {
        printf("No it isn't an acyclic graph.\nThe cycle is :");
        TmpVertex1 = top(Q1);
        pop(Q1);
        while (!IsEmpty(Q1))
        {
            printf("%c-", top(Q1));
            pop(Q1);
        }
        printf("%c\n", TmpVertex1);
        disposeStack(Q1);
        return 0;
    }
    else
        return 0;
}
