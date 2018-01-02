// ==========================================================================
// Copyright (C) 2011 Lior Kogan (koganlior1@gmail.com)
// ==========================================================================

#include "stdafx.h"
#include "CircVal.h"

#include <chrono>
#include <iostream>                 // cout
#include <fstream>                  // ofstream
#include <ppl.h>                    // Concurrency::parallel_for

#include "CircVal.h"                // CircVal, CircValTester
#include "CircStat.h"               // CircAverage, WeightedCircAverage, CAvrgSampledCircSignal, CircMedian
#include "CircHelper.h"             // Sqr, Mod
#include "TruncNormalDist.h"        // truncated_normal_distribution
#include "WrappedNormalDist.h"      // wrapped_normal_distribution
#include "WrappedTruncNormalDist.h" // wrapped_truncated_normal_distribution

// ==========================================================================
int _tmain(int argc, _TCHAR* argv[])
{
    auto Time0= chrono::system_clock::now();

    // ------------------------------------------------------
    // testing correctness of CircVal class implementation
    {
        CircValTester<SignedDegRange  > testA;
        CircValTester<UnsignedDegRange> testB;
        CircValTester<SignedRadRange  > testC;
        CircValTester<UnsignedRadRange> testD;

        CircValTester<TestRange0      > test0;
        CircValTester<TestRange1      > test1;
        CircValTester<TestRange2      > test2;
        CircValTester<TestRange3      > test3;
    }

    // ------------------------------------------------------
    // sample code: basic circular math operations
    {
        CircVal<SignedDegRange  > d1=  10. ;
        CircVal<UnsignedRadRange> d2=   0.2;
        CircVal<SignedDegRange  > d3= d1+d2;

        d1+= 355.;
        double d= d1;

        d = sin(d1) / cos(d2) + tan(d3);
        d1= asin<SignedDegRange>(0.5); // don't do d1= asin(0.5) !!!
    }

    // ------------------------------------------------------
    // sample code: generating wrapped normal distributed random value
    {
        std::default_random_engine rand_engine;
        std::random_device         rnd_device ;
        rand_engine.seed(rnd_device()); // reseed engine

        double fAvrg =    0.;
        double fSigma=   45.;
        double fL    = -180.; // wrapping-range lower-bound
        double fH    =  180.; // wrapping-range upper-bound

        wrapped_normal_distribution<double> r_wrp(fAvrg, fSigma, fL, fH);
        double r1= r_wrp(rand_engine); // random value
    }

    // ------------------------------------------------------
    // sample code: generating truncated normal distributed random value
    {
        std::default_random_engine rand_engine;
        std::random_device         rnd_device ;
        rand_engine.seed(rnd_device()); // reseed engine

        double fAvrg =    0.;
        double fSigma=   45.;
        double fA    =  -40.; // truncation-range lower-bound
        double fB    =   40.; // truncation-range upper-bound

        truncated_normal_distribution<double> r_trn(fAvrg, fSigma, fA, fB);
        double r2= r_trn(rand_engine); // random value
    }

    // ------------------------------------------------------
    // sample code: generating wrapped truncated normal distributed random value
    {
        std::default_random_engine rand_engine;
        std::random_device         rnd_device ;
        rand_engine.seed(rnd_device()); // reseed engine

        // normal distribution is first truncated, and then wrapped

        const double fAvrg =    0.;
        const double fSigma=  100.;
        const double fA    = -500.; // truncation-range lower-bound
        const double fB    =  500.; // truncation-range upper-bound
        const double fL    =    0.; // wrapping  -range lower-bound
        const double fH    =  360.; // wrapping  -range upper-bound

        wrapped_truncated_normal_distribution<double> r_wrp_trn(fAvrg, fSigma, fA, fB, fL, fH);
        double d= r_wrp_trn(rand_engine); // random value
    }

    // ------------------------------------------------------
    // code used to collect data for graphs that demostrate average of circular values
    {
        vector<CircVal<UnsignedDegRange>> Angles2;
        Angles2.push_back( 20.);
        Angles2.push_back(130.);
        Angles2.push_back(230.);
        Angles2.push_back(330.);
        auto y= CircAverage(Angles2);

        ofstream f0("log0.txt");

        for (double x= 0.; x<=360.; x+= 0.1)
        {
            double fSum= 0;
            for (const auto& a : Angles2)
                fSum+= Sqr(__min(abs(x-a), 360.-abs(x-a)));

            f0 << x << "\t" << fSum << endl;
        }
    }

    // ------------------------------------------------------
    // sample code: calculate median, average and weighted-average set of circular-values
    {
        std::default_random_engine rand_engine;
        std::random_device         rnd_device ;
        rand_engine.seed(rnd_device()); // reseed engine

        uniform_real<double> ud(UnsignedDegRange::L, UnsignedDegRange::H);

        vector<     CircVal<UnsignedDegRange>        > angles1;
        vector<pair<CircVal<UnsignedDegRange>,double>> angles2;

        for (size_t i= 0; i<3; ++i)
        {
            double m= ud(rand_engine);
            angles1.push_back(m                );
            angles2.push_back(make_pair(m, 0.3));
        }

        auto Medn = CircMedian         (angles1);
        auto Avrg1= CircAverage        (angles1);
        auto Avrg2= WeightedCircAverage(angles2);
    }

    // ------------------------------------------------------
    // sample code: estimate average of a sampled continuous-time circular signal, using circular linear interpolation
    {
        CAvrgSampledCircSignal<UnsignedDegRange> A1;
        A1.AddMeasurement(CircVal<UnsignedDegRange>(200.), 1);
        A1.AddMeasurement(CircVal<UnsignedDegRange>(300.), 2);
        A1.AddMeasurement(CircVal<UnsignedDegRange>( 20.), 6);

        CircVal<UnsignedDegRange> ad1;
        A1.GetAvrg(ad1);
    }

    // ------------------------------------------------------
    // code used to collect data for RMS error of average estimation based on noisy measurements
    {
        std::default_random_engine rand_engine;
        std::random_device         rnd_device ;
        rand_engine.seed(rnd_device()); // reseed engine

        ofstream f1("log1.txt");

        Concurrency::parallel_for(1, 101, [&](int nStdDev) // for each value of standard-deviation
        {
            uniform_real<double> ud(0., 360.);

            double fSumSqrErr1= 0.;
            double fSumSqrErr2= 0.;

            const size_t nTrails = 50000;                  // number of trails
            const size_t nSamples=  1000;                  // number of observations per trail

            vector<CircVal<UnsignedDegRange>> vInput(nSamples);

            const double fAvrg= ud(rand_engine);           // our const parameter for this trail
            wrapped_normal_distribution          <double> r_wnd1(fAvrg, nStdDev,                       0., 360.);
         // wrapped_truncated_normal_distribution<double> r_wnd1(fAvrg, nStdDev, fAvrg-45., fAvrg+45., 0., 360.);

            for (size_t t= 0; t<nTrails; ++t)
            {
                for (auto& Sample : vInput)
                    Sample= r_wnd1(rand_engine);           // generate "noisy" observation

                set<CircVal<UnsignedDegRange>> sAvrg1= CircAverage(vInput);                   // avrg - method 1 (new method)

                double fSigSin= 0.;
                double fSigCos= 0.;

                for (const auto& Sample : vInput)
                {
                    fSigSin+= sin(Sample);
                    fSigCos+= cos(Sample);
                }

                CircVal<UnsignedDegRange> Avrg2= atan2<UnsignedDegRange>(fSigSin, fSigCos);   // avrg - method 2 (conventional method)

                const double fErr1= CircVal<UnsignedDegRange>::Sdist(*sAvrg1.begin(), fAvrg); // error of estimate - method 1
                const double fErr2= CircVal<UnsignedDegRange>::Sdist(Avrg2          , fAvrg); // error of estimate - method 2

                fSumSqrErr1+= Sqr(fErr1);
                fSumSqrErr2+= Sqr(fErr2);
            }

            const double fRMS1= sqrt(fSumSqrErr1/ (nTrails-1));  // root mean square error - method 1
            const double fRMS2= sqrt(fSumSqrErr2/ (nTrails-1));  // root mean square error - method 2

            f1 << nStdDev << "\t" << fRMS1 << "\t" << fRMS2 << endl; // save RMS results to file
        } );
    }

    // -----------------------------------
    auto Duration= chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now() - Time0).count();
    cout << Duration << endl;

    // system ("pause");

    return 0;
}
