%% AA236A
% HW2
% Zihui Liu

%% Read File
clear all;
filename = fopen('TLE.txt');
datacell = textscan(filename, '%s', 21);
fclose(filename);
datacell = datacell{1};

%% Calculate Orbital Elements
i = str2double(datacell{16})*pi/180;
RAAN = str2double(datacell{17})*pi/180;
e = str2double(datacell{18})*10^-7;
om = str2double(datacell{19})*pi/180; 
M = str2double(datacell{20})*pi/180;
n = str2double(datacell{21})*2*pi/24/3600;
mu = 3.986*10^5;
a = (mu/(n^2))^(1/3);
E = computeE(M*pi/180, e);
nu = 2*atan(sqrt((1+e)/(1-e))*tan(E/2));
[r_eci, v_eci] = OE2ECI(a, e, i, RAAN, om, nu);

%% Functions
function E = computeE(M, e)
    dE = 1;
    E = pi;
    err = 10^-10;
    while abs(dE) > err
        dE = -(E-e*sin(E)-M)/(1-e*cos(E));
        E = E + dE;
    end
end