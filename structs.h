/*
 * structs.h
 *
 *  Created on: 19 okt. 2020
 *      Author: setjon-7
 */
#pragma once
#define MAXNAMELEN  32
enum ObjectDesc
{
	Human,
	NonHuman,
	Vehicle,
	StaticObject
};
enum ObjectForm
{
	Cube,
	Sphere,
	Pyramid,
	Cone
};
struct Coordinate
{
	int x;
	int y;
};
// Message   head
enum MsgType
	{
	Join,  // Client joining game at server
	Leave,// Client leaving game
	Change,  // Information  to clients
	Event,// Information  fro m clients to server
	TextMessage  // Send tex  t messages  to one   or all
	};
// Included  first in all messages
struct MsgHead
{
	unsigned  int  length;  // Total length for whole message
	unsigned  int  seq_no;     // Sequencenumber
	unsigned  int  id;    // Client ID or 0;
	MsgType  type;  // Type of message
};

// Message   type   Join (Client  ->Server)
struct JoinMsg
{
	MsgHead head;
	ObjectDesc desc;
	ObjectForm form;
	char name[MAXNAMELEN]; // nullterminated!,  or empty
	};
// Message   type   Leave (Client  ->Server)
struct LeaveMsg
{
	MsgHead  head;
};
// Message   type   Change (Server ->Client)
enum ChangeType
{
	NewPlayer,
	PlayerLeave,
	NewPlayerPosition
};
// Included  first in all Changemessages
struct ChangeMsg
{
	MsgHead  head;
	ChangeType  type;
};
//   Variations of ChangeMsg
struct NewPlayerMsg
{
	ChangeMsg msg;  //Change  message header with new client id
	ObjectDesc  desc;
	ObjectForm  form;
	char  name[MAXNAMELEN];  // nullterminated!,  or empty
};
struct PlayerLeaveMsg
{
	ChangeMsg msg;  //Change  message header with new client id
	};
struct NewPlayerPositionMsg
{
	ChangeMsg msg;  //Change  messageheader
	Coordinate  pos;  //New object position
	Coordinate  dir;  //New object direction
};

// Messages of  type   Event  (Client  ->Server)
enum EventType
{
	Move
};
// Included  first in all Event messages
struct EventMsg
{
	MsgHead  head;
	EventType type;
};
//   Variantions of EventMsg
struct MoveEvent
{
	EventMsg event;
	Coordinate pos;//Newobjectposition
	Coordinate dir;//Newobjectdirection
	};
// Messages of  type   TextMessage
struct TextMessageMsg  // Optional  at client side!!!
{
	MsgHead  head;
	char  text[1];    // NULL-terminerad  array av chars.
};

struct Client
{
	int id = -1;
	Coordinate pos;
	Coordinate dir;
};

struct ReadToWriteMsg
{
	MsgHead head;
	Client client;
	ChangeType type;
};










