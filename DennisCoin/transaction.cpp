//
//  transaction.cpp
//  DennisCoin
//
//  Created by Dennis Hardy on 4/25/18.
//  Copyright © 2018 Dennis Hardy. All rights reserved.
//

#include "transaction.hpp"
#include "Blockchain.hpp"

transaction::transaction(string from, string to, float amount, vector<transactionInput> input){
    sender = from;
    reciever = to;
    value = amount;
    inputs = input;
    
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

transactionOutput::transactionOutput(string reciever, float amount, string parentId){
    recipient = reciever;
    value = amount;
    parentTransactionId = parentId;
    
}
transactionInput::transactionInput(string OutputId){
    TXOutputId = OutputId;
}

bool transactionOutput::isMine(string myKey){
    return (myKey==recipient);
}
bool transaction::processTransaction(){
    if(!verifySignature()){
        cout << "Could Not verify signature" << endl;
        return false;
    }
    
    for(transactionInput i : inputs){
        //todo
    }
}

void transactionInput::setUTXO(transactionOutput UTXOin){
    UTXO.setId(UTXOin.getId());
    
}

void transactionOutput::setId(string idIn){
    id = idIn;
}
void transactionOutput::setRecipient(string recipientIn){
    recipient = recipientIn;
}
void transactionOutput::setValue(float valueIn){
    value = valueIn;
}
void transactionOutput::setParent(string parentIn){
    parentTransactionId = parentIn;
}
string transactionOutput::getId(){
    return id;
}
string transactionOutput::getRecipient(){
    return recipient;
}
float transactionOutput::getValue(){
    return value;
}
string transactionOutput::getParent(){
    return parentTransactionId;
}
string transactionInput::getTXOutputId(){
    return TXOutputId;
}
