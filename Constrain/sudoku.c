#include <stdio.h>

#define mRow 9
#define mCol 9
#define colBlock 3
#define rowBlock 3

//Toa Do
typedef struct
{
	int row;
	int col;
}ToaDo;

typedef struct
{
	int size;
	ToaDo List[mRow * mCol];
}ListTD; //Dung Luu Tru Toa Do
void initListTD(ListTD *L)
{
	L->size = 0;
}
void appendListTD(ListTD *L,ToaDo x)
{	
	L->List[L->size] = x;
	L->size++;
    
}
void printCor(ToaDo T)
{
	printf("Toa Do : (%d,%d)\n",T.row,T.col);
}
//Done
//Rang Buoc
typedef struct
{
	int no_v;
	int data[mRow*mCol][mRow*mCol] ; //Chua cac dinh tu 0->80 -> theo dinh ne
	//Check Relationship giua 2 vertex -> Yes -> 1 , No -> 0 ; -> Co rela -> value != nhau
}RangBuoc;

void initRB(RangBuoc *RB)
{
	int i,j;
	for(i=0;i<mRow*mCol;i++)
		for(j=0;j<mRow*mCol;j++)
			RB->data[i][j] = 0;
	RB->no_v = mRow*mCol;
}
//Done
//Vertex and Coord
int toVertex(ToaDo T)
{
	return T.row*mRow + T.col ;
}
ToaDo toCoord(int V)
{
	ToaDo result;
	result.row = V/mRow;
	result.col = V%mCol;
	return result;
}
//OKe
int addRB(RangBuoc* RB , ToaDo R,ToaDo T)
{
	int u = toVertex(R);
	int v = toVertex(T);
	
	if(RB->data[u][v]) return 0;
	RB->data[u][v] = 1;
	RB->data[v][u] = 1;
	return 1;
}

ListTD getRB(RangBuoc RB,ToaDo T)
{
	ListTD result;
    initListTD(&result);
	int u = toVertex(T);
	int v;
	for( v=0 ; v < RB.no_v ; v++)
		if(RB.data[u][v] == 1) appendListTD(&result,toCoord(v));
	return result;
}
//GetStart State
typedef struct{
	int state[mRow][mCol];
	RangBuoc RB;
}State; //Sudoku -> coord

#define empty 0

void initStateNull(State *S)
{
	initRB(&S->RB);
	int i,j;
	for(i=0;i<mRow;i++)
		for(j=0;j<mCol;j++)
			S->state[i][j] = empty;
}
void initStateInput(State *S,int Input[mRow][mCol])
{
	initRB(&S->RB);
	int i,j;
	for(i=0;i<mRow;i++)
		for(j=0;j<mCol;j++)
			S->state[i][j] = Input[i][j];
}
void show(State S)
{
	int row,col;
	printf("Sudoku:\n");
    printf("-------------------------------\n");
	for(row=0;row<mRow;row++)
	{
		for(col=0;col<mCol;col++)
            {
                if(col % colBlock == 0 ) printf("|");
                printf(" %d ",S.state[row][col]);
                if(col == mCol-1) printf("|");
            }
		printf("\n");
        if(row%rowBlock == rowBlock-1)
            printf("-------------------------------\n");
	}
}
//Oke
int checkGoal(State S)
{
	int i,j;
	for(i=0;i<mRow;i++)
		for(j=0;j<mCol;j++)
			if(S.state[i][j] == empty) return 0;
	return 1;
}
void LanTruyenRB(ToaDo start,RangBuoc* RB,ListTD *ViTri)
{
	int row = start.row;
	int col = start.col;
	int i,j;
    
	//Lan Truyen theo Row 
	for(i=0;i<mCol;i++) 
		if(i != col)
        {
            ToaDo sameRow = {row,i};
            if(addRB(RB,start,sameRow))
                appendListTD(ViTri,sameRow);
        }
    
	//Lan Truyen theo Column
    for(i=0;i<mRow;i++)
        if(i != row)
        {
            ToaDo sameCol = {i,col};
            if(addRB(RB,start,sameCol))
                appendListTD(ViTri,sameCol);
        }

	//Lan Truyen theo Block
    int rBlock = row/rowBlock;
    int cBlock = col/colBlock;
    for(i=rBlock*rowBlock ; i<rBlock*rowBlock+rowBlock ; i++)
        for(j= cBlock*colBlock ; j<cBlock*colBlock+colBlock ; j++)
            {
                if(i == row && j == col) continue;
                ToaDo sameBlock = {i,j};
                if(addRB(RB,start,sameBlock))
                    appendListTD(ViTri,sameBlock);
            }
}
//Tim Mien Gia Tri cho mot O trong 
typedef struct {
    int data[mRow+1];
    int size;
}List;
void appendList(List *L,int x)
{
    L->data[L->size] = x;
    L->size++;
}
List getAvailValue(ToaDo T,State S)
{
    ListTD DSRangBuoc = getRB(S.RB,T);
    int avail[mRow+1]; //Use 1->9
    int i;
    for(i=0;i<mRow+1;i++)
        avail[i] = 1;
    for(i = 0 ; i < DSRangBuoc.size ; i++)
    {
        ToaDo haveCons = DSRangBuoc.List[i];
        // printCor(haveCons);
        if(S.state[haveCons.row][haveCons.col] != empty)
            avail[S.state[haveCons.row][haveCons.col]] = 0;
    }
    List result;
    result.size = 0;
    for( i=1 ; i<=mRow ; i++) //1->9
        if(avail[i]) appendList(&result,i);
    return result;
}
ToaDo getNextEmpty(State S)
{
    int i,j;
    // ToaDo temp = {-1,-1};
    for(i=0;i<mRow;i++)
        for(j=0;j<mCol;j++)
        {
            ToaDo temp = {i,j};
            if(S.state[i][j] == empty) return temp;
        }
    // return temp ;
}
ToaDo getNextMin(State S)
{
    int minLen = 10;
    int row,col;
    ToaDo result;
    for(row=0;row<mRow;row++)
        for(col=0;col<mCol;col++)
            if(S.state[row][col] == empty)
            {
                ToaDo temp = {row,col};
                int aLen = getAvailValue(temp,S).size;
                if(aLen < minLen)
                {
                    minLen = aLen;
                    result = temp;
                }
            }
    return result ;
}
int RunTime = 0;
int runCallBack(State *S)
{
    if(checkGoal(*S)) return 1;  

    ToaDo next = getNextMin(*S);
    List avail = getAvailValue(next,*S);

    
    if(avail.size == 0) 
    {
        printf("### Fail One Case -> BackTrack\n");
        return 0;
    }
    int i;
    for( i=0 ; i < avail.size ; i++)
    {
        int value = avail.data[i];
        S->state[next.row][next.col] = value;
        RunTime++;
        if(runCallBack(S)) return 1;
        S->state[next.row][next.col] = empty;//Quay Lui neu fail
    }
    return 0;
}
State solveSudoku(State S)
{
    initRB(&S.RB);
    int row,col;
    for(row=0;row<mRow;row++)
        for(col=0;col<mCol;col++)
        {
            ListTD history;
            initListTD(&history);
            ToaDo T = {row,col};
            LanTruyenRB(T,&S.RB,&history);
        }
    RunTime = 0;
        printf("####Create Constrain Done !!####\n");

    if(runCallBack(&S)) 
        printf("Success !!\n");
    else printf("Canot Solve !! \n");

    printf("RunTime : %d \n",RunTime);
    return S;
}

int main()
{
	printCor(toCoord(5));
	State start;
    int input[9][9] = 
    {
        {5,3,0,0,7,0,0,0,0},
        {6,0,0,1,9,5,0,0,0},
        {0,9,8,0,0,0,0,6,0},
        {8,0,0,0,6,0,0,0,3},
        {4,0,0,8,0,3,0,0,1},
        {7,0,0,0,2,0,0,0,6},
        {0,6,0,0,0,0,2,8,0},
        {0,0,0,4,1,9,0,0,5},
        {0,0,0,0,8,0,0,7,9}
    };
    // int input[4][4] =
    // {
    //     {0,0,0,0},
    //     {0,0,0,0},
    //     {0,0,0,0},
    //     {0,0,0,0}
    // };
    initStateInput(&start,input);
	show(start);

    printf("\n\nRun Sudoku : \n\n");
    State resultS = solveSudoku(start);

    // ToaDo a = {0,0};
    // ToaDo b = {0,8};
    // printf("Check : %d\n",addRB(&start.RB,a,b));

    show(resultS);
	// printf("%d",checkGoal(test));


	return 0;
}