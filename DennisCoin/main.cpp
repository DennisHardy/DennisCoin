//
//  main.cpp
//  DennisCoin
//
//  Created by Dennis Hardy on 4/25/18.
//  Copyright © 2018 Dennis Hardy. All rights reserved.
//

#include <iostream>
#include "Block.hpp"


int main(int argc, const char * argv[]) {
   
    Block genesisBlock("Hello I'm the first block", "0");
    cout << "Hash for Block 1: " << genesisBlock.hash << endl;
    
    Block secondBlock("Yo, I'm the second block", genesisBlock.hash);
    cout << "Hash for Block 3: " << secondBlock.hash << endl;
    
    Block thirdBlock("Howdy, I'm the third block", secondBlock.hash);
    cout << "Hash for Block 3: " << thirdBlock.hash << endl;
    
    return 0;
}
