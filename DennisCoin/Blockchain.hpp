//
//  Blockchain.hpp
//  DennisCoin
//
//  Created by Dennis Hardy on 4/25/18.
//  Copyright © 2018 Dennis Hardy. All rights reserved.
//

#ifndef Blockchain_hpp
#define Blockchain_hpp
#define dif 4

#include <stdio.h>
#include <vector>
#include "Block.hpp"
#include <unordered_map>
#include "transaction.hpp"

class transactionOutput;
class Block;
class transaction;

using namespace std;

class Blockchain{
public:
    Blockchain(); //constructor
    void print(); //prints hash values of chain
    void fullPrint();
    void addBlock(Block newBlock); //adds block to the chain
    Block at(int i); //returns block at index of chain
    Block* end(); //returns last block in chain
    int size(); //returns length of chain (# of blocks)
    string getLastHash(); //returns the hash of the last block of the chain
    bool isChainValid(); //checks if hashes are valid
    static int difficulty;
    transactionOutput getUTXO(string outputID);
    void addUTXO(string outputId, transactionOutput output);
    void removeUTXO(string outputId);
    unordered_map<string, transactionOutput> getAllUTXOs();
    transaction *genesisTransaction;
private:
    vector<Block> chain; //vector of blocks in the chains
    unordered_map<string, transactionOutput> UTXOs;
};

#endif /* Blockchain_hpp */
