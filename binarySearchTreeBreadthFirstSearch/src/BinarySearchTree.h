#pragma once

#include <functional> // std::less
#include <iostream>
#include <queue> // std::queue
#include <utility> // std::pair
#include <math.h>

template <typename K, typename V, typename Comparator = std::less<K>>
class BinarySearchTree
{
  public:
    using key_type        = K;
    using value_type      = V;
    using key_compare     = Comparator;
    using pair            = std::pair<key_type, value_type>;
    using pointer         = pair*;
    using const_pointer   = const pair*;
    using reference       = pair&;
    using const_reference = const pair&;
    using difference_type = ptrdiff_t;
    using size_type       = size_t;

  private:
    struct BinaryNode
    {
        pair element;
        BinaryNode *left;
        BinaryNode *right;

        BinaryNode( const_reference theElement, BinaryNode *lt, BinaryNode *rt )
          : element{ theElement }, left{ lt }, right{ rt } { }
        
        BinaryNode( pair && theElement, BinaryNode *lt, BinaryNode *rt )
          : element{ std::move( theElement ) }, left{ lt }, right{ rt } { }
    };

    using node           = BinaryNode;
    using node_ptr       = node*;
    using const_node_ptr = const node*;

    node_ptr _root;
    size_type _size;
    key_compare comp;

  public:
    BinarySearchTree(): _root(nullptr), _size(0) {}
    BinarySearchTree( const BinarySearchTree & rhs ): _root(nullptr) {
        _root = clone( rhs._root );
        _size = rhs._size;
    }
    BinarySearchTree( BinarySearchTree && rhs ): _root(nullptr) {
        _root = rhs._root;
        rhs._root = nullptr;
        _size = rhs._size;

    }
    ~BinarySearchTree() {
        clear();
    }

    const_reference min() const { return min( _root )->element; }
    const_reference max() const { return max( _root )->element; }
    const_reference root() const {
        return _root->element;
    }
    bool contains( const key_type & x ) const { return contains( x, _root ); }
    value_type & find( const key_type & key ) { return find( key, _root )->element.second; }
    const value_type & find( const key_type & key ) const { return find( key, _root )->element.second; }
    bool empty() const {
        if (_size == 0){
            return true;
        } else {
            false;
        }
    }
    size_type size() const {
        return _size;
    }

    void clear() {
        clear( _root );
        _size = 0;
    }
    void insert( const_reference x ) { insert( x, _root ); }
    void insert( pair && x ) { insert( std::move( x ), _root ); }
    void erase( const key_type & x ) { erase(x, _root); }

    BinarySearchTree & operator=( const BinarySearchTree & rhs ) {

        if (_root != rhs._root){
            clear();
            _root = clone(rhs._root);
            _size = rhs._size;
        }

        return *this;
    }
    BinarySearchTree & operator=( BinarySearchTree && rhs ) {
        if (&rhs == this){
            return *this;
        }
        if(!empty()){
            clear();
        }

        _root = rhs._root;
        rhs._root = nullptr;
        _size = rhs._size;

        return *this;
    }

    int calculateHeight() const
    {
        std::queue<node_ptr> nodesInLevel;
        int height = 0;
        int nodeCount = 0; // Calculate  number of nodes in a level.
        node_ptr currentNode; // Pointer to store the address of a
                        // node in the current level.
        if (_root == nullptr) {
            return 0;
        }
        nodesInLevel.push(_root);
        while (!nodesInLevel.empty()) {
            // This while loop runs for every level and
            // increases the height by 1 in each iteration. If
            // the queue is empty then it implies that the last
            // level of tree has been parsed.
            height++;
            // Create another while loop which will insert all
            // the child nodes of the current level in the
            // queue.
    
            nodeCount = nodesInLevel.size();
            while (nodeCount--) {
                currentNode = nodesInLevel.front();
    
                // Check if the current nodes has left child and
                // insert it in the queue.
    
                if (currentNode->left != nullptr) {
                    nodesInLevel.push(currentNode->left);
                }
    
                // Check if the current nodes has right child
                // and insert it in the queue.
                if (currentNode->right != nullptr) {
                    nodesInLevel.push(currentNode->right);
                }
    
                // Once the children of the current node are
                // inserted. Delete the current node.
    
                nodesInLevel.pop();
            }
        }
        return height;
    }





  private:
    void insert( const_reference x, node_ptr & t ) {
        if (t == nullptr){
            t = new BinaryNode{x,nullptr,nullptr};
            _size++;
        } else if (comp(x.first , t->element.first)){
            insert(x,t->left);
        } else if (comp(t->element.first, x.first)){
            insert(x, t->right);
        } else{
            t->element.second = x.second;
        }
    }
    void insert( pair && x, node_ptr & t ) {
        if (t == nullptr){
            t = new BinaryNode{std::move(x),nullptr,nullptr};
            _size++;
        } else if (comp(x.first , t->element.first)){
            insert(std::move(x),t->left);
        } else if (comp(t->element.first, x.first)){
            insert(std::move(x), t->right);
        } else {
            t->element.second = std::move(x.second);
        }
    }

    void erase( const key_type & x, node_ptr & t ) {
        if ( t== nullptr){
            return;
        }
        if ( comp(x, t->element.first)){
            erase(x,t->left);
        } else if (comp(t->element.first, x)){
            erase(x,t->right);
        } else if( t->left != nullptr && t->right != nullptr ){
            t->element = min(t->right)->element;
            erase(t->element.first,t->right);
        } else {
            node_ptr old = t;
            t = ( t->left != nullptr ) ? t->left : t->right;
            delete old;
            _size--;
        }
    }

    const_node_ptr min( const_node_ptr t ) const {
        if (t== nullptr){
            return nullptr;
        }
        if (t->left == nullptr){
            return t;
        }
        return min(t->left);
    }
    const_node_ptr max( const_node_ptr t ) const {
        if (t != nullptr){
            while (t->right != nullptr){
                t = t->right;
            }
        }
        return t;
    }

    bool contains( const key_type & x, const_node_ptr t ) const {
        if (t==nullptr){
            return false;
        } else if (comp(x, t->element.first)){
            return contains(x,t->left);
        } else if (comp(t->element.first, x)){
            return contains(x,t->right);
        } else{
            return true;
        }
    }
    node_ptr find( const key_type & key, node_ptr t ) {
        
        if (t==nullptr){
            return nullptr;
        } else if (key < t->element.first){
            return find(key,t->left);
        } else if (t->element.first < key){
            return find(key,t->right);
        } else{
            return t;
        }

    }
    const_node_ptr find( const key_type & key, const_node_ptr t ) const {
        if (t==nullptr){
            return nullptr;
        } else if (key < t->element.first){
            return find(key,t->left);
        } else if (t->element.first < key){
            return find(key,t->right);
        } else{
            return t;
        }
    }

    void clear( node_ptr & t ) {
        if(t!= nullptr){
            clear(t->left);
            clear(t->right);
            delete t;
        }
        t = nullptr;
    }
    
    node_ptr clone ( const_node_ptr t ) const {
        if (t== nullptr){
            return nullptr;
        } else{
            return new node{ std::move(t->element), clone( t->left ), clone( t->right ) };
        }
    }

  public:
    template <typename KK, typename VV, typename CC>
    friend void printLevelByLevel( const BinarySearchTree<KK, VV, CC>& bst, std::ostream & out );

    template <typename KK, typename VV, typename CC>
    friend std::ostream& printNode(std::ostream& o, const typename BinarySearchTree<KK, VV, CC>::node& bn);

    template <typename KK, typename VV, typename CC>
    friend void printTree( const BinarySearchTree<KK, VV, CC>& bst, std::ostream & out );

    template <typename KK, typename VV, typename CC>
    friend void printTree(typename BinarySearchTree<KK, VV, CC>::const_node_ptr t, std::ostream & out, unsigned depth );

    template <typename KK, typename VV, typename CC>
    friend void vizTree(
        typename BinarySearchTree<KK, VV, CC>::const_node_ptr node, 
        std::ostream & out,
        typename BinarySearchTree<KK, VV, CC>::const_node_ptr prev
    );

    template <typename KK, typename VV, typename CC>
    friend void vizTree(
        const BinarySearchTree<KK, VV, CC> & bst, 
        std::ostream & out
    );
};

template <typename KK, typename VV, typename CC>
std::ostream& printNode(std::ostream & o, const typename BinarySearchTree<KK, VV, CC>::node & bn) {
    return o << '(' << bn.element.first << ", " << bn.element.second << ")";
}

template <typename KK, typename VV, typename CC>
void printLevelByLevel( const BinarySearchTree<KK, VV, CC>& bst, std::ostream & out = std::cout ) {
    using node = typename BinarySearchTree<KK, VV, CC>::node;
    using node_ptr = typename BinarySearchTree<KK, VV, CC>::node_ptr;
    using const_node_ptr = typename BinarySearchTree<KK, VV, CC>::const_node_ptr;

    if (bst._root == nullptr){
        return;
    }

    std::queue<node_ptr> q;

    q.push(bst._root);
    
    int level = 0;

    while (q.empty() == false) {

        int allNulls = 0;

        for (int i = 0; i < pow(2,level); i++){

            const_node_ptr temp = q.front(); // temp node ptr

            // Print front of queue and remove it from queue
            if (temp == nullptr){
                out << "null ";
            } else {
                printNode<KK,VV,CC>(out, *temp);
            }
            
            q.pop();
            
            //add children to queue
            if (temp == nullptr){ // if temp is null
                q.push(nullptr);
                q.push(nullptr);

            } else { // if temp is not null

                /* Enqueue left child */
                if (temp->left == nullptr){
                    q.push(nullptr);
                } else {
                    q.push(temp->left);
                    allNulls++;
                }

                /*Enqueue right child */
                if (temp->right == nullptr){
                    q.push(nullptr);
                } else {
                    q.push(temp->right);
                    allNulls++;
                }
            }
        }

        if (allNulls == 0){
            return;
        }

        out << std::endl;
        level++;
    }
    
}

template <typename KK, typename VV, typename CC>
void printTree( const BinarySearchTree<KK, VV, CC> & bst, std::ostream & out = std::cout ) { printTree<KK, VV, CC>(bst._root, out ); }

template <typename KK, typename VV, typename CC>
void printTree(typename BinarySearchTree<KK, VV, CC>::const_node_ptr t, std::ostream & out, unsigned depth = 0 ) {
    if (t != nullptr) {
        printTree<KK, VV, CC>(t->right, out, depth + 1);
        for (unsigned i = 0; i < depth; ++i)
            out << '\t';
        printNode<KK, VV, CC>(out, *t) << '\n';
        printTree<KK, VV, CC>(t->left, out, depth + 1);
    }
}

template <typename KK, typename VV, typename CC>
void vizTree(
    typename BinarySearchTree<KK, VV, CC>::const_node_ptr node, 
    std::ostream & out,
    typename BinarySearchTree<KK, VV, CC>::const_node_ptr prev = nullptr
) {
    if(node) {
        std::hash<KK> khash{};

        out << "\t" "node_" << (uint32_t) khash(node->element.first)
            << "[label=\"" << node->element.first 
            << " [" << node->element.second << "]\"];" << std::endl;
        
        if(prev)
            out << "\tnode_" << (uint32_t) khash(prev->element.first) <<  " -> ";
        else
            out << "\t";
        
        out << "node_" << (uint32_t) khash(node->element.first) << ";" << std::endl;
    
        vizTree<KK, VV, CC>(node->left, out, node);
        vizTree<KK, VV, CC>(node->right, out, node);
    }
}

template <typename KK, typename VV, typename CC>
void vizTree(
    const BinarySearchTree<KK, VV, CC> & bst, 
    std::ostream & out = std::cout
) {
    out << "digraph Tree {" << std::endl;
    vizTree<KK, VV, CC>(bst._root, out);
    out << "}" << std::endl;
}
