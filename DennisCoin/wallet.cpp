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
