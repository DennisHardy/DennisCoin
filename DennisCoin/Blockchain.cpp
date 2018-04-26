//
//  Blockchain.cpp
//  DennisCoin
//
//  Created by Dennis Hardy on 4/25/18.
//  Copyright © 2018 Dennis Hardy. All rights reserved.
//

#include "Blockchain.hpp"

int Blockchain::difficulty;

Blockchain::Blockchain(){ //constructor
    difficulty=dif;
}

void Blockchain::addBlock(Block newBlock){ //adds block to chain
    chain.push_back(newBlock);
}

void Blockchain::print(){ //prints hashes of each chain block and validity
    
    bool valid = isChainValid(); //print validity of chain
    if (valid) {
        cout << "chain is valid" << endl;
    }
    else{
        cout << "invalid chain" << endl;
    }
    
    //loop through block print hashes
    for (int i = 0 ; i < chain.size(); i++) {
        cout << "Hash for Block " << i << ": " << chain.at(i).hash << "\t" /* << chain.at(i).previousHash */ << endl;
    }
}

Block Blockchain::at(int i){ //returns block at index
    return chain.at(i);
}
int Blockchain::size(){ //returns number of blocks in chain
    return int(chain.size());
}
string Blockchain::getLastHash(){ //returns hash of last block in the chain
    return chain.at(chain.size()-1).hash;
}

Block* Blockchain::end(){
    return &chain.at(chain.size()-1);
}

bool Blockchain::isChainValid(){ //checks validity of chain
    Block* currentBlock;
    Block* lastBlock;
    
    stringstream targetSS;
    for (int i = 0; i< difficulty; i++) {
        targetSS << '0';
    }
    string targetHash = targetSS.str();
    
    //loop through all blocks
    for (int i=1; i<chain.size(); i++) {
        currentBlock = &chain.at(i);
        lastBlock = &chain.at(i-1);
        
        //compare listed hash with own hash calculation
        if(currentBlock->hash != currentBlock->CalculateHash()){
            cout << "Hash not equal at block " << i << endl;
            return false;
        }
        
        //compare previous hash with listed previous hash
        if (currentBlock->previousHash != lastBlock->hash) {
            cout << "Previous hash not equal at block" << i << endl;
            return false;
        }
        //check that hash is solved
        if (currentBlock->hash.substr(0,dif) != targetHash) {
            cout << "Block " << i << " has not been mined (incorrect hash)" << endl;
            return false;
        }
    }
    return true;
}
