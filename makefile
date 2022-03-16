# makefile

CC=gcc
SRCDIR=src/
OBJDIR=obj/

SRC = $(wildcard src/*.cpp)
TMP=$(patsubst %.cpp, %.o, $(SRC))
OBJ=$(patsubst src/%.o, obj/%.o, $(TMP))
EXEC = motLePlusLong

ALL : $(EXEC)
	@echo "debut de all"

$(EXEC) : $(OBJ)
	@echo "========================"
	@echo "build de l'executable $@"
#	@echo "SRCDIR = $(SRCDIR)"
#	@echo "OBJDIR = $(OBJDIR)"
	$(CC) $(OBJ) -o $(EXEC)
	@chmod +x $(EXEC)

obj/%.o: src/%.cpp
	@echo "---------------"
	@echo "build de l'objet $@"
	$(CC) $< -c -o $@

clean:
	@echo "make clean"
	@echo "SRC = $(SRC)"
	@echo "OBJ = $(OBJ)"
	@rm obj/*o
	@rm $(EXEC)