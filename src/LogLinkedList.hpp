#ifndef LOG_LINKED_LIST_HPP
#define LOG_LINKED_LIST_HPP

#include <memory>

//for debugging (print)
#include <string>
#include <vector>
#include <iostream>
#include <sstream>

template <typename T>
class LogLinkedList;

template <typename T>
class LogLinkedListBase
{
protected:
	int size;
	int log_size;
	T t;

	std::shared_ptr<LogLinkedListBase<T>> lower_half;
	std::shared_ptr<LogLinkedListBase<T>> upper_half;

public:
	LogLinkedListBase() : size(0), log_size(1)
	{
		t = T();
		lower_half = std::shared_ptr<LogLinkedListBase<T>>(nullptr);
		upper_half = std::shared_ptr<LogLinkedListBase<T>>(nullptr);
	}

	std::vector<std::string> print();
	std::shared_ptr<LogLinkedListBase<T>> append(T const&);
	bool remove(int const& = -1);

	T& operator[](int const&);

	friend LogLinkedList<T>;
};

template <typename T>
std::vector<std::string> LogLinkedListBase<T>::print()
{
	int i = 0;
	int j = 0;
	int k = 0;
	int l = 0;
	size_t pos;
	std::string str_l;
	std::string str_u;
	std::vector<std::string> v;
	std::stringstream str;

	std::vector<std::string> lower;
	std::vector<std::string> upper;
       	if(lower_half)lower = lower_half->print();
       	if(upper_half)upper = upper_half->print();

	i = 0;
	j = 0;
	while(i < lower.size())
	{
		if(lower[i].length() > j)j = lower[i].length();
		++i;
	}

	i = 0;
	k = 0;
	while(i < upper.size())
	{
		if(upper[i].length() > k)k = upper[i].length();
		++i;
	}

	i = lower.size() - 1;
	while(i > -1 and i >= upper.size())
	{
		str_l = lower[i];
		pos = str_l.find("\n");
		if(pos != std::string::npos)str_l = str_l.substr(0, pos);
		for(l = str_l.length(); l < j; ++l)str_l += " ";

		str_u = "";
		pos = str_u.find("\n");
		if(pos != std::string::npos)str_u = str_u.substr(0, pos);
		for(l = str_u.length(); l < k; ++l)str_u += " ";

		v.push_back(str_l + str_u + "\n");
		--i;
	}

	while(i > -1)
	{
		str_l = lower[i];
		pos = str_l.find("\n");
		if(pos != std::string::npos)str_l = str_l.substr(0, pos);
		for(l = str_l.length(); l < j; ++l)str_l += " ";

		str_u = upper[i];
		pos = str_u.find("\n");
		if(pos != std::string::npos)str_u = str_u.substr(0, pos);
		for(l = str_u.length(); l < k; ++l)str_u += " ";

		v.push_back(str_l + str_u + "\n");
		--i;
	}

	str << " " << t << " ";
	str_l = str.str();
	l = (j + k - str_l.length()) / 2;

	for(i = 0; i < l; ++i)str_l = " " + str_l;
	for(i = 0; i < l; ++i)str_l = str_l + " ";
	str_l += "\n";
	v.push_back(str_l);

	return v;
}

template <typename T>
std::shared_ptr<LogLinkedListBase<T>> LogLinkedListBase<T>::append(T const& _t)
{
	if(size < (1 << log_size) - 2)
	{
		upper_half = upper_half->append(_t);
		++size;
		return std::make_shared<LogLinkedListBase<T>>(*this);
	}
	if(size == (1 << log_size) - 2)
	{
		t = _t;
		++size;
		return std::make_shared<LogLinkedListBase<T>>(*this);
	}

	std::shared_ptr<LogLinkedListBase<T>> base = std::make_shared<LogLinkedListBase<T>>();
	base->size		= size;
	base->log_size		= log_size + 1;
	base->lower_half	= std::make_shared<LogLinkedListBase<T>>(*this);
	base->upper_half	= std::make_shared<LogLinkedListBase<T>>();
	base->append(_t);

	return base;
}

template <typename T>
T& LogLinkedListBase<T>::operator[](int const& _i)
{
	if(_i > size)
	{
		std::cout << "bad index, return last element" << std::endl;
		return t;
	}

	if(_i < ((1 << (log_size - 1)) - 1))return lower_half->operator[](_i);
	if(_i < ((1 << log_size) - 2))return upper_half->operator[](_i - (1 << (log_size - 1) - 1));

	return t;
}

template <typename T>
class LogLinkedList
{
protected:
	std::shared_ptr<LogLinkedListBase<T>> base;

public:
	LogLinkedList()
	{
		base = std::make_shared<LogLinkedListBase<T>>();
	}

	int size(){return base->size;}
	int log_size(){return base->log_size;}
	T& operator[](int const& _i){return base->operator[](_i);}

	void print();
	void append(T const&);
	void remove(int const& = -1);
};

template <typename T>
void LogLinkedList<T>::append(T const& _t)
{
	base = base->append(_t);
}

template <typename T>
void LogLinkedList<T>::print()
{
	std::vector<std::string> v = base->print();
	for(int i = v.size(); i > -1; --i)
	{
		std::cout << v[i];
	}
}

#endif
