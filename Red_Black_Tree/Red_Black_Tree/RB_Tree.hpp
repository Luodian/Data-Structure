//
//  RB_Tree.hpp
//  Red_Black_Tree
//
//  Created by 李博 on 24/04/2017.
//  Copyright © 2017 李博. All rights reserved.
//

#ifndef RB_Tree_h
#define RB_Tree_h

#include "Header.hpp"

using namespace std;

namespace RB
{
	template <class comparable,class ValueType>
	class RedBlackTree
	{
	public:
		explicit RedBlackTree(const comparable &negInf = -INF)
		{
			nullNode = new RedBlackNode;
			if (nullNode == nullptr)
			{
				cout<<"Memory fails.\n";
				exit(0);
			}
			nullNode->left = nullNode->right = nullNode;
			header = new RedBlackNode(negInf);
			if (header == nullptr)
			{
				cout<<"Memory fails.\n";
				exit(0);
			}
			header->left = header->right = nullNode;
		}
		RedBlackTree(const RedBlackTree &rhs)
		{

		}
		~RedBlackTree()
		{
			makeEmpty(header->right);
		}

		const ValueType & findMin() const
		{
			RedBlackNode *t = header;
			RedBlackNode *p = header;

			while(t != nullNode)
			{
				p = t;
				t = t->left;
			}			
			if (t == nullNode)
			{
				return p->value;
			}
			else
			{
				return t->value;
			}
		}

		const ValueType & findMax() const
		{
			RedBlackNode *t = header;
			RedBlackNode *p = header;

			while(t != nullNode)
			{
				p = t;
				t = t->right;
			}			
			if (t == nullNode)
			{
				return p->value;
			}
			else
			{
				return t->value;
			}
		}

		const ValueType & find(const comparable &x) const
		{
			return find(x,header);
		}

		bool contains(const comparable & x) const
		{

		}

		bool isEmpty() const
		{
			if (header->right == nullNode && header->left == nullNode)
			{
				return true;
			}
			else
			{
				return false;
			}
		}


		void printTree() const
		{
			printTree(header->right,0);
		}

		void makeEmpty()
		{

		}

		void insert(const comparable & x,const ValueType &y = ValueType())
		{
			//从根节点向下走
			current = parent = grandparent = header;
			nullNode->element = x;
			nullNode->value = y;

			while(current->element != x)
			{
				greatparent = grandparent;
				grandparent = parent;

				parent = current;

				current = x < current->element ? current->left : current->right;

				if (current->left->color == RED && current->right->color == RED)
				{
					handleReorient(x);
				}
			}
			//insert failed if it's already exists;
			if (current != nullNode)
			{
				return;
			}

			current = new RedBlackNode(x,y,nullNode,nullNode);
			if (current == nullptr)
			{
				cout<<"Memory fails.\n";
				exit(0);
			}

			if (x < parent->element)
			{
				parent->left = current;
			}
			else
			{	
				parent->right = current;
			}

			handleReorient(x);

		}

		void Remove(comparable x)
		{
			Remove(x,header);
		}

		const RedBlackTree & operator = (const RedBlackTree & rhs)
		{
			if (this != &rhs)
			{
				makeEmpty();
				header->right = clone(rhs.header->right);
			}
		}

	private:

		enum node_color {RED,BLACK};
		struct RedBlackNode
		{
			comparable element;
			ValueType value;
			RedBlackNode *left;
			RedBlackNode *right;
			node_color color;

			RedBlackNode(const comparable & theElement = comparable(), const ValueType & theValue = ValueType(),RedBlackNode *lt = nullptr, RedBlackNode *rt = nullptr,node_color _color = BLACK)
			{
				element = theElement;
				value = theValue;
				left = lt;
				right = rt;
				color = _color;
			}

		};

		RedBlackNode *header;
		RedBlackNode *nullNode;
		RedBlackNode *brother;
		RedBlackNode *current;
		RedBlackNode *parent;

		RedBlackNode *grandparent;
		RedBlackNode *greatparent;

		void reclaimMemory(RedBlackNode *t) const
		{

		}	

		void printTree(RedBlackNode *t,int depth) const
		{
			if (t != nullNode)
			{
				printTree(t->right,depth + 1);
				for (int i = 0; i < depth; ++i)
				{
					cout<<"   ";
				}
				if (t->color == RED)
				{
					cout<<t->element<<" RED"<<endl;
				}
				else
				{
					cout<<t->element<<" BLACK"<<endl;
				}
				printTree(t->left,depth + 1);
			}
		}
		const ValueType & find(const comparable &x,RedBlackNode * t) const
		{
			RedBlackNode *p;
			while(t != nullNode && t->element != x)
			{
				p = t;
				if (x < t->element)
				{
					t = t->left;
				}
				else
				{
					t = t->right;
				}
			}
			if (t == nullNode)
			{
				cout<<"Cannot find.\n";
				return p->value;
			}
			else
			{
				return t->value;
			}
		}

		void Remove(comparable item, RedBlackNode *& t)
		{
			t->color = RED;
			current = t->right;
			brother = t->left;
			parent = grandparent = greatparent = t;
			while(current != nullNode)
			{
				//分为2A和2B操作
				//2A操作
				if (current->left->color == BLACK && current->right->color == BLACK)
				{
					if (brother->left->color == BLACK && brother->right->color == BLACK)
					{
						parent->color = BLACK;
						current->color = RED;
						if (brother != nullNode)
						{
							brother->color = RED;
						}
					}
					else
					{
						Remove_case2A23();
					}
					if (current->element == item)
					{
						item = find_delete_item(item);
					}
					else
					{
						normalDown(item);
					}
				}
				else
				{
					if (current->element != item)
					{
						normalDown(item);
					}
					else
					{
						item = find_delete_item(item);
					}

					if (current == nullNode)
					{
						break;
					}

					if (current->color == BLACK)
					{
						Remove_case2B();
					}

					else if (current->element != item)
					{
						normalDown(item);
					}
					else
					{
						item = find_delete_item(item);
					}
				}
			}
			t->color = BLACK;
			t->right->color = BLACK;
		}

		RedBlackNode * RemoveNode(RedBlackNode *target, RedBlackNode * t)
		{
			RedBlackNode *origin = t;
			RedBlackNode *pp;
			while(t != target)
			{
				pp = t;
				if (target->element < t->element)
				{
					t = t->left;
				}
				else
				{
					t = t->right;
				}
			}
			if (t == origin)
			{
				RedBlackNode *temp;
				if (t->right != nullNode)
				{
					temp = t->right;
				}
				else
				{
					temp = t->left;
				}
				delete t;
				return temp;
			}
			if (pp->right == t)
			{
				if (t->right != nullNode)
				{
					pp->right = t->right;
				}
				else
				{
					pp->right = t->left;
				}
			}
			else
			{
				if (t->right != nullNode)
				{
					pp->left = t->right;
				}
				else
				{
					pp->left = t->left;
				}
			}
			delete t;
			return origin;

		}

		comparable find_delete_item(comparable item)
		{
			comparable temp;
			RedBlackNode *todelete;
			if (current->left == nullNode && current->right == nullNode)
			{
				if (parent->right == current)
				{
					parent->right = nullNode;
				}
				else
				{
					parent->left = nullNode;
				}
				delete current;
				current = nullNode;
				temp = item;
			}
			else
			{
				//不是叶子节点
				if (current->right != nullNode)
				{
					//从右边找一个最小的叶子节点放在current的位置上
					todelete = findNext(item,current->right);
					current->element = todelete->element;
					temp = todelete->element;
					if (todelete->color == RED)
					{
						//如果查找到的结点是红色的，可以直接删去。
						current->right = RemoveNode(todelete,current->right);
						current = nullNode;
					}
					else
					{
						grandparent = parent;
						parent = current;
						brother = parent->left;
						current = current->right;
					}
				}
				else
				{
					todelete = findNext(item,current->left);
					current->element = todelete->element;
					temp = todelete->element;
					if (todelete->color == RED)
					{
						current->left = RemoveNode(todelete,current->left);
						current = nullNode;
					}
					else
					{
						grandparent = parent;
						parent = current;
						brother = parent->right;
						current = current->left;

					}
				}
			}
			return temp;
		}

		RedBlackNode* findNext(comparable item, RedBlackNode *t)
		{
			RedBlackNode *p;
			while(t != nullNode && t->element != item)
			{
				p = t;
				if (item < t->element)
				{
					t = t->left;
				}
				else
				{
					t = t->right;
				}
			}
			if (t == nullNode)
			{
				return p;
			}
			else
			{
				return t;
			}
		}
		void Remove_case2A23()
		{
			//如果兄弟在右边
			if (parent->left == current)
			{
				if (brother->left->color == RED)
				{
					//2A2
					parent->color = BLACK;
					current->color = RED;
					rotatewithLeftChild(brother);
					if (grandparent->left == parent)
					{
						rotatewithRightChild(parent);
					}
					else
					{
						rotatewithRightChild(parent);
					}
				}
				else
				{
					//2A3
					current->color = RED;
					parent->color = BLACK;
					brother->color = RED;
					brother->right->color = BLACK;
					if (grandparent->right == parent)
					{
						rotatewithRightChild(parent);
					}
					else
					{
						rotatewithRightChild(parent);
					}
				}
			}
			//兄弟在左边
			else
			{
				if (brother->right->color == RED)
				{
					//2A2
					current->color = RED;
					parent->color = BLACK;
					rotatewithRightChild(brother);
					if (grandparent->left == parent)
					{
						rotatewithLeftChild(parent);
					}
					else
					{
						rotatewithLeftChild(parent);
					}
				}
				else
				{
					//2A3
					current->color = RED;
					parent->color = BLACK;
					brother->color = RED;
					brother->left->color = BLACK;

					if (grandparent->right == parent)
					{
						rotatewithLeftChild(parent);
					}
					else
					{
						rotatewithLeftChild(parent);
					}
				}
			}
		}

		void Remove_case2B()
		{
			brother->color = BLACK;
			parent->color = RED;
			if (parent->left == current)
			{
				if (grandparent->left == parent)
				{
					rotatewithRightChild(parent);
				}
				else
				{
					rotatewithRightChild(parent);
				}
				brother = parent->right;
			}
			else
			{
				if (grandparent->left == parent)
				{
					rotatewithLeftChild(parent);
				}
				else
				{
					rotatewithLeftChild(parent);
				}
				brother = parent->left;
			}
		}

		void normalDown(comparable item)
		{
			if (item < current->element)
			{
				grandparent = parent;
				parent = current;
				brother = parent->right;
				current = current->left;
			}
			else
			{
				grandparent = parent;
				parent = current;
				brother = parent->left;
				current = current->right;
			}
		}

		RedBlackNode * clone(RedBlackNode *t) const
		{
			if (t == t->left)
			{
				return nullNode;
			}
			else
			{
				return new RedBlackNode(t->element,clone(t->left),clone(t->right),t->color);
			}
		}

		void makeEmpty(RedBlackNode *t)
		{
			if (t != nullNode)
			{
				makeEmpty(t->left);
				makeEmpty(t->right);
				delete t;
			}
		}

		void handleReorient(const comparable &item)
		{
			current->color = RED;
			current->left->color = BLACK;
			current->right->color = BLACK;

			//have to rotate;
			if (parent->color == RED)
			{
				grandparent->color = RED;
				//10->对应LR型，01->RL型不平衡;
				//00对应RR，11对应LL
				if (item < grandparent->element != item < parent->element)
				{
					//double rotate
					parent = rotate(item,grandparent);
				}

				current = rotate(item,greatparent);
				current->color = BLACK;
			}

			header->right->color = BLACK; //keep root black
		}

		RedBlackNode * rotate (const comparable & item, RedBlackNode *theParent)
		{
			if (item < theParent->element)
			{
				if (item < theParent->left->element)
				{
					rotatewithLeftChild(theParent->left);//LL
				}
				else
				{
					rotatewithRightChild(theParent->left); //LR
				}
				return theParent->left;
			}
			else
			{
				if (item < theParent->right->element)
				{
					rotatewithLeftChild(theParent->right); //RL
				}
                else
                {
                    rotatewithRightChild(theParent->right); //RR
                }
				return theParent->right;
			}
		}

		void rotatewithLeftChild(RedBlackNode * &k2)
		{
			RedBlackNode *k1 = k2->left;
			k2->left = k1->right;
			k1->right = k2;
			k2 = k1;
		}

		void rotatewithRightChild(RedBlackNode * &k1)
		{
			RedBlackNode *k2 = k1->right;
			k1->right = k2->left;
			k2->left = k1;
			k1 = k2;
		}
	};
}
#endif /* RB_Tree_h */
