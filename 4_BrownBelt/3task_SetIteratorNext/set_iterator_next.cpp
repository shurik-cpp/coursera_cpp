#include "test_runner.h"
#include <cassert>
#include <deque>
#include <iostream>

using namespace std;


struct Node {
	Node(int v, Node* p)
		: value(v)
		, parent(p)
	{}

	int value;
	Node* left = nullptr;
	Node* right = nullptr;
	Node* parent;
};

class NodeBuilder {
public:
	Node* CreateRoot(int value) {
		nodes.emplace_back(value, nullptr);
		return &nodes.back();
	}

	Node* CreateLeftSon(Node* me, int value) {
		assert( me->left == nullptr );
		nodes.emplace_back(value, me);
		me->left = &nodes.back();
		return me->left;
	}

	Node* CreateRightSon(Node* me, int value) {
		assert( me->right == nullptr );
		nodes.emplace_back(value, me);
		me->right = &nodes.back();
		return me->right;
	}

private:
	deque<Node> nodes;
};

Node* SlideToLeft(Node* node) {
	while (node->left != nullptr)
		node = node->left;
	return node;
}

Node* GoUp(Node* node, Node* me) {
	while (node->value < me->value) {
		if (node->parent != nullptr)
			node = node->parent;
		else
			return nullptr; // если нода - корень дерева, значит нода me была самая большая
	}
	return node;
}

Node* Next(Node* me) {
	if (!me->right && !me->parent) return nullptr;

	Node* node = me;
	if (node->right == nullptr) { // если правая нода пуста
		node = node->parent; // поднялись на ступень вверх
		if (node->right != nullptr && node->right->value == me->value) { // если узнаем, что мы вышли из правой ноды текущей ступени
			node = GoUp(node, me); // поднимаемся наверх, пока значение ноды не окажется больше изначальной (me)
		}
	} else {
		node = SlideToLeft(node->right); // делаем шаг вправо и скатываемся в самую нижнюю левую ноду
	}
	return node;
}

void Test1() {
	NodeBuilder nb;

	Node* root = nb.CreateRoot(50);
	ASSERT_EQUAL( root->value, 50 );

	Node* l = nb.CreateLeftSon(root, 2);
	Node* min = nb.CreateLeftSon(l, 1);
	Node* r = nb.CreateRightSon(l, 4);
	ASSERT_EQUAL( min->value, 1 );
	ASSERT_EQUAL( r->parent->value, 2 );

	nb.CreateLeftSon(r, 3);
	Node* five = nb.CreateRightSon(r, 5);
	ASSERT_EQUAL( Next(five)->value, root->value );

	r = nb.CreateRightSon(root, 100);
	l = nb.CreateLeftSon(r, 90);
	nb.CreateRightSon(r, 101);

	nb.CreateLeftSon(l, 89);
	r = nb.CreateRightSon(l, 91);

	ASSERT_EQUAL( Next(l)->value, 91 );
	ASSERT_EQUAL( Next(root)->value, 89 );
	ASSERT_EQUAL( Next(min)->value, 2 );
	ASSERT_EQUAL( Next(r)->value, 100 );

	while (min) {
		cout << min->value << '\n';
		min = Next(min);
	}
}

void TestRootOnly() {
	NodeBuilder nb;
	Node* root = nb.CreateRoot(42);
	ASSERT( Next(root) == nullptr);
};


int main() {
	TestRunner tr;
	RUN_TEST(tr, Test1);
	RUN_TEST(tr, TestRootOnly);
	return 0;
}
