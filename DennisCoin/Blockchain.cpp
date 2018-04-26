//
//  Blockchain.cpp
//  DennisCoin
//
//  Created by Dennis Hardy on 4/25/18.
//  Copyright © 2018 Dennis Hardy. All rights reserved.
//

#include "Blockchain.hpp"

Blockchain::Blockchain(){
    
}

void Blockchain::addBlock(Block newBlock){
    chain.push_back(newBlock);
}

void Blockchain::print(){
    bool valid = isChainValid();
    if (valid) {
        cout << "chain is valid" << endl;
    }
    else{
        cout << "invalid chain" << endl;
    }
    for (int i = 0 ; i < chain.size(); i++) {
        cout << "Hash for Block " << i << ": " << chain.at(i).hash << "\t" /* << chain.at(i).previousHash */ << endl;
    }
}

Block Blockchain::at(int i){
    return chain.at(i);
}
int Blockchain::size(){
    return int(chain.size());
}
string Blockchain::getLastHash(){
    return chain.at(chain.size()-1).hash;
}

bool Blockchain::isChainValid(){
    Block currentBlock;
    Block lastBlock;
    
    //loop through all blocks
    for (int i=1; i<chain.size(); i++) {
        currentBlock = chain.at(i);
        lastBlock = chain.at(i-1);
        
        //compare listed hash with own hash calculation
        if(currentBlock.hash != currentBlock.CalculateHash()){
            cout << "Hash not equal at block " << i << endl;
            return false;
        }
        
        //compare previous hash with listed previous hash
        if (currentBlock.previousHash != lastBlock.hash) {
            cout << "Previous hash not equal at block" << i << endl;
            return false;
        }
    }
    return true;
}
