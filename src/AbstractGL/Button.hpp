#ifndef ABSTRACTGL_BUTTON_HPP
#define ABSTRACTGL_BUTTON_HPP
#include "Widget.hpp"

namespace aGL {

    class Button : public Widget
    {
        char const * const font_ = "/home/gms/progs++/vecplot/FreeMono.otf"; //FIXME: System font
        const Color defaultColor_ = 0x232323ff;
        const Color pressedColor_ = 0x353535ff;

        uint32_t verticalMargin   = 13;
        uint32_t horizontalMargin = 5;
        
        Text text_;
        bool pressed_ = false;

        AObject* eventObject_ = nullptr;
        int eventSignal_ = 0;

    public:

        Button(const char* text, uint32_t x, uint32_t y);

        void setEventFunction(AObject* eventObject, int eventSignal);
        
        int handleEvent(const Event& event) override;

        void onPaintEvent() const override;

    };

}
#endif /* ABSTRACTGL_BUTTON_HPP */
