#include<iostream>
#include<glad/glad.h>

#include"graphics/Texture.hpp"

class FrameBuffer{
    public:
        FrameBuffer(unsigned int width, unsigned height);
        void ResetBuffers(unsigned int width, unsigned height);
        void UseFrameBuffer();
        Texture texture_color;
    private:
        unsigned frame_buffer, render_buffer;
};

