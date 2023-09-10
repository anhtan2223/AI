def show(self):
        print("Sudoku State : !!!")
        print("-------------------------------\n")
        for row in range(maxRow) :
            for col in range(maxCol) :
                if col % blockCol == 0  : print("|")
                print(" %d " %(self.cell[row][col]))
                if col == maxCol-1 : print("|")
            print("\n")
            if row%blockRow == blockRow-1 :
                print("-------------------------------\n")