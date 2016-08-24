LIBS = `pkg-config opencv --libs --cflags`
OPT = -c -Wall

#all : contours
all: contours
	@echo "All done"

#contours: contour.cpp
#	g++ ${OPT} -o contours contour.cpp ${LIBS}
#	@echo "contours OK"
contours: contour.o filtrage.o affichage.o
	g++ contour.o filtrage.o affichage.o -o contours ${LIBS}
	@echo "contours -o OK"

contours.o: contour.cpp
	g++ ${OPT} contour.cpp ${LIBS}
	@echo "contours OK"

filtrage.o: filtrage.cpp
	g++ ${OPT} filtrage.cpp	${LIBS}
	@echo "filtrage OK"

affichage.o: affichage.cpp
	g++ ${OPT} affichage.cpp	${LIBS}
	@echo "affichage OK"

clean :
	rm *o contours