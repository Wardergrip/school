#pragma once
#include "Vector2f.h"
#include "Matrix2x3.h"
#include <vector>
class Texture;

class Diamond
{
public:
	Diamond(const Point2f& startingPos = {});
	~Diamond();

	void Draw() const;
	void Update(float elapsedSec);

	void SwitchSelect();
	void SetSelect(bool state);

	void AddTranslation(const Vector2f& translation);
	void AddRotation(float angle);
	void AddScale(float scale);

	void ResetTransformation();

	bool IsInside(const Point2f& pos) const;
	bool IsSelected() const;

private:
	static Texture* m_pDiamondTexture;
	static unsigned int m_Instances;

	bool m_IsSelected;
	Vector2f m_Translation;
	float m_Angle;
	float m_Scale;
	std::vector<Point2f> m_Vertices;
	std::vector<Point2f> m_TransVertices;

	Matrix2x3 m_CurrentMatrix;
	Matrix2x3 m_LastMatrix;
};