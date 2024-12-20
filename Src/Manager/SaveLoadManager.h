#pragma once
#include <string>
#include <memory>
class Player;
class Stage;
class SaveLoadManager
{
public:
	// ファイル名
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