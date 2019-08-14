#include <iostream>
/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
template <class T>
List<T>::~List() {
  this -> clear();
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <class T>
void List<T>::clear() {
  while (head_ != NULL) {
    ListNode *temp = head_;
    head_ = temp->next;
    delete temp;
  }
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertFront(T const& ndata) {
  ListNode* newNode = new ListNode(ndata);
  newNode -> next = head_;
  if (head_ == NULL) {
    tail_ = newNode;
  }
  head_ = newNode;

  length_++;

  ListNode* afterHead = head_ -> next;
  if (afterHead != NULL) {
    afterHead -> prev = head_;
  }
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertBack(const T& ndata) {
  ListNode* newNode = new ListNode(ndata);
  newNode -> prev = tail_;
  if (tail_ == NULL) {
    head_ = newNode;
  }
  tail_ = newNode;

  length_++;

  ListNode* beforeTail = tail_ -> prev;
  if (beforeTail != NULL) {
    beforeTail -> next = tail_;
  }
}

/**
 * Reverses the current List.
 */
template <class T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <class T>
void List<T>::reverse(ListNode*& startPoint, ListNode*& endPoint) {
  bool startIsHead = false;
  bool endIsTail = false;


  ListNode* edgeStart = startPoint -> prev;
  ListNode* edgeEnd = endPoint -> next;

  if (startPoint == head_) {
    startIsHead = true;
  }
  if (endPoint == tail_) {
    endIsTail = true;
  }

  ListNode* current = startPoint;
  ListNode* nextNode;
  ListNode* prevNode;

  while (current != endPoint) {
    nextNode = current -> next;
    prevNode = current -> prev;

    current -> next = prevNode;
    current -> prev = nextNode;

    current = nextNode;
  }

  ListNode* finalPrevNode = current -> prev;
  current -> next = finalPrevNode;


  if (startIsHead && endIsTail) {
    ListNode* temp = endPoint;
    tail_ = startPoint;
    head_ = temp;
  } else if (startIsHead && !endIsTail) {
    ListNode* oldHead = head_;
    head_ = endPoint;
    head_ -> prev = NULL;
    oldHead -> next = edgeEnd;
    edgeEnd -> prev = oldHead;
  } else if (endIsTail && !startIsHead) {
    ListNode* oldTail = tail_;
    tail_ = startPoint;
    tail_ -> next = NULL;
    oldTail -> prev = edgeStart;
    edgeStart -> next = oldTail;
  }

  if (!startIsHead && !endIsTail) {
    ListNode* oldStartNewEnd = startPoint;
    ListNode* oldEndNewStart = endPoint;

    oldStartNewEnd -> next = edgeEnd;
    edgeEnd -> prev = oldStartNewEnd;

    oldEndNewStart -> prev = edgeStart;
    edgeStart -> next = oldEndNewStart;
  }
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <class T>
void List<T>::reverseNth(int n) {
  if (n >= this -> size()) {
    reverse();
    return;
  }

  int blocks = this -> size()/n;
  if (this -> size()%n != 0) {
    blocks++;
  }

  ListNode* start = head_;
  ListNode* end = head_;

  for (int blockNumber = 0; blockNumber < blocks; blockNumber++) {
    for (int indexInBlock = 0; indexInBlock < n - 1; indexInBlock++) {
      if (end -> next != NULL) {
        end = end -> next;
      }
    }
    reverse(start, end);
    start = start -> next;
    end = start;
  }

}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <class T>
void List<T>::waterfall() {
  ListNode* current = head_;

  while (current -> next != tail_) {
    current = current -> next;

    ListNode* onePastCurrent = current -> next;
    ListNode* oneBeforeCurrent = current -> prev;

    if (oneBeforeCurrent != NULL) {
      oneBeforeCurrent -> next = onePastCurrent;
    }
    if (onePastCurrent != NULL) {
      onePastCurrent -> prev = oneBeforeCurrent;
    }

    current -> prev = tail_;
    tail_ -> next = current;
    current -> next = NULL;

    tail_ = current;
    current = onePastCurrent;
  }
}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <class T>
List<T> List<T>::split(int splitPoint) {
    if (splitPoint > length_)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode* secondHead = split(head_, splitPoint);

    int oldLength = length_;
    if (secondHead == head_) {
        // current list is going to be empty
        head_ = NULL;
        tail_ = NULL;
        length_ = 0;
    } else {
        // set up current list
        tail_ = head_;
        while (tail_->next != NULL)
            tail_ = tail_->next;
        length_ = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head_ = secondHead;
    ret.tail_ = secondHead;
    if (ret.tail_ != NULL) {
        while (ret.tail_->next != NULL)
            ret.tail_ = ret.tail_->next;
    }
    ret.length_ = oldLength - splitPoint;
    return ret;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List objects!
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <class T>
typename List<T>::ListNode* List<T>::split(ListNode* start, int splitPoint) {
    for (int nodesIn = 0; nodesIn < splitPoint; nodesIn++) {
      start = start -> next;
      if (start == NULL) {
        return NULL;
      }
    }
    ListNode* endOfFirstList = start -> prev;
    endOfFirstList -> next = NULL;
    start -> prev = NULL;
    return start;
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <class T>
void List<T>::mergeWith(List<T>& otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <class T>
typename List<T>::ListNode* List<T>::merge(ListNode* first, ListNode* second) {
  ListNode* firstNew;

  ListNode* masterCurrent;
  if (first -> data < second -> data) {
    masterCurrent = first;
    firstNew = masterCurrent;
    first = first -> next;
    if (first != NULL) {
      first -> prev = NULL;
    }
    masterCurrent -> prev = NULL;
  } else {
    masterCurrent = second;
    firstNew = masterCurrent;
    second = second -> next;
    if (second != NULL) {
      second -> prev = NULL;
    }
    masterCurrent -> prev = NULL;
  }

  while (first != NULL && second != NULL) {
    if (first -> data < second -> data) {
      masterCurrent -> next = first;
      first -> prev = masterCurrent;
      first = first -> next;
      masterCurrent = masterCurrent -> next;
    } else {
      masterCurrent -> next = second;
      second -> prev = masterCurrent;
      second = second -> next;
      masterCurrent = masterCurrent -> next;
    }
  }

  if (first == NULL) {
    while (second != NULL) {
      masterCurrent -> next = second;
      second -> prev = masterCurrent;
      second = second -> next;
      masterCurrent = masterCurrent -> next;
    }
  }

  if (second == NULL) {
    while (first != NULL) {
      masterCurrent -> next = first;
      first -> prev = masterCurrent;
      first = first -> next;
      masterCurrent = masterCurrent -> next;
    }
  }

  return firstNew;
}

/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <class T>
void List<T>::sort() {
    if (empty())
        return;
    head_ = mergesort(head_, length_);
    tail_ = head_;
    while (tail_->next != NULL)
        tail_ = tail_->next;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <class T>
typename List<T>::ListNode* List<T>::mergesort(ListNode* start, int chainLength) {
    ListNode* newHead;
    if (chainLength == 1) {
      return start;
    } else {
      int middlePoint = chainLength/2;
      ListNode* rightHead = split(start, middlePoint);

      ListNode* leftHead = mergesort(start, middlePoint);
      rightHead = mergesort(rightHead, chainLength - middlePoint);

      newHead = merge(leftHead, rightHead);

    }

    return newHead;
}
