#
# 'make'        build executable file 'main'
# 'make clean'  removes all .o and executable files
#

# Debug mode is disabled by default. To build in debug, use `make DEBUG=1`
DEBUG=

# CXX compiler to use
CXX = g++

LIBRARIES := libcurl

CFLAGS_DEBUG=-g
CFLAGS_RELEASE=-O3

CXXFLAGS_COMMON := `pkg-config --cflags $(LIBRARIES)` -std=c++20 -Wall -Wextra
CXXFLAGS_DEBUG := $(CXXFLAGS_COMMON) $(CFLAGS_DEBUG)
CXXFLAGS_RELEASE := $(CXXFLAGS_COMMON) $(CFLAGS_RELEASE)

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

ifeq ($(DEBUG), 1)
CXXFLAGS:=$(CXXFLAGS) $(CXXFLAGS_DEBUG)
MODESTR := Debug
else
CXXFLAGS:=$(CXXFLAGS) $(CXXFLAGS_RELEASE)
MODESTR := Release
endif

all: $(OUTPUT) $(MAIN)
	$(info Building in $(MODESTR) mode)
	@echo Executing 'all' complete!

$(OUTPUT):
	$(MD) $(OUTPUT)

$(MAIN): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $(OUTPUTMAIN) $(OBJECTS) $(LFLAGS) $(LIBS)

-include $(DEPS)

.cpp.o:
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -MMD $<  -o $@

.PHONY: clean run

clean:
	$(RM) $(OUTPUTMAIN)
	$(RM) $(call FIXPATH,$(OBJECTS))
	$(RM) $(call FIXPATH,$(DEPS))
	@echo Cleanup complete!

run: all
	@./$(OUTPUTMAIN)
