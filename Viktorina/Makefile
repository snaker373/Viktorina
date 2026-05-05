# Makefile для компіляції вікторини

CC = g++
CFLAGS = -std=c++11 -Wall -O2
TARGET = quiz_ua.exe
SOURCE = quiz_ua.cpp

all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) $(SOURCE) -o $(TARGET)

run: $(TARGET)
	$(TARGET)

run-window: $(TARGET)
	start "🎯 Вікторина 2024" cmd /k "$(TARGET)"

clean:
	del $(TARGET)

.PHONY: all run run-window clean
