TARGET = out

IDIR = .
SDIR = .
ODIR = .

SRC = $(wildcard $(SDIR)/*.cpp)
OBJ = $(SRC:$(SDIR)/%.c=$(ODIR)/%.o)

CXX = g++
CXXFLAGS = -I$(IDIR)
CXXFLAGS += -g -O0
CXXFLAGS += -Iinclude
CFLAGS += -Wall
SCPATH = /usr/local/systemc-2.3.3
LIBS = -lm

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -I$(SCPATH)/include -L. -L$(SCPATH)/lib-linux64 -Wl,-rpath $(SCPATH)/lib-linux64 $^ $(LIBS) -o $@ -lsystemc

$(ODIR)/%.o: $(SDIR)/%.c
	$(CXX) $(CXXFLAGS) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(TARGET)
