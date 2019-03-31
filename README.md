## Questions 
- Skal man dokumentere sin arbejde?
- Har du selv flere test cases?
- Kan jeg ikke bare få en mere, bare for checke, hvordan kan det ellers kunne være?
-- Hvis algoritmen fejler på nogen af din test cases? Betyder det at jeg ikke kan få 12?

## Test cases 

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
