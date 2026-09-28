This project creates a grid and pieces using text files and then can determine whether different combinations are possible for those pieces to be on the board while certain spaces remain revealed.

The files do the following:

board.txt:

This file holds the board where the pieces are to be placed. It is composed of and x by y rectangle of open and close brackets with 3 characters in between. 
If all of the characters are spaces or NUL, the square is seen as an invalid place for pieces to be placed and don't count towards the total number of squares.
Otherwise, the characters there are the name of the square. There is functionality for the program to read 3 letter abbreviations for months and days of the week

output.txt:

This file writes out a list of each combination of revealed grid spaces that remain possible.

pieces.txt:

This file holds the pieces that are placed onto the board. Each piece is stored as a name such as X-Piece, a set of points which are the grid spaces that that piece takes up, and whether or not it is rotationally or reflectionally symmetric.

piecesRef.txt:

This is a reference file for the user and demonstrates the shape that each piece takes up visually. This file has no effect on the program.

textEditor.cpp:

Custom text editor file that has specific used for board.txt and pieces.txt. More specifications are found in textEditor.cpp.

piece.h/piece.cpp:

This file defines a class for pieces that are created by the program. Unique functions pieces have are to rotate and flip them.

grid.cpp:

This is the main program that first creates a grid using the board.txt file. Then it creates a list of pieces using pieces.txt. If argv[1] is all, then the program will try to recursively find one solution to each set of possible grid spaces that are left revealed. Otherwise, argv[1+] are the spaces that are left revealed that the code will try to find a solution to.
