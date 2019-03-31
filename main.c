#include <stdio.h>
#include <malloc.h>
#define MATRIX_SIZE 14000

typedef struct{
    int x;
    int y;
} coordinate;

typedef struct{
    coordinate start;
    coordinate end;
    int highestPoint;
    int pipe_X_value;
} segment;
void printSegments(segment * segments, int n);
int ** initMatrix();
void printMatrix(int** matrix);
void setSegmentIntoMatrix(int ** matrix, segment * s);
int returnPipeLiters(int ** matrix, segment* s);
void sortSegments(segment *segments, int inputs);
void init_segments(segment * segments, int n);

int main(){
	int numInputs;
	int** matrix = initMatrix();

	scanf("%d", &numInputs);

	segment * segments = (segment *) malloc(numInputs* sizeof(segment));
	segment * sorted_segments = (segment *) malloc(numInputs* sizeof(segment));

	// initializing segments
	init_segments(segments, numInputs);
	// Makes a copy of the array to keep the original sequence of segments
	for(int i = 0; i < numInputs; i++){
		sorted_segments[i] = segments[i];
	}
	sortSegments(sorted_segments, numInputs);

	for(int i = 0; i < numInputs; i++){
		setSegmentIntoMatrix(matrix,  &sorted_segments[i]);
	}

	for(int i = 0; i < numInputs; i++){
		printf("%d\n", returnPipeLiters(matrix, &segments[i]));
	}

	return 0;
}

void init_segments(segment * segments, int n){
	for(int i = 0; i < n; i++) {
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
		if(starty > endy){
			temp->highestPoint = starty;
			temp->pipe_X_value = endx;
		} else{
			temp->highestPoint = endy;
			temp->pipe_X_value = endy;
		}
		segments[i] = *temp;
	}
}


/**************************************************************
 *  Insertion sort
 *  It sorts a segments array in the way that the segment
 *  with the highest point is the first element.
 ***************************************************************/
void sortSegments(segment * segments, int inputs) {
	int j, i;
	for(j = 1; j < inputs; j++){
		segment key = segments[j];
		i = j-1;
		while(i>=0 && segments[i].highestPoint < key.highestPoint){
			segments[i+1] = segments[i];
			i--;
		}
		segments[i+1] = key;
	}
}
void printSegments(segment * segments, int n){
    for(int i = 0; i < n; i++){
        printf("Segment %d: %d %d %d %d and highestPoint: %d  \n",
        		i,
        		segments[i].start.x,
        		segments[i].start.y,
        		segments[i].end.x,
        		segments[i].end.y,
        		segments[i].highestPoint);
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

void setSegmentIntoMatrix(int ** matrix, segment * s){
	// set 0`s in all fields under segment
	for(int i = s->highestPoint - 1; i >= 0; i-- ){
		for(int j = s->start.x; j < s->end.x; j++){

			matrix[i][j] = 0;
		}
	}
	// calculate total value by the end of segment
	int totalValue = 0;
	if (matrix[s->highestPoint][s->pipe_X_value] == 1){
		totalValue++; // add 1 to current value if rain drops above the pipe. So it gives correct value to other segments below that pipe.
	}
	totalValue += returnPipeLiters(matrix, s);

	// set pipe value to the bottom
	for(int i = s->highestPoint-1; i>=0; i--){
		matrix[i][s->pipe_X_value] = totalValue;
	}
}
int returnPipeLiters(int ** matrix, segment* s){
	int totalValue = 0;
	for(int i = s->start.x; i<s->end.x; i++){
		totalValue += matrix[s->highestPoint][i];
	}
	return totalValue;
}


/* Test data
########Input:######
6
13 7 15 6
3 8 7 7
1 7 5 6
5 5 9 3
6 3 8 2
9 6 12 8
##Expected & Actual:##
 2
 4
 2
 11
 0
 3
 */


///////////// My test case /////
/*
Input:
2
1 9 17 1
11 5 15 6
 Expected :
 16
 4
 Actual :
 16
 0
Ideas for fix:
 1.find the slope ratio, i.e. how many x per one y
 y2-y1 = x2-x1
 F.eks. 1,9 and 17,1 has a ratio 2. per 2 x, 1 y decreasing.
 2. Change setSegmentIntoMatrix that insert 0`s using the calculated ratio
 */