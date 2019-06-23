TARGET_FTL=bloomftl

OBJ_DIR=./obj

CFLAGS=\
	-g \
	-Wall \
	-D$(TARGET_FTL) \

all: simulator

simulator: main.c $(OBJ_DIR)/$(TARGET_FTL).o
	gcc -o $@ $^ $(CFLAGS)

$(OBJ_DIR)/$(TARGET_FTL).o: $(TARGET_FTL).c
	gcc -c $^
	mv *.o $(OBJ_DIR)/

clean:	
	rm -f ./simulator
	rm -f $(OBJ_DIR)/*.o
