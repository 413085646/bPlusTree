//
//  main.cpp
//  b+
//
//  Created by 谢莎 on 2022/10/15.
//

#include <iostream>
#include "b+Tree.hpp"
using namespace std;
int main(int argc, const char * argv[]) {
    bPlusTree bp=bPlusTree();
    for(int i = 1 ; i <= 5;i++){
        bp.insert(i);
    }
    bp.pt_bPlusTree(bp.root);
    bp.del(4);
    bp.pt_bPlusTree(bp.root);

    
    return 1;
}
