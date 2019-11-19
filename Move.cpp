#include "pch.h"
#include "Move.h"

#include <iostream>

using namespace std;


Move::Move() {


}

Move::~Move(){

}

Move* Move::get_next_move() {
	//cout << "Finding the next move after this  move";
	
	return this->next;


}

void Move::set_next_move(Move *m) {
	this->next = m;
	cout << "\nSET NEXT MOVE TO. " << m << "end";
}