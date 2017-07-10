CXX = g++
CXXFLAGS += -std=c++11 -O2

TEST_SRC = ./000-Main/*.cpp ./001-Test/*.cpp
READTEST_SRC = ./000-Main/*.cpp ./002-ReadTest/*.cpp

all: test readTest

test:
	mkdir -p build
	$(CXX) $(CXXFLAGS) -o build/test $(TEST_SRC)

readTest:
	mkdir -p build
	$(CXX) $(CXXFLAGS) -o build/test $(READTEST_SRC)

clean:
	rm -rf build
