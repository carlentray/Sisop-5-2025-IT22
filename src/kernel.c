#include "shell.h"
#include "kernel.h"

void printChar(char c);

int main() {
  clearScreen();
  shell();
  return 0;
}

void printString(char *str)
{ int i = 0;
 while (str[i] != '\0') {
   char c = str[i++];
   interrupt(0x10, 0x0E00 + c, 0, 0, 0); }
}

void readString(char *buf)
{ int i = 0;
 char c = 0;

 while (1) { c = interrupt(0x16, 0x0000, 0, 0, 0) & 0xFF;

    if (c == '\r') { // Enter
      buf[i++] = '\0';
      printChar('\r');
      printChar('\n');
      break;
} else if (c == 0x08) { // Backspace
      if (i > 0) {
        i--;
        printChar(0x08);
        printChar(' ');
        printChar(0x08);
      }
    } else {
      buf[i++] = c;
      printChar(c);
    }
  }
}

void clearScreen()
{int row, col;
  int segment = 0xB800;
  int offset;

  for (row = 0; row < 25; row++) {
    for (col = 0; col < 80; col++) {
      offset = 2 * (row * 80 + col);
      putInMemory(segment, offset, ' ');
      putInMemory(segment, offset + 1, 0x07); // putih di latar hitam
    }
  }

  interrupt(0x10, 0x0200, 0, 0, 0);
 
}
