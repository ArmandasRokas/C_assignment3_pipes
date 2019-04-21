#include <stdio.h>
#include <malloc.h>
#include <assert.h>

#define MATRIX_SIZE 20
#define TOTAL_MATRIX_SIZE (unsigned long)MATRIX_SIZE*MATRIX_SIZE
#define ARRAY_SIZE 10000000
#define DEBUG 1


typedef struct{
    int x;
    int y;
} coordinate;

typedef struct{
	int index;
    coordinate start;
    coordinate end;
    int highestPoint;
    int pipe_X_value;
    int pipe_liters;
    int isSetOnArray;
//    double slope;
} segment;
void printSegments(segment * segments, int n);
int ** initMatrix();
void printMatrix(int** matrix);
void setSegmentIntoMatrix(int ** matrix, segment * s);
int returnSegmentPipeLiters(int **matrix, segment *s);
void sortSegments(segment *segments, int inputs);
void init_segments(segment * segments, int n);
void setZerosToColumn(int ** matrix, segment * s, int rowNumber,int currColumn);
void setSegmentIntoArray(int * array, segment * s, int numInputs);
void printSegmentsArray(int * array);
int returnSegmentPipeLitersInArray(int * array, segment *s);

void unsortSegments(segment *segments, int inputs);

int main(){
	int numInputs;
//	int** matrix = initMatrix();


	scanf("%d", &numInputs);

	segment * segments = (segment *) malloc(numInputs* sizeof(segment));
//	segment * sorted_segments = (segment *) malloc(numInputs* sizeof(segment));
	init_segments(segments, numInputs);

	// Makes a copy of the array to keep the original sequence of segments
	for(int i = 0; i < numInputs; i++){
		segments[i] = segments[i];
	}
	sortSegments(segments, numInputs);

//	calculateSegmentsPipes(segments);
	int * array = (int *) malloc(ARRAY_SIZE* sizeof(int));
	for(int i = 0; i< ARRAY_SIZE; i++){
		array[i] = 1;
	}

	for(int i = 0; i < numInputs; i++){
		for(int j = i+1; j < numInputs; j++) {
			if (segments[i].end.y < segments[j].start.y && segments[i].end.x > segments[j].start.x
			&& segments[i].start.x < segments[j].start.x) {
				if (segments[j].isSetOnArray == 0) {
					#if DEBUG
							printf("Special case. Segment j: %d %d %d %d \n",
									segments[j].start.x,
								   segments[j].start.y,
								   segments[j].end.x,
								   segments[j].end.y);
							printf("Segment i: %d %d %d %d \n",
								   segments[i].start.x,
								   segments[i].start.y,
								   segments[i].end.x,
								   segments[i].end.y);
					#endif
					setSegmentIntoArray(array, &segments[j], numInputs);
				}
			}
		}
		if(segments[i].isSetOnArray == 0){
			setSegmentIntoArray(array, &segments[i], numInputs);
		}
		//setSegmentIntoMatrix(matrix,  &sorted_segments[i]);
	}

	unsortSegments(segments, numInputs);

	for(int i = 0; i < numInputs; i++){
		printf("%d\n", segments[i].pipe_liters);
		//printf("%d\n", returnSegmentPipeLiters(matrix, &segments[i]));
	}
	//printSegmentsArray(array);
	//printMatrix(matrix);

	return 0;
}

void unsortSegments(segment *segments, int inputs) {
	int j, i;
	for(j = 1; j < inputs; j++){
		segment key = segments[j];
		i = j-1;
		while(i>=0 && segments[i].index > key.index){
			segments[i+1] = segments[i];
			i--;
		}
		segments[i+1] = key;
	}
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
			temp->pipe_X_value = startx-1;
		}
	//	temp->slope = (double) (endy - starty)/(endx-endy);
		temp->index = i;
		temp->isSetOnArray = 0;
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


		int** rows =(int **) malloc(MATRIX_SIZE*sizeof(int *));
	    for (int i=0; i<MATRIX_SIZE; ++i)
		{
			rows[i] = (int *) malloc(MATRIX_SIZE* sizeof(int));
			if(rows[i] == NULL){
				printf("Can not allocate memory\n");
				exit(1);
			}
		}

        for(int i = 0; i < MATRIX_SIZE; i++){
			int * column = *(rows+i);
        	for(int j = 0; j < MATRIX_SIZE; j++ ){
        		*(column+j) =1;
        	}


        }
		return rows;
}
/*
void setZerosToRow(int ** matrix, segment * s, int columnNumber){
    int * column = *(matrix+columnNumber);
    int * element = column + (s->start.x);
    for(int j = s->start.x; j < s->end.x; j++){

        //	int value = *(column+j);
        //	printf("%d", value);
        //matrix[i][j] = 0;
        if(element == NULL){
            printf("Null pointer");
            exit(1);
        }

        *element = 0;
        element++;
    }
};
*/

/*
void setSegmentIntoMatrix(int ** matrix, segment * s){
	// set 0`s in all fields under segment
	for(int i = s->highestPoint - 1; i >= 0; i-- ){
        setZerosToRow(matrix, s, i);
	}
	// calculate total value by the end of segment
	int totalValue = 0;
	if (matrix[s->highestPoint][s->pipe_X_value] == 1){
		totalValue++; // add 1 to current value if rain drops above the pipe. So it gives correct value to other segments below that pipe.
	}
	totalValue += returnSegmentPipeLiters(matrix, s);

	// set pipe value to the bottom
	for(int i = s->highestPoint-1; i>=0; i--){
		matrix[i][s->pipe_X_value] = totalValue;
	}
}
 */
/*
void setSegmentIntoMatrix(int ** matrix, segment * s){
    // one at the time x column
    int currColumn = s->start.x;

    for(int j = s->start.x; j < s->end.x; j++) {

        int rowNumber = s->start.y + ((currColumn - s->start.x) *s->slope);

        setZerosToColumn(matrix, s, rowNumber, currColumn);

        currColumn++;
        //mark the column. with y
    }
}

void setZerosToColumn(int ** matrix, segment * s, int rowNumber, int currColumn){
    for (int i = rowNumber - 1; i >= 0; i--){
        matrix[i][currColumn] = 0;
    }
}

*/
int returnSegmentPipeLiters(int **matrix, segment *s){
	int totalValue = 0;
	for(int i = s->start.x; i<s->end.x; i++){
		totalValue += matrix[s->highestPoint][i];
	}
	return totalValue;
}

void setSegmentIntoArray(int * array, segment * s, int numInputs){
	array[s->pipe_X_value] = returnSegmentPipeLitersInArray(array, s);
	for(int i = s->start.x; i < s->end.x; i++){
		//*(array + i) = 0;
		array[i] = 0;
	}
	s->isSetOnArray = 1;

}
void printSegmentsArray(int * array){
	for(int i = 0; i < ARRAY_SIZE; i++){
		printf("%d ", *(array+i));
	}
}
int returnSegmentPipeLitersInArray(int * array, segment *s){
	int totalValue = 0;
	for(int i = s->start.x; i<s->end.x; i++){
		totalValue += array[i];
	}
	s->pipe_liters = totalValue;

	if (array[s->pipe_X_value] == 1){
		totalValue++; // add 1 to current value if rain drops above the pipe. So it gives correct value to other segments below that pipe.
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