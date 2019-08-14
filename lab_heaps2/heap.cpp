
/**
 * @file heap.cpp
 * Implementation of a heap class.
 */

template <class T, class Compare>
size_t heap<T, Compare>::root() const
{
    return 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild(size_t currentIdx) const
{
    return currentIdx * 2;
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild(size_t currentIdx) const
{
    return currentIdx * 2 + 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t currentIdx) const
{
    return currentIdx/2;
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild(size_t currentIdx) const
{
    if (_elems.size() - 1 >= currentIdx * 2) {
      return true;
    }
    return false;
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild(size_t currentIdx) const
{
    size_t leftChildIdx = leftChild(currentIdx);
    size_t rightChildIdx = rightChild(currentIdx);
    if (leftChildIdx > _elems.size() - 1) {
      return 0;
    }
    if (rightChildIdx > _elems.size() - 1) {
      return leftChildIdx;
    } else {
      if (higherPriority(_elems[leftChildIdx], _elems[rightChildIdx])) {
        return leftChildIdx;
      } else {
        return rightChildIdx;
      }
    }
}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown(size_t currentIdx)
{
    if (!hasAChild(currentIdx)) {
      return;
    }
    size_t priorityChildIdx = maxPriorityChild(currentIdx);
    if (!higherPriority(_elems[currentIdx], _elems[priorityChildIdx])) {
        std::swap(_elems[currentIdx], _elems[priorityChildIdx]);
        heapifyDown(priorityChildIdx);
    }

}

template <class T, class Compare>
void heap<T, Compare>::heapifyUp(size_t currentIdx)
{
    if (currentIdx == root())
        return;
    size_t parentIdx = parent(currentIdx);
    if (higherPriority(_elems[currentIdx], _elems[parentIdx])) {
        std::swap(_elems[currentIdx], _elems[parentIdx]);
        heapifyUp(parentIdx);
    }
}

template <class T, class Compare>
heap<T, Compare>::heap()
{
    _elems.push_back(T());
}

template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T>& elems)
{
    _elems.push_back(T());
    for (size_t i = 0; i < elems.size(); i++) {
      _elems.push_back(elems[i]);
    }
    for (size_t i = elems.size()/2; i > 0; i--) {
      heapifyDown(i);
    }
}

template <class T, class Compare>
T heap<T, Compare>::pop()
{
    if (_elems.size() > 1) {
      T returnElem = _elems[1];
      _elems[1] = _elems[_elems.size() - 1];
      _elems.pop_back();
      heapifyDown(1);
      return returnElem;
    }
    return T();
}

template <class T, class Compare>
T heap<T, Compare>::peek() const
{
  if (_elems.size() > 1) {
    return _elems[1];
  }
  return T();
}

template <class T, class Compare>
void heap<T, Compare>::push(const T& elem)
{
    _elems.push_back(elem);
    heapifyUp(_elems.size() - 1);
}

template <class T, class Compare>
bool heap<T, Compare>::empty() const
{
    /// @todo Determine if the heap is empty
    return _elems.size() == 1;
}

template <class T, class Compare>
void heap<T, Compare>::getElems(std::vector<T> & heaped) const
{
    for (size_t i = root(); i < _elems.size(); i++) {
        heaped.push_back(_elems[i]);
    }
}
