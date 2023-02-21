#ifndef LOG_LINKED_LIST_CPP
#define LOG_LINKED_LIST_CPP



//////////////////////////////////////////
//	node implementation		//	(Done)
//////////////////////////////////////////

template<typename T>
log_linked_list<T>::node::node() :
	prev(nullptr),
	next(nullptr)
{}

template<typename T>
log_linked_list<T>::node::node(T const& _t) :
	prev(nullptr),
	next(nullptr),
	t(_t)
{}



//////////////////////////////////////////
//	singlet implementation		//	(Done)
//////////////////////////////////////////

template<typename T>
log_linked_list<T>::singlet::singlet(std::shared_ptr<log_linked_list<T>::node> const& _end_ptr) :
	end_ptr(_end_ptr)
{}

template<typename T>
int log_linked_list<T>::singlet::size()
{
	return 0;
}

template<typename T>
T& log_linked_list<T>::singlet::operator[](int const& _i)
{
	return end_ptr->t;
}

template<typename T>
void log_linked_list<T>::singlet::remove(int const& _i, std::shared_ptr<log_linked_list<T>::singlet>& _ptr)
{
	//Do nothing
}

template<typename T>
void log_linked_list<T>::singlet::inc_top(std::shared_ptr<log_linked_list<T>::singlet>& _ptr)
{
	//Do nothing
	//this method should never be called
}

template<typename T>
void log_linked_list<T>::singlet::dec_end(std::shared_ptr<log_linked_list<T>::singlet>& _ptr)
{
	//Do nothing
	//this method should never be called
}

template<typename T>
void log_linked_list<T>::singlet::append(T const& _t, int const& _i, std::shared_ptr<log_linked_list<T>::singlet>& _ptr)
{
	std::shared_ptr<log_linked_list<T>::node> top_ptr = std::make_shared<log_linked_list<T>::node>(_t);
	top_ptr->next = end_ptr;
	end_ptr->prev = top_ptr;

	_ptr = std::make_shared<log_linked_list<T>::doublet>(top_ptr, end_ptr);
}

template<typename T>
void log_linked_list<T>::singlet::dec_top(std::shared_ptr<log_linked_list<T>::singlet>& _ptr)
{
	//Do nothing
	//this method should never be called
}

template<typename T>
void log_linked_list<T>::singlet::inc_end(std::shared_ptr<log_linked_list<T>::singlet>& _ptr)
{
	//Do nothing
	//this method should never be called
}



//////////////////////////////////////////
//	doublet implementation		//	(WIP)
//////////////////////////////////////////

template<typename T>
log_linked_list<T>::doublet::doublet(std::shared_ptr<log_linked_list<T>::node> const& _top_ptr, std::shared_ptr<log_linked_list<T>::node> const& _end_ptr) :
	log_linked_list<T>::singlet::singlet(_end_ptr),
	top_ptr(_top_ptr)
{}

template<typename T>
int log_linked_list<T>::doublet::size()
{
	return 1;
}

template<typename T>
T& log_linked_list<T>::doublet::operator[](int const& _i)
{
	return top_ptr->t;
}

template<typename T>
void log_linked_list<T>::doublet::remove(int const& _i, std::shared_ptr<log_linked_list<T>::singlet>& _ptr)
{
	//need to implement
}

template<typename T>
void log_linked_list<T>::doublet::inc_top(std::shared_ptr<log_linked_list<T>::singlet>& _ptr)
{
	//need to implement
}

template<typename T>
void log_linked_list<T>::doublet::dec_end(std::shared_ptr<log_linked_list<T>::singlet>& _ptr)
{
	//need to implement
}

template<typename T>
void log_linked_list<T>::doublet::append(T const& _t, int const& _i, std::shared_ptr<log_linked_list<T>::singlet>& _ptr)
{
	//need to implement
}

template<typename T>
void log_linked_list<T>::doublet::dec_top(std::shared_ptr<log_linked_list<T>::singlet>& _ptr)
{
	//need to implement
}

template<typename T>
void log_linked_list<T>::doublet::inc_end(std::shared_ptr<log_linked_list<T>::singlet>& _ptr)
{
	//need to implement
}

//////////////////////////////////////////
//	triplet implementation		//	(WIP)
//////////////////////////////////////////
//...



//////////////////////////////////////////
//	wrapper implementation		//	(Done)
//////////////////////////////////////////

template<typename T>
log_linked_list<T>::log_linked_list()
{
	std::shared_ptr<log_linked_list<T>::node> end_ptr = std::make_shared<log_linked_list<T>::node>();
	ptr = std::make_shared<log_linked_list<T>::singlet>(end_ptr);
}

template<typename T>
int log_linked_list<T>::size()
{
	return ptr->size();
}

template<typename T>
T& log_linked_list<T>::operator[](int const& _i)
{
	return ptr->operator[](_i);
}

template<typename T>
void log_linked_list<T>::remove(int const& _i)
{
	ptr->remove(_i, ptr);
}

template<typename T>
void log_linked_list<T>::append(T const& _t, int const& _i)
{
	ptr->append(_t, _i, ptr);
}

template<typename T>
void log_linked_list<T>::append(T const& _t)
{
	ptr->append(_t, ptr->size(), ptr);
}

#endif
