COMPILE = g++
LIBS = -lsfml-system -lsfml-graphics -lsfml-window
BUILD = bin
SOURCE = $(wildcard *.cpp)
OUTPUT = JDV 

default:
	mkdir -p $(BUILD)
	$(COMPILE) $(SOURCE) $(LIBS) -O3 -o $(BUILD)/$(OUTPUT)

debug:
	mkdir -p $(BUILD)
	$(COMPILE) $(SOURCE) $(LIBS) -g -o $(BUILD)/$(OUTPUT)

clean:
	rm -rf $(BUILD)
