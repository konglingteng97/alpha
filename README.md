# Alpha induced fluorescence Geant4 simulation

- Author: Lingteng Kong (jn19830@bristol.ac.uk) 

- Copyright (c) Lingteng Kong

- Data: 29.06.2020

## Geometry construction

- A square box with length of 10 m, filled with gas.

## Physics list

- Mainly include radioactivedecay, ionization, scintillation, optical processes and relevant particle definition.
         
## Primary generator

- Default kinematic is an ion (Am-241), at rest, at coordinate origin. 
         
## Histograms

- Include distribution and energy spectrum of relevent particles.

- The histos can be individually activated with the command :
/analysis/h1/set id nbBins  valMin valMax unit 
where unit is the desired unit for the histo (MeV or keV, mm or cm, etc..)

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

- Get ROOT, Geant4 (4.10.06.p02), cmake installed

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

- Recommand: Execute alpha in 'batch' mode from macro files

> ./alpha run.mac
   
- Execute alpha in 'interactive mode' with visualization

> ./alpha

> /run/beamOn 1

> exit

## 4. View results

> root

> TBrowser a