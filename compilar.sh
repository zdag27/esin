g++ -c -std=c++98 call_registry.cpp
g++ -o driver_easydial.e *.o -lesin
./driver_easydial.e < input.in