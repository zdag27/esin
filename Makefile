OPTIONS = -std=c++98 -g -O0 -ansi -Wall

phone.o: phone.hpp phone.cpp phone.rep
	g++ $(OPTIONS) -c phone.cpp

call_registry.o: call_registry.hpp call_registry.cpp call_registry.rep
	g++ $(OPTIONS) -c call_registry.cpp
	
dialog.o: dialog.hpp dialog.cpp
	g++ $(OPTIONS) -c dialog.cpp

easy_dial.o: easy_dial.hpp easy_dial.cpp
	g++ $(OPTIONS) -c easy_dial.cpp
	
driver_easydial.o: driver_easydial.cpp
	g++ $(OPTIONS) -c driver_easydial.cpp

main: phone.o call_registry.o easy_dial.o dialog.o driver_easydial.o 
	g++ $(OPTIONS) -o main driver_easydial.o phone.o call_registry.o easy_dial.o dialog.o -lesin


clean:
	rm *.o
	rm main
