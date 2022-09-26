#ifndef RAYTRACER_RAYTRACER_HPP
#define RAYTRACER_RAYTRACER_HPP
#include <AbstractGL/Widget.hpp>
#include <Raytracer/RenderObject.hpp>
#include <Vector/Vector.hpp>
#include <vector>


class Raytracer: public aGL::Widget{
    template<typename T>
    using Vector = mvc::Vector<T>;

    using Point  = mgm::Point3f;
    using Vec = mgm::Vector3f;
    using Color  = aGL::Color;
    using Ray    = mgm::Ray3f;

    static Color getSkyGradient(const Vec& v);
    
    Vector<RTObjs::RenderObject*> objlist_;

    Point camera_;
    Color ambient_ = 0x202020ff;

    uint64_t labertianDepth_ = 500;

    Color getRayColor(const mgm::Ray3f& ray, int depth = 0) const;
    Color getLambert(const RTObjs::SurfacePoint& surface) const;
    Color getTrueLambert(const RTObjs::SurfacePoint& surfPoint, int depth) const;


    bool isRendered = false;

    public:
        aGL::Window* wind; //HACK

        Raytracer(uint32_t x, uint32_t y, uint32_t w, uint32_t h);
        ~Raytracer() override;

        void onPaintEvent() const override;

        Raytracer(const Raytracer&) = delete;
        Raytracer& operator=(const Raytracer&) = delete;

};

#endif /* RAYTRACER_RAYTRACER_HPP */