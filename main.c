#include <stdio.h>
#include <malloc.h>
#define MATRIX_SIZE 20

typedef struct{
    int x;
    int y;
} coordinate;

typedef struct{
    coordinate start;
    coordinate end;
} segment;
void printSegments(segment * segments, int n);
int ** initMatrix();
int calcWaterLiters(segment param, segment *segments, int n);
void printMatrix(int** matrix);
void setSegmentIntoMatrix(int ** matrix, int x1, int y1, int x2, int y2);
int returnPipeLiters(int ** matrix, int x1, int y1, int x2, int y2);

int main(){
	int numInputs;

	int** matrix = initMatrix();
	setSegmentIntoMatrix(matrix, 9,6,12,8);
	setSegmentIntoMatrix(matrix, 3,8,7,7);
	setSegmentIntoMatrix(matrix, 1,7,5,6);
	setSegmentIntoMatrix(matrix, 5,5,9,3);
	setSegmentIntoMatrix(matrix, 6,3,8,2);
	printMatrix(matrix);

	printf("Pipe liters  9,6,12,8: %d \n",returnPipeLiters(matrix, 9,6,12,8));
	printf("Pipe liters  3,8,7,7: %d \n",returnPipeLiters(matrix, 3,8,7,7));
	printf("Pipe liters  5,5,9,3: %d \n",returnPipeLiters(matrix, 5,5,9,3));
	printf("Pipe liters  1,7,5,6: %d \n",returnPipeLiters(matrix, 1,7,5,6));
	printf("Pipe liters  6,3,8,2: %d \n",returnPipeLiters(matrix, 6,3,8,2));

	scanf("%d", &numInputs);

	segment * segments = (segment *) malloc(numInputs* sizeof(segment));

	// initializing segments
	for(int i = 0; i < numInputs; i++) {
		int startx;
		int starty;
		int endx;
		int endy;
		scanf("%d %d %d %d", &startx, &starty, &endx, &endy);
		segment * temp = (segment *) malloc(sizeof(segment));
		temp->start.x = startx;
		temp->start.y = starty;
		temp->end.x = endx;
		temp->end.y = endy;
		segments[i] = *temp;
	}
	// sort segments

	// init matrix (segments)

//	printSegments(segments, numInputs);


	for(int i = 0; i < numInputs; i++){
	    int waterLiters = calcWaterLiters(segments[i], segments, numInputs);
//	    printf("%d\n", waterLiters);
	}

	return 0;
}

int calcWaterLiters(segment currSegment, segment * segments, int n) {

    int liters = currSegment.end.x - currSegment.start.x;

    return liters;
}

void printSegments(segment * segments, int n){
    for(int i = 0; i < n; i++){
        printf("Segment %d: %d %d %d %d \n", i, segments[i].start.x, segments[i].start.y, segments[i].end.x, segments[i].end.y);
    }
}
void printMatrix(int** matrix){
	for(int i = 0; i < MATRIX_SIZE; i++){
		for(int j = 0; j < MATRIX_SIZE; j++){
			printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}
}

int** initMatrix(){
		int* values = (int *) malloc(MATRIX_SIZE*MATRIX_SIZE*sizeof(int));
		int** rows =(int **) malloc(MATRIX_SIZE*sizeof(int *));
	    for (int i=0; i<MATRIX_SIZE; ++i)
		{
			rows[i] = values + i*MATRIX_SIZE;
		}
		for(int i = 0; i < MATRIX_SIZE*MATRIX_SIZE; i++){
			*values = 1;
			values++;
 		}


		return rows;
}

void setSegmentIntoMatrix(int ** matrix, int x1, int y1, int x2, int y2){
	int height;
	int pipe_X_value;
	if(y1 > y2){
		height = y1;
		pipe_X_value = x2;
	} else{
		height = y2;
		pipe_X_value = x1-1;
	}
	// set 0 under segment
	for(int i = height - 1; i >= 0; i-- ){
		for(int j = x1; j < x2; j++){
			matrix[i][j] = 0;
		}
	}
	// count current pipe value
	int totalValue = 0;
	if (matrix[height][pipe_X_value] == 1){ // maybe  height????
		totalValue++;
	}
	for(int i = x1; i<x2; i++){
		totalValue += matrix[height][i];
	}
	// set pipe value to the bottom
	for(int i = height-1; i>=0; i--){
		matrix[i][pipe_X_value] = totalValue;
	}


//	printf("Total value: %d ", totalValue);

}
int returnPipeLiters(int ** matrix, int x1, int y1, int x2, int y2){
	int height;
	if(y1 > y2){
		height = y1;
	} else{
		height = y2;
	}
	int totalValue = 0;
	for(int i = x1; i<x2; i++){
		totalValue += matrix[height][i];
	}
	return totalValue;
}


/* Test data
6
13 7 15 6
3 8 7 7
1 7 5 6
5 5 9 3
6 3 8 2
9 6 12 8
 */

/*
3
 13 7 15 6
1 7 5 6
3 8 7 7
 */
