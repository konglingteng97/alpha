# Alpha induced fluorescence Geant4 simulation

- Author: Lingteng Kong (jn19830@bristol.ac.uk) 

- Copyright (c) Lingteng Kong

- Data: 29.06.2020

## Detector construction

- Include definititon of relevant material and geometry construction.

- The geomrtry is a square box with length of 10 m, filled with gas.

- The fluorescence material include Air, Nitrogen, Argon gas.

- You are able to set the material with the command: /alpha/det/setMat  material

## Physics list

- Mainly include radioactivedecay, ionization, scintillation, optical processes and relevant particle definition.

- You are able to change the verbose level with the command: /alpha/phys/verbose number, 0 for silent mode (currently not for EM process)

## Primary generator

- Default radioactive source is Am-241, at rest. 

- The radioactive source is dispersed over a 2 cm radius circle at coordinate origin.
         
## Histograms

- 1D histograms of distribution and energy spectrum of relevent particles.

- 2D histogram of distribution of scintillation photon in xy plane.

- nTuples information of all particles.

- The histos can be individually activated with the command :
/analysis/h1/set id nbBins  valMin valMax unit 

- One can control the name of the histograms file with the command:
/analysis/setFileName  name 

- It is possible to choose the format of the histogram file : root (default),
xml, csv, by using namespace in HistoManager.hh

- By default, all selected histos will be written on a file data.root.

## Visualisation

- Visualization Manager is set in the main().
Initialisation of the drawing is done via the commands
/vis/.. in the macro vis.mac. This macro is automatically read from the main 
in case of interactive running mode.


# How to start ?

## Pre-Requirements

- Get ROOT (6.22/00), Geant4 (4.10.06.p02), CMake (3.18.0-rc4) installed

## 1. Install

> cd {where you want to setup the code}

> git clone https://github.com/lingtengkong/alpha.git

> cd alpha

## 2. Build code

> mkdir build

> cd build

> cmake ..

> make -j4

## 3. Run the simulation

- Recommand: Execute alpha in 'batch' mode from macro files.

- You are able to change the parameters by editing {material}.mac

> ./alpha air.mac

> ./alpha N2.mac

> ./alpha Ar.mac
   
- Execute alpha in 'interactive mode' with visualization

> ./alpha

> /run/beamOn 1

> exit

## 4. View results

> root

> TBrowser a

## 5. Plot figures

- You are able to plot figures useing python script plt.py

> python plt.py

- figures are saved as pdf files in /build 