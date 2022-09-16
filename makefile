# compiler options
CXX = gcc
CXXFLAGS = -Wall -Werror -D DEBUG

# file includes and libraries
INCPATH = include/SDL2
LIBPATH = lib/SDL2/x86
LIBS = -lSDL2

# directories where all the files are organized
SRCPATH = src
BUILDPATH = build

# src/main.c - all the .c files
SRCS = $(wildcard $(SRCPATH)/*.c)
# build/main.o - all the .o files
OBJS = $(patsubst $(SRCPATH)/%.c,$(BUILDPATH)/%.o,$(SRCS))
# build/main.d - all the .d file (maybe not need)
DEPS = $(patsubst $(SRCPATH)/%.c,$(BUILDPATH)/%.d,$(SRCS))

# Output file name
target = main.exe

all: $(target)

$(target): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) -I$(INCPATH) -L$(LIBPATH) $(LIBS)

$(OBJS): $(BUILDPATH)/%.o : $(SRCPATH)/%.c
	$(CXX) $(CXXFLAGS) -c $< -o $@ -I$(INCPATH) -L$(LIBPATH) $(LIBS)

$(DEPS): $(BUILDPATH)/%.d : $(SRCPATH)/%.c
	$(CXX) $(CXXFLAGS) -MM -MF"$@" $<

.PHONY: clean
clean:
	rm ./$(target).exe

-include: $(DEPS)