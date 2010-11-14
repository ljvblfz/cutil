#define CC
CC = gcc

#remove temp file
#linux
#clear = -rm
#windows
clear = -del

#include
INCLUDES = include
SOURCES = source

#link Objects
SRC = $(wildcard *.c $(SOURCES)/*.c)

Objects += $(patsubst %.c,%.o,$(SRC))

#execute file
TARGET = cutil
CFLAGS = -Wall -I$(INCLUDES) -c

.PHONY : all clean

all: $(TARGET)
$(TARGET) : $(Objects)
	@echo link cutil.exe ...
	$(CC) -o $(TARGET) $(Objects)

$(Objects): %.o: %.c
	@echo compiling $< ...
	$(CC) $(CFLAGS) -c $< -o $@

clean : 
	@echo clean all the temp files ...
	$(clear) $(TARGET).exe  *.o  $(SOURCES)\*.o
