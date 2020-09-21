#include "graphics/Texture.hpp"

class ToonTexture : public Texture {
    public:
        ToonTexture(std::string texture_path, bool repeat = false,  GLenum img_type = GL_RGBA);
        void  UseTexture(unsigned int texture_num, Shader* shader) override;
};