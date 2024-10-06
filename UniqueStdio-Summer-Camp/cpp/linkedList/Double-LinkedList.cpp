#include<iostream>
using namespace std;
typedef struct DoubleLinkList {

	int data;		//结点的数据域

	DoubleLinkList* next;	//下一个结点的指针域

	DoubleLinkList* prev;	//上一个结点的指针域

}DoubleLinkList,DoubleLinkNode;
bool DoubleLinkListInit(DoubleLinkList* &L) {	//构造一个空的双向链表

	L = new DoubleLinkNode;	//生成新结点作为头结点，用头指针L指向新结点
	if (!L)return false;		//生成结点失败

	L->next = NULL;		//头结点的next指针域指空
	L->prev = NULL;		//头结点的prev指针域指空
	L->data = -1;

	return true;
}
//前插法
bool DoubleLinkListInsertFront(DoubleLinkList*& L, DoubleLinkNode* node) {

	if (!L || !node) return false;

	
	if (L->next == NULL) {//只有头结点
		node->next = NULL;
		node->prev = L;		//新结点的prev指针指向头结点
		L->next = node;		//头结点的next指针指向新结点
	}
	else {
		L->next->prev = node;	//第二个结点的prev指向新结点
		node->next = L->next;	//新结点的next指向第二个结点
		node->prev = L;			//新结点的prev指向第一个结点
		L->next = node;			//第一个结点的next指向新结点
	}
	return true;
}
//尾插法
bool DoubleLinkListInsertBack(DoubleLinkList*& L, DoubleLinkNode* node) {

	DoubleLinkNode* last = NULL;

	if (!L || !node) return false;

	last = L;

	while (last->next) last = last->next;

	node->next = NULL;
	node->prev = last;
	last->next = node;

	return true;
}
//双向链表的遍历输出
void DoubleLinkListPrint(DoubleLinkList* &L) {

	DoubleLinkNode* p=L;

	if (!L) {
		cout << "链表为空" << endl;
		return;
	}

	cout << p->data << "  ";
	while (p->next) {
		cout << p->next->data << "  ";
		p = p->next;
	}

	//逆向打印
	cout << endl << "逆向打印" << endl;
	while (p) {
		cout << p->data << " ";
		p = p->prev;
	}
	cout << endl;

	return;
}
//指定位置插入
bool DoubleLinkListInsert(DoubleLinkList* L,int i,int e) {

	if (!L || !L->next) return false;
	if (i < 1)return false;

	int j = 0;
	DoubleLinkList* p, * s;
	p = L;

	while (p && j < i) {//查找位置为i的结点，p指向该结点
		p = p->next;
		j++;
	}

	if (!p || j != i) {
		cout << "结点不存在" << i << endl;
		return false;
	}

	s = new DoubleLinkNode;
	s->data = e;

	s->next = p;
	s->prev = p->prev;

	p->prev->next = s;
	p->prev = s;

	return true;
}
//双向链表按位取值
bool DoubleLinkListGetElem(DoubleLinkList* &L,int i,int& e) {

	int index;
	DoubleLinkList* p;

	if (!L || !L->next) return false;

	p = L->next;
	index = 1;

	while (p || index < i) { //链表向后扫描，直到p指向第i个元素或者p为空
		p = p->next;		//p指向下一个结点
		index++;				//计数器index加1
	}

	if (!p || index > i) {
		return false;   //i值不合法，i>n或i<=0
	}

	e = p->data;

	return true;
}
//任意位置删除
bool DoubleLinkListDelete(DoubleLinkList*& L, int i) {

	DoubleLinkList* p;
	int index = 0;

	if (!L || !L->next) {
		cout << "双向链表为空！" << endl;
		return false;
	}
	if (i < 1) {
		cout << "不能删除头结点!" << endl;
		return false;
	}
	p = L;

	while (p && index < i) {
		p = p->next;
		index++;
	}
	if (!p)return false; //当结点不存在时，返回失败

	p->prev->next = p->next;
	if(p->next!=nullptr)
		p->next->prev = p->prev;

	delete p;

	return true;
}
//销毁双向链表
void DoubleLinklistDestroy(DoubleLinkList*  &L) {

	DoubleLinkList* p = L;
	cout << "销毁链表" << endl;

	while (p) {
		L = L->next; //L指向下一个结点
		delete p;   //删除当前结点
		p = L;     //p移向下一个结点
	}

}
int main() {
	
	DoubleLinkList* L;
	DoubleLinkList* s;

	//1.初始化一个空的双向链表
	if (DoubleLinkListInit(L)) {
		cout << "初始化链表成功!" << endl;
	}
	else {
		cout << "初始化链表失败！" << endl;
	}

	//2.使用前插法插入数据
	int n;

	cout << "使用前插法创建双向链表" << endl;
	cout << "请输入元素个数：";
	cin >> n;
	cout << endl << "依次输入" << n << "个元素: ";

	while (n > 0) {
		s = new DoubleLinkNode;
		cin >> s->data;
		DoubleLinkListInsertFront(L, s);
		n--;
	}

	DoubleLinkListPrint(L);

	//3.使用尾插法插入数据
	
	cout << "使用尾插法创建双向链表" << endl;
	cout << "请输入元素个数：";
	cin >> n;
	cout << endl << "依次输入" << n << "个元素: ";

	while (n > 0) {
		s = new DoubleLinkNode;
		cin >> s->data;
		DoubleLinkListInsertBack(L, s);
		n--;
	}


	DoubleLinkListPrint(L);

	//4.任意位置插入元素
	for (int j = 0; j < 3; j++) {
		int i, x;
		cout << "请输入要插入的位置和元素(用空格隔开):";
		cin >> i >> x;

		if (DoubleLinkListInsert(L, i, x)) {
			cout << "插入成功！" << endl;
		}
		else {
			cout << "插入失败！" << endl;
		}
		DoubleLinkListPrint(L);
	}

	//5.双向链表删除元素
	if (DoubleLinkListDelete(L, 2)) {
		cout << "删除链表第2个元素成功" << endl;
	}
	else
		cout << "删除链表第2个元素失败！" << endl;


	DoubleLinkListPrint(L);

	//6.销毁链表
	DoubleLinklistDestroy(L);


	return 0;
}
