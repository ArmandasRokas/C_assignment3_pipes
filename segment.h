#include <stdio.h>
#include <malloc.h>
#include <assert.h>

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
} segment;

void printSegments(segment * segments, int n);
void sortSegments(segment *segments, int inputs);
void init_segments(segment * segments, int n);
void setSegmentIntoArray(int * array, segment * s, int numInputs);
void printSegmentsArray(int * array);
int returnSegmentPipeLitersInArray(int * array, segment *s);
void unsortSegments(segment *segments, int inputs);
void calculateSegmentsPipes(segment *segments, int numInputs);

