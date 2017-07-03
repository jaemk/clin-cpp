CXX = g++

# pre-processor settings (-I, -D, etc)
CPPFLAGS =

# compiler settings
CXXFLAGS = -Wall -Wextra -pedantic -Wundef -Wno-unused -std=c++11 -O2

# linker settings
LDFLAGS =

PKGCONFIG = `pkg-config --cflags --libs libnotify`
BUILD_DIR = target
ARTIFACT = clin

.PHONY: build
.PHONY: run

build: src/*.cpp
	rm -rf $(BUILD_DIR)
	mkdir -p $(BUILD_DIR)
	$(CXX) -o $(BUILD_DIR)/$(ARTIFACT) $(CXXFLAGS) $(LDFLAGS) $< $(PKGCONFIG)

run:
	make build
	$(BUILD_DIR)/$(ARTIFACT)

