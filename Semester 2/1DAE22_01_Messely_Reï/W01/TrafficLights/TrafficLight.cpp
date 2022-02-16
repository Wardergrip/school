#include "pch.h"
#include "TrafficLight.h"
#include "utils.h"

using namespace utils;

TrafficLight::TrafficLight(const Point2f& pos)
	:m_State(State::off)
	,m_Position(pos)
	,m_AccumulatedSec(0)
	,m_Rect(pos.x,pos.y,60,160)
{
	m_pLights.push_back(new Circlef{m_Rect.left + m_Rect.width / 2, m_Rect.bottom + m_Rect.height * 0.8f,m_Rect.width * 0.30f});
	m_pLights.push_back(new Circlef{ m_Rect.left + m_Rect.width / 2, m_Rect.bottom + m_Rect.height * 0.5f,m_Rect.width * 0.30f });
	m_pLights.push_back(new Circlef{ m_Rect.left + m_Rect.width / 2, m_Rect.bottom + m_Rect.height * 0.2f,m_Rect.width * 0.30f });
}

TrafficLight::~TrafficLight()
{
	for (Circlef* c : m_pLights)
	{
		delete c;
		c = nullptr;
	}
	m_pLights.clear();
}

void TrafficLight::DoHitTest(const Point2f& point)
{
	bool isInCircle{false};
	for (int i{ 0 }; i < m_pLights.size(); ++i)
	{
		if (IsPointInCircle(point, Circlef{ m_pLights[i]->center,m_pLights[i]->radius }))
		{
			m_AccumulatedSec = 0;
			switch (i)
			{
			case 2:
				m_State = State::green;
				break;
			case 1:
				m_State = State::orange;
				break;
			case 0:
				m_State = State::red;
				break;
			}
			isInCircle = true;
		}
	}
	if (!isInCircle)
	{
		if (IsPointInRect(point, m_Rect))
		{
			m_State = State::off;
		}
	}
}

void TrafficLight::Draw() const
{
	SetColor(Color4f{0,0,0,1});
	FillRect(m_Rect);
	for (int i{0}; i < m_pLights.size(); ++i)
	{
		SetColor(Color4f{ 0.5f,0.5f,0.5f,1 });
		switch (m_State)
		{
		case TrafficLight::State::green:
			if (i == 2) SetColor(Color4f{ 0,1,0,1 });
			break;
		case TrafficLight::State::orange:
			if (i == 1) SetColor(Color4f{ 1,0.5f,0,1 });
			break;
		case TrafficLight::State::red:
			if (i == 0) SetColor(Color4f{ 1,0,0,1 });
			break;
		case TrafficLight::State::off:
			break;
		}
		FillEllipse(m_pLights[i]->center, m_pLights[i]->radius, m_pLights[i]->radius);
	}
}

void TrafficLight::Update(float elapsedSec)
{
	m_AccumulatedSec += elapsedSec;
	switch (m_State)
	{
	case TrafficLight::State::green:
		if (m_AccumulatedSec >= 4) 
		{
			m_AccumulatedSec = 0;
			m_State = State::orange;
		}
		break;
	case TrafficLight::State::orange:
		if (m_AccumulatedSec >= 1)
		{
			m_AccumulatedSec = 0;
			m_State = State::red;
		}
		break;
	case TrafficLight::State::red:
		if (m_AccumulatedSec >= 4)
		{
			m_AccumulatedSec = 0;
			m_State = State::green;
		}
		break;
	case TrafficLight::State::off:
		break;
	}
}

float TrafficLight::GetWidth()
{
	return 0.0f;
}

float TrafficLight::GetHeight()
{
	return 0.0f;
}
