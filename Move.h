#pragma once
class Move
{
public:
	Move();
	~Move();
	int begRow, begCol, endRow, endCol;
	//pointer to next object
	Move *get_next_move();
	void set_next_move(Move *m);
	Move *next = nullptr;
};

