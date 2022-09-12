#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "Raycaster.hpp"
#include "VectorPlot.hpp"
#include <AbstractGL/AWindow.hpp>
#include <AbstractGL/Button.hpp>


class Application{
    aGL::Window* window_     = nullptr;
    VectorPlot* plotRotator_ = nullptr;
    // VectorPlot* plotClicked_ = nullptr;
    Raycaster* raycaster_    = nullptr;
    aGL::Button* exitButton  = nullptr;
    aGL::Button* resetButton = nullptr;

    enum class AppState{
        UnInit = 0,
        Ready,
        Running,
        Stopping,
        Stopped,
        Died,
        Error
    };

    AppState state_ = AppState::UnInit;

public:
    Application();
    Application(int , const char** ) : Application() {}
    
    ~Application();

    int exec();

    int handleEvent(const aGL::Event& event);

    void quit (const aGL::Event& event);
    void reset(const aGL::Event& event);

    Application(const Application& app)             = delete;
    Application& operator= (const Application& app) = delete;

};

#endif /* APPLICATION_HPP */
