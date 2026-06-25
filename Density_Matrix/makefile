CXX = g++
CXXFLAGS =  -O2 -std=c++11 -pedantic -W -Wall -Wshadow -fPIC



ROOT_INC = -I$(shell root-config --incdir)
ROOT_LIBS = $(shell root-config --libs)

CXXFLAGS += $(ROOT_INC) $(PYTHIA8_INC)
LIBS = $(ROOT_LIBS)

TARGET = main_Analysis_test

all: $(TARGET)


$(TARGET): main_Analysis_test.o
	$(CXX) -o $(TARGET) main_Analysis_test.o $(LIBS)

main_Analysis_test.o: main_Analysis_test.C
	$(CXX) $(CXXFLAGS) -c main_Analysis_test.C -o main_Analysis_test.o

clean:
	rm -f $(TARGET) *.o

.PHONY: all clean


