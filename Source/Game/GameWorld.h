#pragma once

namespace CommonUtilities
{
	class InputHandler;
}
namespace CU = CommonUtilities;


enum class NetworkType
{
	Client,
	Server
};

class Client;
class Server;

class CGameWorld
{
public:
	CGameWorld(); 
	~CGameWorld();

	void Init();
	void Update(CU::InputHandler& anInput, const float aDeltaTime);
	void Render();

	void SetNetworkType(const NetworkType aType);

	static NetworkType GetNetType();

private:
	inline static NetworkType myType;
};