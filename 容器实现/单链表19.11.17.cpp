template <class Elem>
class Node
{
public:
	Elem element;
	Node *next;
	Node(const Elem &it, Node *nextval = 0)
	{
		element = it;
		next = nextval;
	}
	Node(Node *nextval = 0)
	{
		next = nextval;
	}
};

template<class Elem>
class List
{
	Node<Elem> *head;
	Node<Elem> *tail;
	Node<Elem> *curr;
	void init()
	{
		curr = tail = head = new Node<Elem>;
		cout << "创建成功" << endl;
	}
	void removeall()
	{
		while (head)
		{
			curr = head;
			head = head->next;
			delete curr;
		}
	}
public:
	List()
	{
		init();
	}
	~List()
	{
		removeall();
	}
	//bool Create(int n)
	//{
	//	Node<Elem> *tem = tail;
	//	for (int i = 0; i < n; i++)
	//	{
	//		tem->next = new Node<Elem>;
	//		if (!tem->next)
	//			return false;
	//		tem = tem->next;
	//		tail = tem;
	//	}
	//	return true;
	//}
	Elem &getValue()
	{
		if (curr == 0 || curr == head)
			cout << "当前位置没有值！" << endl;
		return curr->element;
	}
	Node<Elem> *Locate(Elem e)
	{
		Node<Elem> *tem = head->next;
		while (tem)
		{
			if (tem->element == e)
			{
				curr = tem;
				return tem;
			}
			tem = tem->next;
		}
		cout << "未找到该元素！" << endl;
		return NULL;
	}
	bool IsEmpty()
	{
		return head->next == NULL;
	}
	bool Prev()
	{
		if (curr == head)
			return false;
		Node<Elem> *p = curr;
		curr = head;
		while (curr->next != p)
		{
			curr = curr->next;
		}
		return true;
	}
	bool Next()
	{
		if (!curr->next)
			return false;
		curr = curr->next;
		return true;
	}
	bool setPos(int pos)
	{
		curr = head;
		for (int i = 0; i < pos; i++)
		{
			//curr = curr->next;
			//if (curr == NULL)
			//	return false;
			if (IsTail())
				return false;
			else
				curr = curr->next;
		}
		return true;
	}
	bool Insert(const Elem &x)
	{
		Node<Elem> *p = new Node<Elem>(x, curr->next);
		if (p == NULL)
		{
			cout << "创建新节点失败！" << endl;
			return false;
		}
		//p->element = x;
		//p->next = curr->next;
		curr->next = p;
		if (tail->next)
			tail = tail->next;
		return true;
	}
	bool remove(Elem &x)
	{
		if (!curr->next)
			return false;
		Node<Elem> *p = curr->next;
		curr->next = p->next;
		x = p->element;
		if (p == tail)
			tail = curr;
		delete p;
		return true;
	}
	void clear(const Elem &it = NULL)
	{
		removeall();
		init();
	}
	void Print()
	{
		Node<Elem> *p = head->next;
		while (p)
		{
			cout << p->element << ends;
			p = p->next;
		}
		cout << '\b' << endl;
	}
	//Node<Elem> *getHead()
	//{
	//	return head;
	//}
	void moveToTail()
	{
		curr = tail;
	}
	bool IsTail()
	{
		return curr == tail;
	}
};
