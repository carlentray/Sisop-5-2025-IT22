#include "shell.h"
#include "kernel.h"
#include "std_lib.h"

char username[32] = "user";
char company[32] = "";

void shell() {
  char buf[128];
  char cmd[64];
  char arg[2][64];

  printString("Welcome to EorzeOS!\n");

  while (true) {
    printString(username);
    if (strlen(company) > 0) {
      printString("@");
      printString(company);
    }
    printString("> ");

    readString(buf);
    parseCommand(buf, cmd, arg);

    if (strcmp(cmd, "user") == 0) {
      if (strlen(arg[0]) > 0) {
        strcpy(username, arg[0]);
        printString("Username changed to ");
        printString(username);
        printString("\n");
      } else {
        strcpy(username, "user");
        printString("Username changed to user\n");
      }

    } else if (strcmp(cmd, "grandcompany") == 0) {
      if (strcmp(arg[0], "maelstrom") == 0) {
        clearScreen();
        setColor(RED);
        strcpy(company, "Storm");

      } else if (strcmp(arg[0], "twinadder") == 0) {
        clearScreen();
        setColor(YELLOW);
        strcpy(company, "Serpent");

      } else if (strcmp(arg[0], "immortalflames") == 0) {
        clearScreen();
        setColor(BLUE);
        strcpy(company, "Flame");

      } else {
        printString("Unknown Grand Company!\n");
      }

    } else if (strcmp(cmd, "clear") == 0) {
      clearScreen();
      company[0] = '\0';
      setColor(WHITE);

    } else if (strcmp(cmd, "add") == 0 || strcmp(cmd, "sub") == 0 ||
               strcmp(cmd, "mul") == 0 || strcmp(cmd, "div") == 0) {
      int a = strToInt(arg[0]);
      int b = strToInt(arg[1]);
      int result = 0;

      if (strcmp(cmd, "add") == 0) result = a + b;
      if (strcmp(cmd, "sub") == 0) result = a - b;
      if (strcmp(cmd, "mul") == 0) result = a * b;
      if (strcmp(cmd, "div") == 0) result = b != 0 ? a / b : 0;

      char out[32];
      intToStr(result, out);
      printString(out);
      printString("\n");

    } else if (strcmp(cmd, "yogurt") == 0) {
      char *responses[] = {"yo", "ts unami gng </3", "sygau"};
      int tick = getBiosTick();
      printString(responses[tick % 3]);
      printString("\n");

    } else if (strlen(cmd) > 0) {
      printString(buf);  
      printString("\n");
    }
  }
}

void parseCommand(char *buf, char *cmd, char arg[2][64]) {
  int i = 0, j = 0, k = 0, stage = 0;
  while (buf[i] != '\0') {
    if (buf[i] == ' ') {
      if (stage == 0) {
        cmd[j] = '\0';
        stage = 1;
        k = 0;
      } else if (stage == 1) {
        arg[0][k] = '\0';
        stage = 2;
        k = 0;
      }
    } else {
      if (stage == 0) {
        cmd[j++] = buf[i];
      } else if (stage == 1) {
        arg[0][k++] = buf[i];
      } else if (stage == 2) {
        arg[1][k++] = buf[i];
      }
    }
    i++;
  }

  if (stage == 0) cmd[j] = '\0';
  if (stage == 1) arg[0][k] = '\0';
  if (stage == 2) arg[1][k] = '\0';
}
