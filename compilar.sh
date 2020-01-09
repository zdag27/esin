g++ -std=c++98 -c  easy_dial.cpp
g++ -std=c++98 -o driver_easydial.e *.o -lesin
./driver_easydial.e < jp_public_easy_dial.in >jp_public_easy_dial.out
./main.e < jp_public_easy_dial.out > out.out