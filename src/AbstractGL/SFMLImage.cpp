#include "SFMLImage.hpp"

namespace aGL {
    Image::Image() : ip_(new Image_) {}
    Image::Image(const char* filename) : ip_(new Image_) { ip_->loadFromFile(filename); }
    Image::Image(const Image& oth) : ip_(new Image_(*oth.ip_)) {}
    Image& Image::operator=(const Image& oth) {*ip_ = *oth.ip_; return *this; }
    Image::~Image() { delete  ip_; ip_ = nullptr; }

    void Image::loadFromFile(const char* filename)
    {
        ip_->loadFromFile(filename);
    }

    const Color* Image::getPixels() const
    {
        return reinterpret_cast<const Color*>(ip_->getPixelsPtr());
    }

    Color Image::getPixel(unsigned int x, unsigned int y) const
    {
        sf::Color cl = ip_->getPixel(x, y);
        return {cl.r, cl.g, cl.b, cl.a};
    }

    void Image::create(uint32_t w, uint32_t h, const Color& col)
    {
        ip_->create(w, h, sf::Color(col.r(), col.b(), col.b(), col.a()));
    }

    void Image::setPixel(unsigned int x, unsigned int y, const Color& color)
    {
        ip_->setPixel(x, y, sf::Color(color.color()));
    }

    void Image::saveToFile(const char* filename)
    {
        ip_->saveToFile(filename);
    }

    uint32_t Image::getW() const
    {
        return ip_->getSize().x;
    }
    uint32_t Image::getH() const
    {
        return ip_->getSize().y;
    }

    bool Image::isCreated() const
    {
        return ip_->getSize() != sf::Vector2u{0, 0};
    }

}
