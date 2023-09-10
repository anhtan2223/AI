maxCol = 9
maxRow = 9
blockCol = 3
blockRow = 3
runTime = 0

class Coord :
    def __init__(self,x=0,y=0):
        self.x = x 
        self.y = y
    def show(self):
        print("Toa Do (x,y) = (%d,%d)" %(self.x,self.y))
    def indexOf(self):
        return self.x*maxRow + self.y
def positionOfVertex(vertex):
    coord = Coord()
    coord.x = int(vertex/maxRow)
    coord.y = vertex%maxCol
    return coord
class Constrain :
    def __init__(self) :
        self.data = [[0]*81]*81
        self.n = maxRow*maxCol
    def addConstrain(self,source,target):
        # source = Coord()
        # target = Coord()
        u = source.indexOf()
        v = target.indexOf()
        if(self.data[u][v] == 0):
            printf("Add Constrain : %d " %(self.data[u][v]))
            self.data[u][v] = 1
            self.data[v][u] = 1
            return 1
        return 0
    def getConstrain(self,coord):
        # constrain = Constrain()
        # coord = Coord()
        v = coord.indexOf()
        result = []
        for i in range(self.n) :
            if(self.data[v][i] == 1):
                print(self.data[v][i])
                result.append(positionOfVertex(i))
        return result
def speardConstrain(coord,constrain,changed):
    # coord = Coord() 
    # constrain = Constrain()
    # changed = []
    row = coord.x
    col = coord.y
    # print("Speard Coord :")
    # coord.show()
    # print("---")
    for i in range(maxRow):
        if i != row :
            newCoord = Coord(i,col)
            # newCoord.show()
            if(constrain.addConstrain(coord,newCoord)):
                changed.append(newCoord)
    for i in range(maxCol):
        if i != col :
            newCoord = Coord(row,i)
            # newCoord.show()
            if(constrain.addConstrain(coord,newCoord)):
                changed.append(newCoord)
    for i in range(blockCol):
        for j in range(blockRow):
            areaX = int(row/blockRow) * blockCol
            areaY = int(col/blockCol) * blockRow
            if areaX+i != row or areaY+j != col :
                newCoord = Coord(areaX+i,areaY+j)
                # newCoord.show()
                if(constrain.addConstrain(coord,newCoord)):
                    changed.append(newCoord) 
maxValue = 10
empty = 0

class Sudoku :
    def __init__(self,input = None):
        self.cell = [[0]*maxRow]*maxCol if input == None else input
        self.constrain = Constrain()
    def initSudoku(self):
        for i in range(maxRow):
            for j in range(maxCol):
                self.cell[i][j] = empty
    def initSudokuWithValue(self,input):
        self.cell = input
    def show(self):
        print("Sudoku State : !!!")
        print("-------------------------------")
        for row in range(maxRow) :
            for col in range(maxCol) :
                if col % blockCol == 0  : print("|",end='')
                print(" %d " %(self.cell[row][col]),end='')
                if col == maxCol-1 : print("|",end='')
            print("")
            if row%blockRow == blockRow-1 :
                print("-------------------------------")
    def isFilled(self):
        for i in range(maxCol):
            for j in range(maxRow):
                if self.cell[i][j] == empty :
                    return 0
        return 1
    def getAvailableValue(self,coord): #self is Sudoku
        posList = self.constrain.getConstrain(coord)
        availables = [0]*maxValue
        for i in range(1,maxValue):
            availables[i] = 1
        for i in range(len(posList)):
            pos = Coord(posList[i].x,posList[i].y)
            if(self.cell[pos.x][pos.y] != empty):
                # print(self.cell[pos.x][pos.y])
                availables[self.cell[pos.x][pos.y]] = 0
        result = []
        for i in range(1,maxValue):
            if availables[i] != 0 :
                result.append(i)
        return result
    def getNextEmpty(self):
        for i in range(maxRow):
            for j in range(maxCol):
                if self.cell[i][j] == empty :
                    return Coord(i,j)
    def getNextMin(self):
        minLen = maxValue
        for i in range(maxRow):
            for j in range(maxCol):
                if self.cell[i][j] == empty :
                    pos = Coord(i,j)
                    availableLen = len(self.getAvailableValue(pos))
                    if availableLen < minLen :
                        minLen = availableLen
                        result = Coord(i,j)
        return result
    def sudokuBackTracking(self):
        if self.isFilled() : return 1
        position = self.getNextEmpty()
        # position = self.getNextMin()
        # position.show()
        available = self.getAvailableValue(position)
        if len(available) == 0 :
            return 0
        for j in range(len(available)):
            value = available[j]
            self.cell[position.x][position.y] = value
            # runTime += 1
            if(self.sudokuBackTracking()): return 1
            self.cell[position.x][position.y] = empty
        return 0
    def solveSudoku(self):
        self.constrain = Constrain()
        for i in range(maxRow):
            for j in range(maxCol):
                history = []
                pos = Coord(i,j)
                speardConstrain(pos,self.constrain,history)
        runTime = 0
        if self.sudokuBackTracking() == 1 : print("Solved !! \n")
        else : print("Cannot Solve")
        # print("Run Times : %d" %(runTime))

###Main Function
positionOfVertex(13).show()

input = [
        [5,3,0,0,7,0,0,0,0],
        [6,0,0,1,9,5,0,0,0],
        [0,9,8,0,0,0,0,6,0],
        [8,0,0,0,6,0,0,0,3],
        [4,0,0,8,0,3,0,0,1],
        [7,0,0,0,2,0,0,0,6],
        [0,6,0,0,0,0,2,8,0],
        [0,0,0,4,1,9,0,0,5],
        [0,0,0,0,8,0,0,7,9]]

start = Sudoku(input)
start.solveSudoku()
start.show()