#ifndef LOG_LINKED_LIST_HPP
#define LOG_LINKED_LIST_HPP

#include <memory>

#include <iostream>
#include <string>

template <typename T>
class log_linked_list
{
public:
	class node
	{
	public:
		std::shared_ptr<node> prev = nullptr;
		std::shared_ptr<node> next = nullptr;

		T t;

		node();
		node(T const&);
	};

	//base class for an empty list, containing a single end node
	class singlet
	{
	protected:
		std::shared_ptr<node> end_ptr = nullptr;

	public:
		virtual int size();
		virtual T& operator[](int const&);

		virtual void remove(int const&, std::shared_ptr<singlet>&);
		virtual void inc_top(std::shared_ptr<singlet>&);
		virtual void dec_end(std::shared_ptr<singlet>&);

		virtual void append(T const&, int const&, std::shared_ptr<singlet>&);
		virtual void dec_top(std::shared_ptr<singlet>&);
		virtual void inc_end(std::shared_ptr<singlet>&);

		singlet(std::shared_ptr<node> const&);
	};

	//class for a trivial list, containing an accessible node and an end node
	class doublet : public singlet
	{
	protected:
		using singlet::end_ptr;
		std::shared_ptr<node> top_ptr = nullptr;

	public:
		virtual int size() override;
		virtual T& operator[](int const&) override;

		virtual void remove(int const&, std::shared_ptr<singlet>&) override;
		virtual void inc_top(std::shared_ptr<singlet>&) override;
		virtual void dec_end(std::shared_ptr<singlet>&) override;

		virtual void append(T const&, int const&, std::shared_ptr<singlet>&) override;
		virtual void dec_top(std::shared_ptr<singlet>&) override;
		virtual void inc_end(std::shared_ptr<singlet>&) override;

		doublet(std::shared_ptr<node> const&, std::shared_ptr<node> const&);
	};

	//class for a general list, containing an midpoint node and recursive structure for logarthmic access
	class triplet : public virtual doublet
	{
	protected:
		using doublet::top_ptr;
		using doublet::end_ptr;
		std::shared_ptr<node> mid_ptr = nullptr;

		int mid_pos = 1;
		int end_pos = 2;

		std::shared_ptr<singlet> lower = nullptr;
		std::shared_ptr<singlet> upper = nullptr;

	public:
		int size() override;
		T& operator[](int const&) override;

		void remove(int const&, std::shared_ptr<singlet>&) override;
		void inc_top(std::shared_ptr<singlet>&) override;
		void dec_end(std::shared_ptr<singlet>&) override;

		void append(T const&, int const&, std::shared_ptr<singlet>&) override;
		void dec_top(std::shared_ptr<singlet>&) override;
		void inc_end(std::shared_ptr<singlet>&) override;

		triplet(std::shared_ptr<node> const&, std::shared_ptr<node> const&, std::shared_ptr<node> const&);
	};

	int size();
	T& operator[](int const&);

	void remove(int const&);
	void append(T const&, int const&);
	void append(T const&);

	log_linked_list();

protected:
	std::shared_ptr<singlet> ptr = nullptr;
};

#include "log_linked_list.tcc"

#endif
