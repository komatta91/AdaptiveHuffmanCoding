//
// Created by Komatta on 2016-03-12.
//

#ifndef ADAPTIVEHUFFMANCODING_CODETREE_H
#define ADAPTIVEHUFFMANCODING_CODETREE_H

#include <memory>
#include <list>
#include <NameGenerator.h>

class CodeTree {
    NameGenerator mGenerator;

    struct Node {
        std::shared_ptr<Node> mParent;
        std::shared_ptr<Node> mLeft;
        std::shared_ptr<Node> mRight;
        std::string mSymbol;
        int mCount;

        Node(std::shared_ptr<Node> parent) : mParent(parent), mLeft(nullptr), mRight(nullptr), mSymbol("ZERO"),
                                             mCount(0) { };

        Node(std::shared_ptr<Node> parent, std::string symbol) : mParent(parent), mLeft(nullptr), mRight(nullptr),
                                                                 mCount(1), mSymbol(symbol) { };

        inline bool operator==(char c) const {
            return mSymbol.size() == 1 && mSymbol[0] == c;
        }

        std::string getCode() const {
            if (!mParent) {
                return "";
            }
            std::list<NodePtr> list;
            std::string result;

            list.push_back(mParent);
            while (!list.empty()) {
                NodePtr node = list.front();
                list.pop_front();

                if (!node->mParent) {
                    break;
                }

                if (node->mParent->mLeft->mSymbol == node->mSymbol) {
                    result = "0" + result;
                }

                if (node->mParent->mRight->mSymbol == node->mSymbol) {
                    result = "1" + result;
                }

                if (node->mParent) {
                    list.push_back(node->mParent);
                }
            }
            return result;
        }
    };

    typedef std::shared_ptr<Node> NodePtr;

    NodePtr mRoot;

public:
    CodeTree();

    std::string getCode(char input);

private:
    NodePtr getNode(std::string symbol);

    std::string encode(char input);

    void updateModel(char input, NodePtr node);

    NodePtr addNode(char symbol);

    void processNode(NodePtr node);

    NodePtr getMaxInClass(int clas);

    void swapNodes(NodePtr a, NodePtr b);
};

#endif //ADAPTIVEHUFFMANCODING_CODETREE_H
