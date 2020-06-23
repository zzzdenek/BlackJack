blackjack: Box Player Deck Card Game main.cpp
	g++ -std=c++14 -Wall -o blackjack Box.o Player.o Deck.o Card.o Game.o main.cpp

Game: Game.cpp Game.h
	g++ -c -std=c++14 -Wall -o Game.o Game.cpp

Deck: Deck.cpp Deck.h
	g++ -c -std=c++14 -Wall -o Deck.o Deck.cpp

Card: Card.cpp Card.h
	g++ -c -std=c++14 -Wall -o Card.o Card.cpp

Player: Player.cpp Player.h
	g++ -c -std=c++14 -Wall -o Player.o Player.cpp

Box: Box.cpp Box.h
	g++ -c -std=c++14 -Wall -o Box.o Box.cpp

# clean
clean:
	rm *.o
	rm blackjack