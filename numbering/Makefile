#
CXX = g++
CXXFLAGS = -std=c++17 -O3 -Wall
CXXFLAGS += `pkg-config --cflags opencv4`
LINKFLAGS += `pkg-config --libs opencv4`
LINKFLAGS += -lboost_filesystem
LINKFLAGS += -lboost_program_options
LINKFLAGS += -lboost_system
LINKFLAGS += -lm -lX11

all:	  json2csv dp_test evaluate

json2csv:	json2csv.o
	@$(CXX) $^ $(CXXFLAGS) -o $@ $(LINKFLAGS)

evaluate:	evaluate.o
	@$(CXX) $^ $(CXXFLAGS) -o $@ $(LINKFLAGS)

dp_test:	dp_test.o
	@$(CXX) $^ $(CXXFLAGS) -o $@ $(LINKFLAGS)

clean:
	rm -f *.o *~
