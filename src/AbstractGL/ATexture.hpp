#ifndef ABSTRACTGL_ATEXTURE_HPP
#define ABSTRACTGL_ATEXTURE_HPP

namespace aGL {
    class RenderSurface;
    class Texture
    {
        class Texture_;
        Texture_ * tp_;
        friend class Sprite;
        friend class RenderSurface;
        explicit Texture(const Texture_& tp);
        explicit Texture(Texture_* tp) : tp_(tp) {}
    public:
        Texture();
        Texture(const char* filename);
        
        Texture(const Texture& texture);
        Texture& operator=(const Texture& texture);

        ~Texture();

        bool loadFromFile(const char* filename);
        void setRepeated(bool);
    };
}

#endif /* ABSTRACTGL_ATEXTURE_HPP */
