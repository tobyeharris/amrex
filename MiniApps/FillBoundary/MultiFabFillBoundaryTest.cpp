// --------------------------------------------------------------------------
// MultiFabFillBoundaryTest.cpp
// --------------------------------------------------------------------------
//  this file writes and reads multifabs.
// --------------------------------------------------------------------------
#include <winstd.H>

#include <new>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>

#ifndef WIN32
#include <unistd.h>
#endif

#include <ParmParse.H>
#include <ParallelDescriptor.H>
#include <Utility.H>
#include <VisMF.H>

#ifdef BL_USE_SETBUF
#define pubsetbuf setbuf
#endif

const int maxGrid(64);

// --------------------------------------------------------------------------
int main(int argc, char *argv[]) {

    BoxLib::Initialize(argc,argv);    

    // ---- First use the number of processors to decide how many grids you have.
    // ---- We arbitrarily decide to have one grid per MPI process in a uniform
    // ---- cubic domain, so we require that the number of processors be N^3. 
    // ---- This requirement is somewhat arbitrary, but convenient for now.

    int nprocs = ParallelDescriptor::NProcs();

    // This is the cube root of the number of processors
    int N = exp(log(abs(nprocs))/3.0);

    if (N*N*N != nprocs) 
    {
        BoxLib::Error("We require that the number of processors be a perfect cube");
    }

    // std::cout << "Cube root of " << nprocs << " is " << N << std::endl;

    int nGhost;
    int nComp;

    // Don't restrict ourselves to on-processor communication
    bool local = false;

    // ---- If cross == true then only the faces are exchanged
    // ---- If cross == false then the faces, edges and corners are all exchanged
    bool cross;

    // ---- make a box, then a boxarray with maxSize
    int domain_hi = (N*maxGrid) - 1;
    Box Domain(IntVect(0,0,0), IntVect(domain_hi,domain_hi,domain_hi));
    BoxArray ba(Domain);
    ba.maxSize(maxGrid);

    // ---- Below we will make a MultiFab and set the values to 1.0
    // ----  (this is arbitrary, just makes the values not be undefined)
    // ---- We will do this for nGhost = 1,...,4 and nComp = 1, 4, 20
    // ----  (these are also arbitrary, just meant to be representative)
    // ---- and for "cross" = true or false.

    // --------------------------------------------------------------------------
    // --------------------------------------------------------------------------
    // cross = true;
    // --------------------------------------------------------------------------
    // --------------------------------------------------------------------------

    nGhost = 1;
    nComp  = 1;
    
    MultiFab mf1_1t(ba, nComp, nGhost);
    mf1_1t.setVal(1.0);
    mf1_1t.FillBoundary(local,cross);

    // --------------------------------------------------------------------------
    // --------------------------------------------------------------------------

    nGhost = 2;
    nComp  = 1;
    
    MultiFab mf2_1t(ba, nComp, nGhost);
    mf2_1t.setVal(1.0);
    mf2_1t.FillBoundary(local,cross);

    // --------------------------------------------------------------------------
    // --------------------------------------------------------------------------

    nGhost = 3;
    nComp  = 1;
    
    MultiFab mf3_1t(ba, nComp, nGhost);
    mf3_1t.setVal(1.0);
    mf3_1t.FillBoundary(local,cross);

    // --------------------------------------------------------------------------
    // --------------------------------------------------------------------------

    nGhost = 4;
    nComp  = 1;
    
    MultiFab mf4_1t(ba, nComp, nGhost);
    mf4_1t.setVal(1.0);
    mf4_1t.FillBoundary(local,cross);

    // --------------------------------------------------------------------------
    // --------------------------------------------------------------------------

    nGhost = 1;
    nComp  = 4;
    
    MultiFab mf1_4t(ba, nComp, nGhost);
    mf1_4t.setVal(1.0);
    mf1_4t.FillBoundary(local,cross);

    // --------------------------------------------------------------------------
    // --------------------------------------------------------------------------

    nGhost = 2;
    nComp  = 4;
    
    MultiFab mf2_4t(ba, nComp, nGhost);
    mf2_4t.setVal(1.0);
    mf2_4t.FillBoundary(local,cross);

    // --------------------------------------------------------------------------
    // --------------------------------------------------------------------------

    nGhost = 3;
    nComp  = 4;
    
    MultiFab mf3_4t(ba, nComp, nGhost);
    mf3_4t.setVal(1.0);
    mf3_4t.FillBoundary(local,cross);

    // --------------------------------------------------------------------------
    // --------------------------------------------------------------------------

    nGhost = 4;
    nComp  = 4;
    
    MultiFab mf4_4t(ba, nComp, nGhost);
    mf4_4t.setVal(1.0);
    mf4_4t.FillBoundary(local,cross);

    // --------------------------------------------------------------------------
    // --------------------------------------------------------------------------

    nGhost = 1;
    nComp  = 20;
    
    MultiFab mf1_20t(ba, nComp, nGhost);
    mf1_20t.setVal(1.0);
    mf1_20t.FillBoundary(local,cross);

    // --------------------------------------------------------------------------
    // --------------------------------------------------------------------------

    nGhost = 2;
    nComp  = 20;
    
    MultiFab mf2_20t(ba, nComp, nGhost);
    mf2_20t.setVal(1.0);
    mf2_20t.FillBoundary(local,cross);

    // --------------------------------------------------------------------------
    // --------------------------------------------------------------------------

    nGhost = 3;
    nComp  = 20;
    
    MultiFab mf3_20t(ba, nComp, nGhost);
    mf3_20t.setVal(1.0);
    mf3_20t.FillBoundary(local,cross);

    // --------------------------------------------------------------------------
    // --------------------------------------------------------------------------

    nGhost = 4;
    nComp  = 20;
    
    MultiFab mf4_20t(ba, nComp, nGhost);
    mf4_20t.setVal(1.0);
    mf4_20t.FillBoundary(local,cross);

    // --------------------------------------------------------------------------
    // --------------------------------------------------------------------------
    // cross = false;
    // --------------------------------------------------------------------------
    // --------------------------------------------------------------------------

    nGhost = 1;
    nComp  = 1;
    
    MultiFab mf1_1f(ba, nComp, nGhost);
    mf1_1f.setVal(1.0);
    mf1_1f.FillBoundary(local,cross);

    // --------------------------------------------------------------------------
    // --------------------------------------------------------------------------

    nGhost = 2;
    nComp  = 1;
    
    MultiFab mf2_1f(ba, nComp, nGhost);
    mf2_1f.setVal(1.0);
    mf2_1f.FillBoundary(local,cross);

    // --------------------------------------------------------------------------
    // --------------------------------------------------------------------------

    nGhost = 3;
    nComp  = 1;
    
    MultiFab mf3_1f(ba, nComp, nGhost);
    mf3_1f.setVal(1.0);
    mf3_1f.FillBoundary(local,cross);

    // --------------------------------------------------------------------------
    // --------------------------------------------------------------------------

    nGhost = 4;
    nComp  = 1;
    
    MultiFab mf4_1f(ba, nComp, nGhost);
    mf4_1f.setVal(1.0);
    mf4_1f.FillBoundary(local,cross);

    // --------------------------------------------------------------------------
    // --------------------------------------------------------------------------

    nGhost = 1;
    nComp  = 4;
    
    MultiFab mf1_4f(ba, nComp, nGhost);
    mf1_4f.setVal(1.0);
    mf1_4f.FillBoundary(local,cross);

    // --------------------------------------------------------------------------
    // --------------------------------------------------------------------------

    nGhost = 2;
    nComp  = 4;
    
    MultiFab mf2_4f(ba, nComp, nGhost);
    mf2_4f.setVal(1.0);
    mf2_4f.FillBoundary(local,cross);

    // --------------------------------------------------------------------------
    // --------------------------------------------------------------------------

    nGhost = 3;
    nComp  = 4;
    
    MultiFab mf3_4f(ba, nComp, nGhost);
    mf3_4f.setVal(1.0);
    mf3_4f.FillBoundary(local,cross);

    // --------------------------------------------------------------------------
    // --------------------------------------------------------------------------

    nGhost = 4;
    nComp  = 4;
    
    MultiFab mf4_4f(ba, nComp, nGhost);
    mf4_4f.setVal(1.0);
    mf4_4f.FillBoundary(local,cross);

    // --------------------------------------------------------------------------
    // --------------------------------------------------------------------------

    nGhost = 1;
    nComp  = 20;
    
    MultiFab mf1_20f(ba, nComp, nGhost);
    mf1_20f.setVal(1.0);
    mf1_20f.FillBoundary(local,cross);

    // --------------------------------------------------------------------------
    // --------------------------------------------------------------------------

    nGhost = 2;
    nComp  = 20;
    
    MultiFab mf2_20f(ba, nComp, nGhost);
    mf2_20f.setVal(1.0);
    mf2_20f.FillBoundary(local,cross);

    // --------------------------------------------------------------------------
    // --------------------------------------------------------------------------

    nGhost = 3;
    nComp  = 20;
    
    MultiFab mf3_20f(ba, nComp, nGhost);
    mf3_20f.setVal(1.0);
    mf3_20f.FillBoundary(local,cross);

    // --------------------------------------------------------------------------
    // --------------------------------------------------------------------------

    nGhost = 4;
    nComp  = 20;
    
    MultiFab mf4_20f(ba, nComp, nGhost);
    mf4_20f.setVal(1.0);
    mf4_20f.FillBoundary(local,cross);

    BoxLib::Finalize();
    return 0;
}
// --------------------------------------------------------------------------
