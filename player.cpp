#include "player.h"

player::player(int _socket, grid* _grid, int _id, BroadcastManager *_broadcaster, std::mutex *_mutex)
{
    this->client = new Client;
    this->socket = _socket;
    this->_grid = _grid;
    this->client->id = _id;
	this->broadcaster = _broadcaster;
	this->mutex = _mutex;
	std::cout << std::to_string(_id) << std::endl;
}

void player::Connect(int _socket)
{
	client->pos = _grid->FirstAvailableCoordinate();
	header.seq_no = 0;
	header.id = client->id;
	std::cout << std::to_string(client->id) << std::endl;

	//wait for join request
	std::cout << "waiting for join" << std::endl;
	recv(_socket, readbuffer, sizeof(readbuffer), 0);
	std::cout << "received join" << std::endl;

	//if wanna do stuff based on join info do here

	//send join response
    header.seq_no = header.seq_no + 1;
    //header.
    JoinMsg join;
    join.head = header;
    join.head.type = Join;
    join.head.length = sizeof(join);


	char* sendbuffer[sizeof(join)];

	memcpy(sendbuffer, (char*)&join, sizeof(join));

	send(this->socket, sendbuffer, sizeof(sendbuffer), 0);
    std::cout << "sent join msg" << std::endl;

    ChangeMsg msg;
    msg.type = NewPlayer;
    msg.head.type = Change;
    msg.head.id = this->client->id;
    msg.head.seq_no = ++header.seq_no;
    NewPlayerMsg pmsg;
    msg.head.length = sizeof(pmsg);
    pmsg.msg = msg;

    char* sendBuffer[sizeof(pmsg)];
    memcpy(&sendBuffer, (char*)&pmsg, sizeof(pmsg));
    std::cout << "id: " << std::to_string(pmsg.msg.head.id) << ", length: " << std::to_string(pmsg.msg.head.length) << ", seq: " << std::to_string(pmsg.msg.head.seq_no) << std::endl;
    for (int i = 0; i < this->_grid->players->size(); i++)//sockets.size(); i++)
    {
        if(this->_grid->players->at(i)->client->id != this->client->id)
        {
            std::cout << "row 58: sent " << std::to_string(sizeof(sendBuffer)) << " bytes to id " << std::to_string(this->_grid->players->at(i)->client->id) << std::endl;
            //std::lock_guard<std::mutex> lock(*mutex);
            send(this->_grid->players->at(i)->socket, &sendBuffer, sizeof(sendBuffer), 0);
        }


            /*for (int i = 0; i < this->players.size(); i++)
            {
                if (sockets[i] == players.at(i)->GetSocket())
                {
                    players.at(i)->thread->join();
                    delete players.at(i)->thread;
                }
            }*/

    }

    boi();

    /*for(int i = 0; i < this->_grid->players->size(); i++)
    {
        if(this->_grid->players->at(i)->client->id != this->client->id)
        {
            this->header.seq_no = this->header.seq_no + 1;
            MsgHead head;
            head.seq_no = this->header.seq_no;
            head.id = this->_grid->players->at(i)->client->id;
            head.type = Change;
            ChangeMsg x;
            x.head = head;
            x.type = NewPlayer;

            NewPlayerMsg y;
            x.head.length = sizeof(y);
            y.msg = x;


            char* sendbuf[sizeof(y)];
            memcpy(&sendbuf, (char*)&y, sizeof(y));
            NewPlayerMsg z;
            memcpy(&z, (char*)&sendbuf, sizeof(sendbuf));
            std::cout << "last id: " << z.msg.head.id;
            std::cout << "from id " << std::to_string(y.msg.head.id) << "to id: " << this->client->id << ", length: " << std::to_string(y.msg.head.length) << ", seq: " << std::to_string(y.msg.head.seq_no) << std::endl;
            send(this->socket, sendbuf, y.msg.head.length, 0);
            std::cout << "Sent NewPlayer message" << std::endl;
        }
    }*/

    Listener();
}

void player::boi()
{
    for(int i = 0; i < this->_grid->players->size(); i++)
    {
        if(this->_grid->players->at(i)->client->id != this->client->id)
        {
            ChangeMsg msg;
            msg.type = NewPlayer;
            msg.head.type = Change;
            msg.head.id = this->_grid->players->at(i)->client->id;
            msg.head.seq_no = ++header.seq_no;
            NewPlayerMsg pmsg;
            msg.head.length = sizeof(pmsg);
            pmsg.msg = msg;


            char* sendBuffer[sizeof(pmsg)];
            bzero((void*)&sendBuffer, sizeof(sendBuffer));
            memmove(&sendBuffer, (char*)&pmsg, sizeof(pmsg));
            std::cout << "row 132: sent from id: " << std::to_string(pmsg.msg.head.id) << "To id: " << this->client->id << ", length: " << std::to_string(pmsg.msg.head.length) << ", seq: " << std::to_string(pmsg.msg.head.seq_no) << std::endl;
            //std::lock_guard<std::mutex> lock(*mutex);
            send(this->socket, sendBuffer, sizeof(sendBuffer), 0);

        }
    }
}

void player::Listener()
{
	do {

		if((iResult = recv(socket, readbuffer, sizeof(readbuffer), 0)) > 0)
		{
			printf("bytes received: %d\n", iResult);

			//parse data

			printf("Bytes received: %d\n", iResult);
			MsgHead* msghead;
			msghead = (MsgHead*)readbuffer;
			std::cout << "received: id: " << msghead->id << ", length: " << msghead->length << ", seq: " << msghead->seq_no << std::endl;
			//continue;


			if (msghead->type == Event)
			{
				EventMsg* msgType;
				msgType = (EventMsg*)readbuffer;
				std::cout << "Received event message" << std::endl;
				if (msgType->type == Move)
				{

					MoveEvent* moveEvent;
					moveEvent = (MoveEvent*)readbuffer;

					std::cout << "Received event message: move x: " << std::to_string(moveEvent->pos.x) << ", y: " << std::to_string(moveEvent->pos.y) << std::endl;

                    ChangeMsg change;
                    this->header.seq_no++;
                    this->header.type = Change;
                    change.head = this->header;
                    change.type = NewPlayerPosition;

					NewPlayerPositionMsg msg;
                    change.head.length = sizeof(msg);
					msg.msg.type = NewPlayerPosition;



					if (this->_grid->CanMove(moveEvent->pos))
					{
						this->client->pos = moveEvent->pos;
					}
					else
					{
                        std::cout << "Wrong jump" << std::endl;
					}
					msg.pos = this->client->pos;
					msg.msg = change;

					char* sendBuffer[sizeof(msg)];
					memcpy(sendBuffer, (char*)&msg, sizeof(msg));

					std::cout << "sent: id: " << std::to_string(msg.msg.head.id) << ", length: " << std::to_string(msg.msg.head.length) << ", seq: " << std::to_string(msg.msg.head.seq_no) << ", pos.x: " << msg.pos.x << ", pos.y: " << msg.pos.y << std::endl;

					for (int i = 0; i < this->_grid->players->size(); i++)//sockets.size(); i++)
                    {
                        std::cout << "sent " << std::to_string(sizeof(sendBuffer)) << " bytes to id " << std::to_string(this->_grid->players->at(i)->client->id) << std::endl;
                        send(this->_grid->players->at(i)->socket, &sendBuffer, sizeof(sendBuffer), 0);

                            /*for (int i = 0; i < this->players.size(); i++)
                            {
                                if (sockets[i] == players.at(i)->GetSocket())
                                {
                                    players.at(i)->thread->join();
                                    delete players.at(i)->thread;
                                }
                            }*/

                    }
					//this->broadcaster->Broadcast(sendBuffer);

				}
			}
			else if (msghead->type == Leave)
			{
				std::cout << "Leave message" << std::endl;
				std::cout << "Player ID:" << msghead->id << " has left the game" << std::endl;


				for(int i = 0; i < this->_grid->players->size(); i++)
                {
                    //if(this->_grid->players->at(i)->client->id != this->client->id)
                    //{
                        LeaveMsg pmsg;
                        pmsg.head.type = Leave;
                        pmsg.head.id = this->client->id;
                        pmsg.head.seq_no = ++header.seq_no;
                        pmsg.head.length = sizeof(pmsg);


                        char* sendBuffer[sizeof(pmsg)];
                        bzero((void*)&sendBuffer, sizeof(sendBuffer));
                        memmove(&sendBuffer, (char*)&pmsg, sizeof(pmsg));
                        std::cout << "row 240: sent from id: " << std::to_string(this->client->id) << "To id: " << pmsg.head.id << ", length: " << std::to_string(pmsg.head.length) << ", seq: " << std::to_string(pmsg.head.seq_no) << std::endl;
                        //std::lock_guard<std::mutex> lock(*mutex);
                        send(this->_grid->players->at(i)->socket, sendBuffer, sizeof(sendBuffer), 0);

                    //}
                }

				/*for (int i = 0; i < this->_grid->players->size(); i++)
				{
					if (msghead->id == this->_grid->players->at(i)->client->id)
					{

						//this->_grid->players->erase(this->_grid->players->begin() + i);
						//this->thread->join();
						//delete &thread;
					}
				}*/
			}
        }
        else if (iResult == 0)
        {
			printf("Connection closed\n");
			/*for (int i = 0; i < this->_grid->players->size(); i++)
            {
                if (this->client->id == this->_grid->players->at(i)->client->id)
                {
                    this->_grid->players->erase(this->_grid->players->begin() + i);
                    this->thread->join();
                    this->this_thread.sleep_until(std::chrono.hours.max());
                    //std::thread.
                    std::terminate();
                    //delete &thread;
                }
            }*/
        }
		else
		{
			printf("recv failed: %d\n", iResult);//WSAGetLastError());
            /*for (int i = 0; i < this->_grid->players->size(); i++)
            {
                if (this->client->id == this->_grid->players->at(i)->client->id)
                {
                    this->_grid->players->erase(this->_grid->players->begin() + i);
                    std::terminate();
                    //this->thread->join();
                    //delete &thread;
                }
            }*/
		}

	} while (iResult > 0);
}

int player::GetSocket()
{
	return this->socket;
}

void player::SetThread(std::thread *_thread)
{
	this->thread = _thread;
}



player::~player()
{
	close(socket);
    for (int i = 0; i < _grid->players->size(); i++)
    {
        if(_grid->players->at(i)->client->id == this->client->id)
        {
			player* ptr = _grid->players->at(i);
			_grid->players->erase(_grid->players->begin() + i);
			delete& ptr;
			ptr = NULL;
        }
    }
}
