template <class T>
class MyHeap
{
	vector<T> heap;
	bool m;
	//int heapSize()
	//{
	//	return heap.size();
	//}
	bool isLeaf(int pos)
	{
		return leftChild(pos) >= heap.size();
	}
	int leftChild(int pos)
	{
		return 2 * pos + 1;
	}
	int rightChild(int pos)
	{
		return 2 * pos + 2;
	}
	int parent(int pos)
	{
		return (pos - 1) / 2;
	}
public:
	MyHeap(bool IsMax) :m(IsMax) {}
	~MyHeap() {}
	//void buildHeap()
	void push(const T &e)
	{
		int p = heap.size();
		heap.push_back(e);
		T t;
		if (m)
		{
			while (p > 0 && heap[parent(p)] < heap[p])
			{
				t = heap[p];
				heap[p] = heap[parent(p)];
				heap[parent(p)] = t;
				p = parent(p);
			}
		}
		else
		{
			while (p > 0 && heap[parent(p)] > heap[p])
			{
				t = heap[p];
				heap[p] = heap[parent(p)];
				heap[parent(p)] = t;
				p = parent(p);
			}
		}
	}
	void pop()
	{
		heap.front() = heap.back();
		heap.pop_back();
		int n = heap.size(), p = 0;
		T t;
		if (m)
		{
			while (!isLeaf(p))
			{
				if (rightChild(p) < n)
				{
					if (heap[p] < heap[leftChild(p)] || heap[p] < heap[rightChild(p)])
					{
						p = heap[leftChild(p)] > heap[rightChild(p)] ? leftChild(p) : rightChild(p);
						t = heap[p];
						heap[p] = heap[parent(p)];
						heap[parent(p)] = t;
					}
					else
						break;
				}
				else
				{
					if (heap[p] < heap[leftChild(p)])
					{
						p = leftChild(p);
						t = heap[p];
						heap[p] = heap[parent(p)];
						heap[parent(p)] = t;
					}
					else
						break;
				}
			}
		}
		else
		{
			while (!isLeaf(p))
			{
				if (rightChild(p) < n)
				{
					if (heap[p] > heap[leftChild(p)] || heap[p] > heap[rightChild(p)])
					{
						p = heap[leftChild(p)] < heap[rightChild(p)] ? leftChild(p) : rightChild(p);
						t = heap[p];
						heap[p] = heap[parent(p)];
						heap[parent(p)] = t;
					}
					else
						break;
				}
				else
				{
					if (heap[p] > heap[leftChild(p)])
					{
						p = leftChild(p);
						t = heap[p];
						heap[p] = heap[parent(p)];
						heap[parent(p)] = t;
					}
					else
						break;
				}
			}

		}
	}
	T &top()
	{
		return heap[0];
	}
	bool empty()
	{
		return heap.empty();
	}
};
