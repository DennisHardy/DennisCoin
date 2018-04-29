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
    newBlock.mineBlock(dif);
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

void Blockchain::fullPrint(){ //prints hashes of each chain block and validity
    
    bool valid = isChainValid(); //print validity of chain
    if (valid) {
        cout << "chain is valid" << endl;
    }
    else{
        cout << "invalid chain" << endl;
    }
    
    //loop through block print hashes
    for (int i = 0 ; i < chain.size(); i++) {
        cout << "Block " << i << ": " << endl;
        cout << "\t Hash: \t\t" << chain.at(i).hash << endl;
        cout << "\t PrevHash: \t" << chain.at(i).previousHash << endl;
        //cout << "\t data: \t\t" << chain.at(i).getData() << endl;
        cout << "\t time: \t\t" << chain.at(i).getTimestamp() << endl;
        cout << "\t nonce: \t" << chain.at(i).getNonce() << endl;
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
    
    unordered_map<string, transactionOutput> tempUTXOs;
    tempUTXOs.insert({genesisTransaction->outputs.at(0).getId(), genesisTransaction->outputs.at(0)});
    
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
        transactionOutput tempOutput;
        
        //loop through all transactions
        for (int t=0; t<currentBlock->getNumTransactions(); t++) {
            transaction currentTransaction = currentBlock->getTransactionAt(t);
            
            if (!currentTransaction.verifySignature()) {
                cout << "Invalid signature on transaction: " << "t" << endl;
                return false;
            }
            if (currentTransaction.getInputsValue() != currentTransaction.getOutputsValue()) {
                cout << "Inputs not equal to outputs at transaction: " << "t" << endl;
                return false;
            }
            
            for (transactionInput input : currentTransaction.inputs) {
                unordered_map<string, transactionOutput>::const_iterator temp = tempUTXOs.find(input.getTXOutputId());
                
                if (temp == tempUTXOs.end()) {
                    cout << "input to transaction: " << t << "could not be found" <<endl;
                    return false;
                }
                transactionOutput tempOutput = temp->second;
                
                if (input.getUTXOValue() != tempOutput.getValue()) {
                    cout << "refernced input transaction: " << t << "is not valid" << endl;
                    return false;
                }
                tempUTXOs.erase(temp);
            }
            for (transactionOutput o:currentTransaction.outputs) {
                tempUTXOs.insert({o.getId(), o});
            }
            if(currentTransaction.getOutputAt(0).getRecipient() !=currentTransaction.reciever){
                cout << "Transaction: " << t << "recipient output not who it should be" << endl;
                return false;
            }
            if (currentTransaction.getOutputAt(1).getRecipient() != currentTransaction.sender) {
                cout << "Transaction: " << t << "recipient sender not who it should be" << endl;
                return false;
            }
            
        }
        
    }
    cout << "Chain is valid" <<endl <<endl;
    return true;
}

transactionOutput Blockchain::getUTXO(string outputID){
    return UTXOs.find(outputID)->second;
}

void Blockchain::addUTXO(string outputId, transactionOutput output){
    UTXOs.insert({outputId, output});
    return;
}

void Blockchain::removeUTXO(string outputId){
    UTXOs.erase(outputId);
    return;
}
unordered_map<string, transactionOutput> Blockchain::getAllUTXOs(){
    return UTXOs;
}
