CC = gcc

CFLAGS = -IC:/raylib/w64devkit/include -Iinclude

LIBS = -LC:/raylib/w64devkit/lib -lraylib -lopengl32 -lgdi32 -lwinmm

TARGET = HABAH_BABAH.exe

SRC = $(wildcard src/*.c)


$(TARGET): $(SRC)
	$(CC) $(SRC) $(CFLAGS) $(LIBS) -o $(TARGET)


clean:
	del $(TARGET)