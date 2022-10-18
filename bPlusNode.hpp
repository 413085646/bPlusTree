//
//  bPlusNode.hpp
//  b+
//
//  Created by 谢莎 on 2022/10/16.
//
#define M 3
#ifndef bPlusNode_hpp
#define bPlusNode_hpp

#include <stdio.h>

#endif /* bPlusNode_hpp */
class bPlusNode{
public:
    bPlusNode* p[M+1];
    bPlusNode* parent;
    int k[M];
    bool is_leaf;
    int num;
    struct bPlusNode* next;
    struct bPlusNode* prev;
    bPlusNode();
    ~bPlusNode();
};
