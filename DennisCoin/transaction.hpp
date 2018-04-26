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

using namespace std;

class transactionInput{
public:
    transactionInput();
};

class transactionOutput{
public:
    transactionOutput();
};

class transaction{
public:
    transaction(string from, string to, float ammount, vector<transactionInput> inputs);
    void generateSignature(privatekey_t privateKey);
    bool verifySignature();
    publickey_t fromPub;
private:
    string transactionId; //also hash of transaction
    string sender;
    string reciever;
    float value;
    signature_t signature;
    
    vector<transactionInput> input;
    vector<transactionOutput> outputs;
    int sequence;
    
    string calculateHash();
};
#endif /* transaction_hpp */
