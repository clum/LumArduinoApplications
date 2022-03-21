%Analyze data.
%
%Christopher Lum
%lum@uw.edu

%Version History
%03/21/22: Updated by breaking into two scripts

clear
clc
close all

tic

ChangeWorkingDirectoryToThisLocation();

%% User selections
inputFile   = 'Step01Results.mat';

%% Load data
temp = load(inputFile);
data = temp.data;

%% Analyze and plot results
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

%Isolate valid values
validIndices = find(gps_isValid==1);

%Compute time
time = datetime(gps_date_year,gps_date_month,gps_date_day,gps_time_hour,gps_time_minute,gps_time_second);

%% Plots
figure
subplot(5,1,1)
hold on
plot(time,CelciustoFarenheit(temperatureA_c))
plot(time,CelciustoFarenheit(temperatureB_c))
legend('T_A','T_B')
ylabel('Temperature (F)')
grid on

subplot(5,1,2)
plot(time,gps_satellites_value2)
ylabel('GPS Satellites')
grid on

subplot(5,1,3)
plot(time,gps_speed_mph)
ylabel('GPS Speed (MPH)')
grid on

subplot(5,1,4)
plot(time,gps_altitude_ft)
ylabel('GPS Altitude (ft)')
grid on

subplot(5,1,5)
plot(time,gps_hdop_fraction)
ylabel('GPS HDOP (fraction)')
grid on

%Plot trajectory
figure
geoplot(gps_location_lat_deg(validIndices),gps_location_lng_deg(validIndices))
geobasemap('streets')

toc
disp('DONE!')