//
// Created by Yotam on 22/11/2022.
//

#ifndef WORLDCUP_MYAVLTREE_H
#define WORLDCUP_MYAVLTREE_H


#include <memory>

using namespace std;
template<class Key, class Info>
class Node{
private:
    Key key;
    Info info;
    shared_ptr<Key> left;
    shared_ptr<Key> right;
    int height = 0;
public:
    Node<Key, Info> Node(Key key, Info info){

    }
    int get_height() const {
        return height;
    }
    int get_balance_factor() const{
        return left->get_height - right->get_height;
    }

};
template<class Key, class Info>
class MyAVLTree{
private:
    shared_ptr<Node<Key,Info>> root;
    int number_of_nodes;

    void insert_rec(Node<Key,Info> root,const Key &key,const Info &info){
        if(!root){
            root = shared_ptr<Node<Key,Info>>(new Node<Key,Info>(key,info));
        }
    };
public:
    void insert(const Key &key,const Info &info){

    }
};


#endif //WORLDCUP_MYAVLTREE_H
