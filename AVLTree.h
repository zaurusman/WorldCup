//
// Created by Yotam on 22/11/2022.
//

#ifndef WORLDCUP_AVLTREE_H
#define WORLDCUP_AVLTREE_H


#include <memory>
#include <iostream>

using namespace std;
template<class Key, class Info>
class Node{
public:
    Key key;
    Info info;
    shared_ptr<Node<Key, Info>> left;
    shared_ptr<Node<Key, Info>> right;
    int height = 0;

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

class KeyDoesNotExist : public std::exception {
public:
    const char * what () const noexcept override {
        return "Key does not exist";
    }
};

template<class Key, class Info>
class AVLTree{
private:
    shared_ptr<Node<Key,Info>> root;
    int number_of_nodes = 0;

    static int get_height(shared_ptr<Node<Key, Info>>& root){
        if(!root){
            return -1;
        }
        return root->height;
    }

    static void insert_rec(shared_ptr<Node<Key,Info>>& root, const Key &key,const Info &info){
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
        root->height = 1+max(get_height(root->left), get_height(root->right));
    };

    static void remove_rec(shared_ptr<Node<Key,Info>>& root, const Key &key) {
        if (!root) {
            throw KeyDoesNotExist();
        }

        else if(key < root->key){
            remove_rec(root->left,key);
        }
        else if(root->key < key){
            remove_rec(root->right,key);
        }
        else {   // root->key == key
            // leaf
            if (!root->left && !root->right) {
                root.reset();
            }
            // has only left son
            else if (root->left && !root->right) {
                root = root->left;
            }
            // has only right son
            else if (!root->left && root->right) {
                root = root->right;
            }
            // has both sons
            else {
                shared_ptr<Node<Key,Info>> next = get_next(root);
                root->key = next->key;
                root->info = next-> info;
                remove_rec(root->right, next->key);
            }
        }
    }

    static shared_ptr<Node<Key,Info>> get_next(shared_ptr<Node<Key,Info>> root) {
        root = root->right;
        while (root->left) {
            root = root->left;
        }
        return root;
    }

    static shared_ptr<Node<Key,Info>> get_prev(shared_ptr<Node<Key,Info>> root) {
        root = root->left;
        while (root->right) {
            root = root->right;
        }
        return root;
    }

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

    static shared_ptr<Node<Key,Info>> find_rec(shared_ptr<Node<Key,Info>>& root,Key& key){
        if(!root){
            throw KeyDoesNotExist();
        }
        else if(key < root->key){
            remove_rec(root->left,key);
        }
        else if(root->key < key){
            remove_rec(root->right,key);
        }
        else {   // root->key == key
            return root;
        }

    }
    static void print_inorder(shared_ptr<Node<Key,Info>>& root) {
        if(!root) {
            return;
        }
        print_inorder(root->left);
        std::cout << (root->key) << ", ";
        print_inorder(root->right);
    }

public:
    AVLTree(Key key, Info info) : root(shared_ptr<Node<Key,Info>>(key, info)){}
    explicit AVLTree(std::shared_ptr<Node<Key,Info>>& root): root(root), number_of_nodes(1){}
    AVLTree() = default;
    void insert(const Key &key,const Info &info){
        insert_rec(root, key,info);
        number_of_nodes++;
    }

    void remove(const Key &key){
        remove_rec(root, key);
        number_of_nodes--;
    }

    void inorder() {
        print_inorder(root);
        std::cout << std::endl;
    }

    shared_ptr<Node<Key,Info>> find(Key& key){
        return find_rec(root,key);
    }
};


#endif //WORLDCUP_AVLTREE_H
