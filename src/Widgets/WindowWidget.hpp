#ifndef WIDGETS_WINDOWWIDGET_HPP
#define WIDGETS_WINDOWWIDGET_HPP
#include <Widgets/ContainterWidget.hpp>
#include <AbstractGL/AWindow.hpp>

namespace aGL {
    class WWindow: public Window, public ContainerWidget
    {
    public:
        WWindow(uint32_t w, uint32_t h, const char* title):
            Window(w, h, title), ContainerWidget({0, 0, w, h}, nullptr) {}
        
        void render(const Window &) const override { mFatal << "Window is tried to be drawn\n"; }
        void update() override 
        {
            Event event = {};
            while(pollEvent(event))
            {
                handleEvent(&event);
            }
            Window::update();
        }
    };
}

#endif /* WIDGETS_WINDOWWIDGET_HPP */
