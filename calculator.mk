#calculator.make
#client server calculator make file:
#run using command: make -f calculator.mk

all: client server clean

client: client.o
	gcc -O client.o -o client.exe

server: server.o calculator.o
	gcc -O server.o calculator.o -o server.exe
   
client.o:
	gcc -c client.c
   
server.o:
	gcc -c server.c

calculator.o:
	gcc -c calculator.c
	
clean:
	rm client.o server.o calculator.o