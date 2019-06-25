TARGET_FTL=bloomftl

OBJ_DIR=./obj

CFLAGS=\
	-g \
	-O2 \
	-Wall \
	-D$(TARGET_FTL) \
	-fsanitize=address \

all: simulator

simulator: main.c $(OBJ_DIR)/$(TARGET_FTL).o $(OBJ_DIR)/gc_sim.o
	gcc -o $@ $^ $(CFLAGS)

$(OBJ_DIR)/$(TARGET_FTL).o: $(TARGET_FTL).c
	gcc -c $^ $(CFLAGS)
	mkdir -p $(OBJ_DIR)
	mv *.o $(OBJ_DIR)/

$(OBJ_DIR)/gc_sim.o: gc_sim.c
	gcc -c $^ $(CFLAGS)
	mv *.o $(OBJ_DIR)/

clean:	
	rm -f ./simulator
	rm -f $(OBJ_DIR)/*.o
