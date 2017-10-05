#include <iostream>
#include <vector>

using namespace std;

#define ScreenWidth 80
#define ScreenHeight 23

class ASCIIDisplay {
public:
  ASCIIDisplay() {
    xres = ScreenWidth;
    yres = ScreenHeight;
  }

  void Clear() {
    for (int y = 0; y < yres; y++) {
      for (int x = 0; x < xres; x++) {
        charBuffer[y][x] = '\0';
      }
    }
  }

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
