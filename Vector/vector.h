#ifndef VECTOR__VECTOR_H_
#define VECTOR__VECTOR_H_
#include <iostream>
#include <memory>
template <typename T>
class Vector {
 public:
  using SizeType = size_t;
  using ValueType = T;
  using Pointer = T*;
  using ConstPointer = const T*;
  using Reference = T&;
  using ConstReference = const T&;
  using Iterator = T*;
  using ConstIterator = const T*;
  using ReverseIterator = std::reverse_iterator<Iterator>;
  using ConstReverseIterator = std::reverse_iterator<ConstIterator>;
  SizeType size = 0;
  SizeType capacity = 0;
  T* buffer = nullptr;
  Vector() {
    size = 0;
    capacity = 0;
    buffer = nullptr;
  }
  explicit Vector(SizeType count) {
    buffer = new ValueType[count];
    size = count;
    capacity = count;
  }
  Vector(SizeType new_size, const ValueType& value) {
    if (new_size > 0) {
      buffer = new ValueType[new_size];
      size = new_size;
      capacity = new_size;
      try {
        for (SizeType i = 0; i < new_size; i++) {
          buffer[i] = value;
        }
      } catch (...) {
        delete[] buffer;
        size = 0;
        capacity = 0;
        throw;
      }
    } else {
      size = 0;
      capacity = 0;
      buffer = nullptr;
    }
  }
  Vector(const Vector<ValueType>& other) {  //  конструктор копирования
    if (other.size > 0) {
      auto copy = new ValueType[other.capacity];
      try {
        for (SizeType i = 0; i < other.size; i++) {
          copy[i] = other.buffer[i];
        }
      } catch (...) {
        delete[] copy;
        throw;
      }
      buffer = std::move(copy);
      copy = nullptr;
      capacity = other.capacity;
      size = other.size;
    }
  }
  Vector(Vector<ValueType>&& other) noexcept {  // конструктор перемещения
    size = other.size;
    capacity = other.capacity;
    buffer = std::move(other.buffer);
    other.buffer = nullptr;
    other.size = 0;
    other.capacity = 0;
  }
  Vector& operator=(const Vector<ValueType>& other) {  // копирующее присваивание
    if (this != &other) {
      delete[] buffer;
      buffer = nullptr;
      size = 0;
      capacity = 0;
      if (other.capacity > 0) {
        buffer = new ValueType[other.size];
        capacity = other.size;
        for (; size < other.size; size++) {
          buffer[size] = other.buffer[size];
        }
      } else {
        capacity = other.capacity;
        size = other.size;
      }
    }
    return *this;
  }
  Vector& operator=(Vector<ValueType>&& other) noexcept {  // перемещающее присваивание
    if (this != &other) {
      capacity = other.capacity;
      size = other.size;
      delete[] buffer;
      buffer = std::move(other.buffer);
      other.buffer = nullptr;
      other.capacity = 0;
      other.size = 0;
    }
    return *this;
  }
  ~Vector() {
    delete[] buffer;
    size = 0;
    capacity = 0;
  }
  template <class Iterator, class = std::enable_if_t<std::is_base_of_v<
                                std::forward_iterator_tag, typename std::iterator_traits<Iterator>::iterator_category>>>
  Vector(Iterator first, Iterator last) {
    int test_size = last - first;
    if (test_size > 0) {
      size = 0;
      buffer = new ValueType[test_size];
      try {
        for (auto it = first; it != last; it++) {
          buffer[size++] = *it;
        }
      } catch (...) {
        delete[] buffer;
        size = 0;
        capacity = 0;
        throw;
      }
      capacity = size;
    } else {
      buffer = nullptr;
      size = 0;
      capacity = 0;
    }
  }
  Vector(const std::initializer_list<ValueType>& list) {
    capacity = list.size();
    size = list.size();
    if (size > 0) {
      buffer = new ValueType[size];
      try {
        std::copy(list.begin(), list.end(), buffer);
      } catch (...) {
        delete[] buffer;
        buffer = nullptr;
        size = 0;
        capacity = 0;
        throw;
      }
    } else {
      buffer = nullptr;
    }
  }
  Reference operator[](SizeType idx) {
    return *(buffer + idx);
  }
  ConstReference operator[](SizeType idx) const {
    return *(buffer + idx);
  }
  [[nodiscard]] SizeType Size() const {
    return size;
  }
  [[nodiscard]] SizeType Capacity() const {
    return capacity;
  }
  [[nodiscard]] bool Empty() const {
    return (size == 0);
  }
  Reference At(SizeType idx) {
    if (idx >= 0 && idx < size) {
      return *(buffer + idx);
    }
    throw std::out_of_range{"At"};
  }
  ConstReference At(SizeType idx) const {
    if (idx >= 0 && idx < size) {
      return *(buffer + idx);
    }
    throw std::out_of_range{"At"};
  }
  Reference Front() {
    return buffer[0];
  }
  ConstReference Front() const {
    return buffer[0];
  }
  Reference Back() {
    return buffer[size - 1];
  }
  ConstReference Back() const {
    return buffer[size - 1];
  }
  Pointer Data() {
    return buffer;
  }
  ConstPointer Data() const {
    return buffer;
  }
  void Swap(Vector<ValueType>& other) {
    if (this != &other) {
      SizeType tmp_size = size;
      SizeType tmp_cap = capacity;
      Pointer tmp = buffer;
      buffer = nullptr;
      buffer = other.buffer;
      size = other.size;
      capacity = other.capacity;
      other.buffer = nullptr;
      other.buffer = tmp;
      other.size = tmp_size;
      other.capacity = tmp_cap;
      tmp = nullptr;
    }
  }
  void Resize(SizeType new_size) {
    if (new_size > capacity) {
      auto copy = new ValueType[new_size];
      try {
        for (SizeType i = 0; i < size; i++) {
          copy[i] = std::move_if_noexcept(buffer[i]);
        }
      } catch (...) {
        delete[] copy;
        throw;
      }
      delete[] buffer;
      buffer = std::move(copy);
      copy = nullptr;
      capacity = new_size;
      size = new_size;
    } else {
      if (new_size > 0) {
        size = new_size;
      } else {
        delete[] buffer;
        buffer = nullptr;
        size = new_size;
      }
    }
  }
  void Resize(SizeType new_size, const ValueType& value) {
    if (new_size > capacity) {
      auto copy = new ValueType[new_size];
      try {
        for (SizeType i = 0; i < size; i++) {
          copy[i] = std::move_if_noexcept(buffer[i]);
        }
        for (SizeType i = size; i < new_size; i++) {
          copy[i] = value;
        }
      } catch (...) {
        delete[] copy;
        throw;
      }
      delete[] buffer;
      buffer = std::move(copy);
      copy = nullptr;
      capacity = new_size;
      size = new_size;
    } else {
      if (new_size > 0) {
        if (size < new_size) {
          for (SizeType i = size; i < new_size; i++) {
            buffer[i] = value;
          }
        }
        size = new_size;
      } else {
        delete[] buffer;
        buffer = nullptr;
        size = new_size;
      }
    }
  }
  void Reserve(SizeType new_cap) {
    if (new_cap > capacity) {
      auto copy = new ValueType[new_cap];
      try {
        for (SizeType i = 0; i < size; i++) {
          copy[i] = std::move_if_noexcept(buffer[i]);
        }
      } catch (...) {
        delete[] copy;
        throw;
      }
      delete[] buffer;
      buffer = std::move(copy);
      copy = nullptr;
      capacity = new_cap;
    }
  }
  void ShrinkToFit() {
    if (size < capacity) {
      if (size > 0) {
        auto copy = new ValueType[size];
        try {
          for (SizeType i = 0; i < size; i++) {
            copy[i] = std::move_if_noexcept(buffer[i]);
          }
        } catch (...) {
          delete[] copy;
          throw;
        }
        delete[] buffer;
        buffer = std::move(copy);
        copy = nullptr;
        capacity = size;
      } else {
        delete[] buffer;
        buffer = nullptr;
        capacity = size;
      }
    }
  }
  void Clear() {
    size = 0;
  }
  void PushBack(ValueType&& element) {
    if (capacity == 0) {
      auto copy = new ValueType[capacity + 1];
      try {
        copy[size] = std::move(element);
      } catch (...) {
        delete[] copy;
        throw;
      }
      delete[] buffer;
      buffer = copy;
      capacity++;
      size++;
    } else if (size < capacity) {
      buffer[size] = std::move(element);
      size++;
    } else {
      auto copy = new ValueType[capacity * 2];
      try {
        for (SizeType i = 0; i < size; i++) {
          copy[i] = std::move(buffer[i]);
        }
        copy[size] = std::move(element);
      } catch (...) {
        delete[] copy;
        throw;
      }
      delete[] buffer;
      buffer = copy;
      size++;
      capacity *= 2;
    }
  }
  void PushBack(const ValueType& element) {
    if (capacity == 0) {
      auto copy = new ValueType[capacity + 1];
      try {
        copy[size] = element;
      } catch (...) {
        delete[] copy;
        throw;
      }
      delete[] buffer;
      buffer = copy;
      size++;
      capacity++;
    } else if (size < capacity) {
      buffer[size] = element;
      size++;
    } else {
      auto copy = new ValueType[capacity * 2];
      try {
        for (SizeType i = 0; i < size; i++) {
          copy[i] = buffer[i];
        }
        copy[size] = element;
      } catch (...) {
        delete[] copy;
        throw;
      }
      delete[] buffer;
      buffer = copy;
      size++;
      capacity *= 2;
    }
  }
  void PopBack() {
    if (size > 0) {
      size--;
    }
  }

  Iterator begin() noexcept {  //  NOLINT
    return buffer;
  }
  ConstIterator begin() const noexcept {  //  NOLINT
    return buffer;
  }
  ConstIterator cbegin() const noexcept {  //  NOLINT
    return buffer;
  }
  Iterator end() noexcept {  //  NOLINT
    return buffer + size;
  }
  ConstIterator end() const noexcept {  //  NOLINT
    return buffer + size;
  }
  ConstIterator cend() const noexcept {  //  NOLINT
    return buffer + size;
  }
  ReverseIterator rbegin() noexcept {  //  NOLINT
    return ReverseIterator(end());
  }
  ConstReverseIterator rbegin() const noexcept {  //  NOLINT
    return ConstReverseIterator(end());
  }
  ReverseIterator rend() noexcept {  //  NOLINT
    return ReverseIterator(begin());
  }
  ConstReverseIterator rend() const noexcept {  //  NOLINT
    return ConstReverseIterator(begin());
  }
  ConstReverseIterator crbegin() const noexcept {  //  NOLINT
    return ConstReverseIterator(end());
  }
  ConstReverseIterator crend() const noexcept {  //  NOLINT
    return ConstReverseIterator(begin());
  }
};

template <typename T>
bool operator==(const Vector<T>& first, const Vector<T>& sec) {
  if (first.Size() != sec.Size()) {
    return false;
  }
  int all_size = first.Size();
  for (int i = 0; i < all_size; i++) {
    if (first.buffer[i] != sec.buffer[i]) {
      return false;
    }
  }
  return true;
}
template <typename T>
bool operator<(const Vector<T>& first, const Vector<T>& sec) {
  return std::lexicographical_compare(first.begin(), first.end(), sec.begin(), sec.end());
}
template <typename T>
bool operator<=(const Vector<T>& first, const Vector<T>& sec) {
  return (first < sec || first == sec);
}
template <typename T>
bool operator>(const Vector<T>& first, const Vector<T>& sec) {
  return !(first <= sec);
}
template <typename T>
bool operator>=(const Vector<T>& first, const Vector<T>& sec) {
  return !(first < sec);
}
template <typename T>
bool operator!=(const Vector<T>& first, const Vector<T>& sec) {
  return !(first == sec);
}
#endif