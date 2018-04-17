%spencer jackson
% zpmapping.m - visualizes the effects of sampling by plotting poles/loci from varying parameters in an analog 2 pole resonant filter and mapping the locus to the z plane


%inputs
cutoff = 12000;
cutoff = 20:1:22000; %filter frequency hz (sweep)
damp = .001:.001:1; %damping factor
damp = .1
fs = 44100; %sampling rate hz

%magic
zeta = damp;
omega = 2*pi*cutoff;

% omega^2/(s^2 + 2*zeta*omega + omega^2)
R = -omega*zeta; %real part
I = omega*sqrt(1-zeta.^2); %imaginary

figure(1)
plot(R,I,R,-I);
title("S-Plane")
grid on

%map to z plane z=exp(sT)
g = exp(R/fs);
Rz = g.*cos(I/fs);
Iz = g.*sin(I/fs);
figure(2)
x = -1:.01:1;
y = sqrt(1-x.^2);
plot(x,y,'k',x,-y,'k',Rz,Iz,Rz,-Iz);
title("Z-Plane")
axis("square")
grid on


%next step:
% look at effect of approximations for that mapping
