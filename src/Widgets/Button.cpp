#include <AbstractGL/AText.hpp>
#include "Button.hpp"
#include <iostream>

namespace aGL {

    Button::Button(const char* text, uint32_t x, uint32_t y) :
        Widget({x, y, 1, 1}), text_(text, horizontalMargin, verticalMargin + 2)
    {
        text_.setColor(Colors::Red);

        Rect textRect = text_.getRect();
        Widget::resize(textRect.w + 2 * horizontalMargin, textRect.h + 2 * verticalMargin);
    }

    void Button::setEventFunction(AObject* eventObject, int eventSignal)
    {
        eventObject_ = eventObject;
        eventSignal_ = eventSignal;
    }


    EventHandlerState Button::onMouseButtonPressEvent(const Event* event) 
    {
        if(event->type == EventType::MouseButtonPressed && event->mbed.button == MouseButton::Left &&
                                                                            mgm::contains(rect_, event->mbed.point))
        {
            pressed_ = true;
        }

        if(pressed_ && event->type == EventType::MouseButtonReleased && event->mbed.button == MouseButton::Left)
        {
            pressed_ = false;
            if(mgm::contains(rect_, event->mbed.point))
            {
                eventObject_->handleSignal(eventSignal_);
            }
            return EventHandlerState::Accepted;
        }
        return EventHandlerState::Dropped;
    }

    EventHandlerState Button::onPaintEvent(const Event* ) 
    {
        surface->drawRect({0, 0, rect_.w, rect_.h}, pressed_ ? pressedColor_ : defaultColor_); //TODO: Two pictures different transpatency
        
        int w = static_cast<int>(rect_.w);
        int h = static_cast<int>(rect_.h);

        surface->drawLine({0, 0}, {0, h}, Colors::LGray);
        surface->drawLine({0, h}, {w, h}, Colors::LGray);
        surface->drawLine({w, h}, {w, 0}, Colors::LGray);
        surface->drawLine({w, 0}, {0, 0}, Colors::LGray);
        
        surface->drawText(text_);
        return EventHandlerState::Accepted;
    }

}