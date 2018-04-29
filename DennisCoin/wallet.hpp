//
//  wallet.hpp
//  DennisCoin
//
//  Created by Dennis Hardy on 4/25/18.
//  Copyright © 2018 Dennis Hardy. All rights reserved.
//

#ifndef wallet_hpp
#define wallet_hpp

#include <stdio.h>
#include <string>
#include "ecc.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <unordered_map>
#include "transaction.hpp"
#include "Blockchain.hpp"

using namespace std;
class transactionOutput;
class Blockchain;
class transaction;

string publicKeyToString(publickey_t key);

class wallet{
public:
    string getPublicKey();
    wallet();
    publickey_t publicKey;
    privatekey_t privateKey;
    float getBalance(Blockchain chain);
    transaction sendFunds(string recipient, float value, Blockchain *chain);
private:
    unordered_map<string, transactionOutput> myUTXOs;
     
};

#endif /* wallet_hpp */
