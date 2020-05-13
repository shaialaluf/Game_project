#ifndef A
#define A



typedef struct _move {
	char rows , cols;
} Move;


typedef struct _movesArray {
	unsigned int size;
	Move *moves;
} movesArray;



#endif 