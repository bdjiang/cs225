#ifndef STICKERSHEET
#define STICKERSHEET

#include "Image.h"
#include <iostream>

class StickerSheet {
  public:
    StickerSheet(const Image &picture, unsigned max);
    ~StickerSheet();
    StickerSheet(const StickerSheet &other);
    const StickerSheet& operator= (const StickerSheet &other);
    void changeMaxStickers(unsigned max);
    int addSticker(Image &sticker, unsigned x, unsigned y);
    bool translate(unsigned index, unsigned x, unsigned y);
    void removeSticker(unsigned index);
    Image* getSticker(unsigned index) const;
    Image render() const;

    unsigned getMax() const;
    Image getBaseImage() const;
    Image* getImage(int index) const;

    unsigned* getXCoord(int index) const;
    unsigned* getYCoord(int index) const;

  private:
    Image baseImage_;
    unsigned* xCoords_;
    unsigned* yCoords_;
    Image* images_;
    unsigned max_;
};

#endif
