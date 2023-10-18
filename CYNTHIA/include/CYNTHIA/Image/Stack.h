//
// Created by Samer Ali on 10/18/23.
//

#pragma once

#include <vector>

namespace Cynthia
{
	template < typename T >
	class Stack
	{
	public:
		void push(T element)
		{
			stack.emplace_back(element);
		}
		T pop()
		{
			stack.pop_back();
		}

	private:
		std::vector<T> stack;
	};
}



