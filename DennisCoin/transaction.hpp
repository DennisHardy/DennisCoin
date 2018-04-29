//
//  transaction.hpp
//  DennisCoin
//
//  Created by Dennis Hardy on 4/25/18.
//  Copyright © 2018 Dennis Hardy. All rights reserved.
//

#ifndef transaction_hpp
#define transaction_hpp

#include <stdio.h>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include "ecc.h"
#include <vector>
#include "sha256.h"
#include "wallet.hpp"
#include "Blockchain.hpp"

using namespace std;
class Blockchain;


class transactionOutput{
public:
    transactionOutput(string recipent, float value, string parentId);
    transactionOutput(){};
    bool isMine(string myKey);
    void setId(string idIn);
    void setRecipient(string recipientIn);
    void setValue(float valueIn);
    void setParent(string parentIn);
    string getId();
    string getRecipient();
    float getValue();
    string getParent();
    
private:
    string id;
    string recipient;
    float value;
    string parentTransactionId;
    
};

class transactionInput{
public:
    //transactionInput(string OutputId);
    void setUTXO(transactionOutput UTXOin);
    transactionInput(string OutputId, transactionOutput output);
    string getTXOutputId();
    float getUTXOValue();
    
private:
    string TXOutputId;
    transactionOutput UTXO;
};


class transaction{
public:
    transaction(string from, string to, float ammount, vector<transactionInput> inputs);
    transaction();
    void generateSignature(privatekey_t privateKey);
    bool verifySignature();
    publickey_t fromPub;
    bool processTransaction(Blockchain *chain);
    float getInputsValue();
    float getOutputsValue();
    string getTransactionId();
    transactionOutput getOutputAt(int i);
    void setTransactionId(string idIn);
//private:
    string transactionId; //also hash of transaction
    string sender;
    string reciever;
    float value;
    signature_t signature;
    
    vector<transactionInput> inputs;
    vector<transactionOutput> outputs;
    int sequence;
    
    string calculateHash();
};
#endif /* transaction_hpp */
