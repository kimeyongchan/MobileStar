#ifndef __CLIENT_GAME_PACKET_H__
#define __CLIENT_GAME_PACKET_H__

#include <stdint.h>
#include "BasicPacket.h"

class ClientGamePacket
{
public:

	////////////Packet Command//////////////

	static const int32_t PACKET_VERSION = 7;

    enum EnumCommand // start number is at least 3.
    {
        FIRST_CONNECT_REQ = 10,
        FIRST_CONNECT_RES,
        FIRST_CONNECT_FAIL,
        
        START_GAME_NOTIFY,

        CLIENT_NOTIFY,
        
        FINISH_GAME_REQ,
        FINISH_GAME_RES,
        FINISH_GAME_FAIL,
        FINISH_GAME_OK,
    };
    
    enum EnumFailReason
    {
        PACKET_VERSION_INCORRECT = 1,
        SERVER_ERROR,
        ALREADY_REQUEST,
        ALREADY_FRIEND,
        NOT_FRIEND,
    };
    
    ///////////////////////////////////
    
#pragma pack(push, 1)
    
    ///////////////////////////////////
    
    
    struct FirstConnectReqPacket : public Packet
    {
        FirstConnectReqPacket() { cmd = FIRST_CONNECT_REQ; }
        
        SessionId_t sid;
    };
    
    struct FirstConnectResPacket : public Packet
    {
        FirstConnectResPacket() { cmd = FIRST_CONNECT_RES; }
        
    };
    
    struct StartGameNotifyPacket : public Packet
    {
        StartGameNotifyPacket() { cmd = START_GAME_NOTIFY; }
        
    };
    
    struct ClientNotifyPacket : public Packet
    {
        ClientNotifyPacket() { cmd = CLIENT_NOTIFY; }
        
        uint32_t notiSize;
    };
    
    struct FinishGameReqPacket : public Packet
    {
        FinishGameReqPacket() { cmd = FINISH_GAME_REQ; }
        
        int8_t isWin;
    };
    
    struct FinishGameResPacket : public Packet
    {
        FinishGameResPacket() { cmd = FINISH_GAME_RES; }
        
        char ip[MAX_IP_ADDRESS_LEN];
        uint16_t port;
    };
    
    struct FinishGameOkPacket : public Packet
    {
        FinishGameOkPacket() { cmd = FINISH_GAME_OK; }
    };
    
    
    struct FailPacket
    {
        int32_t failReason;
    };

};
#pragma pack(pop)
#endif //__CLIENT_GAME_PACKET_H__
