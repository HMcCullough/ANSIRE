#include "ASCIIDisplay.h"

int main(void) {
  ASCIIDisplay ad;

  for (int y = 0; y < ScreenHeight; y++) {
    for (int x = 0; x < ScreenWidth; x++) {
      ad.charSet('0' + x, x, y);
    }
  }

  ad.Print("|        TEST        |", 20, 11);

  ad.draw();
}
