//
// Created by Yotam on 22/11/2022.
//

#ifndef WORLDCUP_MYAVLTREE_H
#define WORLDCUP_MYAVLTREE_H


#include <memory>
#include <iostream>

using namespace std;
template<class Key, class Info>
class Node{
private:
    Key key;
    Info info;
    shared_ptr<Node<Key, Info>> left;
    shared_ptr<Node<Key, Info>> right;
    int height = 0;

    static int get_height(shared_ptr<Node<Key, Info>>& root){
        if(!root){
            return -1;
        }
        return root->height;
    }

public:

    Node(const Key &key, const Info &info):key(key), info(info),left(nullptr),right(nullptr),height(0){}
    Node() = default;
    int get_balance_factor() const{

        return get_height(left) - get_height(right);
    }

};

class KeyAlreadyExists : public std::exception {
public:
    const char * what () const noexcept override {
        return "Key already exists";
    }
};

template<class Key, class Info>
class MyAVLTree{
private:
    shared_ptr<Node<Key,Info>> root;
    int number_of_nodes;

    static void insert_rec(shared_ptr<Node<Key,Info>>& root,const Key &key,const Info &info){
        if(!root){
            root = shared_ptr<Node<Key,Info>>(new Node<Key,Info>(key,info));
        }
        else if(key < root->key){
            insert_rec(root->left,key,info);
        }
        else if(root->key < key){
            insert_rec(root->right,key,info);
        }
        else {// root->key == key
            throw KeyAlreadyExists();
        }
        //check balance factor
        root->height = 1+max(root->left->get_height(), root->right->get_height());
    };
    static void balance(shared_ptr<Node<Key,Info>>& root){
        if(!root){
            return;
        }
        int bf = root->get_balance_factor();
        if(bf==2){
            if(root->left->get_balance_factor()>-1){
                //LL
            }
            else if(root->left->get_balance_factor()==-1){
                //LR
            }
        }
        else if(bf==-2){
            if(root->right->get_balance_factor()<1) {
                //RR
            }
            else if(root->left->get_balance_factor()==1){
                //RL
            }
        }
    }
public:
    MyAVLTree(std::shared_ptr<Node<Key,Info>>& root):root(root),number_of_nodes(1){}
    MyAVLTree() = default;
    void insert(const Key &key,const Info &info){
        insert_rec(key,info);
        number_of_nodes++;
    }
};


#endif //WORLDCUP_MYAVLTREE_H
