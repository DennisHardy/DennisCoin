//
//  merkleRoot.hpp
//  DennisCoin
//
//  Created by Dennis Hardy on 4/28/18.
//  Copyright © 2018 Dennis Hardy. All rights reserved.
//

#ifndef merkleRoot_hpp
#define merkleRoot_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include "transaction.hpp"
#include "sha256.h"

class transaction;
using namespace std;
string getMerkleRoot(vector<transaction> transactions);
#endif /* merkleRoot_hpp */
