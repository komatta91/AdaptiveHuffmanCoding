//
// Created by Komatta on 2016-03-12.
//

#include <CodeTree.h>

#include <cassert>
#include <boost/dynamic_bitset.hpp>

#include <iostream>

CodeTree::CodeTree() : mGenerator("NOD") {
    mRoot = NodePtr(new Node(nullptr));
};

std::string CodeTree::getCode(char input) {
    std::string result;
    NodePtr node = getNode(std::string(&input, 1));
    if (node) {
        result = node->getCode();
    }
    else {
        result = encode(input);
    }
    updateModel(input, node);
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
    zero->mLeft = NodePtr(new Node(zero));;
    zero->mRight = NodePtr(new Node(zero, std::string(&symbol, 1)));;
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
    //TODO Tu są jakieś błądy ale nie potrafię ich zlokalizować
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
    assert(aCode == b->getCode());
    assert(bCode == a->getCode());
}
