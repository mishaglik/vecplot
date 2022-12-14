#include "SFMLText.hpp"

namespace aGL {
    extern const char* const systemFont = "/home/gms/progs++/vecplot/FreeMono.otf";

    Text::Text_::Text_(const char* fontFilename, const char* text, uint32_t x, uint32_t y)
    {
        if(!font_.loadFromFile(fontFilename))
        {
            mAssert(0 && "Font not loaded");
        }
        sf::Text::setFont(font_);
        setString(text);
        setPosition( static_cast<float>(x), 
                     static_cast<float>(y));
    }

    Text::Text_::Text_(const char* fontFilename, const uint32_t* text, uint32_t x, uint32_t y)
    {
        if(!font_.loadFromFile(fontFilename))
        {
            mAssert(0 && "Font not loaded");
        }
        sf::Text::setFont(font_);
        setString(text);
        setPosition( static_cast<float>(x), 
                     static_cast<float>(y));
    }

    Text::Text(const char* fontName, const char* text, uint32_t x, uint32_t y)
    {
        tp_ = new Text_(fontName, text, x, y);
    }

    Text::Text(const char* text, uint32_t x, uint32_t y, const char* const fontName)
    {
        tp_ = new Text_(fontName, text, x, y);
    }


    Text::Text(const uint32_t* text, uint32_t x, uint32_t y, const char* const fontName)
    {
        tp_ = new Text_(fontName, text, x, y);
    }


    Text::~Text()
    {
        delete tp_;
    }

    void Text::setPosition(uint32_t x, uint32_t y)
    {
        tp_->setPosition(
            static_cast<float>(x),
            static_cast<float>(y)
        );
    }

    void Text::setPosition(const Point& pt)
    {
        setPosition(pt.x, pt.y);
    }

    void Text::setColor(const Color& color)
    {
        tp_->setFillColor(sf::Color(color));
    }

    void Text::setStyle(unsigned style)
    {
        tp_->setStyle(style);               // Text styles is equal to SFML
    }

    void Text::setCharacterSize(unsigned size)
    {
        tp_->setCharacterSize(size);
    }

    void Text::setFont(const char* font)
    {
        tp_->setFont(font);
    }


    Rect Text::getRect() const
    {
        sf::FloatRect rect = tp_->getGlobalBounds();

        return {
                static_cast<uint32_t>(rect.left), 
                static_cast<uint32_t>(rect.top), 
                static_cast<uint32_t>(rect.width), 
                static_cast<uint32_t>(rect.height)
            };
    }

    void Text::setString(const char* string)
    {
        tp_->setString(string);
    }
    
    void Text::setString(const uint32_t* string)
    {
        tp_->setString(string);
    }

}
