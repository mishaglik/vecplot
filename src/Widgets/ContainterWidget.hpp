#ifndef WIDGETS_CONTAINTERWIDGET_HPP
#define WIDGETS_CONTAINTERWIDGET_HPP
#include <Widgets/Widget.hpp>
#include <AbstractGL/EventManager.hpp>
namespace aGL {
    class ContainerWidget : public Widget
    {
        EventManager emanager_;
    public:
        ContainerWidget() : Widget(), emanager_() {}
        ContainerWidget(const Rect& rect) : Widget(rect), emanager_() {}
        ContainerWidget(const Rect& rect, RenderSurface* surf) : Widget(rect, surf), emanager_() {}


        virtual EventHandlerState handleEvent               (const Event* event) override { return emanager_.handleEvent(event);}
        virtual EventHandlerState onPaintEvent              (const Event* event) override { return emanager_.handleEvent(event);}
        virtual EventHandlerState onKeyPressedEvent         (const Event* event) override { return emanager_.handleEvent(event);}
        virtual EventHandlerState onKeyReleasedEvent        (const Event* event) override { return emanager_.handleEvent(event);}
        virtual EventHandlerState onShortcutEvent           (const Event* event) override { return emanager_.handleEvent(event);}
        virtual EventHandlerState onMouseMoveEvent          (const Event* event) override { return emanager_.handleEvent(event);}
        virtual EventHandlerState onMouseButtonPressEvent   (const Event* event) override { return emanager_.handleEvent(event);}
        virtual EventHandlerState onMouseButtonReleaseEvent (const Event* event) override { return emanager_.handleEvent(event);}
        virtual EventHandlerState onMouseScrollEvent        (const Event* event) override { return emanager_.handleEvent(event);}
        virtual EventHandlerState onTimerEvent              (const Event* event) override { update(); return emanager_.handleEvent(event);}

        
    };
}

#endif /* WIDGETS_CONTAINTERWIDGET_HPP */