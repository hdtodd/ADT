/* test methods for parsing range and plot entries */

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv) {

  char *range = "0.13/.39";
  char *plot = ".3(.05).5";

  float rlow, rhi, plow, pinc, phi;

  sscanf(range, "%f/%f", &rlow, &rhi);
  printf("For %s, got rlow = %f, rhi = %f\n", range, rlow, rhi);

  range = "-.5/+5";
  sscanf(range, "-%f/+%f", &rlow, &rhi);
  printf("For %s, got rlow = %f, rhi = %f\n", range, rlow, rhi);


  return(0);
}
