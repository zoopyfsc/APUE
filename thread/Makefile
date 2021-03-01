include ../Make.rule

CPP_FILES += $(wildcard *.cpp)
C_FILES += $(wildcard *.c)
H_FILES += $(wildcard *.h)

INC +=
LIBS += -lpthread 

BIN_PATH = ./
OBJ_DIR = ./obj/
$(shell if [ ! -d $(OBJ_DIR) ]; then mkdir $(OBJ_DIR); fi;)

OBJS := $(patsubst %.cpp, $(OBJ_DIR)%.o, $(CPP_FILES)) $(patsubst %.c, $(OBJ_DIR)%.o, $(C_FILES))

BIN := $(patsubst %.o, %, $(notdir $(OBJS)))

TARGET := $(foreach proc, $(BIN), $(BIN_PATH)$(proc))

.PHONY: all clean

all: $(TARGET) 
	@echo Target... $(BIN)

$(TARGET): $(OBJS) $(H_FILES)
	@echo link... $@
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ_DIR)$@.o $(INC) $(LIBS)


$(OBJ_DIR)%.o:%.c
	$(CC) $(CFLAGS) -c -o $@ $< $(INC)

$(OBJ_DIR)%.o:%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $< $(INC)

clean:
	rm -f $(TARGET) $(OBJS)
