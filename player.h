/*
 * player.h
 *
 *  Created on: 20 okt. 2020
 *      Author: setjon-7
 */

#pragma once
#include "structs.h"
class grid;
class BroadcastManager;
#include <mutex>
#include "grid.h"
#include <vector>
#include <iostream>
#include <thread>
#include "BroadcastManager.h"
#include <chrono>

class player
{
public:
	player(int socket, grid* _grid, int _id, BroadcastManager *broadcaster, std::mutex *_mutex);
	~player();
    void Connect(int socket);
	void Listener();
	int GetSocket();
	void SetThread(std::thread *_thread);
	void boi();

	std::mutex m;
	Client* client;
	std::thread *thread;
    int socket;
private:
    grid *_grid;
	MsgHead header;
	BroadcastManager *broadcaster;
	int iResult;
	char *readbuffer[256];
	std::mutex* mutex;
};
