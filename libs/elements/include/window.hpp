#ifndef WINDOW
#define WINDOW

#include "basepoint.hpp"

class Window {
public:
	Window(int x, int y, int width, int height) :
			x(x), y(y), width(width), height(height) {
	}

	int getX() {
		return this->x;
	}

	int getY() {
		return this->y;
	}

	int getWidth() const {
		return this->width;
	}

	int getHeight() const {
		return this->height;
	}

	void move(int x, int y) {
		this->x += x;
		this->y += y;
	}

	void zoom(int step) {
		// TODO
	}

private:
	int x, y;
	int width, height;
};

#endif
