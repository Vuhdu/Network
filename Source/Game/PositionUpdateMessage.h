#pragma once

#include "NetMessage.h"

class PositionUpdateMessage : public NetMessage
{
public:
	PositionUpdateMessage();

	void AsServer(sockaddr_in aSocket, int aLength)	override;
	void AsClient(sockaddr_in aSocket, int aLength) override;

	void SetGameObjectID(const int aGameObjectID);
	void SetPosition(const Tga2D::Vector2f& aPos);


private:
	void UpdatePos();

	Tga2D::Vector2f GetPosition() const;
	int GetGameObjectID() const;
};