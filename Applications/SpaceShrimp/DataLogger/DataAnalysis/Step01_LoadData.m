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

% %data just isolated to hide and seek 1 excursion
% dataFile        = '.\22_03_28\LOG05.csv';
% dataStartRow    = 102;
% dataEndRow      = 2266;
% outputFile      = '22_03_28_LOG5_ID02.mat'; 

% %data from test
% dataFile        = '.\22_04_17\LOG06.csv';
% dataStartRow    = 34;
% dataEndRow      = 1188;
% outputFile      = '22_04_17_LOG6_ID01.mat'; 

% %data from GPS_01
% dataFile        = '.\22_04_26\LOG07.csv';
% dataStartRow    = 38;
% dataEndRow      = 29800;
% outputFile      = 'GPS_01.mat'; 

% %data from GPS_02
% dataFile        = '.\22_04_28\LOG07.csv';
% dataStartRow    = 415;
% dataEndRow      = 26360;
% outputFile      = 'GPS_02.mat';

% %data from GPS_03
% dataFile        = '.\22_04_30_GPS_03\LOG07.csv';
% dataStartRow    = 1070;
% dataEndRow      = 14900;
% outputFile      = 'GPS_03.mat';

% %data from GPS_03 (short)
% dataFile        = '.\22_04_30_GPS_03\LOG07.csv';
% dataStartRow    = 1980;
% dataEndRow      = 4402;
% outputFile      = 'GPS_03_short.mat';

%Space Shrimp
dataFile        = '.\22_05_28_SpaceShrimp\LOG07.csv';
dataStartRow    = 800;
dataEndRow      = 5700;
outputFile      = 'SpaceShrimp.mat';

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