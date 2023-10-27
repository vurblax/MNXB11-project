# MNXB11 Project Group E
# About
This is a project for the course MNXB11 at Lund University. This README file contains instructions on how to recreate our results.

# Prerequisites
Firsly, in order for this script to run you need to have ROOT installed. Additionally, this project uses two libraries which needs to be installed in order for the script to work. These are:

- fast-cpp-csv-parser
Created by ben-strasser.
A header-only library. 
Header file: csv.h
SSH: git@github.com:ben-strasser/fast-cpp-csv-parser.git

- date
Created by Howard Hinnant.
Also a header-only library. 
Header file: date.h
SSH: git@github.com:HowardHinnant/date.git

  In order to install these libraries you must clone the HTTPS (or SSH) for each library, and then make sure that its header file is put into the folder: /dependencies/external/include
  If the library header files are put in another folder then the makefile won't be able to find the libraries.

# Data cleaning
Before compiling the script you will need to clean the raw temperature data .csv files using a bash script. The datafiles are included in /datasets as a tarball. The bash script is called cleaner.sh and can be found in the root directory. Clean files are already present in the directory but if you want to recreate our results from step 1 you have to follow these steps: 

Firstly you extract the csv files by opening the dataset.tgz tarball by running tar zxvf datasets.tgz. 

You then clean the files by running cleaner.sh ./datasets/name-of-file

The files are now ready for the data extraction.

# How to compile the script
The script uses a makefile to compile. You need to be in the root directory of the repository, and run make. The script itself has been divided into several translation units:

- DataExtraction
The first part of the script. This script retrieves the data from the cleaned csv and puts it into a ROOT TTree called output.root

- WeatherData
This script works as a check to filter out data points that have not been marked as good quality by SMHI.

- Three analyses with separate translation units:

  Analysis 1 - The temperature of a given day (25th of December).

  Analysis 2 - The change in yearly mean temperature from 1990 - 2023.

  Analysis 3 - The warmest and coldest day of each year.

  All analyses looks at data from Lund.


In order to choose which dataset you want to base your analysis on, you need to go into the main.cxx file and change the filepath on line 17. It is currently set to Lund, which it will have to be if you intend to recreate our graphs.

When you run make, all analyses will be run. 

# Retrieving the graphs
In order to retrieve the resulting graphs and histograms, you need to run the executable by typing ./main. This will produce three png images with the graphs, one for each analysis. The names for each of the images are:

Analysis 1: december25th_histogram.png
Analysis 2: yearmeans.png
Analysis 3: 

You can also view the graphs in root. You enter root by typing: root --web=off
The graphs, as well as the TTree produced by the script, can then be viewed in the TBrowser by typing: TBrowser b("output.root)
