//
//  Block.cpp
//  DennisCoin
//
//  Created by Dennis Hardy on 4/25/18.
//  Copyright © 2018 Dennis Hardy. All rights reserved.
//

#include "Block.hpp"
#include "sha256.h"

Block::Block(string dataIn, string prevHashIn){ //constructor
    data = dataIn; 
    previousHash = prevHashIn;
    timestamp = time(nullptr);
    hash = CalculateHash();

}

Block::Block(){}//empty constructor


string Block::CalculateHash(){ //calculates hash of block
    stringstream ss;
    ss << previousHash << timestamp << nonce << data;
    //cout << ss.str();
    string calculatedhash = sha256(ss.str());
    
    return calculatedhash;
}

void Block::mineBlock(int difficulty){
    stringstream targetSS;
    for (int i = 0; i< difficulty; i++) {
        targetSS << '0';
    }
    string target = targetSS.str();
    
    while (hash.substr(0,difficulty)!=target) {
        this->nonce++;
        this->hash = CalculateHash();
        //cout << hash << endl;
    }
    cout << "Mined Block! :" << this->hash << endl;
    
    return;
}
string Block::getData(){
    return data;
}
time_t Block::getTimestamp(){
    return timestamp;
}
int Block::getNonce(){
    return nonce;
}
