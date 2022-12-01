//
// Created by Yotam on 22/11/2022.
//
#ifndef WORLDCUP_AVLTREE_H
#define WORLDCUP_AVLTREE_H

#include <memory>
#include <iostream>
#include <cmath>
#include "LinkedList.h"
#include "Exception.h"
using namespace std;

template<class Key , class Info>
class Node {
    public:
        Key key;
        Info info;
        shared_ptr<Node<Key, Info>> left;
        shared_ptr<Node<Key, Info>> right;
        int height;

        Node(const Key &key, const Info &info):
            key(key), info(info), left(nullptr), right(nullptr), height(0) {}

        Node<Key,Info>() = default;

        bool operator>(const Node& other) const {
            return key > other.key;
        }
        bool operator<(const Node& other) const {
            return key < other.key;
        }
        bool operator>=(const Node& other) const {
            return !(key < other.key);
        }
        bool operator<=(const Node& other) const {
            return !(key > other.key);
        }
        Node& operator=(const Node& other) {
            if(this != &other) {
                this->key = other.key;
                this->info = other.info;
            }
            return *this;
        }
};

template<class Key, class Info>
class AVLTree {
public:
    AVLTree() : root(nullptr), node_count(0){}

    shared_ptr<Node<Key,Info>>& get_root() {
        return root;
    }

    ~AVLTree() = default;

    void insert(const Key &key,const Info &info){
        insert_rec(root, key,info);
        node_count++;
    }

    void insert_p(const Key &key,const Info &info,shared_ptr<Node<Key,Info>>& parent){
        bool is_parent = false;
        insert_rec_p(root, key,info, &is_parent,parent);
        node_count++;
    }

    void remove(const Key &key){
        remove_rec(root, key);
        node_count--;
    }

//    void inorder() {
//        print_inorder(root);
//        std::cout << std::endl;
//    }

    bool does_exist(Key key) {
        try {
            find(key);
        } catch (KeyDoesNotExist &e) {
            return false;
        }
        return true;
    }

    int get_tree_height(){
        return get_height(root);
    }

    int get_node_count() {
        return node_count;
    }

    shared_ptr<Node<Key,Info>>& find(Key& key){
        return find_rec(root,key);
    }

    static void AVL_to_list_inorder(shared_ptr<Node<Key,Info>>& root,LinkedList<Node<Key,Info>>& out) {
        if(!root) {
            return;
        }
        AVL_to_list_inorder(root->right,out);
        out.push_front(*root);
        AVL_to_list_inorder(root->left,out);
    }

    static AVLTree<Key,Info> make_complete_tree(int tree_height) {
        AVLTree<Key,Info> tree;
        make_complete_tree_rec(tree, tree.get_root(), tree_height);
        return tree;
    }

    static void make_complete_tree_rec(AVLTree<Key,Info>& tree, shared_ptr<Node<Key,Info>>& node, int tree_height) {
        if (tree_height == -1) {
            node = nullptr;
            return;
        }

        node = make_shared<Node<Key,Info>>();
        node->height = tree_height;
        tree.node_count++;
        make_complete_tree_rec(tree, node->left, tree_height - 1);
        make_complete_tree_rec(tree, node->right, tree_height - 1);
    }

    void remove_extra_nodes(AVLTree<Key,Info>& tree, shared_ptr<Node<Key, Info>>& curr, int* extra_nodes) {
        if (!curr || *extra_nodes == 0) {
            return;
        }
        if (!curr->right && !curr->left) {
            curr.reset();
            (*extra_nodes)--;
            tree.node_count--;
            return;
        }

        remove_extra_nodes(tree, curr->right, extra_nodes);
        remove_extra_nodes(tree, curr->left, extra_nodes);
    }

    static AVLTree<Key,Info> make_almost_complete_tree(int node_count) {
        int tree_height = ceil(log2(node_count + 1)) - 1;
        AVLTree<Key,Info> tree = make_complete_tree(tree_height);
        int extra_nodes = tree.get_node_count() - node_count;
        tree.remove_extra_nodes(tree, tree.get_root(), &extra_nodes);
        return tree;
    }

    static void fill_empty_tree(shared_ptr<Node<Key,Info>>& node, LinkedList<Node<Key,Info>>& list) {
        if (!node) {
            return;
        }

        fill_empty_tree(node->left, list);
        *node = list.pop_front();
        fill_empty_tree(node->right, list);
    }

    shared_ptr<Node<Key,Info>> get_max() {
        shared_ptr<Node<Key,Info>> temp = root;
        while (temp && temp->right) {
            temp = temp->right;
        }

        return temp;
    }

private:
    shared_ptr<Node<Key,Info>> root;
    int node_count = 0;

    static int get_height(shared_ptr<Node<Key, Info>>& root) {
        if(!root) {
            return -1;
        }

        return root->height;
    }


    static int get_balance_factor(shared_ptr<Node<Key,Info>>& root) {
        return get_height(root->left) - get_height(root->right);
    }

    static void insert_rec(shared_ptr<Node<Key,Info>>& root, Key const &key, Info const &info){
        if(!root){
            root = make_shared<Node<Key,Info>>(Node<Key,Info>(key,info));
        }
        else if(key < root->key){
            insert_rec(root->left,key,info);
        }
        else if(root->key < key){
            insert_rec(root->right,key,info);
        }
        else { // root->key == key
            throw KeyAlreadyExists();
        }

        balance(root);
        root->height = 1 + max(get_height(root->left), get_height(root->right));
    };

    static void insert_rec_p(shared_ptr<Node<Key,Info>>& root, Key const &key, Info const &info, bool* is_parent,shared_ptr<Node<Key,Info>>& parent){
        if(!root){
            root = make_shared<Node<Key,Info>>(Node<Key,Info>(key,info));
            *is_parent = true;
            parent = nullptr;
        }
        else if(key < root->key){
            insert_rec_p(root->left,key,info, is_parent, parent);
            if (*is_parent) {
                *is_parent = false;
                parent = root;
            }
        }
        else if(root->key < key){
            insert_rec_p(root->right,key,info, is_parent, parent);
            if (*is_parent) {
                *is_parent = false;
                parent = root;
            }
        }
        else { // root->key == key
            throw KeyAlreadyExists();
        }

        balance(root);
        root->height = 1 + max(get_height(root->left), get_height(root->right));
    };

    static void remove_rec(shared_ptr<Node<Key,Info>>& curr, const Key &key) {
        if (!curr) {
            throw KeyDoesNotExist();
        }

        else if(key < curr->key){
            remove_rec(curr->left,key);
            curr->height = 1 + max(get_height(curr->left), get_height(curr->right));
        }
        else if(curr->key < key){
            remove_rec(curr->right,key);
            curr->height = 1 + max(get_height(curr->left), get_height(curr->right));
        }
        else {   // root->key == key
            if (!curr->left && !curr->right) { // TODO: Export condition to function `isLeaf(Node)`
                curr.reset();
            }
//            else if (root-> left && root-> right) {}
//            else if (!root-> left && !root -> right) {}
//            else if (root -> right) {}
//            else {}
                // removed node has only left son
            else if (curr->left && !curr->right) {
                curr = curr->left;
            }
                // removed node has only right son
            else if (!curr->left && curr->right) {
                curr = curr->right;
            }
                // removed node has both sons
            else {
                shared_ptr<Node<Key,Info>> next = get_next_inorder(curr);
                curr->key = next->key;
                curr->info = next-> info;
                remove_rec(curr->right, curr->key);//TODO: the problem is with the values (NULL)
            }
        }

        balance(curr);
    }

    static shared_ptr<Node<Key,Info>> get_next_inorder(shared_ptr<Node<Key,Info>> curr) {
        curr = curr->right;
        while (curr->left) {
            curr = curr->left;
        }
        return curr;
    }
//
//    shared_ptr<Node<Key,Info>> get_prev_inorder(shared_ptr<Node<Key,Info>> curr) {
//        curr = curr->left;
//
//        while (curr->right) {
//            curr = curr->right;
//        }
//
//        return curr;
//    }

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

        if(bf == 2) {
            if(get_balance_factor(root->left) > -1) { // left bf == 1
                LL_rotate(root);
            }
            else if(get_balance_factor(root->left) == -1) {
                //LR rotation
                RR_rotate(root->left);
                LL_rotate(root);
            }
        }
        else if(bf == -2) {
            if(get_balance_factor(root->right)<1) { // right bf == -1
                RR_rotate(root);
            }
            else if(get_balance_factor(root->right)==1){
                //RL rotation
                LL_rotate(root->right);
                RR_rotate(root);
            }
        }
    }

    static shared_ptr<Node<Key,Info>>& find_rec(shared_ptr<Node<Key,Info>>& root,Key& key){
        if(!root){
            throw KeyDoesNotExist();
        }
        else if(key < root->key){
            return find_rec(root->left,key);
        }
        else if(root->key < key){
            return find_rec(root->right,key);
        } else {
            return root;
        }
    }

    static shared_ptr<Node<Key,Info>> find_parent_rec(shared_ptr<Node<Key,Info>>& root,Key& key, shared_ptr<Node<Key, Info>> parent){
        if(!root){
            throw KeyDoesNotExist();
        }
        else if(key < root->key){
            return find_parent_rec(root->left,key, root);
        }
        else if(root->key < key){
            return find_parent_rec(root->right,key, root);
        } else {
            return parent;
        }
    }


    static void print_inorder(shared_ptr<Node<Key,Info>>& curr) {
        if(!curr) {
            return;
        }

        print_inorder(curr->left);
        std::cout << (curr->key) << ", ";
        print_inorder(curr->right);
    }

  //TODO: tree creator with while, int nodes_count, int state. - notice: do not change root. left side first.

};

#endif //WORLDCUP_AVLTREE_H