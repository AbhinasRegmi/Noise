#ifndef PERLIN_H
#define PERLIN_H

namespace Noise{

    class Perlin{

        public:

            Perlin();
            Perlin(int inSeed);

            float genHeight(float posX, float posY);
    };
}

#endif