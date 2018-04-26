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

using namespace std;

string publicKeyToString(publickey_t key);
class wallet{
public:
    string getPublicKey();
    wallet();
    publickey_t publicKey;
    privatekey_t privateKey;
private:
    
     
};

#endif /* wallet_hpp */
