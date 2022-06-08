#include "UnorderedMap.h"

class Foo
{
public:
	Foo(int x, int y)
		:
		x(x),
		y(y)
	{}
	bool operator ==(const Foo& rhs) const
	{
		if ((x == rhs.x) && (y == rhs.y))
		{
			return true;
		}
		return false;
	}
	friend std::ostream& operator<<(std::ostream& out, const Foo& foo)
	{
		return out << "(" << foo.x << "," << foo.y << ")";
	}
public:
	int x;
	int y;
};

namespace std 
{
	template <> class  hash<Foo>
	{
		public:
		size_t operator()(const Foo& foo) const
		{
			hash<int> hasher;
			auto hashx = hasher(foo.x);
			auto hashy = hasher(foo.y);
			
			hashx ^= hashy + 0x9e3779b9 + (hashx << 6) + (hashx >> 2);
			return  hashx;
		}

		//size_t operator()(const Foo& foo) const
		//{
		//	hash<int> hasher;
		//	auto hashx = hasher(foo.x);
		//	auto hashy = hasher(foo.y);
		//
		//	return  hashx + hashy;
		//}
	};
}

int main()
{
	try
	{
		UnorderedMap<std::string, Foo> map{40};

		map.insert("A", { 1, 4 });
		map.insert("A", { 2, 5 });
		map.insert("B", { 3, 6 });

		std::cout << map << std::endl;
		std::cout << map.erase("C").has_value() << std::endl;
		std::cout << map << std::endl;
		std::cout << std::boolalpha << map.empty() << std::endl;
		std::cout << map.size() << std::endl;
		std::cout << std::boolalpha << map.containsKey("A") << std::endl;
		std::cout << std::boolalpha << map.containsKey("B") << std::endl;
		std::cout << std::boolalpha << map.containsValue({ 3, 6 }) << std::endl;
		map.insert("B", { 3, 6 });
		std::cout << std::boolalpha << map.containsKey("B") << std::endl;
		std::cout << std::boolalpha << map.containsValue({ 3, 6 }) << std::endl;

		std::cout << "\n";

		UnorderedMap<Foo, int> map1{30};

		map1.insert({ 1, 4 }, 1);
		map1.insert({ 2, 5 }, 2);
		map1.insert({ 3, 7 }, 3);

		//for (int i = 0; i < 1000; i++)
		//{
		//	map1.insert({ i, i * 2 }, i);
		//}

		std::cout << map1 << std::endl;
		std::cout << map1.erase({ 2, 5 }).value() << std::endl;
		std::cout << map1 << std::endl;
		std::cout << std::boolalpha << map1.empty() << std::endl;
		std::cout << map1.size() << std::endl;
		std::cout << std::boolalpha << map1.containsKey({ 3, 6 }) << std::endl;
		std::cout << std::boolalpha << map1.containsKey({ 2, 5 }) << std::endl;
		std::cout << std::boolalpha << map1.containsValue(2) << std::endl;
		map1.insert({ 2, 5 }, 2);
		std::cout << std::boolalpha << map1.containsKey({ 2, 5 }) << std::endl;
		std::cout << std::boolalpha << map1.containsValue(2) << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
	}

	return 1;
}