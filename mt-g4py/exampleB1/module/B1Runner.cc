//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// $Id: exampleB1.cc 86065 2014-11-07 08:51:15Z gcosmo $
//
/// \file exampleB1.cc
/// \brief Main program of the B1 example

#include "B1DetectorConstruction.hh"
#include "B1ActionInitialization.hh"

#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif

#include "G4UImanager.hh"
#include "QBBC.hh"

#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "Randomize.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


#include <boost/python.hpp>

using namespace boost::python;





class B1Runner
{
  public:
    B1Runner()
    {

        runManager = 0;

        visManager = 0;

    }

    ~B1Runner()
    {


        // Job termination
        // Free the store: user actions, physics_list and detector_description are
        // owned and deleted by the run manager, so they should not be deleted
        // in the main() program !

        delete visManager;
        delete runManager;
    }


    void Initialize_Run()
    {
        // Choose the Random engine
        G4Random::setTheEngine(new CLHEP::RanecuEngine);

        // Construct the default run manager
        //

        runManager = new G4MTRunManager;



        // Set mandatory initialization classes
        //
        // Detector construction
        runManager->SetUserInitialization(new B1DetectorConstruction());

        // Physics list
        G4VModularPhysicsList* physicsList = new QBBC;
        physicsList->SetVerboseLevel(1);
        runManager->SetUserInitialization(physicsList);

        // User action initialization
        runManager->SetUserInitialization(new B1ActionInitialization());

        // Initialize visualization
        //
        visManager = new G4VisExecutive;
        // G4VisExecutive can take a verbosity argument - see /vis/verbose guidance.
        // G4VisManager* visManager = new G4VisExecutive("Quiet");
        visManager->Initialize();

    };

    void SetBatchMacro(G4String fname)
    {


        // Get the pointer to the User Interface manager
        G4UImanager* UImanager = G4UImanager::GetUIpointer();

        // Process macro or start UI session
        //

        G4String command = "/control/execute ";
        G4String fileName = fname;
        UImanager->ApplyCommand(command+fileName);

    }




  private:


     G4MTRunManager* runManager ;
     G4VisManager* visManager;
};





//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....



BOOST_PYTHON_MODULE(exampleB1)
{

    class_<B1Runner>("B1Runner", "B1 Examples Runner")
      .def("Initialize_Run", &B1Runner::Initialize_Run)
      .def("SetBatchMacro", &B1Runner::SetBatchMacro)

      ;



}
