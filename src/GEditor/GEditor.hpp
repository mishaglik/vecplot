#ifndef GEDITOR_GEDITOR_HPP
#define GEDITOR_GEDITOR_HPP

#include <AbstractGL/Signals.hpp>
#include "ColorDialog/ColorDialog.hpp"
#include "GEditorWindow.hpp"
#include "Widgets/Application.hpp"

namespace mge {
    class Tool;
    struct DrawingContext
    {
        aGL::Color foregroundColor = aGL::Colors::Black;
        aGL::Color backgroundColor = aGL::Colors::White;
    };
}

class GEditor : public aGL::BaseApplication
{
    mge::MainWindow* mainWindow_ = nullptr;
    aGL::ColorDialog* dialog_ = nullptr;
    aGL::SkinManager* sm_ = nullptr;

    mge::Tool* currentTool_ = nullptr;

public:
    GEditor(int argc, const char* argv[]);
    ~GEditor();

    static GEditor* app;
    mge::DrawingContext context = {};

    void setCurrentTool(mge::Tool* newTool);
    mge::Tool* getCurrentTool() const { mAssert(currentTool_); return currentTool_; }
    aGL::Signal<mge::Tool* > toolChanged;

    void setFgColor(aGL::Color color) { context.foregroundColor = color; }
    void setBgColor(aGL::Color color) { context.backgroundColor = color; }
};

#endif /* GEDITOR_GEDITOR_HPP */