#include "perlin.h"

namespace Noise{

    //initialize the permutation table
    int Perlin::mPermutationTable[] = { 151,160,137,91,90,15,
        131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,
        190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,
        88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,134,139,48,27,166,
        77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,
        102,143,54, 65,25,63,161, 1,216,80,73,209,76,132,187,208, 89,18,169,200,196,
        135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,250,124,123,
        5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,
        223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167, 43,172,9,
        129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,
        251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,107,
        49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
        138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180
    };

    Perlin::Perlin():
    mSeed(770972),
    mResolution(10){
        //default constructor
    }

    Perlin::Perlin(unsigned int inSeed, int inResolution):
    mSeed(inSeed),
    mResolution(inResolution){
        //parameterizd constructor
    }

    float Perlin::genHeight(int inPosX, int inPosY){

        //first convert the input coordinates to float 
        //such that the integer part gives the coordinate of grid
        //float gives the position inside the grid this varies with resolution

        int posXi = (inPosX / mResolution) & mResolution; //so that the value doesn't exceed resolution
        int posXf = (inPosX % mResolution) & mResolution;
        int posYi = (inPosY / mResolution) & mResolution;
        int posYf = (inPosY % mResolution) & mResolution;

        //we will have four gradient vectors for four corners of a rectangle
        //get a random value for gradient
        //such that it will always give same value for same number

        //using custom values for now
        //this generally comes from permutation table
        int grad1 = mPermutationTable[(mPermutationTable[(posXi) & mResolution] + posYi) & mResolution];
        int grad2 = mPermutationTable[(mPermutationTable[(posXi + 1) & mResolution] + posYi) & mResolution];
        int grad3 = mPermutationTable[(mPermutationTable[(posXi) & mResolution] + posYi + 1) & mResolution];
        int grad4 = mPermutationTable[(mPermutationTable[(posXi + 1) & mResolution] + posYi + 1) & mResolution];

        float dotOfCorner1 = calcGradientDot(grad1, posXf, posYf);
        float dotOfCorner2 = calcGradientDot(grad2, posXf - 1, posYf);
        float dotOfCorner3 = calcGradientDot(grad3, posXf, posYf - 1);
        float dotOfCorner4 = calcGradientDot(grad4, posXf -1 , posYf - 1);

        //use fade function to smooth the edges of grid
        float smoothXf = smoothTheEdges(posXf);
        float smoothYf = smoothTheEdges(posYf);

        //use interpolation to calculate final value
        float interpolatedXUp = linearInterpolation(smoothXf, dotOfCorner1, dotOfCorner2);
        float interpolatedXDown = linearInterpolation(smoothXf, dotOfCorner3, dotOfCorner4);
        float interpolatedY = linearInterpolation(smoothYf, interpolatedXUp, interpolatedXDown);

        return (int)interpolatedY & 50;
    }

    int Perlin::getRandomValue(float inSeed){

        return 0.0f;
    }

    float Perlin::linearInterpolation(float inValue, float inLeft, float inRight){

        return ( (1 - inValue) * inLeft + inValue * inRight );
    }


    float Perlin::smoothTheEdges(float inValue){

        //we will fade the edges using this function
        // 6t^5 - 15t^4 + 10t^3
        //this function has second derivative and is continuous at the edges
        return (6 * pow(inValue, 5) - 15 * pow(inValue, 4) + 10 * pow(inValue, 3));
    }

    float Perlin::calcGradientDot(int inRand, int inXf, int inYf){

        //list of our gradients
        //(1, 1)
        //(-1, 1)
        //(1, -1)
        //(-1, -1)

        //choose gradient based on the value of grad
        //and return dot product
        switch (inRand & 3)
        {
        case 0:
            //use (1, 1)
            return inXf + inYf;
        case 1:
            //use (-1, 1)
            return -inXf + inYf;
        case 2:
            //use (1, -1)
            return inXf - inYf;
        case 3:
            //use (-1, -1)
            return -inXf - inYf;
        default:
            return 0;
        }

    }


    // float Perlin::convToFloat(int inValue){

    //     //find the number of digits 
    //     float input = inValue;
    //     int noOfDigits = 0;

    //     while( input > 0 ){

    //         input = input / pow( 10, noOfDigits++ );
    //     }

    //     return pow(input, noOfDigits - 1 );
    // }
}