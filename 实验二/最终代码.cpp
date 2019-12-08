// 数据结构实验2.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include "pch.h"
#include<queue>
#include<vector>
#include <map>
#include <iostream>
using namespace std;

template <class T>
class HuffmanTree;

template <class T>
class HuffmanTreeNode
{
	friend class HuffmanTree<T>;
	T data;
	int wgt;
	HuffmanTreeNode<T>* left;
	HuffmanTreeNode<T>* right;
public:
	HuffmanTreeNode()
	{
		left = right = 0;
		wgt = 0;
	}
	HuffmanTreeNode(const T &ele, int w, HuffmanTreeNode<T> *l, HuffmanTreeNode<T> *r)
	{
		data = ele;
		wgt = w;
		left = l;
		right = r;
	}
	~HuffmanTreeNode() {}
	T getvalue() const
	{
		return data;
	}
	HuffmanTreeNode<T>* leftchild()const
	{
		return left;
	}
	HuffmanTreeNode<T>* rightchild()const
	{
		return right;
	}
	bool isLeaf()const
	{
		if (right == 0 && left == 0)
			return true;
		return false;
	}
};

template <class T>
class HuffmanTree
{
//protected:
	HuffmanTreeNode<T> *root;
public:
	HuffmanTree()
	{
		root = 0;
	}
	HuffmanTree(T &ele, int w)
	{
		root = new HuffmanTreeNode<T>;
		if (root)
		{
			root->data = ele;
			root->wgt = w;
		}
	}
	HuffmanTree(int w, HuffmanTree<T> *l, HuffmanTree<T> *r)
	{
		root = new HuffmanTreeNode<T>;
		if (root)
		{
			root->wgt = w;
			root->left = l->root;
			root->right = r->root;
		}
	}
	~HuffmanTree()
	{
		DeleteHuffmanTree(root);
	}
	HuffmanTreeNode<T>*& Root() { return root; }
	int getwgt()
	{
		return root->wgt;
	}
	void DeleteHuffmanTree(HuffmanTreeNode<T> *root)
	{
		if (root)
			delete root;
	}
};

template <class T>
class cmp
{
public:
	bool operator()(HuffmanTree<T> *x, HuffmanTree<T> *y)
	{
		return x->getwgt() > y->getwgt();
	}
};

template <class T>
HuffmanTree<T> *BuildHuffTree(T elem[], int w[], int n)	//可vector
{
	priority_queue<HuffmanTree<T> * , vector<HuffmanTree<T> * >, cmp<T>> QHTree;
	for (int i = 0; i < n; i++)
		QHTree.push(new HuffmanTree<T>(elem[i], w[i]));
	while (QHTree.size() > 1)
	{
		HuffmanTree<T> *lc = QHTree.top();
		QHTree.pop();
		HuffmanTree<T> *rc = QHTree.top();
		QHTree.pop();
		HuffmanTree<T> *p = new HuffmanTree<T>(lc->getwgt() + rc->getwgt(), lc, rc);
		QHTree.push(p);
	}
	return QHTree.top();
}

//typedef vector<bool> HuffCode;
map<char, vector<bool> > HuffDic;

template <class T>
void getcode(HuffmanTreeNode<T>* r, vector<bool> c)
{
	if (r->isLeaf())
	{
		HuffDic[r->getvalue()] = c;
		return;
	}
	vector<bool> lc = c;
	vector<bool> rc = c;
	lc.push_back(false);
	rc.push_back(true);
	getcode(r->leftchild(), lc);
	getcode(r->rightchild(), rc);
}

int main()
{
	char key[100];
	int wgt[100];
	vector<bool> cc;
	char c;
	int w, n, i;
	for (i = 0; i < 100; i++)
	{
		cin >> c;
		if (c == '0')
			break;
		else
		{
			cin >> w;
			HuffDic[c] = cc;
			key[i] = c;
			wgt[i] = w;
		}
	}
	n = i;
	getcode(BuildHuffTree<char>(key, wgt, n)->Root(), cc);
	map<char, vector<bool> >::iterator iter;
	for (iter = HuffDic.begin(); iter != HuffDic.end(); iter++)
	{
		cout << '(' << iter->first << ',';
		for (i = 0; i < iter->second.size(); i++)
		{
			cout << iter->second[i];
		}
		cout << ')' << endl;
	}
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
