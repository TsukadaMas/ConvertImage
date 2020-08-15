#include <stdio.h>
#include <string.h>
#include "class.h"

struct pixel {
  int red;
  int blue;
  int green;
};

int main() {
  int option = 0;
  while (option != 4) {
    showMainMenu();
    scanf("%d", &option);
    if (option == 1) {
      createImage();
    } else if (option == 2) {
        greyScale();
    } else if (option == 3) {
        flip();
    } else if (option == 4) {
      //do nothing exit the loop
    } else {
      printf("%d is not a option please choose an option\n\n", option);
    }
  }
}
