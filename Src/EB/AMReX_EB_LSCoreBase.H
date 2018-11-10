#ifndef _AMReX_EB_LSCoreBase_H_
#define _AMReX_EB_LSCoreBase_H_


#include <string>
#include <limits>
#include <memory>

#ifdef _OPENMP
#include <omp.h>
#endif

#include <AMReX_BCRec.H>
#include <AMReX_Vector.H>
#include <AMReX_AmrCore.H>

#include <AMReX_EB_LSCore_F.H>
#include <AMReX_EB_levelset.H>



#if defined(BL_USE_SENSEI_INSITU)
namespace amrex {
class AmrMeshInSituBridge;
}
#endif

//using namespace amrex;

namespace amrex {


class LSCoreBase
    : public AmrCore
{
public:

    /****************************************************************************
     * public member functions                                                  *
     ***************************************************************************/

    // Constructor - reads amr in parameters from inputs file
    //             - sizes multilevel arrays and data structures
    LSCoreBase ();
    virtual ~LSCoreBase ();

    // Initializes multilevel data
    void InitData ();

    // Make a new level using provided BoxArray and DistributionMapping and fill
    // with interpolated coarse level data. Overrides the pure virtual function
    // in AmrCore
    virtual void MakeNewLevelFromCoarse (int lev, Real time, const BoxArray & ba,
                                         const DistributionMapping & dm) override;

    // Remake an existing level using provided BoxArray and DistributionMapping
    // and fill with existing fine and coarse data. Overrides the pure virtual
    // function in AmrCore
    virtual void RemakeLevel (int lev, Real time, const BoxArray & ba,
                              const DistributionMapping & dm) override;

    // NOTE: These are _not_ constructed here but in the template specialization
    // LSCore classes:

    virtual void ClearLevel (int lev) override = 0;
    virtual void MakeNewLevelFromScratch (int lev, Real time, const BoxArray & ba,
                                          const DistributionMapping & dm) override = 0;

    // Tag all cells for refinement. Overrides the pure virtual function in
    // AmrCore
    virtual void ErrorEst (int lev, amrex::TagBoxArray& tags, amrex::Real time, int ngrow) override;

    // Write plotfile to disk
    void WritePlotFile ();


protected:

    /****************************************************************************
     * private member functions                                                 *
     ***************************************************************************/

    // Read in some parameters from inputs file
    void ReadParameters ();

    // Set covered coarse cells to be the average of overlying fine cells
    void AverageDown ();

    // More flexible version of AverageDown() that lets you average down across multiple levels
    void AverageDownTo (int crse_lev);

    // Compute a new multifab by coping in phi from valid region and filling
    // ghost cells works for single level and 2-level cases (fill fine grid
    // ghost by interpolating from coarse)
    void FillPatch (int lev, amrex::Real time, MultiFab & mf, int icomp, int ncomp);

    // Fill an entire multifab by interpolating from the coarser level this
    // comes into play when a new level of refinement appears
    void FillCoarsePatch (int lev, Real time, MultiFab & mf, int icomp, int ncomp);

    // Get plotfile name
    std::string PlotFileName (int lev) const;

    // Put together an array of multifabs for writing
    Vector<const MultiFab *> PlotFileMF ();

    // Set plotfile variables names
    Vector<std::string> PlotFileVarNames () const;

    // Write checkpoint file to disk
    void WriteCheckpointFile () const;

    // read checkpoint file from disk
    void ReadCheckpointFile ();

    // utility to skip to next line in Header
    static void GotoNextLine (std::istream & is);


    /****************************************************************************
     * private data members                                                     *
     ***************************************************************************/

    //
    // EB data used for rebuilding levels from scratch. Used by extension
    // classes (as they rely on template parameters). NOTE: use unique_ptr
    // because LSFactory does not have a default constructor.
    //
    Vector<const EB2::Level *>         eb_levels;
    Vector<std::unique_ptr<LSFactory>> ls_factory;
    // Apparently std::vector<bool> isn't a thing?! (more precisely it's a
    // different thing)
    Vector<int>                        rebuild_eb;

    // Level set data
    Vector<MultiFab>  level_set;
    // Cell-centered level set data:
    Vector<MultiFab>  level_set_cc;

    // Resolve EB up to this many ghost cells (NOTE: these are scaled based on
    // local refinement level)
    int eb_pad;

    // This is essentially a 2*DIM integer array storing the physical boundary
    // condition types at the lo/hi walls in each direction
    BCRec bcs;

    amrex::Vector<int> istep;      // which step?


    /****************************************************************************
     * runtime parameters                                                       *
     ***************************************************************************/

    // if >= 0 we restart from a checkpoint
    std::string restart_chkfile = "";

    // plotfile prefix and frequency
    std::string plot_file {"ls_plt"};
    int plot_int = -1;

    // checkpoint prefix and frequency
    std::string chk_file {"ls_chk"};
    int chk_int = -1;

#if defined(BL_USE_SENSEI_INSITU)
    amrex::AmrMeshInSituBridge *insitu_bridge;
#endif
};


}

#endif