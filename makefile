# ----------------------------------------
# Compiler selection (default = g++)
# ----------------------------------------
CXX ?= g++

# Flags
CXXFLAGS = -Wall -Wextra -std=c++17

# If using a C compiler, link stdc++
ifeq ($(CXX),gcc)
    LIBS = -lstdc++
endif

ifeq ($(CXX),clang)
    LIBS = -lstdc++
endif

# ----------------------------------------
# Executables
# ----------------------------------------
BANKER = banker
GEN = inputGen

# ----------------------------------------
# Source files
# ----------------------------------------
BANKER_SRCS = main.cpp System.cpp
GEN_SRCS = inputGen.cpp

BANKER_OBJS = $(BANKER_SRCS:.cpp=.o)
GEN_OBJS = $(GEN_SRCS:.cpp=.o)

# ----------------------------------------
# Default: build both
# ----------------------------------------
all: $(BANKER) $(GEN)

# ----------------------------------------
# Build BANKER
# ----------------------------------------
$(BANKER): $(BANKER_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

# ----------------------------------------
# Build input generator
# ----------------------------------------
$(GEN): $(GEN_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

# ----------------------------------------
# Generic compile rule
# ----------------------------------------
%.o: %.cpp System.hpp
	$(CXX) $(CXXFLAGS) -c $<

# ----------------------------------------
# Cleaning
# ----------------------------------------
clean:
	rm -f $(BANKER_OBJS) $(GEN_OBJS) $(BANKER) $(GEN)

# ----------------------------------------
# Convenience
# ----------------------------------------
run: $(BANKER)
	./$(BANKER)

print-%:
	@echo "$* = $($*)"
