%Analyze data.
%
%Christopher Lum
%lum@uw.edu

%Version History
%03/21/22: Updated by breaking into two scripts
%04/27/22: Adding time zone to time

clear
clc
close all

tic

ChangeWorkingDirectoryToThisLocation();

%% User selections
% inputFile   = '22_03_21_LOG5_ID01.mat';
% inputFile   = '22_03_28_LOG5_ID01.mat';
% inputFile   = '22_03_28_LOG5_ID02.mat';
% inputFile   = '22_04_17_LOG6_ID01.mat';
% inputFile   = 'GPS_01.mat';
% inputFile   = 'GPS_02.mat';
inputFile   = 'GPS_03.mat';

timeZone = 'America/Los_Angeles';

%% Load data
temp = load(inputFile);
data = temp.data;

%% Analyze and plot results
gps_isValid             = data(:,1);

%Isolate valid values
validIndices = find(gps_isValid==1);

gps_date_year           = data(validIndices,2);
gps_date_month          = data(validIndices,3);
gps_date_day            = data(validIndices,4);
gps_time_hour           = data(validIndices,5);
gps_time_minute         = data(validIndices,6);
gps_time_second         = data(validIndices,7);
gps_satellites_value2   = data(validIndices,8);
temperatureA_c          = data(validIndices,9);
temperatureB_c          = data(validIndices,10);
gps_location_lat_deg    = data(validIndices,11);
gps_location_lng_deg    = data(validIndices,12);
gps_speed_mph           = data(validIndices,13);
gps_altitude_ft         = data(validIndices,14);
gps_hdop_fraction       = data(validIndices,15);

%Compute time
gps_time = datetime(gps_date_year,gps_date_month,gps_date_day,gps_time_hour,gps_time_minute,gps_time_second);
utime = convertTo(gps_time,'posixtime');
time = datetime(utime,'ConvertFrom','posixtime','TimeZone',timeZone);

firstPacketDate = time(1);
lastPacketDate  = time(end);

dataDuration    = lastPacketDate - firstPacketDate;

disp('First packet received at')
disp(firstPacketDate)

disp('Last packet received at')
disp(lastPacketDate)

disp('Duration of data set (HH:MM:SS)')
disp(dataDuration)

%% Plots
%Plot time so we have an idea how many sets of data are in the log file
figure
plot([1:1:length(time)],time)
ylabel('time')
xlabel('Index')
title('Plot to identify how many data sets are in file')
grid on

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
geoplot(gps_location_lat_deg,gps_location_lng_deg,'LineWidth',3)
geobasemap('streets')

toc
disp('DONE!')