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
			return hasher(foo.x) + hasher(foo.y);
		}
	};
}

int main()
{
	try
	{
		UnorderedMap<std::string, Foo> map{};

		map.insert("A", { 1, 4 });
		map.insert("A", { 2, 5 });
		map.insert("B", { 3, 6 });

		std::cout << map << std::endl;
		std::cout << map.erase("B").value() << std::endl;
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

		UnorderedMap<Foo, int> map1{};

		map1.insert({ 1, 4 }, 1);
		map1.insert({ 2, 5 }, 2);
		map1.insert({ 3, 6 }, 3);

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

		Foo f1 = { 1, 2 };
		Foo f2 = { 1, 2 };
		Foo f3 = { 1, 3 };

		if (f1 == f2)
		{
			return true;
		}
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
	}

	return 1;
}