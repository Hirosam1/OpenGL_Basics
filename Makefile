
INCLUDE = ./include
SRC_DIR = src
OBJ_DIR = objs

GAME_MAN_SRC = $(wildcard $(SRC_DIR)/game_managing/*.cpp) 
GAME_MAN_OBJS = $(patsubst $(SRC_DIR)/game_managing/%.cpp,$(OBJ_DIR)/%.o,$(GAME_MAN_SRC))

GAME_OBJ_SRC = $(wildcard $(SRC_DIR)/game_object/*.cpp) 
GAME_OBJ_OBJS = $(patsubst $(SRC_DIR)/game_object/%.cpp,$(OBJ_DIR)/%.o,$(GAME_OBJ_SRC))

GAME_TOO_SRC = $(wildcard $(SRC_DIR)/game_tools/*.cpp) 
GAME_TOO_OBJS = $(patsubst $(SRC_DIR)/game_tools/%.cpp,$(OBJ_DIR)/%.o,$(GAME_TOO_SRC))

GEO_SRC = $(wildcard $(SRC_DIR)/geometry/*.cpp)
GEO_OBJS = $(patsubst $(SRC_DIR)/geometry/%.cpp,$(OBJ_DIR)/%.o,$(GEO_SRC))

CXXFLAGS = -I$(INCLUDE)/
LDLIBS = -lglfw3 -lrt -lm -lXrandr -lXrender -lXi -lGL -lpthread -pthread -lm -ldl -lXdamage -lXfixes -lX11-xcb -lxcb-glx -lxcb-dri2 -lXxf86vm -lXext -lX11 -lpthread -lxcb -lXau -lXdmcp -ldrm

testing: $(OBJ_DIR)/main.o $(OBJ_DIR)/glad.o $(GAME_MAN_OBJS) $(GAME_OBJ_OBJS) $(GAME_TOO_OBJS) $(GAME_TOO_OBJS) $(GEO_OBJS)
	g++ -o $@ $? $(LDLIBS)

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp 
	g++ -o $@ -c $^ $(CXXFLAGS)

$(OBJ_DIR)/glad.o :$(SRC_DIR)/glad.c 
	g++ -o $@ -c $^ $(CXXFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/game_managing/%.cpp
	g++ -o $@ -c $< $(CXXFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/game_object/%.cpp
	g++ -o $@ -c $< $(CXXFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/game_tools/%.cpp
	g++ -o $@ -c $< $(CXXFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/geometry/%.cpp
	g++ -o $@ -c $< $(CXXFLAGS)

clean:
	rm -rf $(OBJ_DIR)/*.o
