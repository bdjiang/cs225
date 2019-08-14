#include "Image.h"
#include <cmath>

Image::Image(int width, int height) {
  width_ = width;
  height_ = height;
  imageData_ = new HSLAPixel[width * height];
}
Image::Image() {
  width_ = 0;
  height_ = 0;
  imageData_ = NULL;
}
void Image::lighten() {
  for (unsigned w = 0; w < this -> width(); w++) {
    for (unsigned h = 0; h < this -> height(); h++) {
      HSLAPixel* pixel = this -> getPixel(w,h);
      if (pixel -> l < 1) {
        pixel -> l += 0.1;
        if (pixel -> l > 1) {
          pixel -> l = 1;
        }
      }
    }
  }
}
void Image::lighten(double amount) {
  for (unsigned w = 0; w < this -> width(); w++) {
    for (unsigned h = 0; h < this -> height(); h++) {
      HSLAPixel* pixel = this -> getPixel(w,h);
      if (pixel -> l < 1) {
        pixel -> l += amount;
        if (pixel -> l > 1) {
          pixel -> l = 1;
        }
      }
    }
  }
}
void Image::darken() {
  for (unsigned w = 0; w < this -> width(); w++) {
    for (unsigned h = 0; h < this -> height(); h++) {
      HSLAPixel* pixel = this -> getPixel(w,h);
      if (pixel -> l < 1) {
        pixel -> l += -0.1;
        if (pixel -> l < 0) {
          pixel -> l = 0;
        }
      }
    }
  }
}
void Image::darken(double amount) {
  for (unsigned w = 0; w < this -> width(); w++) {
    for (unsigned h = 0; h < this -> height(); h++) {
      HSLAPixel* pixel = this -> getPixel(w,h);
      if (pixel -> l < 1) {
        pixel -> l += -amount;
        if (pixel -> l < 0) {
          pixel -> l = 0;
        }
      }
    }
  }
}
void Image::saturate() {
  for (unsigned w = 0; w < this -> width(); w++) {
    for (unsigned h = 0; h < this -> height(); h++) {
      HSLAPixel* pixel = this -> getPixel(w,h);
      if (pixel -> s < 1) {
        pixel -> s += 0.1;
        if (pixel -> s > 1) {
          pixel -> s = 1;
        }
      }
    }
  }
}
void Image::saturate(double amount) {
  for (unsigned w = 0; w < this -> width(); w++) {
    for (unsigned h = 0; h < this -> height(); h++) {
      HSLAPixel* pixel = this -> getPixel(w,h);
      if (pixel -> s < 1) {
        pixel -> s += amount;
        if (pixel -> s > 1) {
          pixel -> s = 1;
        }
      }
    }
  }
}
void Image::desaturate() {
  for (unsigned w = 0; w < this -> width(); w++) {
    for (unsigned h = 0; h < this -> height(); h++) {
      HSLAPixel* pixel = this -> getPixel(w,h);
      if (pixel -> s < 1) {
        pixel -> s += -0.1;
        if (pixel -> s < 0) {
          pixel -> s = 0;
        }
      }
    }
  }
}
void Image::desaturate(double amount) {
  for (unsigned w = 0; w < this -> width(); w++) {
    for (unsigned h = 0; h < this -> height(); h++) {
      HSLAPixel* pixel = this -> getPixel(w,h);
      if (pixel -> s < 1) {
        pixel -> s += -amount;
        if (pixel -> s < 0) {
          pixel -> s = 0;
        }
      }
    }
  }
}
void Image::grayscale() {
  for (unsigned w = 0; w < this -> width(); w++) {
    for (unsigned h = 0; h < this -> height(); h++) {
      HSLAPixel* pixel = this -> getPixel(w,h);
      pixel -> s = 0;
    }
  }
}
void Image::rotateColor(double degrees) {
  for (unsigned w = 0; w < this -> width(); w++) {
    for (unsigned h = 0; h < this -> height(); h++) {
      HSLAPixel* pixel = this -> getPixel(w,h);
      int original = pixel -> h;
      double originalH = (double) original;

      pixel -> h += degrees;
      if (pixel -> h > 359) {
        double difference = 360 - originalH;
        double leftover = degrees - difference;
        pixel -> h = leftover;
      }
      if (pixel -> h < 0) {
        pixel -> h = 360 + pixel -> h;
      }
    }
  }
}
void Image::illinify() {
  for (unsigned w = 0; w < this -> width(); w++) {
    for (unsigned h = 0; h < this -> height(); h++) {
      double orangeDiff;
      double blueDiff;
      HSLAPixel* pixel = this -> getPixel(w,h);
      double hue = pixel -> h;
      double diffToReset = 360 - hue;
      if (abs(diffToReset + 11) < abs(hue - 11)) {
         orangeDiff = fabs(diffToReset + 11);
      } else {
         orangeDiff = fabs(hue-11);
      }
      if (abs(diffToReset + 216) < abs(hue - 216)) {
         blueDiff = fabs(diffToReset + 216);
      } else {
         blueDiff = fabs(hue - 216);
      }
      if (orangeDiff < blueDiff) {
         pixel -> h = 11;
      } else if (orangeDiff > blueDiff) {
         pixel -> h = 216;
      }
    }
  }
}
void Image::scale(double factor) {
  double width = this -> width();
  double height = this -> height();

  PNG oldPic = *this;

  double newWidth = width * factor;
  double newHeight = height * factor;
  this -> resize(newWidth, newHeight);


  for (unsigned w = 0; w < newWidth; w++) {
    for (unsigned h = 0; h < newHeight; h++) {
      HSLAPixel* currentPixel = this -> getPixel(w,h);
      int wIndex = (int)(w/factor);
      int hIndex = (int)(h/factor);
      *currentPixel = *oldPic.getPixel(wIndex, hIndex);
    }
  }
}
void Image::scale(unsigned newWidth, unsigned newHeight) {
  double width = this -> width();
  double height = this -> height();

  PNG oldPic = *this;

  double factorW = newWidth/width;
  double factorH = newHeight/height;
  this -> resize(newWidth, newHeight);

  for (unsigned w = 0; w < newWidth; w++) {
    for (unsigned h = 0; h < newHeight; h++) {
      HSLAPixel* currentPixel = this -> getPixel(w,h);
      int wIndex = (int)(w/factorW);
      int hIndex = (int)(h/factorH);
      *currentPixel = *oldPic.getPixel(wIndex, hIndex);
    }
  }

}
