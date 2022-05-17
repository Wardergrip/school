#pragma once
#include "GameObject.h"
class Texture;
class Level;
class Player;
class KoopaBase : public GameObject
{
public:
	enum class Color{red,green,gray};
	enum class Type{shell,shelled,naked};

	static void InitLevelRef(Level* pLevelRef);

	explicit KoopaBase(Color col = Color::green, Type type = Type::shelled);
	KoopaBase(const KoopaBase& k) = delete;
	KoopaBase& operator=(const KoopaBase& k) = delete;
	KoopaBase(KoopaBase&& k) = delete;
	KoopaBase& operator=(KoopaBase&& k) = delete;
	virtual ~KoopaBase();

	virtual void Draw() const;
	virtual void Update(float elapsedSec, Player* player);
	virtual void UpdateMovement(float elapsedSec);


	void SetPosition(const Point2f& pos);
	void SetVelocity(const Vector2f& vel);

	static bool SwitchHitBoxDraw();

	// Get the positional Rect of the koopa
	Rectf GetRect() const;
	Rectf GetTopHitbox() const;
	Rectf GetSidesHitbox() const;
	Type GetType() const;

protected:
	static Texture* m_pKoopaTexture;
	static unsigned int m_Instances;
	static Level* m_pLevelRef;
	static bool m_DrawHitBoxes;
	Color m_Color;
	Type m_Type;

	Point2f m_Position;
	Vector2f m_Velocity;

	void DrawHitboxes() const;
};

