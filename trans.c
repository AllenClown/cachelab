/* 
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */ 
#include <stdio.h>
#include "cachelab.h"

#define BLOCK_SIZE 20

int is_transpose(int M, int N, int A[N][M], int B[M][N]);

/* 
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. 
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N])
{
	for(int iBlock = 0; iBlock < N/BLOCK_SIZE; iBlock++){
        int istart = iBlock * BLOCK_SIZE;
        for(int jBlock = 0; jBlock < M/BLOCK_SIZE; jBlock++){
            int jstart = jBlock * BLOCK_SIZE;
			int tmp;
            for(int i = istart; i < istart + BLOCK_SIZE; i++ ){
                for(int j = jstart; j < jstart + BLOCK_SIZE; j++ ){
                    if(i - istart == j - jstart && i - istart != BLOCK_SIZE - 1 ) {
                        tmp = A[i][j];
                        continue;
                    }
                    if( i - istart != 0 && i - istart -1 == j - jstart){
                        B[j][i-1] = tmp;
                    }
                    B[j][i] = A[i][j];
                }
            }
        }
    }
}


/* 
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started. 
 */ 
char transpose_test1_desc[] = "Transpose test1";
void transpose_test1(int M, int N, int A[N][M], int B[M][N])
{
	
 
    for(int iBlock = 0; iBlock < N/BLOCK_SIZE; iBlock++){
        int istart = iBlock * BLOCK_SIZE;
		
        for(int jBlock = 0; jBlock < M/BLOCK_SIZE; jBlock++){
            int jstart = jBlock * BLOCK_SIZE;
			//upper left 
			int i,j,tmp;
            for(i = istart; i < istart + BLOCK_SIZE/2; i++ ){
                for( j = jstart; j < jstart + BLOCK_SIZE/2; j++ ){
					if(i - istart == j - jstart && i - istart != BLOCK_SIZE - 1) {
						tmp = A[i][j];
					
						continue;
					}
					if(i - istart -1 == j - jstart && i - istart != 0){
						B[j][i-1] = tmp;
						
					}
					B[j][i] = A[i][j];
//					printf("============================================part A============================================\n");

//					printArray(64,64,B);
					
                }
            }
			int leftD = tmp;
			// upper right
		   for( i = istart; i < istart + BLOCK_SIZE/2; i++ ){
                for(j = jstart + BLOCK_SIZE/2; j < jstart + BLOCK_SIZE; j++ ){
					if(i- istart == j - (jstart + BLOCK_SIZE/2) && i != istart + BLOCK_SIZE/2 -1 ){
						tmp = A[i][j];
						continue;
					}
					if(i- istart - 1 == j - (jstart + BLOCK_SIZE/2) && i - istart != 0){
						B[j][i-1] = tmp;
					}
                    B[j][i] = A[i][j];
//					printf("============================================part B============================================\n");

  //                  printArray(64,64,B);
         
                }
            }
		 // lower right
		     for( i = istart + BLOCK_SIZE/2; i < istart + BLOCK_SIZE; i++ ){
                for(j = jstart +  BLOCK_SIZE/2; j < jstart + BLOCK_SIZE; j++ ){
                    if(i - istart == j - jstart && i - istart != BLOCK_SIZE - 1) {
                        tmp = A[i][j];
  
                        continue;
                    }
                    if(i - istart -1 == j - jstart && i - istart != 0){
                        B[j][i-1] = tmp;
      
                    }
                    B[j][i] = A[i][j];
	//				printf("============================================part C============================================\n");

    //            printArray(64,64,B);


                }
            }

		//lower left
	         for( i = istart + BLOCK_SIZE/2; i < istart + BLOCK_SIZE; i++ ){
                for(j = jstart ; j < jstart + BLOCK_SIZE/2; j++ ){
	               if(i- istart == j - (jstart + BLOCK_SIZE/2) && i != istart + BLOCK_SIZE/2 -1 ){
                        tmp = A[i][j];
						continue;
                    }   
                    if(i- istart - 1 == j - (jstart + BLOCK_SIZE/2) && i - istart != 0){
                        B[j][i-1] = tmp;
                    }

					if(i == istart + BLOCK_SIZE/2 &&  j == jstart + BLOCK_SIZE/2 - 1 )
						B[j][i-1] = leftD; 
                    B[j][i] = A[i][j];
		//			printf("============================================part D============================================\n");
               //    printArray(M,N,B);
      
                }
            }
		
	//printArray(M,N,B);

        }
    }
}

char trans_test2_desc[] = "Transpose test2";
void trans_test2(int M, int N, int A[N][M], int B[N][M]){
	for(int ii = 0; ii < N/BLOCK_SIZE; ii++)
		for(int jj = 0; jj < M/BLOCK_SIZE; jj++){
			int x1, x2, x3, x4, x5, x6;
			int i,j,tmp;
			if(ii == jj){
				int istart = ii * BLOCK_SIZE;
				int jstart = jj * BLOCK_SIZE;	
 	         		for(i = istart; i < istart + BLOCK_SIZE/2; i++ ){
                		for( j = jstart; j < jstart + BLOCK_SIZE/2; j++ ){
						if(i - istart == j - jstart && i - istart != BLOCK_SIZE - 1) {
							tmp = A[i][j];					
							continue;
						}
						if(i - istart -1 == j - jstart && i - istart != 0) 
							B[j][i-1] = tmp;
						B[j][i] = A[i][j];
                		}
          	  	}
				int leftD = tmp;
			// upper right
				for( i = istart; i < istart + BLOCK_SIZE/2; i++ ){
                 		for(j = jstart + BLOCK_SIZE/2; j < jstart + BLOCK_SIZE; j++ ){
						if(i- istart == j - (jstart + BLOCK_SIZE/2) && i != istart + BLOCK_SIZE/2 -1 ){
							tmp = A[i][j];
							continue;
						}
						if(i- istart - 1 == j - (jstart + BLOCK_SIZE/2) && i - istart != 0)
							B[j][i-1] = tmp;
               	     	B[j][i] = A[i][j];
                		}
            		}
		 // lower right
				for( i = istart + BLOCK_SIZE/2; i < istart + BLOCK_SIZE; i++ ){
               		for(j = jstart +  BLOCK_SIZE/2; j < jstart + BLOCK_SIZE; j++ ){
               	     	if(i - istart == j - jstart && i - istart != BLOCK_SIZE - 1) {
               	        		tmp = A[i][j];
                        			continue;
                    		}
                    		if(i - istart -1 == j - jstart && i - istart != 0)
                        			B[j][i-1] = tmp;
                    		B[j][i] = A[i][j];
                		}
            		}

		//lower left
				for( i = istart + BLOCK_SIZE/2; i < istart + BLOCK_SIZE; i++ ){
              			for(j = jstart ; j < jstart + BLOCK_SIZE/2; j++ ){
	               		if(i- istart == j - (jstart + BLOCK_SIZE/2) && i != istart + BLOCK_SIZE/2 -1 ){
                        			tmp = A[i][j];
							continue;
                    		}   
                    	if(i- istart - 1 == j - (jstart + BLOCK_SIZE/2) && i - istart != 0){
                        		B[j][i-1] = tmp;
						}
						if(i == istart + BLOCK_SIZE/2 &&  j == jstart + BLOCK_SIZE/2 - 1 )
							B[j][i-1] = leftD; 
                    		B[j][i] = A[i][j];
                		}
            		}
				continue;
			}
			
			for(i = ii * BLOCK_SIZE; i < ii * BLOCK_SIZE + BLOCK_SIZE/2 ; i++ )
               	for(j = jj * BLOCK_SIZE ; j < jj * BLOCK_SIZE + BLOCK_SIZE/2; j++)
                   		 B[j][i] = A[i][j];


			for(i = ii * BLOCK_SIZE; i < ii * BLOCK_SIZE + BLOCK_SIZE/2 ; i++ )
				for(j = jj * BLOCK_SIZE + BLOCK_SIZE/2; j < jj * BLOCK_SIZE + BLOCK_SIZE; j++)
					B[jj * BLOCK_SIZE + i - ii * BLOCK_SIZE][ii * BLOCK_SIZE + j - jj * BLOCK_SIZE ] = A[i][j];
//			printArray(M,N,B);			
			i =  ii * BLOCK_SIZE + BLOCK_SIZE/2;
			j =  jj * BLOCK_SIZE;

			x1 = B[j][i];
			x2 = B[j][i+1];
			x3 = B[j][i+2];
			x4 = B[j][i+3];

			B[j][i] = A[i][j];
			B[j][i+1] = A[i+1][j];
			B[j][i+2] = A[i+2][j];
			B[j][i+3] = A[i+3][j];
//			printArray(M,N,B);

			B[jj * BLOCK_SIZE + i - ii * BLOCK_SIZE][ii * BLOCK_SIZE + j - jj * BLOCK_SIZE ] = x1;
			B[jj * BLOCK_SIZE + i - ii * BLOCK_SIZE][ii * BLOCK_SIZE + j - jj * BLOCK_SIZE + 1] = B[j+1][i];
			B[jj * BLOCK_SIZE + i - ii * BLOCK_SIZE][ii * BLOCK_SIZE + j - jj * BLOCK_SIZE + 2] = B[j+2][i];
			B[jj * BLOCK_SIZE + i - ii * BLOCK_SIZE][ii * BLOCK_SIZE + j - jj * BLOCK_SIZE + 3] = B[j+3][i];
//			printArray(M,N,B);

			x1 = B[j+1][i+1];
			x5 = B[j+1][i+2];
			x6 = B[j+1][i+3];

			B[j+1][i] = A[i][j+1];
			B[j+1][i+1] = A[i+1][j+1];
			B[j+1][i+2] = A[i+2][j+1];
			B[j+1][i+3] = A[i+3][j+1];
			
		//	printArray(M,N,B);
			B[jj * BLOCK_SIZE + i - ii * BLOCK_SIZE + 1][ii * BLOCK_SIZE + j - jj * BLOCK_SIZE ] = x2;
			B[jj * BLOCK_SIZE + i - ii * BLOCK_SIZE + 1][ii * BLOCK_SIZE + j - jj * BLOCK_SIZE + 1 ] = x1;
			B[jj * BLOCK_SIZE + i - ii * BLOCK_SIZE + 1][ii * BLOCK_SIZE + j - jj * BLOCK_SIZE + 2 ] = B[j+2][i+1];
			B[jj * BLOCK_SIZE + i - ii * BLOCK_SIZE + 1][ii * BLOCK_SIZE + j - jj * BLOCK_SIZE + 3 ] = B[j+3][i+1];

//			printArray(M,N,B);
			x1 = B[j+2][i+2];
			x2 = B[j+2][i+3];

			B[j+2][i] = A[i][j+2];
            B[j+2][i+1] = A[i+1][j+2];
            B[j+2][i+2] = A[i+2][j+2];
            B[j+2][i+3] = A[i+3][j+2];
//			printArray(M,N,B);


			B[jj * BLOCK_SIZE + i - ii * BLOCK_SIZE + 2][ii * BLOCK_SIZE + j - jj * BLOCK_SIZE ] = x3;
			B[jj * BLOCK_SIZE + i - ii * BLOCK_SIZE + 2][ii * BLOCK_SIZE + j - jj * BLOCK_SIZE + 1] = x5;
			B[jj * BLOCK_SIZE + i - ii * BLOCK_SIZE + 2][ii * BLOCK_SIZE + j - jj * BLOCK_SIZE + 2] = x1;
			B[jj * BLOCK_SIZE + i - ii * BLOCK_SIZE + 2][ii * BLOCK_SIZE + j - jj * BLOCK_SIZE + 3] = B[j+3][i+2];
//			printArray(M,N,B);
			x1 = B[j+3][i+3];
			
			B[j+3][i] = A[i][j+3];
            B[j+3][i+1] = A[i+1][j+3];
            B[j+3][i+2] = A[i+2][j+3];
            B[j+3][i+3] = A[i+3][j+3];
//            printArray(M,N,B);


			B[jj * BLOCK_SIZE + i - ii * BLOCK_SIZE + 3][ii * BLOCK_SIZE + j - jj * BLOCK_SIZE ] = x4;
			B[jj * BLOCK_SIZE + i - ii * BLOCK_SIZE + 3][ii * BLOCK_SIZE + j - jj * BLOCK_SIZE + 1] = x6;
			B[jj * BLOCK_SIZE + i - ii * BLOCK_SIZE + 3][ii * BLOCK_SIZE + j - jj * BLOCK_SIZE + 2] = x2;
			B[jj * BLOCK_SIZE + i - ii * BLOCK_SIZE + 3][ii * BLOCK_SIZE + j - jj * BLOCK_SIZE + 3] = x1;
	//		printArray(M,N,B);
			for(i = ii * BLOCK_SIZE + BLOCK_SIZE/2; i < ii * BLOCK_SIZE + BLOCK_SIZE; i++)
				for(j = jj * BLOCK_SIZE + BLOCK_SIZE/2; j < jj * BLOCK_SIZE + BLOCK_SIZE; j++)
					B[j][i] = A[i][j];

//			printArray(M,N,B);
 
		}
	
	
}

/* 
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])

{
    int i, j, tmp;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }    

}

char trans_test3[] = "test 3";
void test3(int M, int N, int A[N][M], int B [M][N]){
	int  x1, x2, x3,x4, x5 , x6, i,j,ii,jj;
	for( ii = 0; ii < N/ BLOCK_SIZE; ii++ ){
		for( jj = 0; jj < M/ BLOCK_SIZE; jj++){
			// handle elements of block
			for( i = ii * BLOCK_SIZE; i < ii * BLOCK_SIZE + BLOCK_SIZE; i++)
				for(j = jj * BLOCK_SIZE; j < jj * BLOCK_SIZE + BLOCK_SIZE; j++){
				//	B[j][i] = A[i][j];
	//				printf("1 %d %d\n", ii, jj);
//					printArray(N,M,B);
			for(i = ii * BLOCK_SIZE; i < ii * BLOCK_SIZE + BLOCK_SIZE/2 ; i++ )
               	for(j = jj * BLOCK_SIZE ; j < jj * BLOCK_SIZE + BLOCK_SIZE/2; j++)
                   		 B[j][i] = A[i][j];


			for(i = ii * BLOCK_SIZE; i < ii * BLOCK_SIZE + BLOCK_SIZE/2 ; i++ )
				for(j = jj * BLOCK_SIZE + BLOCK_SIZE/2; j < jj * BLOCK_SIZE + BLOCK_SIZE; j++)
					B[jj * BLOCK_SIZE + i - ii * BLOCK_SIZE][ii * BLOCK_SIZE + j - jj * BLOCK_SIZE ] = A[i][j];
//			printArray(M,N,B);			
			i =  ii * BLOCK_SIZE + BLOCK_SIZE/2;
			j =  jj * BLOCK_SIZE;

			x1 = B[j][i];
			x2 = B[j][i+1];
			x3 = B[j][i+2];
			x4 = B[j][i+3];

			B[j][i] = A[i][j];
			B[j][i+1] = A[i+1][j];
			B[j][i+2] = A[i+2][j];
			B[j][i+3] = A[i+3][j];
//			printArray(M,N,B);

			B[jj * BLOCK_SIZE + i - ii * BLOCK_SIZE][ii * BLOCK_SIZE + j - jj * BLOCK_SIZE ] = x1;
			B[jj * BLOCK_SIZE + i - ii * BLOCK_SIZE][ii * BLOCK_SIZE + j - jj * BLOCK_SIZE + 1] = B[j+1][i];
			B[jj * BLOCK_SIZE + i - ii * BLOCK_SIZE][ii * BLOCK_SIZE + j - jj * BLOCK_SIZE + 2] = B[j+2][i];
			B[jj * BLOCK_SIZE + i - ii * BLOCK_SIZE][ii * BLOCK_SIZE + j - jj * BLOCK_SIZE + 3] = B[j+3][i];
//			printArray(M,N,B);

			x1 = B[j+1][i+1];
			x5 = B[j+1][i+2];
			x6 = B[j+1][i+3];

			B[j+1][i] = A[i][j+1];
			B[j+1][i+1] = A[i+1][j+1];
			B[j+1][i+2] = A[i+2][j+1];
			B[j+1][i+3] = A[i+3][j+1];
			
		//	printArray(M,N,B);
			B[jj * BLOCK_SIZE + i - ii * BLOCK_SIZE + 1][ii * BLOCK_SIZE + j - jj * BLOCK_SIZE ] = x2;
			B[jj * BLOCK_SIZE + i - ii * BLOCK_SIZE + 1][ii * BLOCK_SIZE + j - jj * BLOCK_SIZE + 1 ] = x1;
			B[jj * BLOCK_SIZE + i - ii * BLOCK_SIZE + 1][ii * BLOCK_SIZE + j - jj * BLOCK_SIZE + 2 ] = B[j+2][i+1];
			B[jj * BLOCK_SIZE + i - ii * BLOCK_SIZE + 1][ii * BLOCK_SIZE + j - jj * BLOCK_SIZE + 3 ] = B[j+3][i+1];

//			printArray(M,N,B);
			x1 = B[j+2][i+2];
			x2 = B[j+2][i+3];

			B[j+2][i] = A[i][j+2];
            B[j+2][i+1] = A[i+1][j+2];
            B[j+2][i+2] = A[i+2][j+2];
            B[j+2][i+3] = A[i+3][j+2];
//			printArray(M,N,B);


			B[jj * BLOCK_SIZE + i - ii * BLOCK_SIZE + 2][ii * BLOCK_SIZE + j - jj * BLOCK_SIZE ] = x3;
			B[jj * BLOCK_SIZE + i - ii * BLOCK_SIZE + 2][ii * BLOCK_SIZE + j - jj * BLOCK_SIZE + 1] = x5;
			B[jj * BLOCK_SIZE + i - ii * BLOCK_SIZE + 2][ii * BLOCK_SIZE + j - jj * BLOCK_SIZE + 2] = x1;
			B[jj * BLOCK_SIZE + i - ii * BLOCK_SIZE + 2][ii * BLOCK_SIZE + j - jj * BLOCK_SIZE + 3] = B[j+3][i+2];
//			printArray(M,N,B);
			x1 = B[j+3][i+3];
			
			B[j+3][i] = A[i][j+3];
            B[j+3][i+1] = A[i+1][j+3];
            B[j+3][i+2] = A[i+2][j+3];
            B[j+3][i+3] = A[i+3][j+3];
//            printArray(M,N,B);


			B[jj * BLOCK_SIZE + i - ii * BLOCK_SIZE + 3][ii * BLOCK_SIZE + j - jj * BLOCK_SIZE ] = x4;
			B[jj * BLOCK_SIZE + i - ii * BLOCK_SIZE + 3][ii * BLOCK_SIZE + j - jj * BLOCK_SIZE + 1] = x6;
			B[jj * BLOCK_SIZE + i - ii * BLOCK_SIZE + 3][ii * BLOCK_SIZE + j - jj * BLOCK_SIZE + 2] = x2;
			B[jj * BLOCK_SIZE + i - ii * BLOCK_SIZE + 3][ii * BLOCK_SIZE + j - jj * BLOCK_SIZE + 3] = x1;
	//		printArray(M,N,B);
			for(i = ii * BLOCK_SIZE + BLOCK_SIZE/2; i < ii * BLOCK_SIZE + BLOCK_SIZE; i++)
				for(j = jj * BLOCK_SIZE + BLOCK_SIZE/2; j < jj * BLOCK_SIZE + BLOCK_SIZE; j++)
					B[j][i] = A[i][j];

//			printArray(M,N,B);
			
				}
			
		}
		//handle right rest of elements
		
		for(i = ii * BLOCK_SIZE; i < ii * BLOCK_SIZE + BLOCK_SIZE; i++)
			for( j = M/BLOCK_SIZE * BLOCK_SIZE ; j < M; j++ ){
				B[j][i] = A[i][j];
	//			printf("2\n");
   //             printArray(N,M,B);
			}	
	}
	ii = N/BLOCK_SIZE;
	 for( jj = 0; jj < M / BLOCK_SIZE; jj++){
	     for( i = ii * BLOCK_SIZE; i < N; i++)
         	for(j = jj * BLOCK_SIZE; j < jj * BLOCK_SIZE + BLOCK_SIZE; j++){
                    B[j][i] = A[i][j];
	//				 printf("3\n");
 //                   printArray(N,M,B);
            }
        }
        //handle right rest of elements

        for(i = ii * BLOCK_SIZE; i < N; i++)
            for( j = M/BLOCK_SIZE * BLOCK_SIZE ; j < M; j++ ){
                B[j][i] = A[i][j];
//				printf("4\n");
  //              printArray(N,M,B);
            }

}
char trans_test4[] = "test 4";
void test4(int M, int N, int A[N][M], int B [M][N]){
	int  i,j,ii,jj;
	for( ii = 0; ii < N/ BLOCK_SIZE; ii++ ){
		for( jj = 0; jj < M/ BLOCK_SIZE; jj++){
			// handle elements of block
			for( i = ii * BLOCK_SIZE; i < ii * BLOCK_SIZE + BLOCK_SIZE; i++)
				for(j = jj * BLOCK_SIZE; j < jj * BLOCK_SIZE + BLOCK_SIZE; j++){
					B[j][i] = A[i][j];
	//				printf("1 %d %d\n", ii, jj);
//					printArray(N,M,B);
			
				}
			
		}
		//handle right rest of elements
		
		for(i = ii * BLOCK_SIZE; i < ii * BLOCK_SIZE + BLOCK_SIZE; i++)
			for( j = M/BLOCK_SIZE * BLOCK_SIZE ; j < M; j++ ){
				B[j][i] = A[i][j];
	//			printf("2\n");
   //             printArray(N,M,B);
			}	
	}
	ii = N/BLOCK_SIZE;
	 for( jj = 0; jj < M / BLOCK_SIZE; jj++){
	     for( i = ii * BLOCK_SIZE; i < N; i++)
         	for(j = jj * BLOCK_SIZE; j < jj * BLOCK_SIZE + BLOCK_SIZE; j++){
                    B[j][i] = A[i][j];
	//				 printf("3\n");
 //                   printArray(N,M,B);
            }
        }
        //handle right rest of elements

        for(i = ii * BLOCK_SIZE; i < N; i++)
            for( j = M/BLOCK_SIZE * BLOCK_SIZE ; j < M; j++ ){
                B[j][i] = A[i][j];
//				printf("4\n");
  //              printArray(N,M,B);
            }

}



/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
//    registerTransFunction(transpose_submit, transpose_submit_desc); 

    /* Register any additional transpose functions */
//    registerTransFunction(trans, trans_desc); 
  //  registerTransFunction(test3, trans_test3);
	registerTransFunction(test4, trans_test4);

	//registerTransFunction(transpose_test1, transpose_test1_desc);
//	registerTransFunction(trans_test2, trans_test2_desc);

}

/* 
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}

