#pragma once
class Texture;
class ButtonBase
{
public:
	ButtonBase(Texture* pTexture = nullptr);
	~ButtonBase();

	void Draw() const;

	void SetRect(const Rectf& rect);
	void SetTexture(Texture* pTexture);
	void SetBL(const Point2f& bottomLeft);

	void CenterTo(const Point2f& center);

	Point2f GetCenter() const;
	bool IsInside(const Point2f& pos) const;

	void CenterRect(const Point2f& p = {});
	Point2f RectToBL() const;
	Point2f CenterOf() const;
	void AdjustRectToTexture(float borderScale = 1);

	// ---- STATICS ----


	// Centers the rect on p
	static void CenterRect(Rectf& r, const Point2f& p = {});
	// Make sure your text fits in the Rectf nicely
	static Point2f Rect_to_BL(const Rectf& r);
	// Returns the center of the obj
	static Point2f Center_of(const Rectf& r);
	// Adjust Rect so that it's dimensions are same as the texture
	static void AdjustRect_to_Texture(Rectf& r, const Texture* t, float borderScale = 1);

protected:
	Texture* m_pTexture;
	Rectf m_Button;
};

