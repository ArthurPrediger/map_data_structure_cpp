#pragma once

#include "Map_ADT.h"
#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <memory>
#include <exception>

template <class Key, class T>
class UnorderedMap : public Map_ADT<Key, T>
{
public:
	UnorderedMap(size_t numBuckets = 20)
		:
		bucket_count(numBuckets)
	{
		keys = std::make_unique<std::vector<Key>[]>(bucket_count);
		values = std::make_unique<std::vector<T>[]>(bucket_count);
	};
	bool empty() const override
	{
		return size_ == 0;
	};
	size_t size() const override
	{
		return size_;
	};
	bool containsKey(const Key& key) const override
	{
		auto hash = std::hash<Key>{}(key);
		size_t pos = hash % bucket_count;

		for (auto i = keys[pos].begin(); i != keys[pos].end(); i++)
		{
			if (hash == std::hash<Key>{}(*i))
			{
				return true;
			}
		}

		return false;
	};
	bool containsValue(const T& value) const override
	{
		for (size_t i = 0; i < bucket_count; i++)
		{
			auto bucket = values[i];
			for (const auto& value_in : bucket)
			{
				if (value == value_in)
				{
					return true;
				}
			}
		}

		return false;
	};
	std::optional<T> erase(const Key& key) override
	{
		if (!containsKey(key))
		{
			throw std::runtime_error("Map does not contain specified erasable key!");
		}
		
		auto hash = std::hash<Key>{}(key);
		size_t pos = hash % bucket_count;

		auto valueIt = values[pos].begin();
		for (auto i = keys[pos].begin(); i != keys[pos].end(); i++, valueIt++)
		{
			if (hash == std::hash<Key>{}(*i))
			{
				keys[pos].erase(i);
				auto erased_value = *valueIt;
				values[pos].erase(valueIt);
				size_--;
				return erased_value;
			}
		}

		return {};
	};
	void insert(const Key& key, const T& value) override
	{
		if (containsKey(key))
		{
			auto hash = std::hash<Key>{}(key);
			size_t pos = hash % bucket_count;
			
			auto valueIt = values[pos].begin();
			for (auto i = keys[pos].begin(); i != keys[pos].end(); i++, valueIt++)
			{
				if (hash == std::hash<Key>{}(*i))
				{
					*valueIt = value;
					break;
				}
			}
		}
		else
		{
			auto hash = std::hash<Key>{}(key);
			size_t pos = hash % bucket_count;

			keys[pos].push_back(key);
			values[pos].push_back(value);
			size_++;
		}
	};
	friend std::ostream& operator<<(std::ostream& out, const UnorderedMap<Key, T>& map)
	{
		if (map.empty())
			return out << "[empty]";

		out << "[";
		size_t numElements = 0;
		for (int i = 0; i < map.bucket_count && numElements != map.size(); i++)
		{
			for (int j = 0; j < map.keys[i].size(); j++)
			{
				if (++numElements == map.size())
				{
					out << map.keys[i][j] << "=" << map.values[i][j] << "]";
				}
				else
				{
					out << map.keys[i][j] << "=" << map.values[i][j] << ", ";
				}
			}
		}
		return out;
	}

private:
	size_t bucket_count;
	size_t size_ = 0;
	std::unique_ptr<std::vector<Key>[]> keys;
	std::unique_ptr<std::vector<T>[]> values;
};

