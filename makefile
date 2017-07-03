CXX = g++

# put pre-processor settings (-I, -D, etc) here
CPPFLAGS =

# put compiler settings here
CXXFLAGS = -Wall -Wextra -std=c++11 -O3

# put linker settings here
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

