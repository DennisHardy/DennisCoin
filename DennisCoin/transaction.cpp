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
    transactionId = calculateHash();
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
    uint8_t hash[ECC_BYTES]="";
    string temp = sha256(data);
    
    for (int i = 0; i<ECC_BYTES; i++) {
        string buffer = "0x"+temp.substr(2*i, 2);
        hash[i] = stoi(buffer, nullptr, 16);
    }
    ecdsa_sign(privateKey, hash, signature);
}

bool transaction::verifySignature(){
    stringstream buffer;
    buffer <<sender << reciever << value;
    string data = buffer.str();
    uint8_t hash[ECC_BYTES]="";
    string temp = sha256(data);
    
    for (int i = 0; i<ECC_BYTES; i++) {
        string buffer = "0x"+temp.substr(2*i, 2);
        hash[i] = stoi(buffer, nullptr, 16);
    }
    
    return ecdsa_verify(fromPub, hash, signature);
}

transactionOutput::transactionOutput(string reciever, float amount, string parentId){
    recipient = reciever;
    value = amount;
    parentTransactionId = parentId;
    id = sha256( recipient+ to_string(value) +parentTransactionId);
    
}
/*transactionInput::transactionInput(string OutputId){
    TXOutputId = OutputId;
}*/
transactionInput::transactionInput(string OutputId, transactionOutput output){
    TXOutputId = OutputId;
    UTXO = output;
}
bool transactionOutput::isMine(string myKey){
    return (myKey==recipient);
}
bool transaction::processTransaction(Blockchain *chain){
    
    if(!verifySignature()){
        cout << "Could Not verify signature" << endl;
        return false;
    }
    
    for(transactionInput i : inputs){
        i.setUTXO(chain->getUTXO(i.getTXOutputId()));
    }
    
    float leftOver = getInputsValue()-value;
    
    transactionId = calculateHash();
    outputs.push_back(transactionOutput(reciever, value, transactionId));
    outputs.push_back(transactionOutput(sender, leftOver, transactionId));
    
    for (transactionOutput o : outputs) {
        chain->addUTXO(o.getId(), o);
    }
    
    for (transactionInput i : inputs) {
        chain->removeUTXO(i.getTXOutputId());
    }
    
    return true;
}

float transaction::getInputsValue(){
    float total = 0.00;
    for (transactionInput i: inputs) {
        if (i.getTXOutputId()=="") break;
        total += i.getUTXOValue();
    }
    return total;
}

float transaction::getOutputsValue(){
    float total = 0.00;
    for (transactionOutput o: outputs) {
        if (o.getId()=="") break;
        total += o.getValue();
    }
    return total;
}
float transactionInput::getUTXOValue(){
    return UTXO.getValue();
}

void transactionInput::setUTXO(transactionOutput UTXOin){
    UTXO = UTXOin;
    
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
string transaction::getTransactionId(){
    return transactionId;
}
void transaction::setTransactionId(string idIn){
    transactionId = idIn;
}
transaction::transaction(){
    transactionId = "NULL";
    sender= "NULL";
    reciever = "NULL";
    value = NULL;
}

transactionOutput transaction::getOutputAt(int i){
    return outputs.at(i);
}

