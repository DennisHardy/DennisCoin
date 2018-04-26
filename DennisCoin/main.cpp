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
#include "wallet.hpp"
#include "transaction.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    Blockchain chain;
    
    wallet wallet1;
    wallet wallet2;
    
    cout <<"A's public key: " << wallet1.getPublicKey() << endl;
    cout <<"B's public key: " << wallet2.getPublicKey() << endl;
    
    vector<transactionInput> inputs;
    
    transaction test(wallet1.getPublicKey(), wallet2.getPublicKey(), 5.00, inputs);
    
    test.generateSignature(wallet1.privateKey);
    /*chain.addBlock(Block("Hello I'm the first block", "0"));
    cout << "trying to mine 0th block" << endl;
    chain.end()->mineBlock(dif);
    
    chain.addBlock(Block("Yo, I'm the second block", chain.getLastHash()));
    cout << "trying to mine First block" << endl;
    chain.end()->mineBlock(dif);
    
    chain.addBlock(Block("Howdy, I'm the third block", chain.getLastHash()));
    cout << "trying to mine second block" << endl;
    chain.end()->mineBlock(dif);
    
    cout << endl;
    chain.fullPrint();*/
    
    cout << "verified: " << test.verifySignature();
    
    return 0;
}

