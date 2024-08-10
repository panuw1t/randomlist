CC = gcc

SRCS = main.c

.PHONY = all clean test

all: randomlist

randomlist: ${SRCS}  
	@echo "compile main"
	${CC} -o ./build/randomlist main.c
	
clean: .\build\randomlist.exe
	@echo "Cleaning up..."
	del .\build\randomlist.exe
	
test: .\build\randomlist.exe .\build\list.txt
	@echo "Test beginning..."
	.\build\randomlist.exe .\build\list.txt
