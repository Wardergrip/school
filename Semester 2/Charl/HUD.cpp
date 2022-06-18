#include "pch.h"
#include "HUD.h"

#include "UserInterfaceElement.h"

// STATICS

std::vector<std::pair<HUD::HUDName, UserInterfaceElement*>> HUD::c_UIQueue{16};

void HUD::QueueUI(const std::pair<HUDName, UserInterfaceElement*>& pair)
{
	c_UIQueue.push_back(pair);
}

void HUD::SwapQueueIdx(int a, int b)
{
	auto temp = c_UIQueue.at(a);
	c_UIQueue.at(a) = c_UIQueue.at(b);
	c_UIQueue.at(b) = temp;
}


// NON STATICS
HUD::HUD(HUDName name, bool readQueue)
	:m_Name{name}
{
	if (readQueue)
	{
		for (size_t i{ 0 }; i < c_UIQueue.size(); ++i)
		{
			if (c_UIQueue[i].first == m_Name)
			{
				m_pUserInterfaceElements.push_back(c_UIQueue[i].second);
				SwapQueueIdx(i, c_UIQueue.size());
				c_UIQueue.pop_back();
			}
		}
	}
}

HUD::~HUD()
{
	for (size_t i{ 0 }; i < m_pUserInterfaceElements.size(); ++i)
	{
		delete m_pUserInterfaceElements[i];
		m_pUserInterfaceElements[i] = nullptr;
	}
}

void HUD::DrawAll() const
{
	for (size_t i{ 0 }; i < m_pUserInterfaceElements.size(); ++i)
	{
		m_pUserInterfaceElements[i]->Draw();
	}
}

void HUD::Pushback(UserInterfaceElement* newElement)
{
	if (newElement == nullptr)
	{
		return;
	}
	m_pUserInterfaceElements.push_back(newElement);
}
