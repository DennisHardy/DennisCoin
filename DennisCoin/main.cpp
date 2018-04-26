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
//#include "BlockChain.hpp"

int main(int argc, const char * argv[]) {
    vector<Block> chain;
    
    chain.push_back(Block("Hello I'm the first block", "0"));
    chain.push_back(Block("Yo, I'm the second block", chain.at(chain.size()-1).hash));
    chain.push_back(Block("Howdy, I'm the third block", chain.at(chain.size()-1).hash));
    
    
    for (int i = 0 ; i < chain.size(); i++) {
        cout << "Hash for Block " << i << ": " << chain.at(i).hash << "\t" << endl;
    }
    return 0;
}
