/*
 * Parallel sum using MPI w/ scatter/gather.
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

   if (rank == 0) {
      numbers = (int *) malloc(sizeof(int) * array_size);

      // read the array from input
      for (int i = 0; i < array_size; i++) {
         scanf("%d", &numbers[i]);
      }
   }
   
   // everyone allocate an array
   int *local_numbers = (int *) malloc(sizeof(int) * array_size/size);

   // Scatter
   MPI_Scatter(numbers, array_size/size, MPI_INT, 
               local_numbers, array_size/size, MPI_INT, 
               0, MPI_COMM_WORLD);

   // every rank compute its partial sum
   int partial_sum = 0;
   for (int i = 0; i < array_size/size; i++) {
      partial_sum += local_numbers[i];
   }

   // Gather
   int *partial_answer = (int *) malloc(sizeof(int) * size);
   MPI_Gather(&partial_sum, 1, MPI_INT, 
              partial_answer, 1, MPI_INT, 
              0, MPI_COMM_WORLD);

   if (rank == 0) {
      // collect and compute the final answer
      int final_answer = 0;
      for (int r = 0; r < size; r++) {
         final_answer += partial_answer[r];
      }

      printf("The sum is %d\n", final_answer);
   }
      
   MPI_Finalize();
}
