#ifndef __LIST_H__
#define __LIST_H__

#include <iostream>

using namespace std;

#ifndef __NODE__
#define __NODE__
template <class ValType>
struct node{
	node* next;
	ValType data;
	
	node() {};
	node(ValType d) {
		next = 0;
		data = d;
	};
};
#endif

template <class ValType>
class TList
{
protected:
	node<ValType>* body;	// указатель на первый элемент
public:

  	TList();
	~TList();
	bool IsEmpty() const;
	void Print() const;
	
//  Вставка
	void InsertAtBegin(node<ValType>* elem);			// вставить в начало элемент elem
	void InsertAtEnd(node<ValType>* elem);				// вставить в конец элемент elem
	void Put(ValType dt);				// вставить в конец элемент с данными dt
	void Insert(node<ValType>* i, node<ValType>* elem);	// вставить элемент elem после i

//  Удаление
	void DeleteAtBegin();		// удалить элемент из начала
	ValType Get();				// удалить и взять элемент из начала
	void DeleteAtEnd();					// удалить элемент в конеце
	void Delete(node<ValType>* elem);	// удалить элемент после elem

	node<ValType>* Search(ValType a);	// поиск элемента a
};

template <class ValType>
TList<ValType>::TList() {
	body = 0;
}

template <class ValType>
TList<ValType>::~TList()
{
	if (body != 0)
	{
		node<ValType>* temp;
		while(body->next != 0) 
		{
			temp = body;
			body = body->next;
			delete temp;
		}
		delete body;
	}
}

template <class ValType>
bool TList<ValType>::IsEmpty() const
{
	return !body;
}

template <class ValType>
void TList<ValType>::Print() const
{
	if(body)
	{
		node<ValType>* temp = body;
		while(temp->next)
		{
			cout<<temp->data<<' ';
			temp = temp->next;
		}
		cout<<temp->data<<'\n';
	}
	else cout<<"List is empty!"<<'\n';
}



template <class ValType>
void TList<ValType>::InsertAtBegin(node<ValType>* elem)
{
	if(elem)
	{
		elem->next = body;
		body = elem;
	}
	else throw "error";
}

template <class ValType>
void TList<ValType>::InsertAtEnd(node<ValType>* elem)
{
	if(elem)
	{
		if(body)
		{
			node<ValType>* temp = body;
			while(temp->next != 0) temp = temp->next;
			temp->next = elem;
		}
		else body = elem;
		elem->next = 0;
	}
	else throw "error";
}

template <class ValType>
void TList<ValType>::Put(ValType dt)
{
	InsertAtEnd(new node<ValType>(dt));
}

template <class ValType>
void TList<ValType>::Insert(node<ValType>* i, node<ValType>* elem)
{
	if(elem && i)
	{
		elem->next = i->next;
		i->next = elem;
	}
	else throw "error";
}



template <class ValType>
void TList<ValType>::DeleteAtBegin()
{
	if(body)
	{
		node<ValType>* temp = body;
		body = body->next;
		delete temp;
	}
}

template <class ValType>
ValType TList<ValType>::Get()
{
	if(body)
	{
		ValType temp=body->data;
		DeleteAtBegin();
		return temp;
	}
	
}

template <class ValType>
void TList<ValType>::DeleteAtEnd()
{
	if(body)
	{
		if(body->next)
		{
			node<ValType>* temp = body;
			while(temp->next->next) temp = temp->next;
			delete temp->next;
			temp->next = 0;
		}
		else
		{
			delete body;
			body = 0;
		}
	}
}

template <class ValType>
void TList<ValType>::Delete(node<ValType>* elem)
{
	if(elem && elem->next)
	{
		node<ValType>* temp = elem->next;
		elem->next = elem->next->next;
		delete temp;
	}
}

template <class ValType>
node<ValType>* TList<ValType>::Search(ValType a)
{
	if(body)
	{
		node<ValType>* temp = body;
		while(temp && temp->data != a) temp = temp->next;
		return temp;
	}
	else return false;
}


#endif


#ifndef __STACK_H__
#define __STACK_H__

#include <iostream>

using namespace std;

template <class ValType>
class TStack: public TList<ValType>
{
public:
	TStack();						// ???????????
	TStack(const TStack &st);		// ??????????? ???????????

	void Push(const ValType elem);	// ???????? ??????? ? ????
	void Clr();						// ?Ц?????? ????
	ValType Pop();					// ?????Ц? ??????? ?? ?????
	ValType Top();					// ???????????? ??????? ?????

};

template <class ValType>
TStack<ValType>::TStack() {
	body = 0;
}

template <class ValType>
TStack<ValType>::TStack(const TStack<ValType> &st) 
{
	if(st.body)
	{
		/* 
		node<ValType>* temp = st.body;
		body = new node<ValType>;
		while(temp->next)
		{
			body->data = temp->data;
			body->next = new node<ValType>;
			
			temp = temp->next;
			body = body->next;
		}
		body->data = temp->data;
		body->next = 0;
		*/
		
		node<ValType>* temp = st.body;
		body = temp;
		while(temp->next)
		{
			TList<ValType>::InsertAtBegin(temp->next);
			temp = temp->next;
		}
	}
	else body = 0;
}

template <class ValType>
void TStack<ValType>::Push(const ValType elem)
{

	TList<ValType>::InsertAtBegin(new node<ValType>(elem));
}

template <class ValType>
void TStack<ValType>::Clr()
{
	if (body !=0 )
	{
		node<ValType>* temp;
		while(body->next != 0) 
		{
			temp = body;
			body = body->next;
			delete temp;
		}
		delete body;
	}
	body = 0;
}

template <class ValType>
ValType TStack<ValType>::Pop()
{
	if(body)
	{
		ValType res = body->data;
		TList<ValType>::DeleteAtBegin();
		return res;
	}
	else throw "Stack is empty";
}

template <class ValType>
ValType TStack<ValType>::Top()
{
	if(body)
	{
		ValType res = body->data;
		return res;
	}
	else throw "Stack is empty";
}

#endif