/*
 * Nethandler.cpp
 *
 *  Created on: 19 okt. 2020
 *      Author: setjon-7
 */
#include "NetReader.h"
#include <netinet/tcp.h>

constexpr auto DEFAULT_READ_PORT = 49152;
constexpr auto DEFAULT_WRITE_PORT = 49153;

NetReader::NetReader()
{
	this->iResult = 0;

	this->sockfd = socket(AF_INET, SOCK_STREAM, 0);


    //idk man
    int flag = 1;
    iResult = setsockopt(sockfd, IPPROTO_TCP, TCP_NODELAY, (char*)&flag, sizeof(int));
    if(iResult < 0)
    {
        std::cout << "error setting socket options" << std::endl;
    }

	if(sockfd < 0)
	{
		std::cout << "Error opening socket";
		exit(1);
	}
	std::cout << "Opened socket successfully" << std::endl;
	bzero((char*)&serv_addr, sizeof(serv_addr));
	portno = DEFAULT_READ_PORT;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);
	if(bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
	{
		std::cout << "Error on socket binding";
		exit(1);
	}
	std::cout << "Bound socket successfully to port: " << std::to_string(portno) << std::endl;
	listen(sockfd, 5);
	std::cout << "socket listening" << std::endl;
	clilen = sizeof(cli_addr);
	//listen(sockfd//newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
	bzero(readbuffer, 256);


	_grid = new grid();
	this->_grid->players = &players;
	broadcaster = new BroadcastManager(_grid->players);

}

void NetReader::listener()
{
    int connectedPlayers = 0;
    std::vector<std::thread> playerThreads;

    socklen_t addrSize = sizeof(serv_addr);

    while(true)
    {
        if(connectedPlayers < 9)
        {
            if (newsockfd = accept(sockfd, (sockaddr*)&serv_addr, &addrSize))//accept(socket, (sockaddr*)&serv_addr, &addrsize) = newsockfd)
            {

                //idk man
                int flag = 1;
                iResult = setsockopt(newsockfd, IPPROTO_TCP, TCP_NODELAY, (char*)&flag, sizeof(int));
                if(iResult < 0)
                {
                std::cout << "error setting socket options" << std::endl;
                }


				int id = FindFreeID();
				player* newPlayer = new player(newsockfd, _grid, id, broadcaster, &mutex);
				this->_grid->players->push_back(newPlayer);
				//playerThreads.push_back();
				//playerThreads[playerThreads.size()-1] = std::thread(&player::Connect());

                std::cout << "received connection" << std::endl;
				std::thread(&player::Connect, newPlayer, newsockfd).detach();
				//playerThreads.at(playerThreads.size() - 1).detach();
				//pthr.detach();

            }
        }
        else
        {
            std::cout << "Max players connected" << std::endl;
        }
    }
}

int NetReader::getSocket()
{
	return this->sockfd;
}

int NetReader::FindFreeID()
{
	int id = 15;
	bool flag = true;
	if(this->_grid->players->size() == 0)
        flag = false;
	while (flag)
	{
		id++;
		flag = false;
		for (int i = 0; i < this->_grid->players->size(); i++)
		{
			if (id == this->_grid->players->at(i)->client->id)
				flag = true;
		}
	}

    int returnID = id % 9;
    if (returnID == 0)
    returnID++;

	return id % 9;
}

NetReader::~NetReader()
{
	close(sockfd);
}




