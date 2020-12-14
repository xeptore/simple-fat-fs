#include <stdio.h>

void info(char* message) { printf(">> %s\n", message); }

void fatal(char* message) {
  printf(">> %s\n", message);
  printf("Exiting...\n");
}

void debug(char* message) { printf("DEBUG: %s\n", message); }
