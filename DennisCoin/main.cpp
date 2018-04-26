//
//  main.cpp
//  DennisCoin
//
//  Created by Dennis Hardy on 4/25/18.
//  Copyright © 2018 Dennis Hardy. All rights reserved.
//

#include <iostream>
#include <vector>
#include "Block.hpp"
#include "Blockchain.hpp"


int main(int argc, const char * argv[]) {
    Blockchain chain;
    
    chain.addBlock(Block("Hello I'm the first block", "0"));
    cout << "trying to mine 0th block" << endl;
    chain.end()->mineBlock(dif);
    
    chain.addBlock(Block("Yo, I'm the second block", chain.getLastHash()));
    cout << "trying to mine First block" << endl;
    chain.end()->mineBlock(dif);
    
    chain.addBlock(Block("Howdy, I'm the third block", chain.getLastHash()));
    cout << "trying to mine second block" << endl;
    chain.end()->mineBlock(dif);
    
    cout << endl;
    chain.print();

    return 0;
}

