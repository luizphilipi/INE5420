all:
	g++ ./src/* `pkg-config --cflags gtk+-3.0` -o CG `pkg-config --libs gtk+-3.0`
