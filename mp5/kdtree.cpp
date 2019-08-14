/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */
template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    bool returnValue = first[curDim] < second[curDim];
    if (first[curDim] == second[curDim]) {
      returnValue = first < second;
    }
    return returnValue;
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
    int currentBestToTarget = 0;
    for (int i = 0; i < Dim; i++) {
      int distance = (currentBest[i] - target[i]) * (currentBest[i] - target[i]);
      currentBestToTarget = currentBestToTarget + distance;
    }

    int potentialToTarget = 0;
    for (int i = 0; i < Dim; i++) {
      int distance = (potential[i] - target[i]) * (potential[i] - target[i]);
      potentialToTarget = potentialToTarget + distance;
    }
    bool returnValue = potentialToTarget < currentBestToTarget;

    if (potentialToTarget == currentBestToTarget) {
      returnValue = potential < currentBest;
    }
    return returnValue;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
    points = newPoints;
    if (points.size() == 0) {
      return;
    }
    KDTreeBuilder(0, 0, points.size() - 1);

}

template <int Dim>
void KDTree<Dim>::KDTreeBuilder(int left, int right, int dimension) {
    int medianIndex = (int)(left + right)/2;
    quickSelect(left, right, dimension, medianIndex);

    if (left < medianIndex) {
      KDTreeBuilder(left, medianIndex - 1, (dimension + 1) % Dim);
    }

    if (right > medianIndex) {
      KDTreeBuilder(medianIndex + 1, right, (dimension + 1) % Dim);
    }
}

template<int Dim>
int KDTree<Dim>::partition(int left, int right, int dimension, int medianIndex)
{
    Point<Dim> pivot = points[medianIndex];
    std::swap(points[right], points[medianIndex]);
    int storeIndex = left;

    for (int i = left; i < right; i++) {
      if (smallerDimVal(points[i], pivot, dimension) == true) {
        std::swap(points[i], points[storeIndex]);
        storeIndex++;
      }
    }
    std::cout << right << std::endl;
    std::swap(points[right], points[storeIndex]);
    return storeIndex;
}


template<int Dim>
void KDTree<Dim>::quickSelect(int left, int right, int dimension, int medianIndex) {
    while (left < right) {
      int pivotIndex = partition(left, right, dimension, medianIndex);
      if (pivotIndex == medianIndex) {
        return;
      } else if (medianIndex < pivotIndex) {
        right = pivotIndex - 1;
      } else {
        left = pivotIndex + 1;
      }
    }
}


template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    Point<Dim> returnPoint = points[0];
    for (int i = 1; i < (int)points.size(); i++) {
      if (shouldReplace(query, returnPoint, points[i])) {
        returnPoint = points[i];
      }
    }
    return returnPoint;

}
