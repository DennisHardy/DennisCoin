//
//  Block.cpp
//  DennisCoin
//
//  Created by Dennis Hardy on 4/25/18.
//  Copyright © 2018 Dennis Hardy. All rights reserved.
//

#include "Block.hpp"
#include "sha256.h"

/*Block::Block(string dataIn, string prevHashIn){ //constructor
    data = dataIn; 
    previousHash = prevHashIn;
    timestamp = time(nullptr);
    hash = CalculateHash();

}*/

Block::Block(string prevHashIn){
    previousHash = prevHashIn;
    timestamp=time(nullptr);
    hash = CalculateHash();
}

Block::Block(){}//empty constructor


string Block::CalculateHash(){ //calculates hash of block
    stringstream ss;
    //ss << previousHash << timestamp << nonce << data;
    ss << previousHash << timestamp << nonce << merkleRoot;
    //cout << ss.str();
    string calculatedhash = sha256(ss.str());
    
    return calculatedhash;
}

void Block::mineBlock(int difficulty){
    merkleRoot = getMerkleRoot(transactions);
    
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
    cout << "Mined Block!!! :" << this->hash << endl <<endl;
    
    return;
}

bool Block::addTransaction(transaction addMe, Blockchain* chain){
    
    if (addMe.getTransactionId() == "") return false;
    if (previousHash != "0") {
        if (addMe.processTransaction(chain) != true) {
            cout << "could not process transaction, discarding"<<endl;
            return false;
        }
        transactions.push_back(addMe);
        cout << "Transaction added to block"<<endl;
    }
    return true;
}

/*string Block::getData(){
    return data;
}*/

time_t Block::getTimestamp(){
    return timestamp;
}
int Block::getNonce(){
    return nonce;
}
int Block::getNumTransactions(){
    return transactions.size();
}
transaction Block::getTransactionAt(int i){
    return transactions.at(i);
}
