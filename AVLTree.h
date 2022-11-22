////
//// Created by Yotam on 19/11/2022.
////
//
//#ifndef WORLDCUP_AVLTREE_H
//#define WORLDCUP_AVLTREE_H
//#include <iostream>
//#include <memory>
//
//using namespace std;
//template <class Key, class Data>
//struct AVLNode {
//    Data data;
//    Key key;
//    shared_ptr<struct AVLNode> left;
//    shared_ptr<struct AVLNode> right;
//    shared_ptr<struct AVLNode> parent;
//    shared_ptr<struct AVLNode> closest;
//    int height = 0;
//
//    AVLNode(const Key &key, Data &data) : key(key), Data(data), left(nullptr), right(nullptr), parent(nullptr), closest(nullptr) {}
//
//    AVLNode(const AVLNode &other) : key(other.key), data(other.data), left(other.left), right(other.right),
//                                    parent(other.parent), closest(other.closest) {}
//};
//
//template <class Key, class Data>
//    class AVLTree {
//    private:
//        int height(shared_ptr<AVLNode<Key,Data>>& node);
//        int balanceFactor(shared_ptr<AVLNode<Key,Data>>& node);
//        static void insert(AVLNode<Key,Data>& node,AVLNode<Key,Data>& root);
//        static void remove(AVLNode<Key,Data>& node,AVLNode<Key,Data>& root);
//        static void balance(AVLNode<Key,Data>& root);
//        static void rrRotate(AVLNode<Key,Data>& root);
//        static void rlRotate(AVLNode<Key,Data>& root);
//        static void lrRotate(AVLNode<Key,Data>& root);
//        static void llRotate(AVLNode<Key,Data>& root);
//        static void unite(AVLNode<Key,Data>& root1,AVLNode<Key,Data>& root2);
//        AVLNode<Key,Data>& getClosest()
//
//    public:
//        shared_ptr<AVLNode<Key,Data>> root;
//
//        AVLTree() = default;
//        AVLTree(Key key, Data data): root(){};
//
//    };
//
//
//#endif //WORLDCUP_AVLTREE_H



#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <memory>
#include <exception>
#include <iostream>
#include "MyArray.h"
#include "wet1util.h"
using namespace std;

/*     EXCEPTIONS     */
//class KeyAlreadyExists : public std::exception {
//public:
 //   virtual const char* what() const noexcept override {
 //           return "Key already exists";
//    }
//};
class KeyDoesNotExist : public std::exception {
public:
    virtual const char* what() const noexcept override {
            return "Key does not exist";
    }
};
class EmptyTree : public std::exception {
public:
    virtual const char* what() const noexcept override {
            return "Can't perform operation on an empty tree.";
    }
};

template<class Key, class Info>
struct Node {
    Info getInfo() const {
        return this->info;
    }
    Key key;
    Info info;
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;
    int height = 0;

    Node(const Key& key, Info info) :
            key(key), info(info), left(nullptr), right(nullptr), height(0) { }
    Node(const Node& other) : key(other.key), info(other.info), left(other.left), right(other.right), height(height) { }
};
template<class Key, class Info>
class AVL {
    typedef Node<Key, Info> _Node;
private:
    /*     Helper Function     */
    // since we can't use std::max
    static inline int max(const int a, const int b) {
        return (a > b) ? a : b;
    }

    static int height(const std::shared_ptr<_Node>& root) {
        if(!root) {
            return -1;
        }
        return root->height;
    }

    static int get_balance_factor(const std::shared_ptr<_Node>& root) {
        return height(root->left) - height(root->right);
    }

    static void RR_rotation(std::shared_ptr<_Node>& parent) {
        std::shared_ptr<_Node> child = parent->right;
        parent->right = child->left;
        parent->height = 1 + max(height(parent->left), height(parent->right));
        child->height = 1 + max(height(child->right), height(parent));
        child->left = parent;
        parent = child;
    }
    static void RL_rotation(std::shared_ptr<_Node>& parent) {
        LL_rotation(parent->right);
        RR_rotation(parent);
    }
    static void LL_rotation(std::shared_ptr<_Node>& parent)
    {
        std::shared_ptr<_Node> child = parent->left;
        std::shared_ptr<_Node> tmp = child->right;
        child->right = parent;
        parent->left = tmp;
        parent->height = 1 + max(height(parent->left), height(parent->right));
        child->height = 1 + max(height(child->left), height(child->right));
        parent = child;
    }
    static void LR_rotation(std::shared_ptr<_Node>& parent) {
        RR_rotation(parent->left);
        LL_rotation(parent);
    }

    static void balance_aux(std::shared_ptr<_Node>& root) {
        if(!root) {
            return;
        }

        int balance_factor = get_balance_factor(root);
        if(balance_factor == 2) {
            if(get_balance_factor(root->left) >= 0) {
                LL_rotation(root);
            }
            else if (get_balance_factor(root->left) == -1) {
                LR_rotation(root);
            }
        }
        else if(balance_factor == -2) {
            if(get_balance_factor(root->right) <= 0) {
                RR_rotation(root);
            }
            else if(get_balance_factor(root->right) == 1) {
                RL_rotation(root);
            }
        }
    }

    static const std::shared_ptr<_Node>& find_aux(const std::shared_ptr<_Node>& root, const Key& key) {
        if(!root || key == root->key) {
            return root;
        }
        else if(key < root->key) {
            return find_aux(root->left, key);
        }
        else {  //(key > root->key) {
            return find_aux(root->right, key);
        }
    }

    static void insert_aux(std::shared_ptr<_Node>& root, const Key& key, const Info& info) {
        if(!root) {
            root = std::make_shared<_Node>(key, info);
            return;
        }
        else if(key < root->key) {
            insert_aux(root->left, key, info);
        }
        else {  // key > root->key
            insert_aux(root->right, key, info);
        }/
        balance_aux(root);
        root->height = 1 + max(height(root->left), height(root->right));
    }

    static void remove_aux(std::shared_ptr<_Node>& root, Key key) {
        if(!root) {
            return;
        }
        if(key < root->key) {
            remove_aux(root->left, key);
            root->height = 1 + max(height(root->left), height(root->right));
        }
        else if(root->key < key) {
            remove_aux(root->right, key);
            root->height = 1 + max(height(root->left), height(root->right));
        }
        else {  // key == root->key
            // root is a leaf
            if(!root->left && !root->right) {
                root = nullptr;//.reset();
            }
                // root has left child
            else if(!root->right) {
                root = root->left;
            }
                // root has right child
            else if(!root->left) {
                root = root->right;
            }
                // root has both childs
            else {
                std::shared_ptr<_Node> next = root->right;
                while(next->left) {
                    next = next->left;
                }
                root->key = next->key;
                root->info = next->info;
                remove_aux(root->right, root->key);
            }
        }
        balance_aux(root);
    }

    static Info& getMaxAux(const std::shared_ptr<_Node>& root) {
        if(!root->right) {
            return root->info;
        }
        return getMaxAux(root->right);
    }
    static Info& getMinAux(const std::shared_ptr<_Node>& root) {
        if(!root->left) {
            return root->info;
        }
        return getMinAux(root->left);
    }

    static void clear_aux(std::shared_ptr<_Node>& root) {
        if(!root) {
            return;
        }
        clear_aux(root->left);
        clear_aux(root->right);
        root.reset();
    }

    static std::shared_ptr<_Node> deep_copy(const std::shared_ptr<_Node>& from, std::shared_ptr<_Node>& to) {
        if(!from) {
            return nullptr;
        }
        to = std::make_shared<_Node>(from->key, from->info);
        to->left = deep_copy(from->left, to->left);
        to->right = deep_copy(from->right, to->right);
        return to;
    }

    /* merge helper functions */
    static void inorderToList(const std::shared_ptr<_Node>& root, MyArray<_Node*>& list) {
        if(!root) {
            return;
        }
        inorderToList(root->left, list);
        list.push_back(root.get());
        inorderToList(root->right, list);
    }
    MyArray<_Node*> getTreeAsList() const {
        MyArray<_Node*> list(number_of_nodes);
        inorderToList(root, list);  // O(n)
        return list;
    }
    class NodesComparator {
    public:
        bool operator()(_Node* left, _Node* right) {
            return left->key < right->key;
        }
    };
    /**
     * getTreeFomListAux: creates a balanced binary tree (AVL) from a list in O(n), n being the length of the list:
     * no need for rotations and searching, each node get assinged a value such that there are balanced number
     * of nodes from each side, using a proccess similliar to binary search.
    */
    static std::shared_ptr<_Node> getTreeFromListAux(const MyArray<_Node*>& list, int start, int end) {
        if(start > end) {
            return nullptr;
        }
        int mid = (start+end)/2;
        std::shared_ptr<_Node>root = std::make_shared<_Node>(list[mid]->key, list[mid]->info);
        root->left = getTreeFromListAux(list, start, mid-1);
        root->right = getTreeFromListAux(list, mid+1, end);
        return root;
    }
    static AVL getTreeFromList(const MyArray<_Node*>& list) {
        AVL avl;
        avl.root = getTreeFromListAux(list, 0, list.getSize());
        avl.number_of_nodes = list.getSize()+1;
        return avl;
    }

public:
    std::shared_ptr<_Node> root;
    int number_of_nodes = 0;
    AVL() = default;
    AVL(Key key, Info info) : root(std::make_shared<_Node>(key, info)) { }
    AVL(const AVL& other) {
        this->root = deep_copy(other.root, this->root);
        this->number_of_nodes = other.number_of_nodes;
    }
    ~AVL() {
        if(number_of_nodes > 0)
            clear_aux(root);  // stack overflow?
    }
    AVL& operator=(const AVL& other) {
        if(this == &other) {
            return *this;
        }
        this->root = deep_copy(other.root, this->root);
        this->number_of_nodes = other.number_of_nodes;
        return *this;
    }
    void copyRoot(const AVL& from) const {
        root = from.root;
    }

    const std::shared_ptr<_Node>& find(const Key& key) const {
        return find_aux(root, key);
    }

    Info& getInfo(const Key& key) const {
        std::shared_ptr<_Node> node = find(key);
        if(!node) {
            throw KeyDoesNotExist();
        }
        return node->info;
    }

    StatusType insert(const Key& key, const Info& info) {
        if(find(key)) {
            throw KeyAlreadyExists();
        }
        insert_aux(root, key, info);
        number_of_nodes++;
        return StatusType::SUCCESS;
    }
    void remove(const Key& key) {
        if(!find(key)) {
            throw KeyDoesNotExist();
        }
        remove_aux(root, key);
        number_of_nodes--;
    }

    Info& getMax() const {
        if(!root) {
            throw EmptyTree();
        }
        return getMaxAux(root);
    }
    Info& getMin() const {
        if(!root) {
            throw EmptyTree();
        }
        return getMinAux(root);
    }

    void clear() {
        clear_aux(root);
    }

    int get_tree_height() const {
        return height(root);
    }

    bool does_exist(const Key& key) const {
        if(find(key)) {
            return true;
        }
        return false;

    }
    // static void print_inorder(std::shared_ptr<_Node>& root) {
    //     if(!root) {
    //         return;
    //     }
    //     print_inorder(root->left);
    //     std::cout << (root->key) << ", ";
    //     print_inorder(root->right);
    // }
    // void inorder() {
    //     print_inorder(root);
    //     std::cout << std::endl;
    // }
    // static void print_preorder(std::shared_ptr<_Node>& root) {
    //     if(!root) {
    //         return;
    //     }
    //     std::cout << root->key << ", ";
    //     print_preorder(root->left);
    //     print_preorder(root->right);
    // }
    // void preorder() {
    //     print_preorder(root);
    //     std::cout << std::endl;
    // }
    // static void print_postorder(std::shared_ptr<_Node>& root) {
    //     if(!root) {
    //         return;
    //     }
    //     print_postorder(root->left);
    //     print_postorder(root->right);
    //     std::cout << root->key << ", ";
    // }
    // void postorder() {
    //     print_postorder(root);
    //     std::cout << std::endl;
    // }

    static MyArray<_Node*> mergeToList(const AVL& avl1, const AVL& avl2) {
        NodesComparator cmp;
        MyArray<_Node*> list1 = avl1.getTreeAsList();  // O(n)
        MyArray<_Node*> list2 = avl2.getTreeAsList();  // O(m)
        MyArray<_Node*> merged_list = MyArray<_Node*>::merge(list1, list2, cmp);  // O(n+m)
        return merged_list;
    }

    static AVL listToAVL(const MyArray<_Node*>& list) {
        AVL avl = getTreeFromList(list);  // O(n+m)
        return avl;
        // counting copying and destructing lists and trees (if performed), the overall complexity is still O(n+m)
    }
    static AVL merge(const AVL& avl1, const AVL& avl2) {
        MyArray<_Node*> merged_list = mergeToList(avl1, avl2);
        return listToAVL(merged_list);
    }

};

#endif