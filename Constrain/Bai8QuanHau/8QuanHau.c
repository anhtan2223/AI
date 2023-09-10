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
void showR(State S)
{
    int i,j;
    printf("State : \n");
    for(i=0;i<mRow;i++)
    {
        for(j=0;j<mCol;j++)
            printf("%2d ",S.data[i][j] == 99 ? S.data[i][j] : 0);
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
int count;
int backtracking(State *S)
{
    count++;
    if(S->nQueen == 8) return 1;
    if(isFull(*S)) return 0;
    State back = copyState(*S);
    int i,j ;
    for(i=0;i<mRow;i++)
        for(j=0;j<mCol;j++)
            if(S->data[i][j] == 0)
            {
                Coord C = {i,j};
                addQueen(S,C);
                if(backtracking(S)) return 1;
                *S = back ;
            }
    return 0; //Run het case van k co gi thi return 0
}
int main()
{
    State root;
    initState(&root);
    printf("---------- Start ----------\n");
    show(root);
    
    // Coord C1 = {0,4};
    // addQueen(&root->state,C1);

    // Coord C2 = {1,1};
    // addQueen(&root->state,C2);

    // Coord C3 = {2,3};
    // addQueen(&root->state,C3);

    // Coord C4 = {3,6};
    // addQueen(&root->state,C4);

    // Coord C5 = {4,2};
    // addQueen(&root->state,C5);
    backtracking(&root);
    printf("RunTime : %d \n",count);

    showR(root);
    // if(result == NULL) printf("\n\n NULL Value Bro");
    // else showR(result->state);
}