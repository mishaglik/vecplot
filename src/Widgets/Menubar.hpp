#ifndef WIDGETS_MENUBAR_HPP
#define WIDGETS_MENUBAR_HPP
#include <Widgets/ContainerWidget.hpp>
#include <Widgets/Button.hpp>

namespace aGL {

    class Menubar : public ContainerWidget
    {
    public:
        class MenuButton;
        class Menu;

        Menubar(uint32_t x, uint32_t y, uint32_t w, uint32_t h, Widget* parent = nullptr);
        Menubar(const Rect& rect, Widget* parent = nullptr);
        ~Menubar() override;

        size_t addMenuEntry(const char* name);
        
        const mvc::Vector<Menu*>& entries() const {return menus_;}

        Menu* operator[](size_t i) const { return menus_[i]; }

        bool hasEventPoint(const Point& pt) override;

        void render(const Surface* surf) const override;
        void setTextColor(const aGL::Color color);
        void setFont(const char* font);
        void setCharSize(uint32_t size);



    private:
        aGL::Color textColor_ = aGL::Colors::Red;
        mvc::Vector<Menu*> menus_;
        Menu* activeMenu = nullptr;

        void setActiveMenu(Menu* menu);
        void setNoActiveMenu() {activeMenu = nullptr;}

    };

    class Menubar::Menu : public Widget
    {
    public:
        Menu(uint32_t x, uint32_t y, uint32_t w, uint32_t h, const char* name, Widget* parent = nullptr);
        ~Menu() override;

        EventHandlerState onPaintEvent(const Event* ) override;
        virtual void render(const Surface*) const override;
        
        void show();
        void hide(); 
        void toggle() { isActive_ ? hide() :  show(); }

        bool hasEventPoint(const Point& pt) override;

        const mvc::Vector<MenuButton*>& buttons() const {return buttons_;}

        size_t addMenuEntry(const char* text);

        Signal<Menu*> activated;
        Signal<> deactivated;

        void setTextColor(const aGL::Color color);
        void setFont(const char* font);
        void setCharSize(uint32_t size);


    private:
        bool isActive_ = false;

        MenuButton* mainButton_ = nullptr;
        mvc::Vector<MenuButton* > buttons_; 
        
    };
    

    class Menubar::MenuButton : public AbstractButton
    {
        bool isMain_ = false;
        bool isActive_ = false;
    public:
        MenuButton(uint32_t x, uint32_t y, uint32_t w, uint32_t h, const char* text, Widget* parent = nullptr);
        void setMain() { isMain_ = true; }
        void setActive(bool active) { isActive_ = active; needsRepaint_ = true; }
        virtual EventHandlerState onPaintEvent(const Event*) override;
        void setTextColor(const aGL::Color color)
        {
            text_.setColor(color);
            needsRepaint_ = true;
        }
        void setFont(const char* font)
        {
            text_.setFont(font);
        }

        void setCharSize(uint32_t size)
        {
            text_.setCharacterSize(size);
        }


    private:
    };

}

#endif /* WIDGETS_MENUBAR_HPP */
