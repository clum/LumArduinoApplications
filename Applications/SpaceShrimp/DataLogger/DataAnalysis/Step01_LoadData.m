%Load csv data and isolate appropriate rows
%
%Christopher Lum
%lum@uw.edu

%Version History
%12/09/21: Created
%03/21/22: Cleaned up and generalized
%03/29/22: Cleaned up

clear
clc
close all

tic

ChangeWorkingDirectoryToThisLocation();

%% User selections
% dataFile        = '.\22_03_21\LOG05.csv';
% dataStartRow    = 6;
% dataEndRow      = 285;
% outputFile      = '22_03_21_LOG5_ID01.mat'; 

% %All data from hide and seek 1 (includes prep/testing)
% dataFile        = '.\22_03_28\LOG05.csv';
% dataStartRow    = 1;
% dataEndRow      = 2266;
% outputFile      = '22_03_28_LOG5_ID01.mat'; 

%data just isolated to hide and seek 1 excursion
dataFile        = '.\22_03_28\LOG05.csv';
dataStartRow    = 102;
dataEndRow      = 2266;
outputFile      = '22_03_28_LOG5_ID02.mat'; 

%% Load data
T = readtable(dataFile);
data = table2array(T);

%Isolate data to the appropriate range
data = data(dataStartRow:dataEndRow,:);

%% Save data
save(outputFile,'data')
disp(['Saved to ',outputFile])

toc
disp('DONE!')