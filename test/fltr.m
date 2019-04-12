%spencer Jackson

%filter
pkg load control;

w = 880*2*pi; %cutoff
d = 1.707; %damping factor

H = tf([w^2],[1 2*d*w w^2]);

bode(H);


%discretize
%TODO: this isn't the right way
Hz = tf(H,1/44100,'tsam');
figure()
bode(Hz);
