CC = g++
CFLAGS = -std=c++20 -O2 -Wall -Wno-unused-result -I ./external -I ./include -lrt

TARGET = pianoLED
SRC_DIR = src
OBJ_DIR = build

CSRCS = $(shell find ./src/  -type f -name '*.cpp' -printf "%f\n")
OBJS = $(addprefix ${OBJ_DIR}/, $(CSRCS:.cpp=.o))

all: ${TARGET} 

${TARGET}: ${OBJ_DIR} ${OBJS}
	$(CC) -o ${TARGET} ./ws2812-rpi.o ${OBJS} ${CFLAGS}

${OBJ_DIR}/%.o: ${SRC_DIR}/%.cpp
	$(CC) -c $< -o $@ ${CFLAGS}

${OBJ_DIR}:
	mkdir -p ${OBJ_DIR}

clean:
	rm -rf ${OBJ_DIR}

	
