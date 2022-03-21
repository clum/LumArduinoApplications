%Load csv data and isolate appropriate rows
%
%Christopher Lum
%lum@uw.edu

%Version History
%12/09/21: Created
%03/21/22: Cleaned up and generalized

clear
clc
close all

tic

ChangeWorkingDirectoryToThisLocation();

% dataFile = '.\21_12_29\LOG03.csv';
% 
% T = readtable(dataFile);
% data = table2array(T);
% 
% t_s = data(:,1)./1000;
% T1_f = CelciustoFarenheit(data(:,2));
% T2_f = CelciustoFarenheit(data(:,3));
% 
% figure
% hold on
% plot(t_s,T1_f)
% plot(t_s,T2_f)
% grid on

%% User selections
dataFile        = '.\22_03_21\LOG05.csv';
dataStartRow    = 6;
dataEndRow      = 285;
outputFile      = 'Step01Results.mat';

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