#include <iostream>
#include <thread>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

// Constants
bool gameOver = false;
enum eDirection {STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;
// Canvas
int canvasY = 30;
int canvasX = 50;

void Setup() {

}

// std::cout << "Hello";
// std::cout << std::endl;

void Draw() {
	system("clear");
	for (int i = 0; i < canvasY; i++) {
		for (int y = 0; y < canvasX; y++) {
			if (i == 0 || i == canvasY - 2) {
				std::cout << "#";
			} else {
				std::cout << " ";
			}
			// if (y == 3) {
			// 	std::cout << "#";
			// }
		}
	}
}

void Logic() {

}

int kbhit(void) {
  struct termios oldt, newt;
  int ch;
  int oldf;
 
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
 
  ch = getchar();
 
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);
 
  if(ch != EOF)
  {
    ungetc(ch, stdin);
    return 1;
  }
  return 0;
}

void Input() {
	if (kbhit()) {
		switch(getchar()) {
			case 'a' :
				dir = LEFT;
				break;
			case 'd' :
				dir = RIGHT;
				break;
			case 'w' :
				dir = UP;
				break;
			case 's' :
				dir = DOWN;
				break;
			case 'x' :
			gameOver = true;
			break;
		}
	}
}

void controlls() {
	while (!gameOver) {
		Input();
	}
}

int main() {
	std::thread parallelThread(controlls);
	parallelThread.detach();

	Setup();
	while (!gameOver) {
		Draw();
		Logic();
	}
}