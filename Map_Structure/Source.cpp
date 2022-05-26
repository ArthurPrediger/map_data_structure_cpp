#include "UnorderedMap.h"

int main()
{
	UnorderedMap<float, std::string> map{};

	map.insert(1.0f, "F");
	map.insert(1.0f, "A");
	map.insert(2.0f, "B");

	std::cout << map << std::endl;
	std::cout << map.erase(2.0f) << std::endl;
	std::cout << map << std::endl;
	std::cout << std::boolalpha << map.empty() << std::endl;
	std::cout << map.size() << std::endl;
	std::cout << std::boolalpha << map.containsKey(1.0f) << std::endl;
	std::cout << std::boolalpha << map.containsKey(2.0f) << std::endl;
	std::cout << std::boolalpha << map.containsValue("B") << std::endl;
	map.insert(2.0f, "B");
	std::cout << std::boolalpha << map.containsKey(2.0f) << std::endl;
	std::cout << std::boolalpha << map.containsValue("B") << std::endl;

	return 1;
}