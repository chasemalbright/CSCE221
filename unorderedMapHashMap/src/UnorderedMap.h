#include <cstddef>    // size_t
#include <functional> // std::hash
#include <utility>    // std::pair
#include <iostream>

#include "primes.h"

template <typename Key, typename T, typename Hash = std::hash<Key>, typename Pred = std::equal_to<Key>>
class UnorderedMap {
    public:

    using key_type = Key;
    using mapped_type = T;
    using hasher = Hash;
    using key_equal = Pred;
    using value_type = std::pair<const key_type, mapped_type>;
    using reference = value_type &;
    using const_reference = const value_type &;
    using pointer = value_type *;
    using const_pointer = const value_type *;
    using size_type = size_t;
    using difference_type = ptrdiff_t;

    private:

    struct HashNode {
        HashNode *next;
        value_type val;

        HashNode(HashNode *next = nullptr) : next{next} {}
        HashNode(const value_type & val, HashNode * next = nullptr) : next { next }, val { val } { }
        HashNode(value_type && val, HashNode * next = nullptr) : next { next }, val { std::move(val) } { }
    };

    HashNode **_buckets;
    size_type _size;
    size_type _bucket_count;

    HashNode _head;

    Hash _hash;
    key_equal _equal;

    static size_type _range_hash(size_type hash_code, size_type bucket_count) {
        return hash_code % bucket_count;
    }

    public:

    class iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = std::pair<const key_type, mapped_type>;
        using difference_type = ptrdiff_t;
        using pointer = value_type *;
        using reference = value_type &;

    private:
        friend class UnorderedMap<Key, T, Hash, key_equal>;
        using HashNode = typename UnorderedMap<Key, T, Hash, key_equal>::HashNode;

        HashNode * _node;

        explicit iterator(HashNode *ptr) noexcept : _node{ptr} {}

    public:
        iterator() : _node(nullptr) {};
        iterator(const iterator &) = default;
        iterator(iterator &&) = default;
        ~iterator() = default;
        iterator &operator=(const iterator &) = default;
        iterator &operator=(iterator &&) = default;
        reference operator*() const {return this->_node->val;}
        pointer operator->() const {return  &(this->_node->val);}

        iterator &operator++() {
            _node = _node->next;
            return *this;
        }
        iterator operator++(int) {
            iterator temp = iterator(this->_node);
            ++(*this);
            return temp;
        }
        bool operator==(const iterator &other) const noexcept {
            return this->_node == other._node;
        }
        bool operator!=(const iterator &other) const noexcept {
            return !(this->_node == other._node);
        }
    };

    class local_iterator {
        public:
            using iterator_category = std::forward_iterator_tag;
            using value_type = std::pair<const key_type, mapped_type>;
            using difference_type = ptrdiff_t;
            using pointer = value_type *;
            using reference = value_type &;

        private:
            friend class UnorderedMap<Key, T, Hash, key_equal>;
            using HashNode = typename UnorderedMap<Key, T, Hash, key_equal>::HashNode;

            UnorderedMap * _map;
            HashNode * _node;
            size_type _bucket;

            explicit local_iterator(UnorderedMap * map, HashNode *ptr, size_type bucket) noexcept : _map{map}, _node{ptr}, _bucket{bucket} {}
        public:
            local_iterator() : _node(nullptr) {};
            local_iterator(const local_iterator &) = default;
            local_iterator(local_iterator &&) = default;
            ~local_iterator() = default;
            local_iterator &operator=(const local_iterator &) = default;
            local_iterator &operator=(local_iterator &&) = default;
            reference operator*() const { return this->_node->val; }
            pointer operator->() const { return &this->_node->val; }
            local_iterator & operator++() {

                if (_node->next == nullptr){
                    _node = nullptr;
                } else if (_map->bucket(_node->val.first) != _map->bucket(_node->next->val.first) ){
                    _node = nullptr;
                } else {
                    _node = _node->next;
                }

                return *this;
            }
            local_iterator operator++(int) {

                local_iterator temp = local_iterator(_map,_node,_bucket);
                ++(*this);
                return temp;
            }
            bool operator==(const local_iterator &other) const noexcept {
                return this->_node == other._node;
            }
            bool operator!=(const local_iterator &other) const noexcept {
                return !(this->_node == other._node);
            }
    };

private:

    size_type _bucket(size_t code) const { return _range_hash( code, this->_bucket_count); }
    size_type _bucket(const Key &key) const { return _bucket(_hash(key));}

    void _insert_before(size_type bucket, HashNode *node) {
        size_type positioninarray = bucket; // get bucket #
        HashNode* &currentpointer = _buckets[positioninarray];

        if (currentpointer == nullptr){ // edge case

            if (_head.next){
                size_t bucketkey = _bucket(_head.next->val.first);
                _buckets[bucketkey] = node;
                node->next = _head.next;            // handle case when != null
            }

            _head.next = node;
            currentpointer = &_head;
        }else { // if it exists
            node->next = currentpointer->next;
            currentpointer->next = node;
        }
        _size++; // increment size
    }

    HashNode*& _bucket_begin(size_type bucket) {
        if (_buckets[bucket] == nullptr) { return _buckets[bucket];} // returns the first element in bucket
        return _buckets[bucket]->next;
    }

    HashNode* _find_prev(size_type code, size_type bucket, const Key & key) {

        if (_buckets[bucket] == nullptr){return _buckets[bucket];} // if it is null return and break

        HashNode * curr = _buckets[bucket]->next; // one ahead
        HashNode * prev = _buckets[bucket]; // at node

        while(curr != nullptr){ // find end
            if (bucket != _bucket(key)) {return nullptr;} // if not in bucket return null
            if (_equal(curr->val.first,key)){// if found return 
                return prev;
            }

            prev = prev->next; // traverse
            curr = curr->next;
        }

        return nullptr; // all else fails return null
    }

    HashNode* _find_prev(const Key & key) {
        size_t code = _hash(key); // find the code key
        size_t index = bucket(key); // get index
        return _find_prev(code,index,key); // find node before
    }

    void _erase_after(HashNode * prev) {
        HashNode * temp = prev->next;
        size_type bucketIndex = _bucket(temp->val.first);

        prev->next = prev->next->next;
        delete temp;
        _size--;

        size_type nextBucketIndex = std::numeric_limits<size_type>::max();

        if (prev->next != nullptr){

            nextBucketIndex = _bucket(prev->next->val.first);

            if (_buckets[nextBucketIndex] == temp){
                _buckets[nextBucketIndex] = prev;
            }
        }

        if (_buckets[bucketIndex] == prev && bucketIndex != nextBucketIndex){
            _buckets[bucketIndex] = nullptr;
        }



    }
//move_content(other,*this) &&
public:
    explicit UnorderedMap(size_type bucket_count, const Hash & hash = Hash { },
                const key_equal & equal = key_equal { }): _size(0), _hash(hash), _equal(equal), _head{},_bucket_count(next_greater_prime(bucket_count)) {

                    _buckets = new HashNode * [_bucket_count](); // create empty array with nullptrs
        
    }

    ~UnorderedMap() {
        clear();
    }

    UnorderedMap(const UnorderedMap & other): _size(0), _hash(other._hash), _equal(other._equal), _head{}, _bucket_count(other._bucket_count) {
        _buckets = new HashNode*[_bucket_count]();
        for (auto poin = other._head.next; poin != nullptr; poin = poin->next ){
            insert(poin->val);
        }
    }

    UnorderedMap(UnorderedMap && other) {
        _equal = other._equal;
        _buckets = other._buckets;
        _bucket_count = other._bucket_count;
        _size = other._size;
        _hash = other._hash;
        _head.next = other._head.next;

        if (_head.next != nullptr){
            _buckets[_bucket(other._head.next->val.first)] = &_head;
        }

        other._hash = Hash{};

        other._equal = key_equal{};

        other._size = 0;
        
        other._head.next = nullptr;
        other._buckets = new HashNode *[other._bucket_count]();
        


    }

    UnorderedMap & operator=(const UnorderedMap & other) {
        if (this == &other){
            return *this;
        } else {
            if (this != nullptr){
                clear();
                delete[] _buckets;
            }
            _bucket_count = other._bucket_count;
            _size = 0;



            _buckets = new HashNode*[other._bucket_count]();
            for (auto poin = other._head.next; poin != nullptr; poin = poin->next ){
                insert(poin->val);
            }


        }
    }

    UnorderedMap & operator=(UnorderedMap && other) {
        clear();
        delete[] _buckets;
        _equal = other._equal;
        _buckets = other._buckets;
        _bucket_count = other._bucket_count;
        _size = other._size;
        _hash = other._hash;
        _head.next = other._head.next;

        if (_head.next != nullptr){
            _buckets[_bucket(other._head.next->val.first)] = &_head;
        }

        other._hash = Hash{};

        other._equal = key_equal{};

        other._size = 0;
        
        other._head.next = nullptr;
        other._buckets = new HashNode *[other._bucket_count]();

        
    }

    void clear() noexcept {
        while(_size != 0){
            erase(begin());
        }
    }

    size_type size() const noexcept { return this->_size; }

    bool empty() const noexcept { return this->_size == 0; }

    size_type bucket_count() const noexcept { return this->_bucket_count; }

    iterator begin() { return iterator(_head.next); }

    iterator end() { return iterator(nullptr); }

    local_iterator begin(size_type n) { return local_iterator(this,_bucket_begin(n),n); }

    local_iterator end(size_type n) { return local_iterator(this,nullptr,n); }

    size_type bucket_size(size_type n) { 

        local_iterator temp = begin(n);
        size_type size = 0;
        while (temp != end(n)){
            ++temp;
            ++size;
        }
        return size;
     }

    float load_factor() const { return (float)_size/_bucket_count;}

    size_type bucket(const Key & key) const { return _hash(key)%_bucket_count;}

    std::pair<iterator, bool> insert(value_type && value) {

        auto temp = _find_prev(value.first); // create temp variable

        if (temp != nullptr){ // if it exists
            return std::pair<iterator,bool>(iterator(temp->next),false); // false case
        } else{
            size_type keyhash = _hash(value.first);
            size_type buck = _bucket(keyhash);

            HashNode * ins = new HashNode(std::move(value)); // allocate new mem

            _insert_before(buck,ins);

            return std::pair<iterator,bool>(iterator(ins),true); // true case
        }
    }

    std::pair<iterator, bool> insert(const value_type & value) {

        auto temp = _find_prev(value.first); // create temp variable

        if (temp != nullptr){ // if it exists
            return std::pair<iterator,bool>(iterator(temp->next),false); // false case
        } else{
            size_type keyhash = _hash(value.first);
            size_type buck = _bucket(keyhash);

            HashNode * ins = new HashNode(value); // allocate new mem

            _insert_before(buck,ins);

            return std::pair<iterator,bool>(iterator(ins),true); // true case
        }
    }

    iterator find(const Key & key) {
        HashNode * temp = _find_prev(key); // create temp var

        if (temp == nullptr){
            return iterator(nullptr);
        }
        return iterator(temp->next);
    }

    T& operator[](const Key & key) {
        HashNode* check = _find_prev(key);

        if(check == nullptr){
            auto temp = std::make_pair(key, mapped_type{});

            iterator temp2 = insert(temp).first;

            return temp2->second;
        } else {
            return check->next->val.second;
        }



    }

    iterator erase(iterator pos) {
        HashNode * prev = _find_prev(pos->first);
        _erase_after(prev);
        return iterator(prev->next);
    }

    size_type erase(const Key & key) {
        HashNode * prevNode = _find_prev(key);
        if (prevNode != nullptr){
            _erase_after(prevNode);
            return 1;
        } else {
            return 0;
        }
    }

    template<typename KK, typename VV>
    friend void print_map(const UnorderedMap<KK, VV> & map, std::ostream & os);
};

template<typename K, typename V>
void print_map(const UnorderedMap<K, V> & map, std::ostream & os = std::cout) {
    using size_type = typename UnorderedMap<K, V>::size_type;
    using HashNode = typename UnorderedMap<K, V>::HashNode;

    HashNode const * node = map._head.next;
    os << "List: ";
    do {
        if(node) {
            os << "(" << node->val.first << ", " << node->val.second << ") ";
        } else {
            os << "(nullptr)";
            break;
        }

        node = node->next;
    } while(true);
    os << std::endl;

    for(size_type bucket = 0; bucket < map.bucket_count(); bucket++) {
        os << bucket << ": ";

        HashNode const * node = map._buckets[bucket];

        if(!node) {
            os << "(nullptr)";
        } else {
            while((node = node->next) && map.bucket(node->val.first) == bucket) {
                os << "(" << node->val.first << ", " << node->val.second << ") ";
            }
        }
        os << std::endl;
    }
}