#ifndef CONFIG_3534_H
#define CONFIG_3534_H

#include "myMath.h"

namespace Conf
{
    inline constexpr float FOVangle{PI / 2.5f};
    inline constexpr float renderDistance{100.0f};
    inline constexpr float chunkWidth{10.0f};
    inline constexpr float wallWidth{2.0f};

    inline constexpr unsigned int windowWidth{1600};
    inline constexpr unsigned int windowHeight{900};

}

#endif
