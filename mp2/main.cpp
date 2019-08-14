#include "StickerSheet.h"
#include "Image.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

using namespace cs225;

int main() {
  Image base;
  base.readFromFile("nbaCourt.png");

  Image lin;
  lin.readFromFile("lin.png");

  Image lowry;
  lowry.readFromFile("lowry.png");

  Image lebron;
  lebron.readFromFile("lebron.png");

  StickerSheet sheet(base, 3);
  sheet.addSticker(lin, 20, 200);
  sheet.addSticker(lowry, 300, 10);
  sheet.addSticker(lebron, 500, 300);

  Image newImage = sheet.render();
  newImage.writeToFile("NBA.png");

  return 0;
}
