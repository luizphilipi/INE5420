INCLUDE_PATH=-I ./view/include \
-I ./controller/include \
-I ./libs

SRC_FILES=main.cpp \
controller/src/canvasController.cpp \
view/src/telaPrincipal.cpp \
libs/elements/include/listaEnc.hpp


all:
	g++ $(INCLUDE_PATH) `pkg-config --cflags gtk+-3.0` -o CG $(SRC_FILES) `pkg-config --libs gtk+-3.0`
