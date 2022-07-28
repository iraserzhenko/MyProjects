#ifndef UNORDERED_SET__UNORDERED_SET_H_
#define UNORDERED_SET__UNORDERED_SET_H_
#include <iostream>
#include <vector>
#include <list>
template<typename KeyT> class UnorderedSet {
 public:
  size_t n_buckets = 0;
  size_t n_keys = 0;
  std::vector<std::list<KeyT>> hashtable;
  UnorderedSet() = default;
  explicit UnorderedSet(size_t count) {
    n_buckets = count;
    hashtable = std::vector<std::list<KeyT>>(count);
  }
  using Iterator = KeyT*;
  template <class Iterator, class = std::enable_if_t<std::is_base_of<
                                std::forward_iterator_tag, typename std::iterator_traits<Iterator>::iterator_category>>>
  UnorderedSet(Iterator first, Iterator last) {
    n_buckets = 0;
    for (auto it = first; it != last; it++) {
      n_buckets++;
    }
    n_keys = 0;
    hashtable = std::vector<std::list<KeyT>>(n_buckets);
    for (auto it = first; it != last; it++) {
      auto idx = std::hash<KeyT>{}(*it) % n_buckets;
      hashtable[idx].push_back(*it);
      n_keys++;
    }
  }
  UnorderedSet(const UnorderedSet<KeyT>& set) {  //  copy constructor
    hashtable.clear();
    hashtable = set.hashtable;
    n_buckets = set.n_buckets;
    n_keys = set.n_keys;
  }
  UnorderedSet(UnorderedSet<KeyT>&& set) noexcept { //  move constructor
    hashtable = std::move(set.hashtable);
    n_buckets = set.n_buckets;
    n_keys = set.n_keys;
    set.n_buckets = 0;
    set.n_keys = 0;
  }
  UnorderedSet& operator=(const UnorderedSet<KeyT>& other) {  //  copy assigment
    if (this != &other) {
      hashtable.clear();
      hashtable = std::vector<std::list<KeyT>>(other.n_buckets);
      for (size_t i = 0; i < other.n_buckets; i++) {
        for (auto elem : other.hashtable[i]) {
          hashtable[i].push_back(elem);
        }
      }
      n_buckets = other.n_buckets;
      n_keys = other.n_keys;
    }
    return *this;
  }
  UnorderedSet& operator=(UnorderedSet<KeyT>&& other) noexcept {  //  move assigment
    if (this != &other) {
      hashtable.clear();
      hashtable = std::move(other.hashtable);
      n_buckets = other.n_buckets;
      n_keys = other.n_keys;
      other.n_buckets = 0;
      other.n_keys = 0;
    }
    return *this;
  }
  ~UnorderedSet() {
    hashtable.clear();
    n_buckets = 0;
    n_keys = 0;
  }
  size_t Size() const {
    return n_keys;
  }
  bool Empty() const {
    return (n_keys == 0);
  }
  void Clear() {
    hashtable.clear();
    n_buckets = 0;
    n_keys = 0;
  }
  void Reallocate(size_t new_buckets) {
    auto copy = std::vector<std::list<KeyT>>(new_buckets);
    for (size_t i = 0; i < n_buckets; i++) {
      for (auto elem : hashtable[i]) {
        size_t idx = std::hash<KeyT>{}(elem) % (new_buckets);
        copy[idx].push_back(std::move_if_noexcept(elem));
      }
    }
    hashtable.clear();
    hashtable = copy;
    n_buckets = new_buckets;
  }
  void Insert(const KeyT& key) {
    if (Find(key) == 1) {
      return;
    }
    if (n_keys < n_buckets) {
      size_t idx = std::hash<KeyT>{}(key) % n_buckets;
      hashtable[idx].push_back(key);
      n_keys++;
    } else {
      if (n_buckets == 0) {
        hashtable = std::vector<std::list<KeyT>>(n_buckets + 1);
        n_buckets++;
        n_keys++;
        size_t idx = std::hash<KeyT>{}(key) % n_buckets;
        hashtable[idx].push_back(key);
      } else {
        Reallocate(2 * n_buckets);
        size_t idx = std::hash<KeyT>{}(key) % n_buckets;
        hashtable[idx].push_back(key);
        n_keys++;
      }
    }
  }
  void Insert(KeyT&& key) {
    if (Find(key) == 1) {
      return;
    }
    if (n_keys < n_buckets) {
      size_t idx = std::hash<KeyT>{}(key) % n_buckets;
      hashtable[idx].push_back(std::move(key));
      n_keys++;
    } else {
      if (n_buckets == 0) {
        hashtable = std::vector<std::list<KeyT>>(n_buckets + 1);
        n_buckets++;
        n_keys++;
        size_t idx = std::hash<KeyT>{}(key) % n_buckets;
        hashtable[idx].push_back(std::move(key));
      } else {
        Reallocate(2 * n_buckets);
        size_t idx = std::hash<KeyT>{}(key) % n_buckets;
        hashtable[idx].push_back(std::move(key));
        n_keys++;
      }
    }
  }
  void Erase(const KeyT& key) {
    size_t idx = std::hash<KeyT>{}(key) % n_buckets;
    for (auto it = hashtable[idx].begin(); it != hashtable[idx].end(); it++) {
      if (*it == key) {
        hashtable[idx].erase(it);
        n_keys--;
        return;
      }
    }
  }
  bool Find(const KeyT& key) const {
    if (n_buckets == 0) {
      return false;
    }
    size_t idx = std::hash<KeyT>{}(key) % n_buckets;
    for (auto elem : hashtable[idx]) {
      if (key == elem) {
        return true;
      }
    }
    return false;
  }
  void Rehash(size_t new_bucket_count) {
    if (new_bucket_count == n_buckets || n_keys > new_bucket_count) {
      return;
    }
    Reallocate(new_bucket_count);
  }
  void Reserve(size_t new_bucket_count) {
    if (new_bucket_count > n_buckets) {
      Reallocate(new_bucket_count);
    }
  }
  size_t BucketCount() const {
    return n_buckets;
  }
  size_t BucketSize(size_t id) const {
    if (id >= n_buckets) {
      return 0;
    }
    return hashtable[id].size();
  }
  size_t Bucket(const KeyT& key) const {
    size_t idx = std::hash<KeyT>{}(key) % n_buckets;
    return idx;
  }
  double LoadFactor() const {
    if (n_buckets == 0) {
      return 0;
    }
    double result = static_cast<double>(n_keys) / n_buckets;
    return result;
  }
};
#endif
