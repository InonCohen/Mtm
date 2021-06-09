CC = gcc 
OBJS = map_test.o map.o
EXEC = map.out
DEBUG_FLAGS = -g
COMP_FLAGS = -std=c99 -Wall -pedantic-errors -Werror -Wextra -Wconversion 
BUILD_O_FILE = $(CC) -c $(DEBUG_FLAGS) $(COMP_FLAGS)

$(EXEC): $(OBJS)
	$(CC) $(DEBUG_FLAGS) $(COMP_FLAGS) $(OBJS) -o $@
	
map_test.o: ../tests/map_example_test.c ../test_utilities.h map.h
	$(BUILD_O_FILE) ../tests/map_example_test.c	-o $@
	
map.o: map.c map.h
	$(BUILD_O_FILE) map.c -o $@
	
clean:
	rm -f $(OBJS) $(EXEC)

