#ifndef PERLIN_H
#define PERLIN_H

#include <cstdlib>
#include <cmath>

namespace Noise{

    class Perlin{

        public:

            Perlin();
            Perlin(unsigned int inSeed, int inResolution);

            float genHeight(int posX, int posY);

        private:
            unsigned int mSeed;
            static int mPermutationTable[];
            int mResolution;

            //utility functions
            float calcGradientDot(int inRand, int x, int y);
            float smoothTheEdges(float inValue);
            float linearInterpolation(float inValue, float inLeft, float inRight);
            int getRandomValue(float inSeed);
    };
}

#endif