%Load csv data
%
%Christopher Lum
%lum@uw.edu

%Version History
%12/09/21: Created
%01/13/22: Updated

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


dataFile = '22_01_13_LOG04.CSV';

T = readtable(dataFile);
data = table2array(T);

gps_isValid             = data(:,1);
gps_date_year           = data(:,2);
gps_date_month          = data(:,3);
gps_date_day            = data(:,4);
gps_time_hour           = data(:,5);
gps_time_minute         = data(:,6);
gps_time_second         = data(:,7);
gps_satellites_value2   = data(:,8);
temperatureA_c          = data(:,9);
temperatureB_c          = data(:,10);
gps_location_lat_deg    = data(:,11);
gps_location_lng_deg    = data(:,12);
gps_speed_mph           = data(:,13);
gps_altitude_ft         = data(:,14);
gps_hdop_fraction       = data(:,15);

%% Plots
figure
hold on
subplot(3,1,1)
plot(gps_isValid)
ylabel(StringWithUnderscoresForPlot('gps_isValid'))
grid on

subplot(3,1,2)
plot(gps_satellites_value2)
ylabel(StringWithUnderscoresForPlot('gps_satellites_value2'))
grid on

subplot(3,1,3)
plot(gps_hdop_fraction)
ylabel(StringWithUnderscoresForPlot('gps_hdop_fraction'))
grid on

figure
hold on
plot(temperatureA_c)
plot(temperatureB_c)
grid on


figure
subplot(2,1,1)
hold on
plot(gps_speed_mph)
ylabel(StringWithUnderscoresForPlot('gps_speed_mph'))
grid on

subplot(2,1,2)
hold on
plot(gps_altitude_ft)
ylabel(StringWithUnderscoresForPlot('gps_altitude_ft'))
grid on

figure
startIdx = 270;
plot(gps_location_lng_deg(startIdx:end),gps_location_lat_deg(startIdx:end))

%% Write to KML
outputFile = 'TestGPS.kml';
kmlwriteline(outputFile,gps_location_lat_deg(startIdx:end),gps_location_lng_deg(startIdx:end));

% 
% % plot([1:1:length(t_s)],t_s)
% 
% plot([1:1:length(t_s)],T1_f)




toc
disp('DONE!')