/*
 * netWriter.cpp
 *
 *  Created on: 20 okt. 2020
 *      Author: setjon-7
 */

#include "NetWriter.h"

NetWriter::NetWriter(int _socket)
{
	this->socket = _socket;

	this->iResult = NULL;
}

void NetWriter::listener()
{/*
	while(true)
	{
		while(this->buffer->size() > 0)
		{
			switch (this->buffer->at(0).type)
			{
				case (Join):
					JoinMsg joinmsg;
					char sendbuf1[sizeof(joinmsg)];
					joinmsg.head = this->buffer->at(0).head;
					memcpy((void*)sendbuf1, (void*)&joinmsg, sizeof(joinmsg));
					this->sendMessage(sendbuf1);
					break;
				case (Leave):
					LeaveMsg leavemsg;
					char sendbuf2[sizeof(leavemsg)];
					leavemsg.head = this->buffer->at(0).head;
					memcpy((void*)sendbuf2, (void*)&leavemsg, sizeof(leavemsg));
					this->sendMessage(sendbuf2);
					break;
				case (Change):
					ChangeMsg changemsg;
					changemsg.head = this->buffer->at(0).head;
					changemsg.type = this->buffer->at(0).type;
					switch(this->buffer->at(0).type)
					{
						case (NewPlayer):
							NewPlayerMsg newplayermsg;
							char sendbuf3[sizeof(newplayermsg)];
							newplayermsg.msg = changemsg;
							memcpy((void*)sendbuf3, (void*)&newplayermsg, sizeof(newplayermsg));
							this->sendMessage(sendbuf3);
							break;
						case (NewPlayerPosition):
							NewPlayerPositionMsg newplayerpositionmsg;
							char sendbuf4[sizeof(newplayerpositionmsg)];
							newplayerpositionmsg.msg = changemsg;
							newplayerpositionmsg.pos = this->buffer->at(0).client.pos;
							newplayerpositionmsg.dir = this->buffer->at(0).client.dir;
							memcpy((void*)sendbuf4, (void*)&newplayerpositionmsg, sizeof(newplayerpositionmsg));
							this->sendMessage(sendbuf4);
							break;
						case (PlayerLeave):
							PlayerLeaveMsg playerleavemsg;
							char sendbuf5[sizeof(playerleavemsg)];
							playerleavemsg.msg = changemsg;
							memcpy((void*)sendbuf5, (void*)&playerleavemsg, sizeof(playerleavemsg));
							this->sendMessage(sendbuf5);
							break;
					}

					break;
				case (TextMessage):
						//implement maybe idk
						std::cout << "Received textmessage, dropped bc not implemented lul";
						break;
			}
			buffer->erase(buffer->begin());
		}
	}
	*/
}

void NetWriter::sendMessage(char sendbuf[])
{
	if((iResult = write(socket, (void*)sendbuf, sizeof(*sendbuf))) < 0)
	{
		std::cout << "error writing to socket";
	}
	else if(iResult == 0)
	{
		std::cout << "connection closed.";
	}
	else
	{
		std::cout << "Sent " + std::to_string(iResult) + " bytes.";
	}
}


