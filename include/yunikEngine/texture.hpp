#pragma once

#include <string>

namespace yunikEngine {
    class Texture {
    public:
        ~Texture (void);

        enum class Type {
            TEXTURE_1D,
            TEXTURE_2D,
            TEXTURE_3D,
            TEXTURE_1D_ARRAY,
            TEXTURE_2D_ARRAY,
            TEXTURE_RECTANGLE,
            TEXTURE_CUBE_MAP,
            TEXTURE_CUBE_MAP_ARRAY,
            TEXTURE_BUFFER,
            TEXTURE_2D_MULTISAMPLE,
            TEXTURE_2D_MULTISAMPLE_ARRAY
        };

        bool load (const Type textureType, std::string& fileName);
        void bind (const unsigned int textureUnit);

    private:
        unsigned int type;
        unsigned int m_textureObj;

        unsigned char* image = nullptr;
        int image_width = 0;
        int image_height = 0;
        int image_channels = 0;

        unsigned int convertTypeToGLenum (const Type textureType) const;
    };
}
