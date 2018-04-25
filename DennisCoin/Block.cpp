//
//  Block.cpp
//  DennisCoin
//
//  Created by Dennis Hardy on 4/25/18.
//  Copyright © 2018 Dennis Hardy. All rights reserved.
//

#include "Block.hpp"
#include "sha256.h"

Block::Block(string dataIn, string prevHashIn){
    data = dataIn; 
    previousHash = prevHashIn;
    timestamp = time(nullptr);
    hash = CalculateHash();
}

string Block::CalculateHash(){
    stringstream ss;
    ss << previousHash << timestamp << data;
    string calculatedhash = sha256(ss.str());
    
    return calculatedhash;
}
