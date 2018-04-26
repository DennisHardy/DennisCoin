//
//  transaction.cpp
//  DennisCoin
//
//  Created by Dennis Hardy on 4/25/18.
//  Copyright © 2018 Dennis Hardy. All rights reserved.
//

#include "transaction.hpp"


transaction::transaction(string from, string to, float amount, vector<transactionInput> inputs){
    sender = from;
    reciever = to;
    value = amount;
    input = inputs;
    
    stringstream buffer;
    for (int i = 0; i<ECC_BYTES+1; i++) {
        fromPub[i] = stoul(from.substr(2*i,2), nullptr, 16);
    }
}

string transaction::calculateHash(){
    sequence++;
    stringstream ss;
    ss << sender << reciever << value << sequence;
    //cout << ss.str();
    string calculatedhash = sha256(ss.str());
    
    return calculatedhash;
}

void transaction::generateSignature(privatekey_t privateKey){
    stringstream buffer;
    buffer <<sender << reciever << value;
    string data = buffer.str();
    const uint8_t hash[ECC_BYTES] = "data";
    
    ecdsa_sign(privateKey, hash, signature);
}

bool transaction::verifySignature(){
    stringstream buffer;
    buffer <<sender << reciever << value;
    string data = buffer.str();
    const uint8_t hash[ECC_BYTES] = "data";
    
    return ecdsa_verify(fromPub, hash, signature);
}
