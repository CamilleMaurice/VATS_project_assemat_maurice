LIBS = -lopencv_core -lopencv_imgproc -lopencv_highgui
INCLUDES = /usr/include/opencv-2.3.1/

main: main.o fgseg.o
	g++ -o main main.o fgseg.o $(LIBS) -lm
main.o: fgseg.hpp
	g++ -c main.cpp
fgseg.o: fgseg.hpp
	g++ -c fgseg.cpp -I$(INCLUDES) -O
	
clean: 
	rm -f *.o main 
	

