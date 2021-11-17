# Code taken from cthorpe/public/142/listeditor

fv: ui.o bufferlib.o
	g++ ui.o bufferlib.o -o fv

ui.o: ui.cpp buffer.h
	g++ -std=c++11 -c ui.cpp -o ui.o

driver: driver.o bufferlib.o
	g++ -std=c++11 driver.o bufferlib.o -o driver

driver.o: driver.cpp buffer.h
	g++ -std=c++11 -c driver.cpp -o driver.o

bufferlib.o: bufferlib.cpp buffer.h
	g++ -std=c++11 -c bufferlib.cpp -o bufferlib.o
