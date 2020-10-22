/*
 * netWriter.h
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

class NetWriter
{
public:
	NetWriter(int socket);
	~NetWriter();
	void listener();
	void sendMessage(char sendbuf[]);

private:
	int socket;
	int iResult;
};
