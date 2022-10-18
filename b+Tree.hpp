//
//  b+Tree.hpp
//  b+
//
//  Created by 谢莎 on 2022/10/15.
//

#ifndef b_Tree_hpp
#define b_Tree_hpp
#include <queue>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#endif /* b_Tree_hpp */
#include "struct.cpp"
#include "bPlusNode.hpp"
#include <math.h>
class bPlusTree{
    int  insertkey(bPlusNode* node,int target);
    void  insertPoint(bPlusNode* node,bPlusNode* newnode,int target);
    int findPos(bPlusNode* node ,int key);
    void del_key(bPlusNode *leafNode,int target);
    void del_direct(bPlusNode *node , int target);
    void borrow_fromPrev(bPlusNode *leafNode,int target);
    void borrow_fromNext(bPlusNode *leafNode,int target);
public:
    int getMin();
    virtual bPlusNode *findInternal(int target);
    bPlusNode *root;
    bPlusTree();
    virtual void insert(int target);
    virtual void split(int target,bPlusNode* node);
    virtual void pt_bPlusTree(bPlusNode* node);
    virtual bPlusNode *find(int target);
    virtual int del(int target);
private:
};

