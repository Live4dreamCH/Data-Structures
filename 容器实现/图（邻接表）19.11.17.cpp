struct NodeUnit
{
	int vertex;
	int weight;
};

ostream &operator<<(ostream &out, const NodeUnit &u)
{
	cout << '(' << u.vertex << ',' << u.weight << ')';
	return out;
}

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

class Graph
{
	int vexnum;
	int edgenum;
	List<NodeUnit> *vexList;
	bool *visited;
	int *outdeg;
public:
	Graph(int n) :vexnum(n)
	{
		vexList = new List<NodeUnit>[vexnum];
		edgenum = 0;
		visited = new bool[vexnum];
		outdeg = new int[vexnum];
	}
	~Graph()
	{
		delete[] vexList;
		delete[] visited;
		delete[] outdeg;
	}
	void setEdge(int from, int to, int weight)
	{
		List<NodeUnit> &a = vexList[from];
		if (a.setPos(1))
		{
			while (!a.IsTail() && a.getValue().vertex < to)
			{
				a.Next();
			}
			if (a.IsTail())
			{
				NodeUnit t;
				t.vertex = to;
				t.weight = weight;
				a.Insert(t);
				edgenum++;
				outdeg[from]++;
				return;
			}
			else if (a.getValue().vertex == to)
			{
				a.getValue().weight = weight;
				return;
			}
			else if (a.getValue().vertex > to)
			{
				a.Prev();
				NodeUnit t;
				t.vertex = to;
				t.weight = weight;
				a.Insert(t);
				edgenum++;
				outdeg[from]++;
				return;
			}
		}
		else
		{
			NodeUnit t;
			t.vertex = to;
			t.weight = weight;
			a.Insert(t);
			edgenum++;
			outdeg[from]++;
			return;
		}
	}
	int weight(int from, int to)
	{
		//Node<NodeUnit> *t = vexList[from].getHead()->next;
		//while (t->next != 0 && t->element.vertex != to)
		//{
		//	t = t->next;
		//}
		//return t->next->element.weight;
		List<NodeUnit> &a = vexList[from];
		if (!a.setPos(1))
			return -1;
		while (!a.IsTail() && a.getValue().vertex != to)
		{
			a.Next();
		}
		if (a.getValue().vertex == to)
			return a.getValue().weight;
		else
			return -1;
	}
	int Firstadj(int from)
	{
		List<NodeUnit> &a = vexList[from];
		if (a.setPos(1))
			return a.getValue().vertex;
		else
			return -1;
	}
	int Nextadj(int from, int prevex)
	{
		List<NodeUnit> &a = vexList[from];
		if (a.setPos(1))
		{
			while (!a.IsTail() && a.getValue().vertex <= prevex)
			{
				a.Next();
			}
			if (!a.IsTail())
				return a.getValue().vertex;
			return -1;
		}
		else
			return -1;
	}
	bool delEdge(int from, int to)
	{
		List<NodeUnit> &a = vexList[from];
		if (!a.setPos(1))
			return false;
		while (!a.IsTail() && a.getValue().vertex != to)
		{
			a.Next();
		}
		if (!a.IsTail())
		{
			a.Prev();
			NodeUnit t;
			if (!a.remove(t))
				return false;
			edgenum--;
			outdeg[from]--;
		}
		return false;
	}
	void print()
	{
		cout << "格式：(邻接点下标,权值）" << endl;
		for (int i = 0; i < vexnum; i++)
		{
			cout << "第" << i << "个顶点的邻接点：" << endl;
			vexList[i].Print();
		}
	}
	void Dijkstra(int *&dist, int *&pre, int s)
	{
		MyHeap<pair<int, int> > s_v(false);	//小顶堆
		delete[] dist, pre;
		dist = new int[vexnum];
		pre = new int[vexnum];
		int i, j;
		for (i = 0; i < vexnum; i++)
		{
			visited[i] = false;
			if (i != s)
			{
				if (weight(s, i) == -1)
				{
					pre[i] = -1;
					dist[i] = -1;
				}
				else
				{
					dist[i] = weight(s, i);
					pre[i] = s;
				}
			}
		}
		pre[s] = s;
		dist[s] = 0;
		visited[s] = true;

		for (i = 0; i < vexnum - 1; i++)
		{
			for (j = 0; j < vexnum; j++)
			{
				if (!visited[j] && dist[j] != -1)
				{
					pair<int, int> t(dist[j], j);
					s_v.push(t);
				}
			}
			int v = s_v.top().second;
			while (!s_v.empty())
			{
				s_v.pop();
			}
			visited[v] = true;
			for (j = 0; j < vexnum; j++)
			{
				if (!visited[j])
				{
					int x = weight(v, j);	//降低时间复杂度
					if (x == -1)
						continue;
					if (dist[j] == -1)
					{
						dist[j] = dist[v] + x;
						pre[j] = v;
					}
					else if (dist[v] + x < dist[j])
					{
						dist[j] = dist[v] + x;
						pre[j] = v;
					}
				}
				//dist[j]=dist[v] + weight(v, j)<dist[j]?
			}

			for (j = 0; j < vexnum; j++)
			{
				cout << '(' << dist[j] << ',' << pre[j] << ')' << ends;
			}
			cout << endl;
		}
	}
};

void findpath(int dist[], int pre[], int s, int n)
{
	int i, k;
	vector<int> *path = new vector<int>[n];
	for (i = 0; i < n; i++)
	{
		k = i;
		while (pre[k] != s)
		{
			path[i].insert(path[i].begin(), pre[k]);
			k = pre[k];
		}
		//while (pre[k] != s);
		//{
		//	path[i].insert(path[i].begin(), pre[k]);
		//	k = pre[k];
		//}
		path[i].insert(path[i].begin(), pre[k]);
	}
	for (i = 0; i < n; i++)
	{
		cout << 'V' << s << "结点到V" << i << "结点的最短路径为： ";
		for (k = 0; k < path[i].size(); k++)
		{
			cout << 'V' << path[i][k] << "->";
		}
		cout << 'V' << i;
		cout << "\t\t\t最短距离为： " << dist[i] << endl;
	}
}
