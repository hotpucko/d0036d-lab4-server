/*
 * NetReader.h
 *
 *  Created on: 20 okt. 2020
 *      Author: setjon-7
 */
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <vector>
#include "structs.h"
#include <iostream>
#include <mutex>
#include "player.h"
#include "grid.h"
#include "BroadcastManager.h"

#include <thread>
#include <arpa/inet.h>
#include <pthread.h>
#include <chrono>
#include <cstring>
#include <math.h>

class NetReader
{

public:
	~NetReader();
	NetReader();

	void listener();
	int getSocket();
	int FindFreeID();
private:
	int sockfd, newsockfd, portno;
	socklen_t clilen;
	char readbuffer[256];
	struct sockaddr_in serv_addr, cli_addr;
	int iResult;
	grid* _grid;
	BroadcastManager* broadcaster;
    std::vector<player*> players;
	std::mutex mutex;
};
