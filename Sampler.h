#ifndef SAMPLER_H
#define SAMPLER_H

#include "common.h"
#include "Point.h"

class Sampler {
    public:
        Sampler();
        Sampler(const int &);
        virtual ~Sampler();

        virtual void generateSamples() = 0;

        void setupShuffledIndices();
        void shuffleSamples();
        Point2D sampleUnitSquare();

        void setNumSets(const int &);
        int getNumSets() const;
        int getNumSamples() const;

        void shuffleXCoordinates();
        void shuffleYCoordinates();

        // map samples to disk
        void mapSamplesToUnitDisk();

        // map samples to hemisphere
        void mapSamplesToHemisphere(const RTdouble &);
        Point sampleHemisphere();

    protected:
        int numSamples;
        int numSets;
        vector <Point2D> samples;
        vector <int> shuffledIndices;
        unsigned long count;
        int jump;

        vector <Point2D> diskSamples;
        vector <Point> hemisphereSamples;
};

class PureRandom: public Sampler {
    public:
        virtual ~PureRandom();
        virtual void generateSamples();
};

class Regular: public Sampler {
    public:
        Regular();
        Regular(const int &);
        virtual ~Regular();

        virtual void generateSamples();
};

class Jittered: public Sampler {
    public:
        Jittered();
        Jittered(const int &);
        virtual ~Jittered();

        virtual void generateSamples();
};

class NRooks: public Sampler {
    public:
        NRooks();
        NRooks(const int &);
        virtual ~NRooks();

        virtual void generateSamples();
};

class MultiJittered: public Sampler {
    public:
        MultiJittered();
        MultiJittered(const int &);
        virtual ~MultiJittered();

        virtual void generateSamples();
};

class Hammersley: public Sampler {
    public:
        virtual ~Hammersley();
        virtual void generateSamples();
};

#endif
