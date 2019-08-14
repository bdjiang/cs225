#include "StickerSheet.h"

StickerSheet::StickerSheet(const Image &picture, unsigned max) {
  images_ = new Image[max];
  xCoords_ = new unsigned[max];
  yCoords_ = new unsigned[max];
  baseImage_ = picture;
  max_ = max;

  for (int i = 0; i < max_; i++) {
    xCoords_[i] = -1;
    yCoords_[i] = -1;
  }
}
StickerSheet::~StickerSheet() {
  delete[] images_;
  delete[] xCoords_;
  delete[] yCoords_;
}

StickerSheet::StickerSheet(const StickerSheet &other) {
  images_ = NULL;
  xCoords_ = NULL;
  yCoords_ = NULL;
  delete[] images_;
  delete[] xCoords_;
  delete[] yCoords_;
  max_ = other.getMax();
  images_ = new Image[max_];
  xCoords_ = new unsigned[max_];
  yCoords_ = new unsigned[max_];
  baseImage_ = other.getBaseImage();

  for (int i = 0; i < max_; i++) {
    images_[i] = *other.getImage(i);
    xCoords_[i] = *other.getXCoord(i);
    yCoords_[i] = *other.getYCoord(i);
  }
}

const StickerSheet& StickerSheet::operator= (const StickerSheet &other) {
  images_ = NULL;
  xCoords_ = NULL;
  yCoords_ = NULL;
  max_ = other.getMax();
  images_ = new Image[max_];
  xCoords_ = new unsigned[max_];
  yCoords_ = new unsigned[max_];
  baseImage_ = other.getBaseImage();

  for (int i = 0; i < max_; i++) {
    images_[i] = *other.getImage(i);
    xCoords_[i] = *other.getXCoord(i);
    yCoords_[i] = *other.getYCoord(i);
  }
  return *this;
}

void StickerSheet::changeMaxStickers(unsigned max) {
  unsigned iteratorMax;
  if (max > max_) {
    iteratorMax = max_;
  } else {
    iteratorMax = max;
  }

  Image* newStickerSheet = new Image[max];
  unsigned* newXCoords = new unsigned[max];
  unsigned* newYCoords = new unsigned[max];

  for (unsigned i = 0; i < iteratorMax; i++) {
    newStickerSheet[i] = images_[i];
    newXCoords[i] = xCoords_[i];
    newYCoords[i] = yCoords_[i];
  }

  delete images_;
  delete xCoords_;
  delete yCoords_;

  images_ = newStickerSheet;
  xCoords_ = newXCoords;
  yCoords_ = newYCoords;
  max_ = max;
}

int StickerSheet::addSticker(Image &sticker, unsigned x, unsigned y) {

  for (int i = 0; i < max_; i++) {
    if (xCoords_[i] < 0 || yCoords_[i] < 0) {
      images_[i] = sticker;
      xCoords_[i] = x;
      yCoords_[i] = y;
      return i;
    }
  }

  return -1;
}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y) {
  if (xCoords_[index] < 0 || yCoords_[index] < 0 || index > max_) {
    return false;
  }

  xCoords_[index] = x;
  yCoords_[index] = y;
  return true;
}

void StickerSheet::removeSticker(unsigned index) {
  xCoords_[index] = -1;
  yCoords_[index] = -1;
}

Image* StickerSheet::getSticker(unsigned index) const {
  if (xCoords_[index] < 0 || yCoords_[index] < 0 || index > max_) {
    return NULL;
  }

  return &images_[index];
}

Image StickerSheet::render() const {


  Image masterImage = baseImage_;

  for (int i = 0; i < max_; i++) {
    if (xCoords_[i] < 0 || yCoords_[i] < 0) {
      continue;
    }
    Image currentPicture = images_[i];
    for (int x = 0; x < currentPicture.width(); x++) {
      for (int y = 0; y < currentPicture.height(); y++) {
        HSLAPixel* masterPixel = masterImage.getPixel(xCoords_[i] + x, yCoords_[i] + y);
        HSLAPixel* currentPixel = currentPicture.getPixel(x, y);
        if (currentPixel -> a > 0) {
          masterPixel -> h = currentPixel -> h;
          masterPixel -> s = currentPixel -> s;
          masterPixel -> l = currentPixel -> l;
          masterPixel -> a = currentPixel -> a;
        }
      }
    }

  }

  return masterImage;
}

Image* StickerSheet::getImage(int index) const {
  return &images_[index];
}

Image StickerSheet::getBaseImage() const {
  return baseImage_;
}

unsigned StickerSheet::getMax() const {
  return max_;
}

unsigned* StickerSheet::getXCoord(int index) const {
  return &xCoords_[index];
}

unsigned* StickerSheet::getYCoord(int index) const {
  return &yCoords_[index];
}
