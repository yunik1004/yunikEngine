#include <yunikEngine/texture.hpp>

#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif
#include <GL/glew.h>
#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif
#include <stb_image.h>

namespace yunikEngine {
    Texture::~Texture (void) {
        glDeleteTextures(1, &m_textureObj);

        if (image) {
            stbi_image_free(image);
        }
    }

    bool Texture::load (const Type textureType, std::string& fileName) {
        image = stbi_load(fileName.c_str(), &image_width, &image_height, &image_channels, STBI_rgb_alpha);
        if (!image) {
            return false;
        }

        type = convertTypeToGLenum(textureType);

        glGenTextures(1, &m_textureObj);
        glBindTexture(type, m_textureObj);
        glTexImage2D(type, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
        glTexParameterf(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameterf(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glBindTexture(type, 0);

        return true;
    }

    void Texture::bind (const unsigned int textureUnit) {
        glActiveTexture(GL_TEXTURE0 + textureUnit);
        glBindTexture(type, m_textureObj);
    }

    unsigned int Texture::convertTypeToGLenum (const Texture::Type textureType) const {
        switch (textureType) {
            case Type::TEXTURE_1D:
                return GL_TEXTURE_1D;
            case Type::TEXTURE_2D:
                return GL_TEXTURE_2D;
            case Type::TEXTURE_3D:
                return GL_TEXTURE_3D;
            case Type::TEXTURE_1D_ARRAY:
                return GL_TEXTURE_1D_ARRAY;
            case Type::TEXTURE_2D_ARRAY:
                return GL_TEXTURE_2D_ARRAY;
            case Type::TEXTURE_RECTANGLE:
                return GL_TEXTURE_RECTANGLE;
            case Type::TEXTURE_CUBE_MAP:
                return GL_TEXTURE_CUBE_MAP;
            case Type::TEXTURE_CUBE_MAP_ARRAY:
                return GL_TEXTURE_CUBE_MAP_ARRAY;
            case Type::TEXTURE_BUFFER:
                return GL_TEXTURE_BUFFER;
            case Type::TEXTURE_2D_MULTISAMPLE:
                return GL_TEXTURE_2D_MULTISAMPLE;
            case Type::TEXTURE_2D_MULTISAMPLE_ARRAY:
                return GL_TEXTURE_2D_MULTISAMPLE_ARRAY;
        }
    }
}
