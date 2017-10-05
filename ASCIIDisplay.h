/* Copyright (C) 2017 Logan Williamson - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the MIT license, and this disclaimer must
 * remain in this source file while code is being used.
 */

#include <iostream>
#include <vector>

using namespace std;

// Size of the display buffer
#define ScreenWidth 80
#define ScreenHeight 23

class ASCIIDisplay {
public:
  // Constructor, essentially just sets the resolution variables
  ASCIIDisplay() {
    xres = ScreenWidth;
    yres = ScreenHeight;
  }

  // Clears the display buffer, but not the screen
  void Clear() {
    for (int y = 0; y < yres; y++) {
      for (int x = 0; x < xres; x++) {
        charBuffer[y][x] = '\0';
      }
    }
  }

  // Sets a character at a given point in the buffer
  void charSet(char c, int xpoint, int ypoint) {
    for (int y = 0; y < yres; y++) {
      for (int x = 0; x < xres; x++) {
        if (x == xpoint && y == ypoint) {
          if (c != ' ')
            charBuffer[y][x] = c;
        }
      }
    }
  }

  // Sets an entire string at a given point in the buffer
  void Print(string s, int xpoint, int ypoint) {
    for (int y = 0; y < yres; y++) {
      for (int x = 0; x < xres; x++) {
        if (x == xpoint && y == ypoint) {
          for (int i = 0; i < s.length(); i++) {
            if (s[i] != ' ')
              charBuffer[y][x + i] = s[i];
          }
        }
      }
    }
  }

  // Redraws the buffer to the screen
  void draw() {
    clrscrn();
    for (int y = 0; y < yres; y++) {
      for (int x = 0; x < xres; x++) {
        cout << charBuffer[y][x];
      }
      cout << endl;
    }
  }

private:
  // Clears the screen
  void clrscrn() {
#ifdef WINDOWS
    std::system("cls");
#else
    // Assume POSIX
    std::system("clear");
#endif
  }

  int xres, yres;
  char charBuffer[ScreenHeight][ScreenWidth];
};
