
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define N 9
/* NOTE: You will have to code the 2 functions BELOW "checkDups" and "clearArray"
         before running this program to see the generated output.
*/
int checkDups(int [ ], int, int);
void clearArray(int [ ], int);

int genSudokuNumbers(int grid[ ]); /* already coded */

void genSudokuBoard(int grid[ ], int display[ ]);
void displaySudokuBoard(int grid[ ], int bigOh);
void getRandNum(int low, int high, int *pn);
void printSudokuBoardToFile(int display[ ], const char *fileName);

int main( ) {
   int i, grid[N*N];
   int loops, display[N*N];

   loops = genSudokuNumbers(grid); /* students must add code to return the correct
                                      value for all instructions executed in all loops */   
	displaySudokuBoard(grid, loops);
//	displaySudokuBoard(display, loops);
/*	for(i=0; i<N*N; i++) {  // displaying all N*N numbers in the 'grid' array 
		if(i%N==0 && i!=0) { // printing a newline for every multiple of N 
        		printf("\n");
			}
		printf("%d ", grid[i]);
	}
	printf("\ntotal iterations:%d\n", loops);*/
//displaySudokuBoard(display,loops);
genSudokuBoard(grid, display); 
printSudokuBoardToFile(display, "sudoku.txt");
   return 0;
}

/* given an array of 'n' elements, this function determines if the
   value 'num' is already present within the array 'nums' and if
   so, sends back a true value (1) or false (0) otherwise */
int checkDups(int nums[ ], int search, int n) {     //done		
	int i;
	int dup=0;	
		
	for(i=0;i<n;i++) {
		if (nums[i]==search) {
			dup=1;
		}
	}
	return dup;
}

/* Sets all 'n' values in the 'nums' array to 0 */
void clearArray(int nums[ ], int n) {   //done
	int i;
	
	for(i=0;i<n;i++) {
		nums[i]=0;
	}
}
void genSudokuBoard(int grid[ ], int display[ ]) { //done
	int i, k, h;
	int a;
	int pick1=0, pick2=0, pick3=0, pick4=0;
	int p1, p2, p3, p4;
	int index [N];
	int a1=0, a2, a3, a4, a5, a6, a7, a8, a9;

	clearArray(display, (N*N));

	for(h=0;h<N;h++) {
		if(h%3==0&&h!=0) {
			a1+=21;
		}
		else {
			if(h!=0) {
				a1+=3;
			}
		}
		a2=a1+1;
		a3=a1+2;
		a4=a1+9;
		a5=a1+10;
		a6=a1+11;
		a7=a1+18;
		a8=a1+19;
		a9=a1+20;

		index[0]=a1;
		index[1]=a2;
		index[2]=a3;
		index[3]=a4;
		index[4]=a5;
		index[5]=a6;
		index[6]=a7;
		index[7]=a8;
		index[8]=a9;	

		do {
			getRandNum(0,9,&pick1);
			getRandNum(0,9,&pick2);
			getRandNum(0,9,&pick3);
			getRandNum(0,9,&pick4);
		} while(pick1==pick2||pick1==pick3||pick2==pick3||pick1==pick4||pick2==pick4||pick3==pick4);		

		display[index[pick1]]=grid[index[pick1]];
		display[index[pick2]]=grid[index[pick2]];
		display[index[pick3]]=grid[index[pick3]];
		display[index[pick4]]=grid[index[pick4]];
		
		pick1='\0';
		pick2='\0';
		pick3='\0';
		pick4='\0';
		
	}	
}
void displaySudokuBoard(int grid[ ], int bigOh) { //done
	int i;
		
	printf("PLAY IPC144 SUDOKU\n");
	printf("+-----+-----+-----+\n");		
	for(i=0; i<N*N; i++) { 
		if(i%N==0 && i!=0) { 
	       	        printf("\n");
	        }
		if(i%N==0&&i!=27&&i!=54) {
			printf("|");
  		}
		if(i==27||i==54) {
			printf("+-----+-----+-----+\n|");
		}		 
		if(i%N==2||i%N==5||i%N==8) {
			printf("%d|", grid[i]);			
		}
		else {
			printf("%d ", grid[i]);
		}
	}
	printf("\n");
	printf("+-----+-----+-----+\n");
	printf("total instructions: %d\n", bigOh);
}
void getRandNum(int low, int high, int *pn) { //done
	*pn=low+(rand( )%high);
}
void printSudokuBoardToFile(int display[], const char *filename){
	int i;

	FILE *fp;
	fp = fopen(filename, "w");
		
	fprintf(fp, "PLAY IPC144 SUDOKU\n");
	fprintf(fp, "+-----+-----+-----+\n");		
	for(i=0; i<N*N; i++) { 			
		if(i%N==0 && i!=0) { 
	       	        fprintf(fp, "\n");
	        }
		if(i%N==0&&i!=27&&i!=54) {
			fprintf(fp, "|");
  		}
		if(i==27||i==54) {
			fprintf(fp, "+-----+-----+-----+\n|");
		}		 
		if(i%N==2||i%N==5||i%N==8) {
			if(display[i]==0) {	
				fprintf(fp, " |");
			}
			else {	
				fprintf(fp, "%d|", display[i]);			
			}
		}
		else {
			if(display[i]==0) {
				fprintf(fp, "  ");
			}
			else {
				fprintf(fp, "%d ", display[i]);
			}
		}
	}
	fprintf(fp, "\n");
	fprintf(fp, "+-----+-----+-----+\n");

	fclose(fp);
}
int genSudokuNumbers(int grid[ ]) {
   int c, i, j, rowNum, colNum, blockNum;
   int test[N], dup, temp, valid, cnt, iterations=0;

   srand(time(NULL));         /* seeding the random number generator */
   for(i=0; i<N*N; i++) {     /* initializing the grid array to all 0's */
      grid[i] = 0;
   }


   for(c=0; c<N*N; c++) {     /* main loop to generate N*N numbers for the grid */
      temp = rand( ) % N + 1; /* generate random # from 1 to N inclusive */
	
      valid = dup = cnt = 0;
      while(!valid) {         /* keep looping as long as the 'valid' flag is false */
         clearArray(test, N);
                              /* the calculations below determine the row, col,
                                 and block numbers (index 0 to 8) based on the
                                 linear index variable 'c' */
         rowNum = c / N;
         colNum = c % N;
         blockNum = (rowNum / 3) * 3 + (colNum / 3);

                              /* now check to see if the number 'temp' is a
                                 duplicate in the row, column, and block to which
                                 'c' corresponds */

         for(j=0; j<colNum; j++) {    /* fill row (but only up to colNum) */
            test[j] = grid[rowNum*N+j];
	    iterations++;
         }
         dup += checkDups(test, temp, colNum);

         if(!dup) {                   /* row is valid, now check column */
            clearArray(test, N);
            for(j=0; j<rowNum; j++) { /* fill column (but only up to rowNum) */
               test[j] = grid[j*N + colNum];
	       iterations++;
            }
            dup += checkDups(test, temp, rowNum);

            if(!dup) {                /* column is valid now check block */
               clearArray(test, N);

               for(j=0; j<N; j++) {
                  test[j] = grid[((blockNum/3)*N*3) + (colNum/3)*3 + (j/3)*N + j%3];
               }
                                      /* equation used to generate array
                                         coordinates for all N blocks
                                         (i.e.)
                                         0, 1, 2,   9, 10, 11,  18, 19, 20  {blk 0}
                                         3, 4, 5,  12, 13, 14,  21, 22, 23  {blk 1}
                                         6, 7, 8,  15, 16, 17,  24, 25, 26  {blk 2}

                                         33, 34, 35, 42, 43, 44, 51, 52, 53

                                         54, 55, 56, 63, 64, 65, 72, 73, 74
                                         57, 58, 59, 66, 67, 68, 75, 76, 77
                                         60, 61, 62, 69, 70, 71, 78, 79, 80 {blk 8}
                                      */
               dup += checkDups(test, temp, N);
            }
         }
         if(!dup) { /* no duplicates in row, column, or block, so number
                       can be inserted into the grid */
            grid[c] = temp;
            valid = 1;
            cnt = 0;
         }
         else {     /* duplicate number found, so reset flags and generate
                       new random number */
            temp = rand( ) % N + 1;
            dup = 0;
            cnt++;
         }
         if(cnt > N*N) {
                    /* if after N*N attempts, no possible value is found
                       then reset the entire array and start over
                       (brute force algorithm)
                       average runtime: 50000 iterations */
            valid = dup = cnt = 0;
            clearArray(grid, N*N);
            temp = rand( ) % N + 1;
            c = -1; /* will be reset to 0 in for loop */
         }
      }
   }
   return iterations; /* this value must be updated by within this function BEFORE it is returned */
}
