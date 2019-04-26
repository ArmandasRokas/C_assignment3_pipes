#include <stdio.h>
#include <malloc.h>
#include <assert.h>
#define SIZE_OF_X_AXIS 1000000
#define DEBUG 0

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
} segment;

void printSegments(segment * segments, int n);
void sortSegments(segment *segments, int inputs);
void init_segments(segment * segments, int n);
void setSegmentIntoArray(int * array, segment * s);
void printSegmentsArray(int * array);
int returnSegmentPipeLitersInArray(int * array, segment *s);
void unsortSegments(segment *segments, int inputs);
void calculateSegmentsPipes(segment *segments, int numInputs);
void printSegmentsPipeFlow(segment * segments, int numInputs);


int main(){
	int numInputs;
	scanf("%d", &numInputs);
	segment * segments = (segment *) malloc(numInputs* sizeof(segment));
	init_segments(segments, numInputs);
	sortSegments(segments, numInputs);
	calculateSegmentsPipes(segments, numInputs);
	unsortSegments(segments, numInputs);
    printSegmentsPipeFlow(segments, numInputs);

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
		if(temp == NULL){
			printf("Could not allocate memory for segment\n");
			exit(1);
		}
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

void calculateSegmentsPipes(segment *segments, int numInputs) {
	int * currWaterFall_Xaxis = (int *) malloc(SIZE_OF_X_AXIS* sizeof(int));
	for(int i = 0; i< SIZE_OF_X_AXIS; i++){
		currWaterFall_Xaxis[i] = 1;
	}

	for(int i = 0; i < numInputs; i++){

		// Search for the special case where not segment with the highest point should be added first
		for(int j = i+1; j < numInputs; j++) {
			if (segments[i].end.y < segments[j].start.y
				&& segments[i].end.x > segments[j].start.x
				&& segments[i].start.x < segments[j].start.x){

				if (segments[j].isSetOnArray == 0) {
					#if DEBUG
					printf("Special case. \n");
					printf("Segment i: %d %d %d %d \n",
						   segments[i].start.x,
						   segments[i].start.y,
						   segments[i].end.x,
						   segments[i].end.y);
					printf("Segment j: %d %d %d %d \n",
						   segments[j].start.x,
						   segments[j].start.y,
						   segments[j].end.x,
						   segments[j].end.y);
					#endif
					setSegmentIntoArray(currWaterFall_Xaxis, &segments[j]);
				}
			}
		}
		if(segments[i].isSetOnArray == 0){
			setSegmentIntoArray(currWaterFall_Xaxis, &segments[i]);
		}
		#if DEBUG
		printSegmentsArray(currWaterFall_Xaxis);
		#endif
	}
}

void setSegmentIntoArray(int * array, segment * s){
	array[s->pipe_X_value] = returnSegmentPipeLitersInArray(array, s);
	for(int i = s->start.x; i < s->end.x; i++){
		*(array + i) = 0;
	}
	s->isSetOnArray = 1;

}
int returnSegmentPipeLitersInArray(int * array, segment *s){
	int totalValue = 0;
	for(int i = s->start.x; i<s->end.x; i++){
		totalValue += array[i];
	}
	s->pipe_liters = totalValue;
	totalValue += array[s->pipe_X_value];
	return totalValue;
}

void printSegmentsArray(int * array){
	for(int i = 0; i < SIZE_OF_X_AXIS; i++){
		printf("%d ", *(array+i));
	}
	printf("\n");
}

void printSegmentsPipeFlow(segment * segments, int numInputs){
    for(int i = 0; i < numInputs; i++){
        printf("%d\n", segments[i].pipe_liters);
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

