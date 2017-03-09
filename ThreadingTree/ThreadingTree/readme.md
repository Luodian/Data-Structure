进度

1. 线索化查找先序中序后继结点貌似有错



11-14 23:21分 fixed constructor according level完成了BinaryTree的主体代码

11-15 17:14 完成了包括输出部分的所有代码，有时间再写显示的部分。

总结：

1. 需要系统学习指针管理的具体操作，这次在指针上浪费了很多时间，以后和树有关的操作离不开指针，必须的结合C++的特性系统学习指针。

2. 了解关于类的析构函数的知识，原因如上

3. 二叉树的三个结论如下，不知正确如否

   1. ```C++
      //用中序线索化二叉树求结点的先序后继
      //如果左子树不为空，返回左儿子即可
      //如果左子树空，右子树非空，返回右儿子
      //如果左右子树都空，则找到右线索中第一个有右儿子的的结点，返回这个右儿子。
      ```

   2. ```C++
      //用中序线索化二叉树求结点的中序后继
      //右子树非空则右子树中的最左结点就是中序后继
      //右子树为空则右线索就是中序后继
      ```

   3. ```Cpp
      //用中序线索二叉树求结点的后序后继
      //记录p的父结点father
      //如果father没有右子树(指r->rtag == thread)或者是r->right != p,此时的r为p的后序后继
      //如果father有右子树，则r右子树进行后序遍历的第一个结点就是后序后继
      ```

   4. 找父亲结点函数的实现粗糙的不敢想象，但是考虑到已经很久没睡觉了，真的想不出太好的办法，注意这里每次找后序后继，father相当于全局变量，每次需要清零。

      ```cpp
      ThreadingNode *father = nullptr;
      void FindParent(ThreadingNode *p,ThreadingNode *root)
      {
          ThreadingNode *r = root;
          if ((r->Rtag == Link && r->right == p) ||(r->Ltag == Link && r->left == p))
          {
              father = r;
          }
          if (r != nullptr && r->Ltag == Link)
          {
              FindParent(p,r->left);
          }
          r = root;
          if (r != nullptr && r->Rtag == Link)
          {
              FindParent(p,r->right);
          }
      }
      ```
      ​