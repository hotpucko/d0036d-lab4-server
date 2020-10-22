#include "BroadcastManager.h"

BroadcastManager::BroadcastManager(std::vector<player*> *_players)
{
	this->players = _players;
}

BroadcastManager::~BroadcastManager()
{
}

bool BroadcastManager::AddSocket(int socket)
{
	for (int i = 0; i < this->sockets.size(); i++)
	{
		if (socket == this->sockets[i])
			return false;
	}
	this->sockets.push_back(socket);
	return true;
}

void BroadcastManager::RemoveSocket(int socket)
{
	for (int i = 0; i < this->sockets.size(); i++)
	{
		if (socket == this->sockets[i])
			sockets.erase(sockets.begin() + i);
	}

}

void BroadcastManager::Broadcast(char* buffer[])
{
	char* sendbuffer[sizeof(buffer)];

	memcpy(&sendbuffer,  &buffer, sizeof(buffer));
    std::cout << "it shouldn't be here" << std::endl;
	for (int i = 0; i < this->players->size(); i++)//sockets.size(); i++)
	{
        std::cout << "sent " << std::to_string(sizeof(sendbuffer)) << " bytes to id " << std::to_string(this->players->at(i)->client->id) << std::endl;
		send(this->players->at(i)->socket, &sendbuffer, sizeof(sendbuffer), 0);

			/*for (int i = 0; i < this->players.size(); i++)
			{
				if (sockets[i] == players.at(i)->GetSocket())
				{
					players.at(i)->thread->join();
					delete players.at(i)->thread;
				}
			}*/

	}
}
