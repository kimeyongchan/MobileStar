
//
// GameClient.h
//
// create by kimyc on 2014.6.28
//

#ifndef __GAME_CLIENT_H__
#define __GAME_CLIENT_H__

#include "GameDefines.h"
#include "BasicPacket.h"
#include <string>
#include <vector>

class GameClient
{
public:
	static GameClient& GetInstance();
	static GameClient* GetPointer();
	static const GameClient& GetConst();
	

public:
	static void intToString(std::string& str, int integer);
private:
	GameClient();
	~GameClient();

public:
	bool Initialize();
	void SetUserInfo(UserInfo* _userInfo);
	UserInfo* GetUserInfo() {
		return userInfo;
	}

public:
    SessionId_t sessionId;
	UserInfo* userInfo;
	int currentScene;
	int16_t channelNo;

    int roomNo;
    int tribe;
};

#endif //__GAME_CLIENT_H__


