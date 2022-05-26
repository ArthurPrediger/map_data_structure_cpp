#pragma once

template <class Key, class T>
class Map_ADT
{
public:
	virtual bool empty() const = 0;
	virtual size_t size() const = 0;
	virtual bool containsKey(const Key& key) const = 0;
	virtual bool containsValue(const T& value) const = 0;
	virtual T erase(const Key& key) = 0;
	virtual void insert(const Key& key, const T& value) = 0;
};