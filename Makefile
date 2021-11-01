CC = g++
CFLAGS = -g -Wall
TARGET = test

all: $(TARGET)
$(TARGET): $(TARGET).cpp
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).cpp tfloat8.h tfloat8.cpp
clean:
	$(RM) $(TARGET)
