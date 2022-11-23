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

    static int get_balance_factor(shared_ptr<Node<Key, Info>>& root){
        return get_height(root->left) - get_height(root->right);
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

        balance(root);
        root->height = 1 + max(get_height(root->left), get_height(root->right));
    };

    static void remove_rec(shared_ptr<Node<Key,Info>>& root, const Key &key) {
        if (!root) {
            throw KeyDoesNotExist();
        }

        else if(key < root->key){
            remove_rec(root->left,key);
            root->height = 1 + max(get_height(root->left), get_height(root->right));
        }
        else if(root->key < key){
            remove_rec(root->right,key);
            root->height = 1 + max(get_height(root->left), get_height(root->right));
        }
        else {   // reached node to remove: root->key == key
            // removed node is leaf
            if (!root->left && !root->right) {
                root.reset();
            }
            // removed node has only left son
            else if (root->left && !root->right) {
                root = root->left;
            }
            // removed node has only right son
            else if (!root->left && root->right) {
                root = root->right;
            }
            // removed node has both sons
            else {
                shared_ptr<Node<Key,Info>> next = get_next(root);
                root->key = next->key;
                root->info = next-> info;
                remove_rec(root->right, next->key);
            }
        }

        balance(root);
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

    static void LL_rotate(shared_ptr<Node<Key,Info>>& root) {
        // B = root, A = root->left
        // A left child stays the same
        // A right child becomes B
        // B left child becomes A prev left child
        // B right child stays the same
        shared_ptr<Node<Key,Info>> Ar = root->left->right;
        shared_ptr<Node<Key,Info>> B = root;
        root = root->left;
        root->right = B;
        root->right->left = Ar;
        root->right->height = 1 + max(get_height(root->right->left), get_height(root->right->right));
        root->height = 1 + max(get_height(root->left), get_height(root->right));
    }

    static void RR_rotate(shared_ptr<Node<Key,Info>>& root) {
        // A = root, B = root->right
        // A left child stays the same
        // A right child becomes prev B left child
        // B left child becomes A
        // B right child stays the same
        shared_ptr<Node<Key,Info>> Bl = root->right->left;
        shared_ptr<Node<Key,Info>> A = root;
        root = root->right;
        root->left = A;
        root->left->right = Bl;
        root->left->height = 1 + max(get_height(root->left->left), get_height(root->left->right));
        root->height = 1 + max(get_height(root->left), get_height(root->right));
    }

    static void balance(shared_ptr<Node<Key,Info>>& root){
        if(!root){
            return;
        }
        int bf = get_balance_factor(root);
        if(bf == 2){
            if(get_balance_factor(root->left) > -1){ // left bf == 1
                LL_rotate(root);
            }
            else if(get_balance_factor(root->left)==-1){
                //LR
                RR_rotate(root->left);
                LL_rotate(root);
            }
        }
        else if(bf==-2){
            if(get_balance_factor(root->right)<1) { // right bf == -1
                RR_rotate(root);
            }
            else if(get_balance_factor(root->right)==1){
                //RL
                LL_rotate(root->right);
                RR_rotate(root);
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

    int get_tree_height(){
        return get_height(root);
    }
};


#endif //WORLDCUP_AVLTREE_H
