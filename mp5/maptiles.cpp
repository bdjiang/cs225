/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"

using namespace std;

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage> const& theTiles)
{
    /**
     * @todo Implement this function!
     */
    MosaicCanvas* returnCanvas = new MosaicCanvas(theSource.getRows(), theSource.getColumns());
    vector<Point<3>> colorPoints;
    map<Point<3>, TileImage> map;

    for (int i = 0; i < (int)theTiles.size(); i++) {
        HSLAPixel pixel = theTiles[i].getAverageColor();
        Point<3> newColorPoint = Point<3>(pixel.h, pixel.s, pixel.l);

        map[newColorPoint] = theTiles[i];

        colorPoints.push_back(newColorPoint);
    }

    KDTree<3>* masterTree = new KDTree<3>(colorPoints);

    for (int i = 0; i < (int)theSource.getRows(); i++) {
      for (int j = 0; j < (int)theSource.getColumns(); j++) {
        HSLAPixel pixel = theSource.getRegionColor(i, j);
        Point<3> tempPoint(pixel.h, pixel.s, pixel.l);
        tempPoint = masterTree -> findNearestNeighbor(tempPoint);

        returnCanvas -> setTile(i, j, map[tempPoint]);
      }
    }


    return returnCanvas;
}
