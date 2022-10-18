//
//  bPlusNode.cpp
//  b+
//
//  Created by 谢莎 on 2022/10/16.
//
#include "bPlusNode.hpp"
bPlusNode::bPlusNode(){
    num=0;
    parent=NULL;
    for(int i = 0 ; i < M+1 ; i++){
        p[i]=NULL;
    }
    for(int i = 0 ; i < M ; i++){
        k[i]=0;
    }
    is_leaf=true;
    prev=NULL;
    next=NULL;
}
