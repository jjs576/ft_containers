#include <iostream>

#include "list.hpp"
#include "stack.hpp"
#include "vector.hpp"
#include "map.hpp"
#include "queue.hpp"
#include "deque.hpp"
#include <type_traits>

int main()
{
	std::cout << __cplusplus << std::endl;
	ft::list<int> list1;
	ft::vector<int> vector1;
	ft::stack<int> stack1;
	ft::map<int, int> map1;
	ft::queue<int> queue1;
	ft::deque<int> deque1;

	return 0;
}
