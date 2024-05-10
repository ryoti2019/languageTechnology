#pragma once
#include <string>
#include <memory>
class Player;
class SaveLoadManager
{
public:
	// ƒtƒ@ƒCƒ‹–¼
	static const std::string FILE_NAME;
	SaveLoadManager(void);
	~SaveLoadManager(void);
	void Update(void);
	void Load(void);
	void Save(void);
	void SetPlayer(std::shared_ptr<Player> player);
private:

	std::shared_ptr<Player> player_ = nullptr;

	//std::vector<std::shared_ptr<Player>> players_;


};