%spencer jackson

nharm = 200;
nsamp = 2048;
t=-pi:(2*pi)/2048:(1*pi-1/2048);
t=[1:nharm]'*t;
size(t)

den = repmat(1./[1:nharm]',1,nsamp);
size(den)
saw = sum(repmat([-1;1],nharm/2,nsamp).*sin(t).*den);
saw = -2*sum(sin(t).*den)/pi;
size(saw)
tmp=fft(saw);
plot(1:nsamp,tmp)
plot(1:nsamp,abs(tmp))
plot(1:nsamp,ifft(tmp));
%plot(saw)

tmp2 = tmp;
tmp2(floor(.05*nsamp):ceil(.95*nsamp)) = 0;
figure(2);
plot(1:nsamp,ifft(tmp2))
figure(1);
