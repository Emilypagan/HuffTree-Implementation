/** CS515 Assignment 8
 * File: HuffTree.cpp
 * Name: Mily
 * Section: 02
 * Date: 11/05/20
 * Collaboration Declaration: piazza */

#include "HuffTree.h"
#include "PQueue.h"

//returns the Huffman code of char c
string HuffTree::getCode(char c) {
    int index = 0;
    for (int i = 0; i < (treesize/2)+1; i++) {
        if (_originalfoo[i].data == c) {
            index = i;
        }
    }
    return _originalfoo[index].code;
}

//traverses the HuffTree until pointer NULL - when pointer is NULL all leaf nodes were set with a code
void HuffTree::setcodes(HuffNode *&cur, string arrFoo[], int top) {
    if (cur->left) {
        arrFoo[top] = "0";
        setcodes(cur->left, arrFoo, top + 1);
    }
    // Assign 1 to right edge and recur
    if (cur->right) {
        arrFoo[top] = "1";
        setcodes(cur->right, arrFoo, top + 1);
    }
    if (cur->isLeaf) {
        traverse = "";
        for (int i = 0; i < top; ++i) {
            traverse = traverse + arrFoo[i];
        }

        for (int i = 0; i < (treesize/2)+1; i++) {
            if (_originalfoo[i].data == cur->data) {
                _originalfoo[i].code = traverse;
            }
        }
    }
}

//builds Huffman Tree using a min Heap - priority queue
void HuffTree::buildTree(char * chs, int * freqs, int size) {
    treesize = size+size-1; //number of internal HuffNodes is size-1 thus the total number of nodes is size+size-1
    PQueue<HuffNode, 100> foo; //helps make tree
    HuffNode originalfoo[size]; //holds copies original HuffNodes

    //inserting original HuffNodes
    for (int i = 0; i < size; i++) {
        HuffNode *c = new HuffNode;
        c->freq = freqs[i];
        c->isLeaf = true;
        c->data = chs[i];
        originalfoo[i] = *c;
        foo.insert(*c);
    }

    //_originalfoo points to original HuffNodes that contain data
    _originalfoo = originalfoo;

    //building the tree - creating new HuffNodes
    while (!foo.isEmpty()) {
        HuffNode *z = new HuffNode();
        z->left = new HuffNode(foo.findMin());
        foo.deleteMin();
        z->right = new HuffNode(foo.findMin());
        foo.deleteMin();
        z->freq = z->left->freq + z->right->freq;
        if (foo.isEmpty()) {
          _root = z;
        } else {
            foo.insert(*z);
        }
    }

    //set the Huff codes for each leaf node containing data
    string arrFoo[treesize];
    int top = 0;
    setcodes(_root, arrFoo, top);
}

HuffTree::~HuffTree() {
    if (_root->left != NULL) {  // not an empty tree
        destructCode(_root);
    }
}

void HuffTree::destructCode(HuffNode *& p) {
    if (p == NULL) return;

    /* first delete both subtrees */
    destructCode(p->left);
    destructCode(p->right);

    delete p;
}

bool HuffNode::operator >(const HuffNode &rhs) {
    if(this->freq > rhs.freq) {
        return true;
    }
    return false;
}

bool HuffNode::operator <=(const HuffNode &rhs) {
    if (this->freq < rhs.freq) {
        return true;
    }
    if (this->freq == rhs.freq) {
        return true;
    }
    return false;
}