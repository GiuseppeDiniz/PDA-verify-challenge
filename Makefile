APPS = ./apps
BIN = ./bin
INCLUDE = ./include
LIB = ./lib
OBJ = ./obj
SRC = ./src

FLAGS = -O3 -Wall
LIBS = -lm -led -L $(LIB)

all: libed app

libed: \
	$(OBJ)/stack.o 
	ar -rcs $(LIB)/libed.a $(OBJ)/*.o


app: clean_apps \
	$(BIN)/app

$(OBJ)/%.o: $(SRC)/%.cpp $(INCLUDE)/%.h
	g++ $(FLAGS) -c $< -I $(INCLUDE) -o $@

$(BIN)/%: $(APPS)/%.cpp
	g++ $(FLAGS) $< $(LIBS) -I $(INCLUDE) -o $@

run:
	$(BIN)/app

clean:
	rm -rf $(BIN)/* $(LIB)/* $(OBJ)/*

clean_apps:
	rm -rf $(BIN)/*