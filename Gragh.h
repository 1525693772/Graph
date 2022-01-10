#define MaxVertexNum 100
#define MaxEdgeNum 100

typedef char VertexType;

struct MatrixGragh
{
    VertexType vertex[MaxVertexNum];
    int edge[MaxEdgeNum][MaxEdgeNum];
    int VertexNum, edgeNum;
};


struct ListEdgeNode
{
    VertexType Vertex;
    struct ListEdgeNode *next;
};
struct StackRecord;
typedef struct StackRecord* Stack;
struct ListVertexNode
{
    VertexType data;
    int size;
    struct ListEdgeNode *firstedge;
};


typedef struct MatrixGragh *PtrToMatrixGragh;
typedef struct ListVertexNode *PtrToListGragh;
typedef struct ListEdgeNode *PtrToListGraghEdge;

Stack MFindCircle(VertexType V, PtrToMatrixGragh MG);
int LocateMatrixVertex(PtrToMatrixGragh MG, VertexType V);
PtrToMatrixGragh MatrixConstruct(int VertexNum, int edgeNum);
int Mjudge(PtrToMatrixGragh MG);

Stack LFindCircle(VertexType V, PtrToListGragh LG);
int LocateListVertex(PtrToListGragh LG, VertexType V);
PtrToListGragh ListConstruct(int VertexNum, int edgeNum);
int Ljudge(PtrToListGragh LG);

