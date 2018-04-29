//
//  main.cpp
//  DennisCoin
//
//  Created by Dennis Hardy on 4/25/18.
//  Copyright © 2018 Dennis Hardy. All rights reserved.
//

#include <iostream>
#include <vector>
#include "Blockchain.hpp"
#include "Block.hpp"
#include "wallet.hpp"
#include "transaction.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    vector<transactionInput> none;
    Blockchain chain;
    
    wallet wallet1;
    wallet wallet2;
    wallet coinBase;
    
    cout <<"A's public key: " << wallet1.getPublicKey() << endl;
    cout <<"B's public key: " << wallet2.getPublicKey() << endl;
    
    transaction trans0(coinBase.getPublicKey(), wallet1.getPublicKey(), 100, none);
    chain.genesisTransaction = &trans0;
    chain.genesisTransaction->generateSignature(coinBase.privateKey);
    chain.genesisTransaction->setTransactionId("0");
    
    transactionOutput out(chain.genesisTransaction->reciever, chain.genesisTransaction->value, chain.genesisTransaction->transactionId);
    chain.genesisTransaction->outputs.push_back(out);
    chain.addUTXO(chain.genesisTransaction->outputs.at(0).getId(), chain.genesisTransaction->outputs.at(0));
    
    cout << "creating and mining genesis block" << endl;
    
    Block genesis("0");
    genesis.addTransaction(*chain.genesisTransaction, &chain);
    chain.addBlock(genesis);
    
    //testing
    
    Block block1(chain.getLastHash());
    cout << "Wallet 1s ballance is: " << wallet1.getBalance(chain) << endl;
    
    cout << "wallet1 trying to send 40 to wallet2" <<endl;
    block1.addTransaction(wallet1.sendFunds(wallet2.getPublicKey(), 40, &chain), &chain);
    chain.addBlock(block1);
    
    cout << "Wallet 1s ballance is: " << wallet1.getBalance(chain) << endl;
    cout << "Wallet 2s ballance is: " << wallet2.getBalance(chain) << endl;
    
    Block block2(chain.getLastHash());
    cout << "waller1 trying to send more funds than avaliable" <<endl;
    block2.addTransaction(wallet1.sendFunds(wallet2.getPublicKey(), 1000, &chain), &chain);
    chain.addBlock(block2);
    
    cout << "Wallet 1s ballance is: " << wallet1.getBalance(chain) << endl;
    cout << "Wallet 2s ballance is: " << wallet2.getBalance(chain) << endl;
    
    Block block3(chain.getLastHash());
    cout << "wallet2 trying to send 20 to wallet1" <<endl;
    block3.addTransaction(wallet2.sendFunds(wallet1.getPublicKey(), 20, &chain), &chain);
    chain.addBlock(block3);
    
    cout << "Wallet 1s ballance is: " << wallet1.getBalance(chain) << endl;
    cout << "Wallet 2s ballance is: " << wallet2.getBalance(chain) << endl;
    
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
    chain.fullPrint();
    
    cout << "verified: " << test.verifySignature() <<endl;*/
    cout <<endl;
    chain.isChainValid();
    return 0;
}

