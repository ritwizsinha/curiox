

MODULE_big = curiox
EXTENSION = curiox 
DATA = curiox--0.0.1.sql
SRCS = $(wildcard src/*.cpp src/*/*.cpp)
OBJS = $(subst .cpp,.o, $(SRCS))

C_SRCS = $(wildcard src/*.c src/*/*.c)
OBJS += $(subst .c,.o, $(C_SRCS))

COMPILER_FLAGS=-Wno-sign-compare -Wshadow -Wswitch -Wunreachable-code -Wno-unknown-pragmas -Wall -Wextra

override PG_CPPFLAGS += -Iinclude ${COMPILER_FLAGS}
override PG_CXXFLAGS += -std=c++17 ${COMPILER_FLAGS} -Wno-register
override SHLIB_LINK += -Wl,-rpath,$(PG_LIB)/ -lpq  -L$(PG_LIB) -lstdc++

include Makefile.global

COMPILE.cc.bc += $(PG_CPPFLAGS)
COMPILE.cxx.bc += $(PG_CXXFLAGS)

$(shlib): $(OBJS)