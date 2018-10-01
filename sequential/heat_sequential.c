/* 
 * Heat simulation for a square room.
 *
 * J. Hollingsworth
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "gfx.h"

#define SZ 400
#define AMBIENT 0.3
#define COLD 0.0
#define HOT 1.0
#define HEATER_COUNT 2
#define HEATER_SZ 30
#define ITERATIONS 2000
#define K 0.25

int main() {

   // the room (need 2 since we're doing a discrete event simulation)
   double new_grid[SZ][SZ];
   double old_grid[SZ][SZ];

   // initialize the grid
   for (int x = 0; x < SZ; x++) {
      for (int y = 0; y < SZ; y++) {
         old_grid[x][y] = AMBIENT;

         // set the edges to be COLD
         if (x == 0 || x == SZ - 1 || y == 0 || y == SZ -1) {
              old_grid[x][y] = COLD;
              new_grid[x][y] = COLD;
         }
      }
   }

   // drop some heaters in the room
   int heater_location_x[HEATER_COUNT];
   int heater_location_y[HEATER_COUNT];
   srand(time(NULL));
   for (int i = 0; i < HEATER_COUNT; i++) {
      // location for the heater
      int x_center = (int)(rand() % (SZ - 2 * HEATER_SZ)) + HEATER_SZ;
      int y_center = (int)(rand() % (SZ - 2 * HEATER_SZ)) + HEATER_SZ;

      // remember the heater's location
      heater_location_x[i] = x_center;
      heater_location_y[i] = y_center;

      // set the heaters to HOT
      for (int x = 0; x < HEATER_SZ; x++) {
         for (int y = 0; y < HEATER_SZ; y++) {
            old_grid[x_center - HEATER_SZ/2 + x][y_center - HEATER_SZ/2 + y] = HOT;
         }
      }
   }


   // open the window for graphics
   gfx_open(SZ, SZ, "Heat Transfer");

   for (int i = 0; i < ITERATIONS; i++) {
      printf("Step %d\n", i);
   
      // draw the room
      for (int x = 0; x < SZ; x++) {
         for (int y = 0; y < SZ; y++) {
            double p = old_grid[x][y];
            gfx_color(p*255, p*255, p*255);
            gfx_line(x, y, x, y);
         }
      }
      gfx_flush();

      // one step in the simulation
      for (int x = 1; x < SZ - 1; x++) {
         for (int y = 1; y < SZ - 1; y++) {
            new_grid[x][y] = old_grid[x][y]
                             + K * (old_grid[x+1][y] 
                             + old_grid[x-1][y]
                             + old_grid[x][y+1]
                             + old_grid[x][y-1]
                             - 4 * old_grid[x][y]);
         }
      }

      // update the heaters
      for (int j = 0; j < HEATER_COUNT; j++) {
         for (int x = 0; x < HEATER_SZ; x++) {
            for (int y = 0; y < HEATER_SZ; y++) {
               new_grid[heater_location_x[j] - HEATER_SZ/2 + x]
                       [heater_location_y[j] - HEATER_SZ/2 + y] = HOT;
            }
         }
      }

      // copy the new grid into the old grid
      for (int x = 0; x < SZ; x++) {
         for (int y = 0; y < SZ; y++) {
            old_grid[x][y] = new_grid[x][y];
         }
      }
   }

   while (1) {
      char c = gfx_wait();
      if (c == 'q') break;
   }

   return 0;

}
/* gcc -o heat_sequential heat_sequential.c gfx.c -I/usr/X11/include -L/usr/X11/lib -lX11 */
