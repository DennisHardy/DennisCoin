//
//  Blockchain.hpp
//  DennisCoin
//
//  Created by Dennis Hardy on 4/25/18.
//  Copyright © 2018 Dennis Hardy. All rights reserved.
//

#ifndef Blockchain_hpp
#define Blockchain_hpp

#include <stdio.h>
#include <vector>
#include "Block.hpp"

class Blockchain{
public:
    Blockchain();
    void print();
    void addBlock(Block newBlock);
    Block at(int i);
    int size();
    string getLastHash();
    bool isChainValid(); //checks if hashes are valid
private:
    vector<Block> chain;

};

#endif /* Blockchain_hpp */
