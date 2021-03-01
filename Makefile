include Make.rule

CODE_DIRS = intro \
			process \
			standardio \
			systemfile \
			fileio \
			filedir \
			signal	\
			thread

LIB_DIRS = lib

CODE_PATH = $(foreach path, $(CODE_DIRS), $(SRC_PATH)/$(path))
LIB_PATH = $(foreach path, $(LIB_DIRS), $(SRC_PATH)/$(path))

.PHONY: all lib 

all: lib 
	$(foreach src, $(CODE_PATH), $(MAKE) -C $(src) -f ../BinMakefile && ) true  

lib:
	$(foreach src, $(LIB_PATH), $(MAKE) -C $(src) -f ../LibMakefile && ) true 

clean:
	$(foreach src, $(CODE_PATH), $(MAKE) -C $(src) -f ../BinMakefile clean && ) true
