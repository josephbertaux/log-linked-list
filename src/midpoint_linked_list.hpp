#ifndef MIDPOINT_LINKED_LIST_HPP
#define MIDPOINT_LINKED_LIST_HPP

//////////////////////////////////////////
//	"midpoint linked list"		//
//					//
//	A doubly linked list		//
//	But with a midpoint field	//
//	For log time access		//
//////////////////////////////////////////

#include <memory>
#include <iostream>

template <typename T>
class midpoint_linked_list
{
public:
//Doubly linked list
	class doubly_linked_node
	{
	public:
		T t;

		std::shared_ptr<doubly_linked_node> prev;
		std::shared_ptr<doubly_linked_node> next;

		doubly_linked_node()
		{
			t = T();

			prev = nullptr;
			next = nullptr;
		}
	};
protected:
//Midpoint linked list fields
	int end_pos;
	int mid_pos;

	std::shared_ptr<doubly_linked_node> top_pt;
	std::shared_ptr<doubly_linked_node> mid_pt;
	std::shared_ptr<doubly_linked_node> end_pt;

	std::shared_ptr<midpoint_linked_list<T>> lower;
	std::shared_ptr<midpoint_linked_list<T>> upper;

	void inc_top();
	void dec_top();

	void inc_end();
	void dec_end();

public:
	midpoint_linked_list();
	~midpoint_linked_list();

	int size(){return end_pos;}
	int half(){return mid_pos;}

	std::shared_ptr<doubly_linked_node> begin(){return top_pt;}

	T& operator[](int);

	void append(T const&, int const&);
	void append(T const& _t){append(_t, end_pos);}
	void remove();
};

template <typename T>
midpoint_linked_list<T>::midpoint_linked_list()
{
	end_pos = 0;
	mid_pos = 0;

	top_pt = nullptr;
	mid_pt = nullptr;
	end_pt = nullptr;

	lower = nullptr;
	upper = nullptr;
}

template <typename T>
midpoint_linked_list<T>::~midpoint_linked_list<T>()
{
	//
}

template <typename T>
void midpoint_linked_list<T>::inc_top()
{
	if(!mid_pt)
	{
		std::cout << "Bad case in inc_top" << std::endl;
	}

	if(!(lower and upper))
	{
		end_pos = 1;
		mid_pos = 0;

		top_pt = mid_pt;
		mid_pt = nullptr;

		return;
	}

	if(lower->mid_pt and upper->mid_pt)
	{
		top_pt = top_pt->next;
		lower->inc_top();
		--end_pos;
		--mid_pos;

		if(mid_pos < end_pos / 2)
		{
			mid_pt = mid_pt->next;
			++mid_pos;

			lower->inc_end();
			upper->inc_top();
		}

		return;
	}

	end_pos = 2;
	mid_pos = 1;

	if(upper->mid_pt)
	{
		top_pt = upper->top_pt;
		mid_pt = upper->mid_pt;
		end_pt = upper->end_pt;
	}

	if(lower->mid_pt)
	{
		top_pt = lower->mid_pt;
		mid_pt = upper->top_pt;
		end_pt = upper->end_pt;
	}

	lower = nullptr;
	upper = nullptr;
}

template <typename T>
void midpoint_linked_list<T>::dec_top()
{
	if(!mid_pt)
	{
		end_pos = 2;
		mid_pos = 1;

		top_pt = top_pt->prev;
		mid_pt = end_pt->prev;

		return;
	}

	if(!(lower and upper))
	{
		top_pt = top_pt->prev;
		mid_pt = mid_pt->prev;

		end_pos = 3;
		mid_pos = 1;

		lower = std::make_shared<midpoint_linked_list<T>>();
		upper = std::make_shared<midpoint_linked_list<T>>();

		lower->end_pos = 1;
		lower->mid_pos = 0;
		lower->top_pt = top_pt;
		lower->end_pt = mid_pt;

		upper->end_pos = 2;
		upper->mid_pos = 1;
		upper->top_pt = mid_pt;
		upper->mid_pt = end_pt->prev;
		upper->end_pt = end_pt;

		return;
	}

	top_pt = top_pt->prev;
	lower->dec_top();
	++end_pos;
	++mid_pos;

	if(mid_pos > end_pos / 2)
	{
		mid_pt = mid_pt->prev;
		--mid_pos;

		upper->dec_top();
		lower->dec_end();
	}
}

template <typename T>
void midpoint_linked_list<T>::inc_end()
{
	if(!mid_pt)
	{
		end_pos = 2;
		mid_pos = 1;

		mid_pt = top_pt->next;
		end_pt = end_pt->next;

		return;
	}

	if(!(lower and upper))
	{
		end_pt = end_pt->next;

		end_pos = 3;
		mid_pos = 1;

		lower = std::make_shared<midpoint_linked_list<T>>();
		upper = std::make_shared<midpoint_linked_list<T>>();

		lower->end_pos = 1;
		lower->mid_pos = 0;
		lower->top_pt = top_pt;
		lower->end_pt = mid_pt;

		upper->end_pos = 2;
		upper->mid_pos = 1;
		upper->top_pt = mid_pt;
		upper->mid_pt = end_pt->prev;
		upper->end_pt = end_pt;

		return;
	}

	end_pt = end_pt->next;
	upper->inc_end();
	++end_pos;

	if(mid_pos < end_pos / 2)
	{
		mid_pt = mid_pt->next;
		++mid_pos;

		lower->inc_end();
		upper->inc_top();
	}
}

template <typename T>
void midpoint_linked_list<T>::dec_end()
{
	if(!mid_pt)
	{
		std::cout << "Bad case in dec_end" << std::endl;
	}

	if(!(lower and upper))
	{
		end_pos = 1;
		mid_pos = 0;

		end_pt = mid_pt;
		mid_pt = nullptr;

		return;
	}

	if(lower->mid_pt and upper->mid_pt)
	{
		end_pt = end_pt->prev;
		upper->dec_end();
		--end_pos;

		if(mid_pos > end_pos / 2)
		{
			mid_pt = mid_pt->prev;
			--mid_pos;

			upper->dec_top();
			lower->dec_end();
		}

		return;
	}

	end_pos = 2;
	mid_pos = 1;

	if(upper->mid_pt)
	{
		top_pt = lower->top_pt;
		mid_pt = upper->top_pt;
		end_pt = upper->mid_pt;
	}

	if(lower->mid_pt)
	{
		top_pt = lower->top_pt;
		mid_pt = lower->mid_pt;
		end_pt = lower->end_pt;
	}

	lower = nullptr;
	upper = nullptr;
}

template <typename T>
T& midpoint_linked_list<T>::operator[](int _i)
{
	if(_i == 0) return top_pt->t;
	if(_i == mid_pos)return mid_pt->t;
	if(_i < mid_pos)return lower->operator[](_i);
	if(_i < end_pos)return upper->operator[](_i - mid_pos);

	//throw exception
	std::cout << "bad case in operator[]" << std::endl;

	return end_pt->t;
}

template <typename T>
void midpoint_linked_list<T>::append(T const& _t, int const& _i)
{
	if(lower and upper)
	{
		if(_i < mid_pos)
		{
			lower->append(_t, _i);
			++mid_pos;
		}
		else
		{
			upper->append(_t, _i - mid_pos);
		}
		++end_pos;

		if(mid_pos < end_pos / 2)
		{
			mid_pt = mid_pt->next;
			++mid_pos;

			lower->inc_end();
			upper->inc_top();
		}

		if(mid_pos > end_pos / 2)
		{
			mid_pt = mid_pt->prev;
			--mid_pos;

			upper->dec_top();
			lower->dec_end();
		}
		return;
	}

	if(mid_pt)
	{
		end_pos = 3;
		mid_pos = 1;

		lower = std::make_shared<midpoint_linked_list<T>>();
		upper = std::make_shared<midpoint_linked_list<T>>();

		std::shared_ptr<doubly_linked_node> new_pt = std::make_shared<doubly_linked_node>();

		new_pt->t = _t;
		mid_pt->next = new_pt;
		new_pt->prev = mid_pt;
		new_pt->next = end_pt;
		end_pt->prev = new_pt;

		if(_i == 0)
		{
			new_pt->t = mid_pt->t;
			mid_pt->t = top_pt->t;
			top_pt->t = _t;
		}

		if(_i == 1)
		{
			new_pt->t = mid_pt->t;
			mid_pt->t = _t;
		}

		lower->end_pos = 1;
		lower->mid_pos = 0;
		lower->top_pt = top_pt;
		lower->end_pt = mid_pt;

		upper->end_pos = 2;
		upper->mid_pos = 1;
		upper->top_pt = mid_pt;
		upper->mid_pt = new_pt;
		upper->end_pt = end_pt;

		return;
	}

	if(top_pt and end_pt)
	{
		end_pos = 2;
		mid_pos = 1;

		mid_pt = std::make_shared<doubly_linked_node>();

		mid_pt->t = _t;
		top_pt->next = mid_pt;
		mid_pt->prev = top_pt;
		mid_pt->next = end_pt;
		end_pt->prev = mid_pt;

		if(_i == 0)
		{
			mid_pt->t = top_pt->t;
			top_pt->t = _t;
		}

		return;
	}

	top_pt = std::make_shared<doubly_linked_node>();
	end_pt = std::make_shared<doubly_linked_node>();

	end_pos = 1;
	mid_pos = 0;

	top_pt->next = end_pt;
	end_pt->prev = top_pt;

	top_pt->t = _t;

	return;
}

#endif
