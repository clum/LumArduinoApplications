%Analyze data.
%
%Christopher Lum
%lum@uw.edu

%Version History
%03/21/22: Updated by breaking into two scripts
%04/27/22: Adding time zone to time
%06/01/22: Saving data to results file
%06/04/22: Computing vertical speeds

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

%Compute vertical speeds
sampleWindow = 15;
vertical_speed_fps = zeros(size(time));
for k=sampleWindow+1:length(time)
    deltaT_s = seconds(time(k) - time(k-sampleWindow));
    delta_h_ft = gps_altitude_ft(k) - gps_altitude_ft(k-sampleWindow);
    vertical_speed_fps(k) = delta_h_ft/deltaT_s;
end

%% Plots
%Plot time so we have an idea how many sets of data are in the log file
figure
plot([1:1:length(time)],time)
ylabel('time')
xlabel('Index')
title('Plot to identify how many data sets are in file')
grid on

figure
ax = [];
ax(end+1) = subplot(6,1,1);
hold on
plot(time,CelciustoFarenheit(temperatureA_c))
plot(time,CelciustoFarenheit(temperatureB_c))
legend('T_A','T_B')
ylabel('Temperature (F)')
grid on

ax(end+1) = subplot(6,1,2);
plot(time,gps_satellites_value2)
ylabel('GPS Satellites')
grid on

ax(end+1) = subplot(6,1,3);
plot(time,gps_speed_mph)
ylabel('GPS Speed (MPH)')
grid on

ax(end+1) = subplot(6,1,4);
plot(time,gps_altitude_ft)
ylabel('GPS Altitude (ft)')
grid on

ax(end+1) = subplot(6,1,5);
plot(time,vertical_speed_fps)
ylabel('Vertical Speed (ft/s)')
grid on

ax(end+1) = subplot(6,1,6);
plot(time,gps_hdop_fraction)
ylabel('GPS HDOP (fraction)')
grid on

linkaxes(ax,'x');

%Plot trajectory
figure
geoplot(gps_location_lat_deg,gps_location_lng_deg,'LineWidth',3)
geobasemap('streets')

%% Analyze data and draw objects
if(strcmp(inputFile,'SpaceShrimp.mat'))
    %Individual plots
    lineWidth       = 3;
    markerSize      = 25;
    
    launchIndex     = 158;
    burstIndex      = 3909;
    landingIndex    = 4654;
    
    launchTime      = time(launchIndex);
    burstTime       = time(burstIndex);
    landingTime     = time(landingIndex);
    
    timeAscent      = time(launchIndex:burstIndex);
    timeDescent     = time(burstIndex:landingIndex);
    
    ascentRate_fps  = 14;
    descentRate_fps = -29;
    
    %Find maximum/minium values
    max_gps_altitude_ft = gps_altitude_ft(burstIndex);
    
    min_temperatureA_c = min(temperatureA_c);
    min_temperatureA_c_idx = min(find(temperatureA_c==min_temperatureA_c));
    
    min_temperatureB_c = min(temperatureB_c);
    min_temperatureB_c_idx = min(find(temperatureB_c==min_temperatureB_c));
    
    max_gps_speed_mph = max(gps_speed_mph);
    max_gps_speed_mph_idx = min(find(gps_speed_mph==max_gps_speed_mph));
    
    figure
    hold on
    plot(time,gps_altitude_ft,'LineWidth',lineWidth)
    plot(time(launchIndex),gps_altitude_ft(launchIndex),'x','MarkerSize',markerSize,'LineWidth',lineWidth)
    plot(time(burstIndex),gps_altitude_ft(burstIndex),'x','MarkerSize',markerSize,'LineWidth',lineWidth)
    plot(time(landingIndex),gps_altitude_ft(landingIndex),'x','MarkerSize',markerSize,'LineWidth',lineWidth)
    plot(time(min_temperatureA_c_idx),gps_altitude_ft(min_temperatureA_c_idx),'^','MarkerSize',markerSize,'LineWidth',lineWidth)
    ylabel('Altitude (ft)')
    legend(...
        'Altitude',...
        'Launch',...
        ['Burst Altitude = ',num2str(gps_altitude_ft(burstIndex)),' ft'],...
        'Landing',...
        'Altitude at minimum TemperatureA',...
        'Location','Best')
    grid on
    
    figure
    hold on
    plot(time,CelciustoFarenheit(temperatureA_c),'LineWidth',lineWidth)
    plot(time,CelciustoFarenheit(temperatureB_c),'LineWidth',lineWidth)
    plot(time(min_temperatureA_c_idx),CelciustoFarenheit(min_temperatureA_c),'rx','MarkerSize',markerSize','LineWidth',lineWidth)
    plot(time(min_temperatureB_c_idx),CelciustoFarenheit(min_temperatureB_c),'rx','MarkerSize',markerSize','LineWidth',lineWidth)
    legend(...
        'T_A',...
        'T_B',...
        ['min T_A = ',num2str(CelciustoFarenheit(min_temperatureA_c)),' F'],...
        ['min T_B = ',num2str(CelciustoFarenheit(min_temperatureB_c)),' F'],...
        'Location','Best')
    ylabel('Temperature (F)')
    grid on
    
    figure
    plot(time,gps_satellites_value2,'LineWidth',lineWidth)
    ylabel('GPS Satellites')
    grid on
    
    figure
    hold on
    plot(time,gps_speed_mph,'LineWidth',lineWidth)
    plot(time(max_gps_speed_mph_idx),max_gps_speed_mph,'rx','MarkerSize',markerSize','LineWidth',lineWidth)
    ylabel('GPS Speed (MPH)')
    legend(...
        'Speed',...
        ['Max speed = ',num2str(max_gps_speed_mph),' MPH'],...
        'Location','Best')
    grid on
    
    figure
    hold on
    plot(time,vertical_speed_fps,'LineWidth',lineWidth)
    plot(timeAscent,ascentRate_fps*ones(size(timeAscent)),'LineWidth',lineWidth)
    plot(timeDescent,descentRate_fps*ones(size(timeDescent)),'LineWidth',lineWidth)
    legend('Vertical Speed (ft/s)',...
        ['Ascent Rate = ',num2str(ascentRate_fps),' (ft/s)'],...
        ['Descent Rate = ',num2str(descentRate_fps),' (ft/s)'],...
        'Location','Best')
    ylabel('Vertical Speed (ft/s)')
    grid on
    
    %Display stats
    ascentTime  = minutes(timeAscent(end) - timeAscent(1));
    descentTime = minutes(timeDescent(end) - timeDescent(1));
    missionTime = minutes(timeDescent(end) - timeAscent(1));
    
    display(['Burst Altitude = ',num2str(gps_altitude_ft(burstIndex)),' ft'])
    display(['Ascent Time   = ',num2str(ascentTime),' min'])
    display(['Descent Time  = ',num2str(descentTime),' min'])
    display(['Mission Time  = ',num2str(missionTime),' min'])
else
end

% MaximizeFigureAll();

%% Save data
saveVars = {
    'gps_date_year'
    'gps_date_month'
    'gps_date_day'
    'gps_time_hour'
    'gps_time_minute'
    'gps_time_second'
    'gps_satellites_value2'
    'temperatureA_c'
    'temperatureB_c'
    'gps_location_lat_deg'
    'gps_location_lng_deg'
    'gps_speed_mph'
    'gps_altitude_ft'
    'gps_hdop_fraction'
    'time'
    'vertical_speed_fps'
    };

[inputFileName,~]=SeperateFileNameAndExtension(inputFile);
outputFile = [inputFileName,'_Reduced.mat'];

s = SaveVarsString(outputFile,saveVars);
eval(s)
disp(['Saved to ',outputFile])

SaveAllFigures(inputFileName,'png')
disp('Saved all figures')

toc
disp('DONE!')