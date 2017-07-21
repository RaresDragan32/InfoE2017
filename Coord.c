%function [d1km d2km]=lldistkm(latlon1,latlon2)
% format: [d1km d2km]=lldistkm(latlon1,latlon2)
% Distance:
% d1km: distance in km based on Haversine formula
% (Haversine: http://en.wikipedia.org/wiki/Haversine_formula)
% d2km: distance in km based on Pythagoras theorem
% (see: http://en.wikipedia.org/wiki/Pythagorean_theorem)
% After:
% http://www.movable-type.co.uk/scripts/latlong.html
%
% --Inputs:
%   latlon1: latlon of origin point [lat lon]
%   latlon2: latlon of destination point [lat lon]
%
% --Outputs:
%   d1km: distance calculated by Haversine formula
%   d2km: distance calculated based on Pythagoran theorem
%
% --Example 1, short distance:
%   latlon1=[-43 172];
%   latlon2=[-44  171];
%   [d1km d2km]=distance(latlon1,latlon2)
%   d1km =
%           137.365669065197 (km)
%   d2km =
%           137.368179013869 (km)
%   %d1km approximately equal to d2km
%
% --Example 2, longer distance:
%   latlon1=[-43 172];
%   latlon2=[20  -108];
%   [d1km d2km]=distance(latlon1,latlon2)
%   d1km =
%           10734.8931427602 (km)
%   d2km =
%           31303.4535270825 (km)
%   d1km is significantly different from d2km (d2km is not able to work
%   for longer distances).
%
% First version: 15 Jan 2012
% Updated: 17 June 2012
%--------------------------------------------------------------------------
 
 
format long
 
latlon1=[-43 172];
latlon2=[-44  171];
 
latlon1=[46.437963, 21.830177];
%latlon1=[44.391136, 26.042021];
%latlon1=[44.391848, 26.041169];
latlon2=[46.437172, 21.835853];
 
radius=6371;
lat1=latlon1(1)*pi/180;
lat2=latlon2(1)*pi/180;
lon1=latlon1(2)*pi/180;
lon2=latlon2(2)*pi/180;
 
deltaLat=lat2-lat1;
deltaLon=lon2-lon1;
 
a=sin((deltaLat)/2)^2 + cos(lat1)*cos(lat2) * sin(deltaLon/2)^2;
c=2*atan2(sqrt(a),sqrt(1-a));
d1km=radius*c;    %Haversine distance
 
disp(d1km);
x=deltaLon*cos((lat1+lat2)/2);
y=deltaLat;
d2km=radius*sqrt(x*x + y*y); %Pythagoran distance
disp(d2km);
 
az = azimuth(lat1,lon1,lat2,lon2)
%az1 = atan2(cos(lat2) .* sin(lon2-lon1),...
%           cos(lat1) .* sin(lat2) - sin(lat1) .* cos(lat2) .* cos(lon2-lon1));
 %    radtodeg(az1)
       
 
%azimut2       
b = acos ( cos (pi/2 - lat2) * cos (pi/2 - lat1) + sin (pi/2 - lat2) * sin (pi/2 - lat1) * cos (lon2 - lon1) );
A = asin ( sin (pi/2 - lat2) * sin (lon2 - lon1) / sin (b) );
%A=A*-1;
if lat1<lat2
    if A<0
        A=-pi-A;
    else
        A=pi-A;
    end
    
az_deg=radtodeg(A)
end
az2=radtodeg(A)
%dreapta+ stanga-
A=A+degtorad(-90);%unghiul de virare
A=A*-1;
az21=radtodeg(A)
 
%prob 3
latlon3=[46.440352, 21.836668];
%% 
lat3=latlon3(1)*pi/180;
lon3=latlon3(2)*pi/180;
 
distance=0.1
b1 = distance / radius;
a1 = acos(cos(b1)*cos(pi/2 - lat3) + sin(pi/2 - lat3)*sin(b1)*cos(A));
B = asin(sin(b1)*sin(A)/sin(a1));
 
f_lat2 = radtodeg(pi/2 - a1)
f_lon2 = radtodeg(B + lon3)
 
f_latlon3(1)=f_lat2;
f_latlon3(2)=f_lon2;
disp(f_latlon3);
%end
