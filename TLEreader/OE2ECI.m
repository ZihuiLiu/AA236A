%% OE2ECI
% adapted from last year's AA236 documents
% https://github.com/aa236b-winter-2019/payload-documentation/blob/9a9ab027a94dcec37076d68f5ceaea82b6715593/Matlab/SpaceMechFCNs/OE2ECI.m

function [r_eci, v_eci] = OE2ECI(a, e, i, RAAN, om, nu)    
    mu = 3.986*10^5;
    r_mag = a*(1-e^2)/(1+e*cos(nu));
    p = r_mag*(1 + e*cos(nu));
    vel_vec_perifocal = (sqrt(mu/p)).*[-sin(nu); (e+cos(nu)); 0];
    r_vec_perifocal = [r_mag*cos(nu); r_mag*sin(nu); 0];
    if e == 0 && i ~= 0
        R = rotz(RAAN)*rotx(i);
    elseif e > 0 && i == 0
        R = rotz(om);
    elseif e == 0 && i == 0
        R = [1 0 0;0 1 0;0 0 1];
    else
        R = rotz(RAAN)*rotx(i)*rotz(om);
    end
    r_eci = R*r_vec_perifocal;
    v_eci = R*vel_vec_perifocal;
end

function R = rotx(theta)
    R = [1  0            0;
         0  cos(-theta)  sin(-theta);
         0  -sin(-theta) cos(-theta)];
end

function R = rotz(theta)
    R = [cos(-theta) sin(-theta) 0; 
        -sin(-theta) cos(-theta) 0;
           0          0          1]; 
end