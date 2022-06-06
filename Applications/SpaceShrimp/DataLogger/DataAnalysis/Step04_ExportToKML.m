%Write data to KML file
%
%Christopher Lum
%lum@uw.edu

%Version History
%06/01/22: Created

clear
clc
close all

tic

ChangeWorkingDirectoryToThisLocation();

%% User selections
inputFile   = 'SpaceShrimp_Reduced.mat';

%% Load data
temp = load(inputFile);

%% Analyze and plot results
time                    = temp.time;
gps_location_lat_deg    = temp.gps_location_lat_deg;
gps_location_lng_deg    = temp.gps_location_lng_deg;
gps_altitude_ft         = temp.gps_altitude_ft;

%% Write to KML
[inputFileName,~]=SeperateFileNameAndExtension(inputFile);
outputFile = [inputFileName,'.kml'];

%altitude in kml should be in meters
gps_altitude_m = FttoM(gps_altitude_ft);
kmlwriteline(outputFile,gps_location_lat_deg,gps_location_lng_deg,gps_altitude_m)

disp(['Saved to ',outputFile])

toc
disp('DONE!')