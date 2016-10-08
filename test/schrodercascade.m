%spencer jackson
% this is quicker (and probably more efficient) than making a bunch of code to do it

g1 = .5; % gain of 1st schroeder filter
N1 = 225; % delay of the 1st schroeder filter

g2 = .5; % gain of next schroeder filter
N2 = 556; % delay of the next schroeder filter

g3 = .5; % gain of next schroeder filter
N3 = 441; % delay of the next schroeder filter

g4 = .5; % gain of next schroeder filter
N4 = 341; % delay of the next schroeder filter


pkg load control
AP1 = tf([-g1 zeros(1,N1-1) 1], [1 zeros(1,N1-1) -g1],1,'variable','z^-1')
AP2 = tf([-g2 zeros(1,N2-1) 1], [1 zeros(1,N2-1) -g2],1,'variable','z^-1')
AP3 = tf([-g3 zeros(1,N3-1) 1], [1 zeros(1,N3-1) -g3],1,'variable','z^-1')
AP4 = tf([-g4 zeros(1,N4-1) 1], [1 zeros(1,N4-1) -g4],1,'variable','z^-1')

AP1*AP2*AP3*AP4


