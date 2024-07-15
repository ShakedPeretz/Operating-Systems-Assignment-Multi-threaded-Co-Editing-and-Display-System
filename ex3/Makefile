# Compiler
CXX = g++
# Compiler flags
CXXFLAGS = -std=c++11 -Wall -Wextra

# Source files
SRCS = BoundedBuffer.cpp \
       CoEditor.cpp \
       Dispatcher.cpp \
       Producer.cpp \
       ScreenManager.cpp \
       UnboundedBuffer.cpp \
       main.cpp

# Header files directory
INCDIR = .

# Object files directory
OBJDIR = obj

# Object files (generated from source files)
OBJS = $(patsubst %.cpp,$(OBJDIR)/%.o,$(SRCS))

# Target executable
TARGET = ex3.out

# Make all target
all: $(TARGET)

# Linking target executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

# Compiling source files into object files
$(OBJDIR)/%.o: %.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -I$(INCDIR) -c $< -o $@

# Clean target
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets
.PHONY: all clean
