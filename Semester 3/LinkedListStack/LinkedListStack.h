#ifndef LLS_LINKEDLISTSTACK
#define LLS_LINKEDLISTSTACK
#include <memory>

// Write a linked list stack using: templates and smartpointers(and therefor RAII)
// must allow to: 
// 
// [x] push items on the stack
// [x] pop items off the stack
//

namespace LLS
{
	template<typename T>
	class LinkedListStack final
	{
	public:
		LinkedListStack() {};

		inline void push_back(const T& value)
		{
			// make a new object holding the value
			auto temp = std::make_unique<StackElement>();
			temp->value = value;

			// if there is something at the top of the stack
			if (m_pTopStackElement.get())
			{
				// Let the previous top point to the new top
				temp->pNextStackElement = std::move(m_pTopStackElement);
				// move as top
				m_pTopStackElement = std::move(temp);
				return;
			}
			m_pTopStackElement = std::move(temp);
		}

		inline void pop_back()
		{
			auto temp = std::move(m_pTopStackElement);
			m_pTopStackElement = std::move(temp->pNextStackElement);
		}

		inline const T& GetTop() const
		{
			if (!m_pTopStackElement.get())
			{
				throw std::out_of_range;
			}
			return m_pTopStackElement.get().value;
		}

	private:
		struct StackElement final
		{
			T value;
			std::unique_ptr<StackElement> pNextStackElement;
		};
		std::unique_ptr<StackElement> m_pTopStackElement;
	};
}

#endif