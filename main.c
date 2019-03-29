#include <stdio.h>
#include <malloc.h>

typedef struct{
    int x;
    int y;
} coordinate;

typedef struct{
    coordinate start;
    coordinate end;
} segment;
void printSegments(segment * segments, int n);

int calcWaterLiters(segment param, segment *segments, int n);

int main(){
	int numInputs;
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
	printSegments(segments, numInputs);


	// find pipes?
	// form right to left

	// take most left segment, find the next start segment and check if it lower or higher
	// find min start.x




	// given the segment, segments and number of segments return water in litters

	for(int i = 0; i < numInputs; i++){
	    int waterLiters = calcWaterLiters(segments[i], segments, numInputs);
	    printf("%d\n", waterLiters);
	}

	return 0;
}

int calcWaterLiters(segment currSegment, segment * segments, int n) {

    //int startLiters = currSegment.end.x - currSegment.start.x;


    for(int i = 0; i < n; i++){
        if (currSegment.end.x >= segments[i].start.x && currSegment.start.x <= segments[i].start.x){ // if there is another segment that starts in the middle of current segment. Either lower or higher
            // determines if its lower or higher
            if(currSegment.start.y < segments[i].start.y && currSegment.end.x < segments[i].end.x){  // curr segment is lower and higher segment is longer than curr segment



                // so jeg skal finde ud af hvor start den ovre segment og minus fra mit startLiters

                currSegment.end.x = segments[i].start.x;

                // hvor ender den ovre segment?
        //        int lengthOverlaps = segments[i].end.x - currSegment.end.x;
                //  overste - resultat

                // FORKORTE change start og end after minus



                // og så skal jeg minusere resultatet fra


            }
        }


        if (currSegment.start.x <= )


        // if finds segmant which overlaps


        //if(currSegment.end.x > segments[i])
    }

    // calculate lengthen hvad er tilbage

    int liters = currSegment.end.x - currSegment.start.x;

    return liters;
}

void printSegments(segment * segments, int n){
    for(int i = 0; i < n; i++){
        printf("Segment %d: %d %d %d %d \n", i, segments[i].start.x, segments[i].start.y, segments[i].end.x, segments[i].end.y);
    }
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

/*



 */