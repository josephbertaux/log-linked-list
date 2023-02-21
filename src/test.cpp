#include <memory>
#include <string>
#include <iostream>

template <typename T>
class A
{
public:
	T t;

	A(T const& _t) : t(_t) {}

	virtual void foo(){std::cout << "Hello from A" << std::endl;}
};

template <typename T>
class B : public A<T>
{
public:
	using A<T>::t;
	//using A<T>::A
	//We don't want to inherit A's constructors
	//that is, we just a B constuctor with a shared pointer to an A
	//we don't want there to be a B constructor with a T

	std::shared_ptr<A<T>> ptr;

	//However, A has no default constructor
	//So we must manually specify which of A's
	//constructors we inherit from in each of B's constructors
	B(std::shared_ptr<A<T>> const& _ptr) :
		A<T>::A(_ptr->t),
		ptr(_ptr)
	{
		//Do nothing
	}

	void foo() override {std::cout << "Hello from B" << std::endl;}
};

int main()
{
	std::shared_ptr<A<int>> my_A_ptr = std::make_shared<A<int>>(7);
	std::shared_ptr<A<int>> my_B_ptr = std::make_shared<B<int>>(my_A_ptr);
	//std::shared_ptr<A<int>> my_B_ptr = std::make_shared<B<int>>(8);
	//A<int>* my_B_ptr = new B<int>(my_A_ptr);

	std::cout << "here" << std::endl;
	std::cout << my_B_ptr->t << std::endl;
	std::cout << std::hex << std::static_pointer_cast<B<int>>(my_B_ptr)->ptr << std::endl;
	std::cout << std::hex << my_A_ptr << std::endl;

	return 0;
}
