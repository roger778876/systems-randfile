#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int rand_num(int h) {
  int output;
  read(h, &output, sizeof(int));
  if (errno) {
    printf("Error %d: %s\n", errno, strerror(errno));
  }
  return output;
}

int main() {
  // creates array of random ints
  int fd = open("/dev/random", O_RDONLY);
  int a[10];
  int i = 0;
  printf("random a[10]:\n");
  for (i; i < 10; i++) {
    // a[i] = i;
    a[i] = rand_num(fd);
    printf("random %d: %d\n", i, a[i]);
  }
  close(fd);

  // writes array to file "randarray"
  fd = open("randarray", O_RDWR | O_CREAT | O_TRUNC, 0644);
  write(fd, a, 10 * sizeof(int));
  close(fd);
  if (errno) {
    printf("Error %d: %s\n", errno, strerror(errno));
  }

  // reads "randarray" into new array
  fd = open("randarray", O_RDONLY);
  int a1[10];
  read(fd, a1, 10 * sizeof(int));
  close(fd);
  if (errno) {
    printf("Error %d: %s\n", errno, strerror(errno));
  }

  // prints new array
  printf("\nrandom a1[10]:\n");
  i = 0;
  for (i; i < 10; i++) {
    printf("random %d: %d\n", i, a1[i]);
  }
}