//============================================================================
// Name        : D0036D-lab4-server.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#pragma once
#include <iostream>
#include "structs.h"
#include <vector>
#include <thread>

#include "NetReader.h"
#include "NetWriter.h"
#include "player.h"
#include "BroadcastManager.h"
#include <pthread.h>

using namespace std;

int main() {
	std::vector<ReadToWriteMsg> buffer;
	std::vector<ReadToWriteMsg>* bufptr = &buffer;
	std::vector<Client*> _clients;
	std::mutex *mutex = new std::mutex;

	NetReader* reader = new NetReader();
	//NetWriter* writer = new NetWriter(reader->getSocket());

	std::thread readerThread (&NetReader::listener, reader);
	readerThread.detach();
	std::cout << "readerThread started" << std::endl;
	//std::thread writerThread (&NetWriter::listener, writer);
	//writerThread.detach();
	//std::cout << "writerThread started" << std::endl;
	while(true)
	{

	}

	std::cout << "Reached end of file" << std::endl;
	return 0;

	/*
	 * sockets
	 * http://linuxhowtos.org/C_C++/socket.htm sockets
	 *
	 * linux server example of the lab
	 * https://github.com/MLGcat/D0036D/tree/master/Lab%204/Spelprotokoll_server_linux
	 *
	 *
	 *
	 *
	 * Måste accepta connections, skapa trådar för varje connection som hanterar reads i guess, checka gitten
	 */
}
