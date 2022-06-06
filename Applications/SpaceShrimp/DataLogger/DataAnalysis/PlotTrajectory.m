%Plot the 3D trajectory of the space shrimp mission
%
%Amara Lum

%Version History
%06/04/22: created

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
% inputFile   = 'GPS_03.mat';
% inputFile   = 'GPS_03_short.mat';
inputFile   = 'SpaceShrimp.mat';

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
% converting feet to meters
gps_altitude_m=FttoM(gps_altitude_ft);

plot3(gps_location_lng_deg,gps_location_lat_deg,gps_altitude_m)
xlabel('gps_location_lng_deg')
ylabel('gps_location_lat_deg')
zlabel('gps_altitude_m')
grid on
MaximizeFigureAll();
% write to Google Earth
kmlwriteline('SpaceShrimpGoogleEarth.kml',gps_location_lat_deg,gps_location_lng_deg,gps_altitude_m)

toc
disp('DONE!')