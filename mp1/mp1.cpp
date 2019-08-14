#include <string>

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

using namespace cs225;

void rotate(std::string inputFile, std::string outputFile) {
  PNG* image = new PNG();
  image->readFromFile(inputFile);
  unsigned width = image->width();
  unsigned height = image->height();

  PNG* output = new PNG(width, height);

  for (unsigned x = 0; x < width; x++) {
    for (unsigned y = 0; y < height; y++) {
      HSLAPixel* pixel = image->getPixel(x, y);
      HSLAPixel* mirrorPixel = image->getPixel(width - 1 - x, height - 1 - y);

      HSLAPixel* outputPixel1 = output->getPixel(x,y);
      HSLAPixel* outputPixel2 = output->getPixel(width - 1 - x, height - 1 - y);

      *outputPixel1 = *mirrorPixel;
      *outputPixel2 = *pixel;
    }
  }
  output->writeToFile(outputFile);

  delete image;
  delete output;

}
