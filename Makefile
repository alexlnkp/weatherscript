#
# 'make'        build executable file 'main'
# 'make clean'  removes all .o and executable files
#

# CXX compiler to use
CXX = g++

LIBRARIES := libcurl

CXXFLAGS := `pkg-config --cflags $(LIBRARIES)` -std=c++20 -O3 -Wall -Wextra -g
LFLAGS    = `pkg-config --libs $(LIBRARIES)`

OUTPUT	:= output
SRC		:= src
INCLUDE	:= include
LIB		:= lib

ifneq ($(SYSTEM),)
ifeq ($(SYSTEM),imperial)
CXXFLAGS += -DIMPERIAL
else ifeq ($(SYSTEM),metric)
CXXFLAGS += -DMETRIC
else
$(error Invalid system specified: $(SYSTEM))
endif
else
CXXFLAGS += -DMETRIC
endif

ifeq ($(OS),Windows_NT)
MAIN	    := main.exe
SOURCEDIRS	:= $(SRC)
INCLUDEDIRS	:= $(INCLUDE)
LIBDIRS		:= $(LIB)
FIXPATH      = $(subst /,\,$1)
RM			:= del /q /f
MD	        := mkdir
else
MAIN	    := main
SOURCEDIRS	:= $(shell find $(SRC) -type d)
INCLUDEDIRS	:= $(shell find $(INCLUDE) -type d)
LIBDIRS		:= $(shell find $(LIB) -type d)
FIXPATH      = $1
RM           = rm -f
MD	        := mkdir -p
endif

INCLUDES   := $(patsubst %,-I%, $(INCLUDEDIRS:%/=%))
LIBS	   := $(patsubst %,-L%, $(LIBDIRS:%/=%))
SOURCES	   := $(wildcard $(patsubst %,%/*.cpp, $(SOURCEDIRS)))
OBJECTS	   := $(SOURCES:.cpp=.o)
DEPS	   := $(OBJECTS:.o=.d)

OUTPUTMAIN := $(call FIXPATH,$(OUTPUT)/$(MAIN))

all: $(OUTPUT) $(MAIN)
	@echo Executing 'all' complete!

$(OUTPUT):
	$(MD) $(OUTPUT)

$(MAIN): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $(OUTPUTMAIN) $(OBJECTS) $(LFLAGS) $(LIBS)

-include $(DEPS)

.cpp.o:
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -MMD $<  -o $@

.PHONY: clean
clean:
	$(RM) $(OUTPUTMAIN)
	$(RM) $(call FIXPATH,$(OBJECTS))
	$(RM) $(call FIXPATH,$(DEPS))
	@echo Cleanup complete!

run: all
	@./$(OUTPUTMAIN)
