#
#
#  _____  ______          _____  __  __ ______ 
# |  __ \|  ____|   /\   |  __ \|  \/  |  ____|
# | |__) | |__     /  \  | |  | | \  / | |__   
# |  _  /|  __|   / /\ \ | |  | | |\/| |  __|  
# | | \ \| |____ / ____ \| |__| | |  | | |____ 
# |_|  \_\______/_/    \_\_____/|_|  |_|______|
#                                              
#
#                                              


1. FIRST STEPS:
	Download this directory.
	Add your own chess's (c & h) files into this directory.
	Add your map.c into mtm_map.

2. COMPILING MAP:
	Get from terminal inside mtm_map directory and call make.

3. COMPILING CHESS:
	Use your own makefile or run from terminal the next line:
		gcc -g -std=c99 -o chessSystem -Wall -pedantic-errors -Werror -Wconversion -Wextra *.c  ./tests/chessSystemTestsExample.c ./mtm_map/map.c
		
		
4. BONUS: 
	If you want another long test for chess just uncomment lines 1416, 1448 in ./tests/chessSystemTestsExample.c 
	It will seems like it stuck but donwt worry it is just a long time test.
		
5. CHESS OUTPUT FILES:
	The tester create your output files, compare them to the expected files and then remove your files.
	If all of your tests pass you won't see any of your output files.
	Otherwise you might see your output files inside actual_output directory (don't worry the tester create it by itself).
	I recommend you to run valgrind after all your tests pass (in that way you will be sure all files are closed as required).
	

6. PAY ATTENTION: I've used additional compiling flags (i.e. -Werror), you can change them if you like (I suggest you to not).
7. No memory leaks were founded using this tests.
8. The tests and the output files are compatible to UNIX operating systems and were checked on them.

For bug reports you gotta know how to find me :)
ENJOY !!!

