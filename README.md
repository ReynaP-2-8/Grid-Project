This project creates a grid and pieces using text files and then can determine whether different combinations are possible for those pieces to be on the board while certain spaces remain revealed.

The files do the following:
board.txt:
This file holds the board where the pieces are to be placed. It is composed of and x by y rectangle of open and close brackets with 3 characters in between. 
If all of the characters are spaces, the square is seen as an invalid place for pieces to be placed and don't count towards the total number of squares.
Otherwise, the characters there are the name of the square. There is functionality for the program to read 3 letter abbreviations for months and days of the week

output.txt:

pieces.txt:

piecesRef.txt:

textEditor.cpp:

piece.h/piece.cpp:

grid.cpp:
