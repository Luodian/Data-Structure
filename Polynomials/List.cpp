#include <iostream>
#include <fstream>
//可以相应的增加First(),End()方法，表示表头和表尾。

using namespace std;

template <typename Object>
class List
{
private:
	struct Node
	{
		Object data;
		Node *prev;
		Node *next;
		//引用了object的构造函数
		Node (const Object &d = Object(), Node *p = NULL,Node *n = NULL)
		: data(d),prev(p),next(n)
		{

		}
	};

public:
	class const_iterator
	{
	public:
		const_iterator():current(NULL)
		{

		}
		const Object &operator *() const
		{
			return retrieve();
		}
		//++itr的实现
		const_iterator &operator ++()
		{
			current = current->next;
			return *this;
		}
		//itr++的实现
		const_iterator operator ++ (int)
		{
			const_iterator old = *this;
			++(*this);
			return old;
		}
		bool operator == (const const_iterator &rhs) const
		{
			return current == rhs.current;
		}
		bool operator != (const const_iterator &rhs) const
		{
			return !(*this == rhs);
		}
	protected:
		//iterator里面包含了指向当前节点的元素指针
		Node *current;
		Object & retrieve() const
		{
			return current->data;
		}
		const_iterator (Node *p) : current(p)
		{

		}
		friend class List<Object>;
	};
	class iterator : public const_iterator
	{
	public:
		iterator()
		{

		}
		Object & operator *()
		{
			return const_iterator::retrieve();
		}
		const Object &operator *() const
		{
			return const_iterator::operator *();
		}
		iterator & operator ++()
		{
			const_iterator :: current = const_iterator :: current->next;
			return *this;
		}
		iterator operator ++(int)
		{
			iterator old = *this;
			++(*this);
			return old;
		}
	protected:
		iterator(Node *p) : const_iterator(p)
		{

		}
		friend class List<Object>;
	};
public:
	List()
	{
		init();
	}
	List(const List & rhs)
	{
		init();
		*this = rhs;
	}
	~List()
	{
		clear();
		delete head;
		delete tail;
	}
	const List &operator = (const List &rhs)
	{
		if (this == &rhs)
		{
			return *this;
		}
		clear();
		for (const_iterator itr = rhs.begin(); itr != rhs.end(); ++itr)
		{
			push_back(*itr);
		}
		return *this;
	}
	iterator begin()
	{
		return iterator (head->next);
	}
	const_iterator begin() const
	{
		return iterator(head->next);
	}
	iterator end()
	{
		return tail;
	}
	const_iterator end() const
	{
		return const_iterator(tail);
	}
	int size() const
	{
		return theSize;
	}
	bool empty() const
	{
		return size() == 0;
	}
	void clear()
	{
		while (!empty())
		{
			pop_front();
		}
	}
	Object &front()
	{
		return *begin();
	}
	const Object &front() const
	{
		return *begin();
	}
	Object & back()
	{
		return *(--end());
	}
	const Object & back() const
	{
		return *(--end());
	}
	void push_front(const Object &x)
	{
		insert(begin(),x);
	}
	void push_back(const Object &x)
	{
		insert(end(),x);
	}
	void pop_front()
	{
		erase(begin());
	}
	void pop_back()
	{
		erase(--end());
	}
	iterator insert(iterator itr,const Object &x)
	{	
		Node *p = itr.current;
		theSize ++;
		return iterator(p->prev = p->prev->next = new Node(x,p->prev,p));
	}
	iterator erase(iterator itr)
	{
		Node *p = itr.current;
		iterator retVal(p->next);
		p->prev->next = p->next;
		p->next->prev = p->prev;
		delete p;
		theSize --;
		return retVal;
	}
private:
	int theSize;
	Node *head;
	Node *tail;
	void init()
	{	
		theSize = 0;
		head = new Node;
		tail = new Node;
		head->next = tail;
		tail->prev = head;
	}
};