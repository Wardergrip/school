#pragma once
#include <string>

class Texture;
class Timer;

class ProjectileManager;

class Ability
{
public:
	static void InitProjManager(ProjectileManager* projMan);
protected:
	static ProjectileManager* c_ProjectileManagerRef;
public:
	enum class Type
	{
		selfCast, enemyCast, skillshot
	};

	Ability(Type type, const std::string& key, const std::string& name = "Default name", float cooldown = 0);
	Ability(const Ability& ability) = delete;
	Ability& operator=(const Ability& ability) = delete;
	Ability(Ability&& ability) = delete;
	Ability& operator=(Ability&& ability) = delete;
	virtual ~Ability();

	virtual void Draw() const = 0;
	void DrawUI() const;

	virtual void OnPress(const Point2f& mousePos) = 0;
	virtual void OnHolding(float elapsedSec, const Point2f& mousePos) = 0;
	virtual void OnRelease(const Point2f& mousePos) = 0;

	virtual void Update(float elapsedSec) = 0;

protected:
	const Type m_Type;

	bool m_ShowTelegraph;

	std::string m_Name;
	Timer* m_Cooldown;

	Texture* m_pButtonKeyTexture;

	virtual void DrawIcon() const = 0;
};

