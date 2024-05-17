#pragma once
#include <memory>
#include <vector>

class Transform;

class UnityStage
{
public:
	UnityStage(void);
	~UnityStage(void);
	void Update(void);
	void Draw(void);
	void Load(void);
private:

	std::vector <std::unique_ptr<Transform>> transform_;

};

