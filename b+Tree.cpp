//
//  b+Tree.cpp
//  b+
//
//  Created by 谢莎 on 2022/10/15.
//

#include "b+Tree.hpp"
using namespace std;
bPlusTree::bPlusTree(){
    root=NULL;
}
int bPlusTree::findPos(bPlusNode *node, int key){
    int pos(0);
    for(int i = 0; i < node->num ; i++){
        if(key >= node->k[i])pos++;
        else return pos;
    }
    return pos;
}

int bPlusTree::getMin(){
    bPlusNode *node=root;
    int min(-1);
    while(!node->is_leaf){
        node=node->p[0];
    }
    min=node->k[0];
    return min;
}


int bPlusTree::insertkey(bPlusNode *node, int target){
    int pos(node->num);
    for(int i = node->num-1;i>=0;i--){
        if(target<node->k[i])pos--;
    }
    for(int i = node->num-1;i >= pos;i--){
        node->k[i+1]=node->k[i];
    }
    node->k[pos]=target;
    node->num++;
    return pos;
}

void bPlusTree::insertPoint(bPlusNode *node,bPlusNode *newnode,int target){
    int pos(0);
    bPlusNode *parent=node->parent;
    pos=insertkey(parent, target);//parent->k[pos]=target
    for(int i = pos+1 ;i < parent->num ; i++ ){
        parent->p[i+1]=parent->p[i];
    }
    parent->p[1+pos]=newnode;
    if(parent->num==M){//如果指针满了先分裂，然后再调用插入指针。
        bPlusNode *newpoint=new bPlusNode;
        newpoint->is_leaf=false;
        for(int i = 0 ; i < (M+1)/2;i++){
            newpoint->k[i]=parent->k[i+M/2];
            newpoint->p[i]=parent->p[i+M/2+1];
            newpoint->p[i]->parent = newpoint;
            newpoint->num++;
            parent->num--;
        }
        newpoint->parent=parent->parent;
        int nextk=newpoint->k[0];
        for(int i = 0;i < newpoint->num-1 ; i++){
            newpoint->k[i]=newpoint->k[i+1];
        }
        newpoint->num--;
        if(parent->parent==NULL){
            bPlusNode *newparent=new bPlusNode;;
            newparent->is_leaf=false;
            parent->parent=newparent;
            newpoint->parent=newparent;
            newparent->k[0]=nextk;
            newparent->p[0]=parent;
            newparent->p[1]=newpoint;
            newparent->num++;
            root=newparent;
        }
        else{
            insertPoint(parent,newpoint,nextk);
        }
    }

}


void bPlusTree::split(int target,bPlusNode* node){
    bPlusNode *parent=node->parent;
    bPlusNode *newchild=new bPlusNode;;
    insertkey(node, target);
    for(int i = 0 ; i < ((M+1)/2) ; i++){
        newchild->k[i]=node->k[i+M/2];
        newchild->num++;
        node->num--;
    }
    newchild->next=node->next;
    if(node->next)node->next->prev=newchild;
    node->next=newchild;
    newchild->prev=node;
    if(parent==NULL){
        parent=new bPlusNode;;
        parent->is_leaf=false;
        parent->k[0]=node->k[M/2];
        parent->num++;
        parent->p[0]=node;
        parent->p[1]=newchild;
        node->parent=parent;
        newchild->parent=parent;
        root=parent;
    }
    else{
        newchild->parent=parent;
        insertPoint(node,newchild,node->k[M/2]);
    }
    
}

void bPlusTree::insert(int target){
    if(root==NULL){
        bPlusNode *node=new bPlusNode;;
        node->k[0]=target;
        node->num++;
        node->is_leaf=true;
        root=node;
    }
    else{
        bPlusNode *node=root;
        while(!node->is_leaf){
            int pos=findPos(node, target);
            node=node->p[pos];
        }
        if(node->num < M-1){
            insertkey(node, target);
        }
        else {
            split(target,node);
        }
    }
    
    
}

void bPlusTree::pt_bPlusTree(bPlusNode *node){
    queue<bPlusNode*> q;
    q.push(node);
    int k(1);
    while(!q.empty()){
        int n(0);
        for(int t = 0 ; t < k ; t++){
            bPlusNode* temp=q.front();
            q.pop();
            printf("[");
            for(int i = 0 ; i < temp->num ; i++){
                printf("%d ",temp->k[i]);
            }
            printf("]");
            for(int i = 0 ; i < temp->num+1; i++){
                if(NULL!=temp->p[i]){
                    q.push(temp->p[i]);
                    n++;
                }
            }
        }
        printf("\n");
        k=n;
    }
    return ;
}

bPlusNode* bPlusTree::find(int target){
    bPlusNode* node = root;
    while(!node->is_leaf){
        int pos=findPos(node, target);
        node=node->p[pos];
    }
    for(int i  = 0 ; i < node->num ; i++){
        if(target==node->k[i])return node;
    }
    return NULL;
}

bPlusNode* bPlusTree::findInternal(int target){
    bPlusNode* node = root;
    
    while(1){
        int pos=findPos(node, target);
        if(pos-1>=0 && node->k[pos-1]==target)return node;
        node=node->p[pos];
        if(node->is_leaf)return NULL;
    }
    return NULL;
}

void  bPlusTree::del_key(bPlusNode *leafNode,int target){
    int pos=findPos(leafNode , target);
    pos--;
    for(int i = pos ;i < leafNode->num-1 ; i++){
        leafNode->k[i]=leafNode->k[i+1];
    }
    leafNode->num--;
}

void bPlusTree::del_direct(bPlusNode *node, int target){
    if(node->k[0]==target){
        bPlusNode *internalNode = findInternal(target);
        int ppos=findPos(internalNode, target);
        ppos--;
        internalNode->k[ppos]=node->k[1];
    }
    del_key(node, target);
}

void bPlusTree::borrow_fromPrev(bPlusNode *leafNode, int target){
    bPlusNode *prev=leafNode->prev;
    del_key(leafNode , target);
    
}

void bPlusTree::borrow_fromNext(bPlusNode *leafNode, int target){
    bPlusNode *next=leafNode->next;
    del_key(leafNode , target);
    
}


int bPlusTree::del(int target){
    bPlusNode *leafNode = find(target);
    int fillFactor=ceil(M/2)-1;
    if(NULL == leafNode ) return -1;
    if(leafNode->num > fillFactor){
        del_direct(leafNode, target);
    }
    else{
        if(leafNode->next && leafNode->next->num > fillFactor)borrow_fromNext(leafNode, target);
        else if(leafNode->prev && leafNode->prev->num > fillFactor)borrow_fromPrev(leafNode, target);
    }
    return 1;
    
}
