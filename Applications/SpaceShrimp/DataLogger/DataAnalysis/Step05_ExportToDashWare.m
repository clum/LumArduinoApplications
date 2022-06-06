%Write data to file that can be used in DashWare to drive video overlays.
%
%Christopher Lum
%lum@uw.edu

%Version History
%06/03/22: Created
%06/04/22: Cleaned up

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
gps_date_year           = temp.gps_date_year;
gps_date_month          = temp.gps_date_month;
gps_date_day            = temp.gps_date_day;
gps_time_hour           = temp.gps_time_hour;
gps_time_minute         = temp.gps_time_minute;
gps_time_second         = temp.gps_time_second;
gps_satellites_value2   = temp.gps_satellites_value2;
temperatureA_c          = temp.temperatureA_c;
temperatureB_c          = temp.temperatureB_c;
gps_location_lat_deg    = temp.gps_location_lat_deg;
gps_location_lng_deg    = temp.gps_location_lng_deg;
gps_speed_mph           = temp.gps_speed_mph;
gps_altitude_ft         = temp.gps_altitude_ft;
gps_hdop_fraction       = temp.gps_hdop_fraction;

time                    = temp.time;
vertical_speed_fps      = temp.vertical_speed_fps;

%% Plot data to check
plot3(gps_location_lng_deg,gps_location_lat_deg,gps_altitude_ft)
xlabel('lon (deg)')
ylabel('lat (deg)')
zlabel('alt (ft)')
grid on

figure
subplot(2,1,1)
plot(time,gps_speed_mph)
legend(StringWithUnderscoresForPlot('gps_speed_mph'))
grid on

subplot(2,1,2)
plot(time,temperatureA_c,time,temperatureB_c)
legend(StringWithUnderscoresForPlot('temperatureA_c'),StringWithUnderscoresForPlot('temperatureB_c'))
grid on

%% convert units
gps_altitude_m      = FttoM(gps_altitude_ft);
gps_speed_mps       = MPHtoMetersPerSec(gps_speed_mph);
vertical_speed_mps  = FeetPerSectoMetersPerSec(vertical_speed_fps);

%% Write to csv
headerLine1 = 'DashWare Lum CSV File';
headerLine2 = 'Time,Longitude [deg],Latitude [deg],Altitude [m],Speed [m/s],TemperatureA [C],TemperatureB [C],NumSatellites,VerticalSpeed [m/s]';

data = {};
data{1,1} = headerLine1;
data{2,1} = headerLine2;

tStart = time(1);
for k=1:length(time)
    %Format the date and time.  This should be written to CSV in UTC
    date_str = [...
        num2str(gps_date_year(k)),'/',...
        num2str(gps_date_month(k),'%02d'),'/',...
        num2str(gps_date_day(k),'%02d'),' ',...
        num2str(gps_time_hour(k),'%02d'),':',...
        num2str(gps_time_minute(k),'%02d'),':',...
        num2str(gps_time_second(k),'%02d')];
    
    %current line
    str_k = [...
        date_str,','...        
        num2str(gps_location_lng_deg(k),'%.6f'),',',...
        num2str(gps_location_lat_deg(k),'%.6f'),',',...
        num2str(gps_altitude_m(k)),',',...
        num2str(gps_speed_mps(k)),',',...
        num2str(temperatureA_c(k)),','...
        num2str(temperatureB_c(k)),','...
        num2str(gps_satellites_value2(k)),',',...
        num2str(vertical_speed_mps(k),'%.2f'),...
        ];
    
    data{end+1,1} = str_k;
        
end

%% Write to a csv
[inputFileName,~]=SeperateFileNameAndExtension(inputFile);
outputFile = [inputFileName,'_DashWare.csv'];

fid = fopen(outputFile,'w');
for k=1:length(data)
    fprintf(fid,data{k});
    fprintf(fid,'\n' );
end
fclose(fid);

disp(['Wrote to ',outputFile])

toc
disp('DONE!')