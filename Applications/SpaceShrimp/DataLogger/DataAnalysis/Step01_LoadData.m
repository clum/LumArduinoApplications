%Load csv data
%
%Christopher Lum
%lum@uw.edu

%Version History
%12/09/21: Created

clear
clc
close all

tic

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


dataFile = '.\21_12_29\LOG01.csv';

T = readtable(dataFile);
data = table2array(T);

t_s = data(:,1)./1000;
T1_f = CelciustoFarenheit(data(:,2));

% figure
% hold on
% plot(t_s,T1_f)
% grid on

% plot([1:1:length(t_s)],t_s)

plot([1:1:length(t_s)],T1_f)

toc
disp('DONE!')