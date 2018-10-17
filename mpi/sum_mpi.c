/*
 * Naive approach of a parallel sum using MPI.
 * 
 * J. Hollingsworth
 */
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define NORMAL_TAG 11

int main(int argc, char **argv) {

   int array_size;
   int *numbers;

   MPI_Init(&argc, &argv);
   
   int rank, size;
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   MPI_Comm_size(MPI_COMM_WORLD, &size);

   if (rank == 0) {     // master process

      // build an array of numbers
      scanf("%d", &array_size);

      // send the array size to everyone
      for (int r = 0; r < size; r++) 
         MPI_Send(&array_size, 1, MPI_INT, r, NORMAL_TAG, MPI_COMM_WORLD);
   }

   // everyone receive the array size
   MPI_Status status;
   MPI_Recv(&array_size, 1, MPI_INT, 0, NORMAL_TAG, MPI_COMM_WORLD, &status);

   // everyone allocate an array
   numbers = (int *) malloc(sizeof(int) * array_size);

   if (rank == 0) {
      // read the array from input
      for (int i = 0; i < array_size; i++) {
         scanf("%d", &numbers[i]);
      }
      
      // send everyone the array
      for (int r = 1; r < size; r++) {
         MPI_Send(numbers, array_size, MPI_INT, r, NORMAL_TAG, MPI_COMM_WORLD);
      }

   } else {
      // all ranks but 0 receive the array
      MPI_Recv(numbers, array_size, MPI_INT, 0, NORMAL_TAG, MPI_COMM_WORLD, &status);
   }

   // every rank compute its partial sum
   int partial_sum = 0;
   for (int i = (array_size/size) * rank; i < (array_size/size) * rank + (array_size/size); i++) {
      partial_sum += numbers[i];
   }

   MPI_Send(&partial_sum, 1, MPI_INT, 0, NORMAL_TAG, MPI_COMM_WORLD);

   if (rank == 0) {
      int partial_answer, final_answer = 0;
      for (int r = 0; r < size; r++) {
         MPI_Recv(&partial_answer, 1, MPI_INT, r, NORMAL_TAG, MPI_COMM_WORLD, &status);
         final_answer += partial_answer;
      }

      printf("The sum is %d\n", final_answer);
   }
      
   MPI_Finalize();
}
