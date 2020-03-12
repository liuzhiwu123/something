#include <iostream>
using namespace std;


#define  _CRT_SECURE_NO_WARNINGS


class CStack
{
public:
	CStack(int size = 10);
	~CStack();//释放资源
	void push(int val);
	void pop();
	int top();
	bool empty();
	bool full();
	void Printf();
	void childMenue()
	{
		int choice;
		while (1)
		{
			cout << "-------------------------" << endl;
			cout << "1.查看" << endl;
			cout << "2.添加" << endl;
			cout << "3.删除" << endl;
			cout << "4.返回" << endl;
			cout << "-------------------------" << endl;
			cout << "please choice" << endl;
			cin >> choice;
			switch (choice)
			{
			case 1:Printf(); break;
			case 2:cout << "please input val:" << endl; cin >> choice; push(choice); break;
			case 3:pop(); break;
			case 4:return;
			default:cout << "input error,again" << endl;
			}
		}
	}
private:
	int *mpStack;
	int mTop;
	int mSize;
	static int high;
	bool resize(int size);
};
CStack::CStack(int size)
{
	mSize = size;
	mTop = -1;
	mpStack = new int[size];//new int[size]()  初始化为0，其他值要for	
	//将文件里的数据拷贝出来      文件不空和空俩中情况，测出文件大小一目了然
	FILE *fp = fopen("stack.txt", "rb+");//wb+ 创建一个读写的二进制文件，会清空
		if (fp == nullptr)
		{
			cout << "open stack.txt error" << endl;
		}
		else
		{
			fseek(fp, 0,SEEK_END);
			long size = ftell(fp);
			fseek(fp, 0, SEEK_SET);
			if (size > 0)
			{
				int num = size / sizeof(int);
				int* buff = new int[num];
				fread(buff, sizeof(int)*num, 1, fp);
				for (int i = 0; i < num; i++)
				{
					push(buff[i]);
				}
				delete[]buff;
			}

		}
		fclose(fp);
	cout << "CStack()" << mSize<<endl;
}
//二进制文件存入的是二进制，文本文件存入的是ascll码，读写匹配错误会出错。比如数字0，文本文件存入48，二进制存入的0000000，读取时
//若是用二进制读取文本文件内容，会读取出48.
CStack:: ~CStack()
{

	//析构前先把数据存入文件
	FILE* fp = fopen("stack.txt", "wb+");//rb+打开读写的二进制文件   wb+已经把文件清空了
	if (fp == nullptr)
	{
		cout << "open stack.txt error" << endl;
	}
	else
	{
		if (mTop == -1)
		{
			cout << "stack.empty" << endl;
		}
		else
		{
			fwrite(mpStack, sizeof(int)*(mTop + 1), 1, fp);//二进制文件的写，对应二进制文件的读fread   它们是按字节读取
		}
	}
	fclose(fp);
	delete[]mpStack;//数组加【】
	mpStack = nullptr;
	cout << "~CStack" << endl;
}
void CStack::push(int val)// push(CStack* this, int val)
{
	if (full())
	{
		if (!resize(2 * mSize))
		{
			return;
		}
	}
	mpStack[++mTop] = val;
}
int CStack::top()
{
	if (empty())
		throw"stack empty";
	return mpStack[mTop];

}
void CStack::pop()
{
	if (empty())
		return;
	mTop--;
}
bool CStack::full()
{
	return mTop == mSize - 1 ? true : false;
}
bool CStack::empty()
{
	return mTop == -1;//都可以和和上面的写法
}
bool CStack::resize(int size)
{
	int* newdata = new int[size]();//if(newdata==nullptr)  无效，new空间失败是抛出异常，并非判空
	for (int i = 0; i < mSize; i++)
	{
		newdata[i] = mpStack[i];
	}
	mSize = 2 * mSize;
	delete[]mpStack;
	mpStack = newdata;
	return true;
}
void CStack::Printf()
{
	for (int i = 0; i <= mTop; i++)
	{
		cout << mpStack[i]<<" ";
	}
	cout << endl;
}




class CQueue
{
public:
	CQueue(int size = 10);
	~CQueue();
	void push(int val);
	void pop();
	int front();
	int back();
	bool empty();
	bool full();
	void Printf();
	void childMenue()
	{
		int choice;
		while (1)
		{
			cout << "-------------------------" << endl;
			cout << "1.查看" << endl;
			cout << "2.添加" << endl;
			cout << "3.删除" << endl;
			cout << "4.返回" << endl;
			cout << "-------------------------" << endl;
			cout << "please choice" << endl;
			cin >> choice;
			switch (choice)
			{
			case 1:Printf(); break;
			case 2:cout << "please input val:" << endl; cin >> choice; push(choice); break;
			case 3:pop(); break;
			case 4:return;
			default:cout << "input error,again" << endl;
			}
		}
	}
private:
	int *mQue;
	int mSize;
	int mFront;
	int mRear;
	bool resize(int size);
};
CQueue::CQueue(int size)
{
	mQue = new int[size];
	mSize = size;
	mFront = mRear = 0;
	//将文件里的数据拷贝出来      文件不空和空俩中情况，测出文件大小一目了然
	FILE *fp = fopen("que.txt", "rb+");//wb+ 创建一个读写的二进制文件，会清空  rb+只打开
	if (fp == nullptr)
	{
		cout << "open que.txt error" << endl;
	}
	else
	{
		fseek(fp, 0, SEEK_END);
		long size = ftell(fp);
		fseek(fp, 0, SEEK_SET);
		if (size > 0)
		{
			int num = size / sizeof(int);
			int* buff = new int[num];
			fread(buff, sizeof(int)*num, 1, fp);
			for (int i = 0; i < num; i++)
			{
				push(buff[i]);
			}
			delete[]buff;
		}

	}
	fclose(fp);
	cout << "CQueue()" << mSize<<endl;
}
CQueue:: ~CQueue()
{
	//析构前先把数据存入文件
	FILE* fp = fopen("que.txt", "wb+");//rb+打开读写的二进制文件   wb+已经把文件清空了
	if (fp == nullptr)
	{
		cout << "open que.txt error" << endl;
	}
	else
	{
		if (empty())
		{
			cout << "que.empty" << endl;
		}
		else
		{
			for(int i=mFront;i!=mRear;i=(i+1)%mSize)
			fwrite(mQue+i, sizeof(int), 1, fp);//二进制文件的写，对应二进制文件的读fread   它们是按字节读取
		}
	}
	delete[]mQue;
	mRear = mFront = 0;
	mQue = nullptr;
	cout << "~CQueue" << endl;
}
void CQueue::push(int val)
{
	if (full())
	{
		if (!resize(2*mSize))
			return;
	}
	mQue[mRear] = val;
	mRear = (mRear + 1) % mSize;
}
void CQueue::pop()
{
	if (!empty())
		mFront = (mFront + 1) % mSize;
	return;
}
int CQueue::front()
{
	if(!empty())
	return mQue[mFront];
	throw"mQue empty";
}
int CQueue::back()
{
	if (!empty())
		return mQue[(mRear + mSize - 1) % mSize];
	throw"mQue empty";
}
bool CQueue::empty()
{
	return mFront == mRear;
}
bool CQueue::full()
{
	return (mRear + 1) % mSize == mFront;
}
bool CQueue::resize(int size)
{
	int* newdata = new int[size];
	for (int i = mFront, j = 0; i!= mRear; i = (i + 1) % mSize, j++)
	{
		newdata[j] = mQue[i];
	}
	mFront = 0;
	mRear = mSize-1;
	mSize = 2 * mSize;
	delete []mQue;
	mQue = newdata;
	return true;
}
void CQueue::Printf()
{
	for (int i = mFront; i != mRear; i = (i + 1) % mSize)
	{
		cout << mQue[i]<<" ";
	}
	cout << endl;
}

class CLink
{
public:
	CLink()
	{
		link = new Node;
		//将文件里的数据拷贝出来      文件不空和空俩中情况，测出文件大小一目了然
		FILE *fp = fopen("link.txt", "rb+");//wb+ 创建一个读写的二进制文件，会清空  rb+只打开
		if (fp == nullptr)
		{
			cout << "open link.txt error" << endl;
		}
		else
		{
			fseek(fp, 0, SEEK_END);
			long size = ftell(fp);
			fseek(fp, 0, SEEK_SET);
			if (size > 0)
			{
				int num = size / sizeof(int);
				int* buff = new int[num];
				fread(buff, sizeof(int)*num, 1, fp);
				for (int i = 0; i < num; i++)
				{
					insert(buff[i]);
				}
				delete[]buff;
			}

		}
		fclose(fp);
		cout << "CLink()" << endl;
	}
	void insert(int val)
	{
		Node* p = link;
		while (p->next != nullptr)
		{
			p = p->next;
		}
		p->next = new Node(val);
	}
	void remove(int val)
	{
		Node* p = link;
		while (p->next!=nullptr&&p->next->data != val)
		{
			p = p->next;
		}
		if (p->next == nullptr) return;
		Node* s = p->next;
		p->next = s->next;
		delete s;
		return;
	}
	void Printf()
	{
		Node* p = link->next;
		while (p != nullptr)
		{
			cout << p->data << " ";
			p = p->next;
		}
		cout << endl;
	}
	~CLink()
	{
		Node* p = link->next;
		Node* s = p;
		//析构前先把数据存入文件
		FILE* fp = fopen("link.txt", "wb+");//rb+打开读写的二进制文件   wb+已经把文件清空了
		if (fp == nullptr)
		{
			cout << "open link.txt error" << endl;
		}
		else
		{
			while(p!=nullptr)
			{
					fwrite(&p->data, sizeof(int), 1, fp);//二进制文件的写，对应二进制文件的读fread   它们是按字节读取
					p = p->next;
			}
		}
		fclose(fp);
		p = s;
		while (p != nullptr)
		{
			p = p->next;
			delete s;
			s = p;
		}
		delete link;
		link = nullptr;
		cout << "~CLink()" << endl;
	}
	void childMenue()
	{
		int choice;
		while (1)
		{
			cout << "-------------------------" << endl;
			cout << "1.查看" << endl;
			cout << "2.添加" << endl;
			cout << "3.删除" << endl;
			cout << "4.返回" << endl;
			cout << "-------------------------" << endl;
			cout << "please choice" << endl;
			cin >> choice;
			switch (choice)
			{
			case 1:Printf(); break;
			case 2:cout << "please input val:" << endl; cin >> choice; insert(choice); break;
			case 3:cout << "please input val:" << endl; cin >> choice; remove(choice); break;
			case 4:return;
			default:cout << "input error,again" << endl;
			}
		}
	}
private:
	struct Node
	{
		Node(int val=0):next(nullptr),data(val){}
		int data;
		struct Node* next;
	};
	Node* link;
};


class CSystem
{
public:
	void start()
	{
		int choice;
		while (1)
		{
			cout << "-------------------------" << endl;
			cout << "1.栈" << endl;
			cout << "2.队列" << endl;
			cout << "3.链表" << endl;
			cout << "4.退出" << endl;
			cout << "-------------------------" << endl;
			cout << "please choice:" << endl;
			cin >> choice;
			switch ((TYPE)choice)
			{
			case STACK:stk.childMenue(); break;
			case QUE:que.childMenue(); break;
			case LINK:link.childMenue(); break;
			case 4:cout << "system shut down" << endl; return;
			default:cout << "input error,again" << endl;
			}
		}
	}
private:
	enum TYPE{ STACK=1,QUE,LINK };
	CStack stk;
	CQueue que;
	CLink link;
};
int main()
{
system sys;
sys.start();
 return 0;
}
