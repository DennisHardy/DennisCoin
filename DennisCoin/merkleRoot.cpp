//
//  merkleRoot.cpp
//  DennisCoin
//
//  Created by Dennis Hardy on 4/28/18.
//  Copyright © 2018 Dennis Hardy. All rights reserved.
//

#include "merkleRoot.hpp"

string getMerkleRoot(vector<transaction> transactions){
    int count = transactions.size();
    
    vector<string> previousTreeLayer;
    for (transaction aTransaction: transactions) {
        previousTreeLayer.push_back(aTransaction.getTransactionId());
    }
    
    while (count > 1) {
        vector<string> treeLayer;
        for (int i = 1; i<previousTreeLayer.size(); i++) {
            treeLayer.push_back(sha256(previousTreeLayer.at(i-1)+previousTreeLayer.at(i)));
        }
        count=treeLayer.size();
        previousTreeLayer = treeLayer;
    }
    string merkleRoot = (previousTreeLayer.size()==1) ? previousTreeLayer.at(0) : "";
    return merkleRoot;
}
