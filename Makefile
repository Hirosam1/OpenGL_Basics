
INCLUDE = ./include
SRC_DIR = src
OBJ_DIR = objs

file_name = MyOpenGLTest

LIB_PATH = lib

GAME_MAN_SRC = $(wildcard $(SRC_DIR)/game_managing/*.cpp) 
GAME_MAN_OBJS = $(patsubst $(SRC_DIR)/game_managing/%.cpp,$(OBJ_DIR)/%.o,$(GAME_MAN_SRC))

GAME_OBJ_SRC = $(wildcard $(SRC_DIR)/game_object/*.cpp) 
GAME_OBJ_OBJS = $(patsubst $(SRC_DIR)/game_object/%.cpp,$(OBJ_DIR)/%.o,$(GAME_OBJ_SRC))

GAME_TOO_SRC = $(wildcard $(SRC_DIR)/game_tools/*.cpp) 
GAME_TOO_OBJS = $(patsubst $(SRC_DIR)/game_tools/%.cpp,$(OBJ_DIR)/%.o,$(GAME_TOO_SRC))

GEO_SRC = $(wildcard $(SRC_DIR)/geometry/*.cpp)
GEO_OBJS = $(patsubst $(SRC_DIR)/geometry/%.cpp,$(OBJ_DIR)/%.o,$(GEO_SRC))

GRAPHI_SRC = $(wildcard $(SRC_DIR)/graphics/*.cpp)
GRAPHI_OBJS = $(patsubst $(SRC_DIR)/graphics/%.cpp,$(OBJ_DIR)/%.o,$(GRAPHI_SRC))

PER_SRC = $(wildcard $(SRC_DIR)/personal_objects/*.cpp)
PER_OBJS = $(patsubst $(SRC_DIR)/personal_objects/%.cpp,$(OBJ_DIR)/%.o,$(PER_SRC))

LIGHT_SRC = $(wildcard $(SRC_DIR)/game_object/light/*.cpp)
LIGHT_OBJS = $(patsubst $(SRC_DIR)/game_object/light/%.cpp,$(OBJ_DIR)/%.o,$(LIGHT_SRC))

IMGUI_SRC = $(wildcard $(SRC_DIR)/imgui/*.cpp)
IMGUI_OBJS = $(patsubst $(SRC_DIR)/imgui/%.cpp,$(OBJ_DIR)/%.o,$(IMGUI_SRC))

CXXFLAGS = -I$(INCLUDE)/ -O1 -O2 -O3
LDLIBS_LINUX = -lglfw3 -lrt -lm -lXrandr -lassimp -lXrender -lXi -lGL -lpthread -pthread -lm -ldl -lXdamage -lXfixes -lX11-xcb -lxcb-glx -lxcb-dri2 -lXxf86vm -lXext -lX11 -lpthread -lXdmcp -ldrm -lGL -lXinerama -lXcursor 
LDLIBS_WIN = -lassimp -lglfw3 -lglu32 -lgdi32 -lpthread 


#For linux export LD_LIBRARY_PATH=/usr/local/lib
linux: $(OBJ_DIR)/main.o $(OBJ_DIR)/glad.o $(GAME_MAN_OBJS) $(GAME_OBJ_OBJS) $(GAME_TOO_OBJS) $(GAME_TOO_OBJS) $(GEO_OBJS) $(GRAPHI_OBJS) $(PER_OBJS) $(LIGHT_OBJS) $(IMGUI_OBJS)
	g++ -o $(file_name) $^ -L$(LIB_PATH)/ $(LDLIBS_LINUX)

windows: $(OBJ_DIR)/main.o $(OBJ_DIR)/glad.o $(GAME_MAN_OBJS) $(GAME_OBJ_OBJS) $(GAME_TOO_OBJS) $(GAME_TOO_OBJS) $(GEO_OBJS) $(GRAPHI_OBJS) $(PER_OBJS) $(LIGHT_OBJS) $(IMGUI_OBJS)
	g++ -o $(file_name) $^ -static-libgcc -static-libstdc++ -L$(LIB_PATH)/  $(LDLIBS_WIN) my.res

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

#-static-libgcc -static-libstdc++

$(OBJ_DIR)/%.o: $(SRC_DIR)/graphics/%.cpp	
	g++ -o $@ -c $< $(CXXFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/personal_objects/%.cpp	
	g++ -o $@ -c $< $(CXXFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/game_object/light/%.cpp	
	g++ -o $@ -c $< $(CXXFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/imgui/%.cpp	
	g++ -o $@ -c $< $(CXXFLAGS)

clear:
	rm -rf $(OBJ_DIR)/*.o

clear_windows:
	DEL /F /Q /A $(OBJ_DIR)\*.o