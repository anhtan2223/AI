#include <stdio.h>
#include <stdlib.h>

#define mRow 8
#define mCol 8

typedef struct {
    int data[mRow][mCol];
    int nQueen ; //0->8
}State;
typedef struct {
    int row;
    int col;
}Coord;
void initState(State *S)
{
    S->nQueen = 0;
    int i,j;
    for(i=0;i<mRow;i++)
        for(j=0;j<mCol;j++)
            S->data[i][j] = 0 ;
}
void show(State S)
{
    int i,j;
    printf("State : \n");
    for(i=0;i<mRow;i++)
    {
        for(j=0;j<mCol;j++)
            printf("%2d ",S.data[i][j]);
        printf("\n");
    }
}
int addQueen(State *S,Coord C)
{
    if( S->data[C.row][C.col] != 0 ) return 0;
    //Case can add
    int row = C.row;
    int col = C.col;
    S->data[row][col] = 99;
    int i,j,k = 1;
    for(i=0;i<mRow;i++)
    {
        if(i != row) S->data[i][col]--;
        if(i != col) S->data[row][i]--;
    }
    while(k<8)
    {
        if(row-k > -1 && col-k > -1)
            S->data[row-k][col-k]-- ;
        if(row-k > -1 && col+k < mCol)
            S->data[row-k][col+k]-- ;
        if(row+k < mRow && col-k > -1)
            S->data[row+k][col-k]-- ;
        if(row+k < mRow && col+k < mCol)
            S->data[row+k][col+k]-- ;
        k++ ;
    }
    S->nQueen++;
    return 1;
}
State copyState(State S)
{
    State new ;
    new.nQueen = S.nQueen ; 
    int i,j;
    for(i=0;i<mRow;i++)
        for(j=0;j<=mCol;j++)
            new.data[i][j] = S.data[i][j];
    return new ; 
}
typedef struct Node {
    State state;
    struct Node* parent;
}Node;

void initNode(Node *N)
{
    initState(&N->state);
    N->parent = NULL;
}
int isFull(State S)
{
    int i,j;
    for(i=0;i<mRow;i++)
        for(j=0;j<mCol;j++)
            if( S.data[i][j] == 0) return 0;
    return 1;
}
int countEmpty(State S)
{
    int count = 0;
    int i,j;
    for(i=0;i<mRow;i++)
        for(j=0;j<mCol;j++)
            if(S.data[i][j] == 0) count++ ;
    return count;
}
typedef struct {
    Coord list[64];
    int len ;
}ListCoord;
void initList(ListCoord* L)
{
    L->len = 0;
}
void append(ListCoord *L,Coord C)
{
    L->list[L->len] = C;
    L->len++;
}
Coord pop(ListCoord* L)
{
    L->len = L->len - 1 ;
    return L->list[L->len] ;
}
ListCoord getNextMin(State S)
{
    int Max = -99 ;
    Coord Cmin ;
    ListCoord CLmin;
    initList(&CLmin);
    int i,j ,  arr[64] , len = 0 ;
    for(i=0;i<mRow;i++)
        for(j=0;j<mCol;j++)
        {
            if(S.data[i][j] == 0)
            {
                State copy = copyState(S);
                Coord C = {i,j};
                addQueen(&copy,C);
                int blank = countEmpty(copy);
                // show(copy);
                if(blank > Max)
                {
                Max = blank;
                printf("Count blank : %d\n",blank);
                append(&CLmin,C);
                } 
            }
        }
    return CLmin;
}
int count;
Node* solveProblem(Node* root)
{
    count++;
    printf("%d\n",count);
    int i,j;
    for(i=0;i<mRow;i++)
        for(j=0;j<mCol;j++)
        {
            if(root->state.data[i][j] == 0)
            {
                Node* newNode = (Node*)malloc(sizeof(Node));
                newNode->parent = root ;
                newNode->state = copyState(root->state);
                Coord C = {i,j};
                addQueen(&newNode->state,C);
                show(newNode->state);
                if(newNode->state.nQueen == 8) return newNode; 
                return solveProblem(newNode);
            }
        }
}
State solveProblem2(State S)
{
    if(S.nQueen == 8) return S;
    else if(isFull(S) || S.nQueen + countEmpty(S) < 8) 
    {
        printf("Fail One Case");
        // return NULL;
    }
    ListCoord next = getNextMin(S);
    printf("Len : %d \n",next.len);
    while(next.len != 0)
    {
        Coord C = pop(&next);
        // printf("(row,col) = (%d,%d)\n",C.row,C.col);
        State Snew = copyState(S);
        addQueen(&Snew,C);
        show(Snew);
        solveProblem2(Snew);
    }
}
int main()
{
    Node* root = (Node*) malloc(sizeof(Node));
    initNode(root);
    printf("---------- Start ----------\n");
    show(root->state);
    
    Coord C1 = {0,4};
    addQueen(&root->state,C1);

    Coord C2 = {1,1};
    addQueen(&root->state,C2);

    Coord C3 = {2,3};
    addQueen(&root->state,C3);

    // Coord C4 = {3,6};
    // addQueen(&root->state,C4);

    // Coord C5 = {4,2};
    // addQueen(&root->state,C5);


    show(root->state);
    printf("Run Function ");



    // State result = solveProblem2(root->state);
    Node* result = solveProblem(root);

    show(result->state);

    

    // printf("Result : %d\n",result->state.nQueen);
    // show(result->state);
    // if(result == NULL) printf("Hi");
    // show(result->state);
}