//
//  wallet.cpp
//  DennisCoin
//
//  Created by Dennis Hardy on 4/25/18.
//  Copyright © 2018 Dennis Hardy. All rights reserved.
//

#include "wallet.hpp"

using namespace std;

string publicKeyToString(publickey_t key){
    stringstream buffer;
    for (int i = 0; i< ECC_BYTES+1; i++) {
        int j = key[i];
        buffer <<setfill('0') <<setw(2)<<hex<< j;
    }
    return buffer.str();
}

wallet::wallet(){
    ecc_make_key(publicKey, privateKey);
}

string wallet::getPublicKey(){
    return publicKeyToString(publicKey);
}

float wallet::getBalance(Blockchain chain){
    float total = 0.00;
    unordered_map<string, transactionOutput>allUTXOs = chain.getAllUTXOs();
    for (pair<string, transactionOutput> item: allUTXOs) {
        transactionOutput UTXO = item.second;
        if (UTXO.isMine(publicKeyToString(publicKey))) {
            myUTXOs.insert({UTXO.getId(),UTXO});
            total += UTXO.getValue();
        }
    }
    return total;
}

transaction wallet::sendFunds(string recipient, float value, Blockchain *chain){
    if (getBalance(*chain)< value) {
        cout << "Not enough funds to send transaction, transaction discarded" <<endl;
        return transaction();
    }
    vector<transactionInput> inputs;
    float total = 0.00;
    for (pair<string, transactionOutput> item: myUTXOs) {
        transactionOutput UTXO = item.second;
        total += UTXO.getValue();
        inputs.push_back(transactionInput(UTXO.getId(),UTXO));
        if(total>value) break;
    }
    transaction newTransaction(publicKeyToString(publicKey), recipient, value, inputs);
    newTransaction.generateSignature(privateKey);
    
    for (transactionInput input:inputs) {
        myUTXOs.erase(input.getTXOutputId());
    }
    
    return newTransaction;
}
