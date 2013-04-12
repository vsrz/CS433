kefile for Comer CNAI Simple TCP API
# Linux Version

DEFS    = -DLINUX
INC_DIR = ./
INCLUDE = -I$(INC_DIR)
LD      = ld
CC      = gcc
LIBS    =
FLAGS   = -c -g -Wall


API_DIR = ./
API_SRC =  

API_OBJ = $(API_SRC:.c=.o)

APP_DIR = ./
APP_SRC = kernel1.c               

APP_OBJ = $(APP_SRC:.c=.o)
APP_EXE = kernel2 

CFILES = $(API_DIR)/*.c $(APP_DIR)/*.c

apps: $(APP_EXE)

kernel2: kernel2.o 
        $(CC) -o $@ $(LIBS) kernel2.o

test2:   test2.o
        $(CC) -o $@ $(LIBS) test2.o

$(APP_OBJ):
        $(CC) -c $(INCLUDE) $(FLAGS) $(DEFS) $(APP_DIR)/$(@:.o=.c)
$(CNAIAPI_LIB): $(API_OBJ)
        $(LD) -r -o $(CNAIAPI_LIB) $(API_OBJ)
$(API_OBJ):
        $(CC) $(INCLUDE) $(FLAGS) $(DEFS) $(API_DIR)/$(@:.o=.c)

clean:
        \rm -rf *.o core $(CNAIAPI_LIB) $(APP_EXE)

# Application Dependancies
kernel2.o: $(APP_DIR)/kernel2.c $(INC_DIR)/kernel2.h
test2.o: $(APP_DIR)/test2.c $(INC_DIR)/kernel2.h

