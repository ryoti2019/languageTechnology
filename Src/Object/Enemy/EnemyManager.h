#pragma once
#include <vector>
class Enemy;

class EnemyManager
{
public:
	
	void Load(void);

	void Draw(void);

private:

	std::vector<std::shared_ptr<Enemy>> enemys_;

	int i_ = 0;

};

