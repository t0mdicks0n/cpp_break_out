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
const int canvasY = 20;
const int canvasX = 50;

void Setup() {

}

void Draw() {
	system("clear");
	for (int y = 0; y <= canvasY; y++) {
		for (int x = 0; x <= canvasX; x++) {
			// Draw "#" on the canvas if i and j are either at
			// their minimum or their maximum.
			// Otherwise draw " "
			if (y == 0 || y == canvasY || x == 0 || x == canvasX) {
				std::cout << "#";
			} else {
				std::cout << " ";
			}
		}
		std::cout << std::endl;
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