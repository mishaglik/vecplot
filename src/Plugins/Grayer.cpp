#include "Grayer.hpp"

constexpr uint8_t getR(uint32_t color) { return (color >> 24) & 0xFF;}
constexpr uint8_t getG(uint32_t color) { return (color >> 16) & 0xFF;}
constexpr uint8_t getB(uint32_t color) { return (color >> 8 ) & 0xFF;}
constexpr uint8_t getA(uint32_t color) { return (color >> 0 ) & 0xFF;}
constexpr uint32_t getColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) { return (r << 24) | (g << 16) | (b << 8) | (a << 0); }

constexpr uint32_t getGray(uint32_t color)
{
    uint32_t r = getR(color);
    uint32_t g = getG(color);
    uint32_t b = getB(color);
    uint8_t  a = getA(color);
    uint8_t avg = static_cast<uint8_t>((299 * r + 587 * g + 114 * b) / 1000);
    return getColor(avg, avg, avg, a);
}

void Grayer::apply(Image* image, const Event* event)
{
    if(event->type == EventType::MousePressed && event->Oleg.mbedata.button == MouseButton::Left)
    {
        for(uint32_t x = 0; x < image->getW(); ++x)
            for(uint32_t y = 0; y < image->getH(); ++y)
                image->setPixel(x, y, getGray(image->getPixel(x, y)));
    }
}

static const GUID GUID_ = {"c6fc5136-7d8f-4def-9684-a276e42ba8a4"};

extern "C" GUID getGUID()
{
    return GUID_;
}

extern "C" void init_module()
{
    addFilter(new Grayer);
}
