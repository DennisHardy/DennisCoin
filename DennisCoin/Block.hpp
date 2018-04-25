//
//  Block.hpp
//  DennisCoin
//
//  Created by Dennis Hardy on 4/25/18.
//  Copyright © 2018 Dennis Hardy. All rights reserved.
//

#ifndef Block_hpp
#define Block_hpp

#include <stdio.h>
#include <string>
#include <sstream>
#include <iostream>
#include "sha256.h"

using namespace std;

class Block {
public:
    string hash;
    string previousHash;
    Block(string data, string prevHash);
    string CalculateHash();
    
private:
    string data; //will be a simple message
    time_t timestamp; //time block
    
};
#endif /* Block_hpp */
