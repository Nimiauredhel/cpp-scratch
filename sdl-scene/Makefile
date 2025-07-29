SOURCE= *.cpp
PROGRAM=program
EXE_NAME=$(PROGRAM)
ARGS=
BUILD_DIR=build/
EXE_PATH=$(BUILD_DIR)$(EXE_NAME)
INC=
LIBS=-lSDL2 -lSDL2main -lSDL2_image
DEFAULT_FLAGS= -std=c++14 -Werror=narrowing
STRICT_FLAGS= $(DEFAULT_FLAGS) -Wall -pedantic -Wextra -Weffc++
DEBUG_FLAGS= $(STRICT_FLAGS) -g -o0

default:
	mkdir $(BUILD_DIR)
	g++ $(SOURCE) $(DEFAULT_FLAGS) $(INC) $(LIBS) -o $(EXE_PATH)
	make post
                                     
strict:                              
	mkdir $(BUILD_DIR)
	bear -- g++ $(SOURCE) $(STRICT_FLAGS) $(INC) $(LIBS) -o $(EXE_PATH)
	make post
                    
debug:              
	mkdir $(BUILD_DIR)
	g++ $(SOURCE) $(DEBUG_FLAGS) $(INC) $(LIBS) -o $(EXE_PATH)
	make post

.ONESHELL:
run:
	 cd $(BUILD_DIR); ./$(EXE_NAME) $(ARGS)

andrun:
	make default
	make run

gdb:
	cd $(BUILD_DIR); gdb ./$(EXE_NAME) $(ARGS)

valgrind:
	cd $(BUILD_DIR); valgrind -s --leak-check=yes --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(EXE_NAME) $(ARGS)

clean:
	rm -rf $(BUILD_DIR)
	rm -f compile_commands.json

post:
	cp -r textures $(BUILD_DIR)

