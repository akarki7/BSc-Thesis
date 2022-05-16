# Bachelor's Thesis

## Basic Information:
* Topic: **B-Scheduling on Ubuntu Linux**
* Supervisor: Prof. Andreas Birk (`a.birk@jacobs-university.de`)
* Jacobs University Bremen (2022)

## Linux used:
* DISTRIB_ID=Ubuntu
* DISTRIB_RELEASE=20.04
* DISTRIB_CODENAME=focal
* DISTRIB_DESCRIPTION="Ubuntu 20.04.4 LTS"
* NAME="Ubuntu"
* VERSION="20.04.4 LTS (Focal Fossa)"

## Requirements and setup
---------------------------------------------
* Make sure you have Ubuntu Linux OS. 
* Make sure you have `make` installed on your device.
* Make sure you have `python` and `gcc` installed on your device.
* Make sure you have python `virtualenv` installed on your device

## Steps to run the B-Scheduling algorithm
---------------------------------------------
* From the code directory run `make`
* Run `./main.out` and enter the time period either in Hz or Seconds
* To cleanup run `make deleteall`
* To get only the output schedule of a single major cycle run `./output.out` (usage: [-f] [-o filename] [-a] [-p])
  * `-f` for output to be directed to a file
  * `-o filename` for giving desired filename to the output file (by default set to `output.txt`)
  * `-p` to get the results for same `MAXPV` but increasing `av`
  * `-a` to get the analysis of the B-schedule output like WL,av and balance values
  * Except for `-p` option, you need to create a scenario of your need for running B-scheduling as asked in the input

## Steps to run the simulation
---------------------------------------------
* From the directory /code/simulation run `make`
* For simple simulation run `./simulation.out`
* For complex simulation run `./simulation.out` 

## Steps to create plots
---------------------------------------------
* From the directory /code/plots run `make run`
* Choose the options as asked in the screen to get desired graph plots


## Folder and File Descriptions: (only the important files are listed)

    code
    ├── plots (used to create plots from the results obtained)
        ├── data (contains the data used for plotting)
        ├── plotter.py (python file used to create plots using matplotlib)
    ├── simulation
        ├── simulation.c (simple simulation)
        ├── simulation_complex.c (complex simulation)
    ├── b_scheduling.c (core b-scheduling algorithm)
    ├── main.c (running b-scheduling algorithm at a certain frequency)
    ├── output_only.c (get results of B-scheduling and the analysis of output for dynamic scenarios as inputted)

    outputs (stores important output obtained from the execution)


### Notes
------------------------------
* If you have any queries you can contact me at `karkiaabishkar@gmail.com`