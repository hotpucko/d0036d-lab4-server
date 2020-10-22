#pragma once
#include "structs.h"
#include <vector>
class player;
#include "player.h"
#include <sys/types.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <mutex>

class BroadcastManager
{
public:
	BroadcastManager(std::vector<player*> *_players);
	~BroadcastManager();
	bool AddSocket(int socket);
	void RemoveSocket(int socket);
	void Broadcast(char* buffer[]);

private:
	std::vector<int> sockets;
	int seq_no;
	std::vector<player*> *players;
};
