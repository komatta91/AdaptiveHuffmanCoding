//
// Created by Komatta on 2016-03-12.
//

#include <CodeTree.h>

#include <boost/dynamic_bitset.hpp>

#include <iostream>

std::string CodeTree::mPrefix = "NOD";

CodeTree::CodeTree() : mGenerator(mPrefix), newSymbolNext(false) {
    mRoot = NodePtr(new Node(nullptr));
};


std::string CodeTree::zeroCode() {
    return getNode(std::string("ZERO"))->getCode();
}

std::string CodeTree::getCode(char input) {
    std::string result;
    NodePtr node = getNode(std::string(&input, 1));
    if (node) {
        result = node->getCode();
    }
    else {
        result = zeroCode() + encode(input);
    }
    updateModel(input, node);
    return result;
}

std::string CodeTree::getDecoded(std::string bits) {
    std::string result = "";
    std::list<NodePtr> list;
    list.push_back(mRoot);

    mDecodeQueue = mDecodeQueue.append(bits);
    unsigned int queuePos = 0;
    while (!list.empty() && queuePos < mDecodeQueue.length() && mDecodeQueue.length()>=8) {
        NodePtr node = list.front();
        list.pop_front();
        assert(node);

        if(node->isZero() && !newSymbolNext){
            newSymbolNext = true;
            mDecodeQueue = mDecodeQueue.substr(zeroCode().length());
            if(mDecodeQueue.length()>=8){
                list.clear();
                list.push_back(mRoot);
                queuePos = 0;
                continue;
            }
            break;
        }
        if(newSymbolNext){
            char newSymbol = decode(mDecodeQueue);
            result += newSymbol;
            getCode(newSymbol);
            mDecodeQueue = mDecodeQueue.substr(8);
            if(newSymbolNext){
                newSymbolNext=false;
            }
            list.clear();
            list.push_back(mRoot);
            queuePos = 0;
            continue;
        }

        if(!node->isInternalNode()){
            assert(node->mSymbol.length() == 1);

            result += node->mSymbol;
            std::string code = getCode(node->mSymbol.front());

            list.clear();
            list.push_back(mRoot);
            mDecodeQueue = mDecodeQueue.substr(queuePos);
            queuePos = 0;
            continue;
        }

        if (mDecodeQueue.at(queuePos) == '0') {
            list.push_back(node->mLeft);
        }else if(mDecodeQueue.at(queuePos) == '1'){
            list.push_back(node->mRight);
        }else{
            throw "Unknown symbol in code: "+mDecodeQueue.at(queuePos);
        }

        ++queuePos;
    }
    return result;
}

CodeTree::NodePtr CodeTree::getNode(std::string symbol) {
    std::list<NodePtr> list;
    list.push_back(mRoot);
    while (!list.empty()) {
        NodePtr node = list.front();
        list.pop_front();
        assert(node);
        if (node->mSymbol == symbol) {
            return node;
        }
        if (node->mRight && node->mLeft) {
            list.push_back(node->mRight);
            list.push_back(node->mLeft);
        }
    }
    return nullptr;
}

std::string CodeTree::encode(char input) {
    boost::dynamic_bitset<unsigned char> result(CHAR_BIT);
    result[0] = (input & 1) != 0;
    result[1] = (input & 2) != 0;
    result[2] = (input & 4) != 0;
    result[3] = (input & 8) != 0;
    result[4] = (input & 16) != 0;
    result[5] = (input & 32) != 0;
    result[6] = (input & 64) != 0;
    result[7] = (input & 128) != 0;

    std::string buffer;
    boost::to_string(result, buffer);
    return buffer;
}

char CodeTree::decode(std::string input) {
    char result = 0;
    for(int i=0; i<input.length() && i < 8; ++i){
        result = result << 1;
        if(input.at(i) == '1'){
            result |= 1;
        }
    }
    return result;
}

void CodeTree::updateModel(char input, NodePtr node) {
    if (!node) {
        node = addNode(input);
    }
    assert(node);
    processNode(node);
}

CodeTree::NodePtr CodeTree::addNode(char symbol) {
    NodePtr zero = getNode(std::string("ZERO"));
    assert(zero);

    zero->mSymbol = mGenerator.generate();
    zero->mLeft = NodePtr(new Node(zero));
    zero->mRight = NodePtr(new Node(zero, std::string(&symbol, 1)));

/*
 _______ .______    __    ______
|   ____||   _  \  |  |  /      |
|  |__   |  |_)  | |  | |  ,----'
|   __|  |   ___/  |  | |  |
|  |____ |  |      |  | |  `----.
|_______|| _|      |__|  \______|
 */
    processNode(zero);// Praise be to the flying spaghetti monster!
/*
 _______  __  ___   ___
|   ____||  | \  \ /  /
|  |__   |  |  \  V  /
|   __|  |  |   >   <
|  |     |  |  /  .  \
|__|     |__| /__/ \__\

 */

    return zero;
}

void CodeTree::processNode(NodePtr node) {
    assert(node);
    NodePtr maxNode = getMaxInClass(node->mCount);
    assert(maxNode);

    if (node->mSymbol != maxNode->mSymbol) {
        swapNodes(node, maxNode);
    }
    node->mCount++;

    if (node->mParent) {
        processNode(node->mParent);
    }
}

CodeTree::NodePtr CodeTree::getMaxInClass(int clas) {
    std::list<NodePtr> list;
    list.push_back(mRoot);
    while (!list.empty()) {
        NodePtr node = list.front();
        list.pop_front();
        if (node->mCount == clas) {
            return node;
        }
        if (node->mRight && node->mLeft) {
            list.push_back(node->mRight);
            list.push_back(node->mLeft);
        }
    }
    assert(false);
}

void CodeTree::swapNodes(NodePtr a, NodePtr b) {
    std::string aCode = a->getCode();
    std::string bCode = b->getCode();

    NodePtr aParent = a->mParent;
    NodePtr bParent = b->mParent;

    if (aParent->mSymbol == bParent->mSymbol) {
        NodePtr temp = aParent->mLeft;
        aParent->mLeft = aParent->mRight;
        aParent->mRight = temp;
    }
    else {
        if (a->mParent->mLeft->mSymbol == a->mSymbol) {
            aParent->mLeft = b;
        }
        else {
            aParent->mRight = b;
        }

        if (b->mParent->mLeft->mSymbol == b->mSymbol) {
            bParent->mLeft = a;
        }
        else {
            bParent->mRight = a;
        }
        a->mParent = bParent;
        b->mParent = aParent;
    }

    assert(a->mParent != a);
    assert(b->mParent != b);
    assert(a->mParent != b);
    assert(b->mParent != a);
    assert(aCode == b->getCode());
    assert(bCode == a->getCode());
}
