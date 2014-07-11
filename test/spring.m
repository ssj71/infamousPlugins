%Spencer Jackson
%a bunch of stuff for a spring reverb
1;

%Time version

%generate an all-pass fractional delay using the Thiran approximation This interpolates between samples to provide a non-integer delay.
%sys = thiran(tau, Ts)
%inputs:
%tau - time of delay
%Ts - sampling time
%
%Outputs:
%sys - transfer function of the filter
%
%Example:
% H = thiran(4.4,.5);
%		generates 9th order fractional delay filter delaying 4.4 seconds 
%
% H = thiran(8,.01);
%		generate pure delay of 8 seconds 
%See Also: thiran2
function sys = thiran(tau, Ts)
	D = tau/Ts;
	N = ceil(D);
	if(N==D)
		sys = tf([1],[1 zeros(1,N)],Ts);
	else
		
		a = (-1).^(1:N).*bincoeff(N,1:N).*prod((D-N+[0:N]'*ones(1,N))./(D-N+(1:N)+[0:N]'));
		sys = tf([a(N:-1:1) 1],[1 a],Ts);
	end
end

%the code below implements the thiran approximation:
%a = ones(1,N);
%for k=1:N
%	for i=0:N
%		a(k) = a(k)*(D-N+i)/(D-N+k+i);
%	end
%	a(k) = (-1)^k*bincoeff(N,k)*a(k);
%end
		
%sample delay version

%generate an all-pass fractional delay using the Thiran approximation. This interpolates between samples to provide a non-integer delay.
%sys = thiran(tau, Ts)
%inputs:
%D - delay in samples
%Ts - sampling time
%
%Outputs:
%sys - transfer function of the filter
%
%Example:
% H = thiran2(4.4, 8000);
%		generate 5th order fractional delay filter delaying 4.4 samples 
%
% H = thiran2(8, 100);
%		generate pure time delay of 8 samples (.08 seconds)
%See Also: thiran
function sys = thiran2(D, Ts)
	N = ceil(D);
	if (N==D)
		sys = tf([1],[1 zeros(1,N)],Ts);
	else
		a = (-1).^(1:N).*bincoeff(N,1:N).*prod((D-N+[0:N]'*ones(1,N))./(D-N+(1:N)+[0:N]'));
		sys = tf([a(N:-1:1) 1],[1 a],Ts);
	end
end

Fs = 44100/4;%48000; 44100
Ts = 1/Fs;
Nyquist = Fs/2;

 
%first lets work on the low frequency chirp section
%allpass
Fc =  2800;%4300;% 3700, 2800;
k = 3.56;%Fs/Fc;%stretch factor this affects Fc. %k=10=4.4khz ,11=4k, 12=3.6k,17=2.6k, 18=2.4k, 9=5k
Fc = Fs/k/4;
d = k-floor(k);%larger d makes more stable
ki = floor(k);
%for decimal part of k, d E(0,1) a2 = (1-d)/(d+1)
%then allpass (single stage) is 
%H = (a1 + a1a2z^-1 + a2z^-k + z^-k-1 )/ (1 + a2z^-1 + a1a2z^-k + a1z^-k-1)

al = -.2;%allpass filter coeff (negative due to changes), this stretches the delay curve
M = 34;% Number of allpass stages (50?) 23 stable limit for al = -.6
	%k=17;al=-.6;M=23;%2700hz spring
	%k=12;al=-.36;M=35;3600hz
	%k=10;al=-.3;M=40;4300hz
	%k=10;al=-.7;M=19;
	%k=10;al=-.5;M=30;
%Hap = (tf([al zeros(1,k-1) 1],[1 zeros(1,k-1) al],Ts))^M;%old way
a2 = 0;
if(d)
	a2 = (1-d)/(d+1);
end
Hap = (tf([al al*a2 zeros(1,ki-2) a2 1],[1 a2 zeros(1,ki-2) al*a2 al],Ts))^M;

a = [al al*a2 zeros(1,ki-2) a2 1];
b = [1 a2 zeros(1,ki-2) al*a2 al];

%break

	%so for 3 springs (k al M Fcfreq) 
	%1 17 -.6 23 2594hz
	%2 12 -.36 35 3675hz
	%3 10 -.3 40 4410hz
	%4 10 -.7 19 4410hz
	%5 10 -.5 30 4410hz
%new design decimate x4
%4300hz k=2.564; al=-.7; M=16; D=63ms
%4300hz k=2.564; al=-.5; M=24; D=88ms
%4300hz k=2.564; al=-.3; M=33; D=56ms
%3700hz k=2.9797;al=-3.6;M=42; D=56.2ms
%2800hz k=3.9375;al=-.6; M=22; D=56.15ms


%stretching factor (k) is inversely proportional to Fc
%Fc = Fs/k;%"cutoff" for a spring, where the maximum dispersion occurs
if(1)
	[y t] = impulse(Hap,.06);
	specgram(y,64,Fs,hanning(64),64-8)
	%specgram(y,256,Fs,hanning(256),256-32)
	break
	%pause;
end
break

if(0)
	k=2.56;al=-.7;M=16;%this way works for any rate
	%Fc = 4300;%4300;% 3700, 2800;
	%k = Fs/Fc;
	d = k-floor(k);%larger d makes more stable
	ki = floor(k);
	a2 = 0;
	if(d)
		a2 = (1-d)/(d+1);
	end
	Hap1 = (tf([al al*a2 zeros(1,ki-2) a2 1],[1 a2 zeros(1,ki-2) al*a2 al],Ts))^M;
	Hap1 = Hap1*tf(1,[1 zeros(1,ceil(.007*Fs))],Ts);	

	k=2.56;al=-.5;M=24;
	%Fc = 4300;%4300;% 3700, 2800;
	%k = Fs/Fc;
	d = k-floor(k);%larger d makes more stable
	ki = floor(k);
	a2 = 0;
	if(d)
		a2 = (1-d)/(d+1);
	end
	Hap2 = (tf([al al*a2 zeros(1,ki-2) a2 1],[1 a2 zeros(1,ki-2) al*a2 al],Ts))^M;
	Hap2 = Hap2*tf(1,[1 zeros(1,ceil(.032*Fs))],Ts);

	k=2.56;al=-.3;M=33;
	%Fc = 4300;%4300;% 3700, 2800;
	%k = Fs/Fc;
	d = k-floor(k);%larger d makes more stable
	ki = floor(k);
	a2 = 0;
	if(d)
		a2 = (1-d)/(d+1);
	end
	Hap3 = (tf([al al*a2 zeros(1,ki-2) a2 1],[1 a2 zeros(1,ki-2) al*a2 al],Ts))^M;
	
	k=2.9;al=-.36;M=40;
	%Fc = 3700;%4300;% 3700, 2800;
	%k = Fs/Fc;
	%M = 16;%48k
	d = k-floor(k);%larger d makes more stable
	ki = floor(k);
	a2 = 0;
	if(d)
		a2 = (1-d)/(d+1);
	end
	Hap4 = (tf([al al*a2 zeros(1,ki-2) a2 1],[1 a2 zeros(1,ki-2) al*a2 al],Ts))^M;
	Hap4 = Hap4*tf(1,[1 zeros(1,ceil(.0002*Fs))],Ts);

	k=3.9;al=-.6;M=22;
	%Fc = 2800;%4300;% 3700, 2800;
	%k = Fs/Fc;
	%M = 13;%48k
	%d = k-floor(k);%larger d makes more stable
	ki = floor(k);
	a2 = 0;
	if(d)
		a2 = (1-d)/(d+1);
	end
	Hap5 = (tf([al al*a2 zeros(1,ki-2) a2 1],[1 a2 zeros(1,ki-2) al*a2 al],Ts))^M;
	Hap5 = Hap5*tf(1,[1 zeros(1,ceil(.00015*Fs))],Ts);

	[y1 t] = impulse(Hap1,.1);
	[y2 t] = impulse(Hap2,.1);
	[y3 t] = impulse(Hap3,.1);
	[y4 t] = impulse(Hap4,.1);
	[y5 t] = impulse(Hap5,.1);
	yt = y1+y2+y3+y4+y5;

	specgram(yt,64,Fs,hanning(64),64-8)
	%specgram(yt,256,Fs,hanning(256),256-32)

	tmp = Hap1.num{1};
	save('Spring1Coeff.txt','tmp','-ascii');
	tmp = Hap2.num{1};
	save('Spring2Coeff.txt','tmp','-ascii');
	tmp = Hap3.num{1};
	save('Spring3Coeff.txt','tmp','-ascii');
	tmp = Hap4.num{1};
	save('Spring4Coeff.txt','tmp','-ascii');
	tmp = Hap5.num{1};
	save('Spring5Coeff.txt','tmp','-ascii');
	break;
end

%8th order linkwitz riley x-over, used for chirp straightening
[b a] = butter(4,Fc/2/Nyquist);
Hxl = tf(conv(b,b),conv(a,a),Ts);
[b a] = butter(4,Fc/2/Nyquist,'high');
Hxh = tf(conv(b,b),conv(a,a),Ts);

%anti-aliasing filter 
%[b a] = ellip(10,1.5,80,Fc/Nyquist);%this needs to cutoff at Fc for each spring 
[b a] = cheby1(10,1.5,Fc/Nyquist);
Haa = tf(b,a,Ts);
%freqz(b,a,Fs);
%break
%we won't model the downsampling for this exercize

if(0)
	[y t] = impulse(Haa,.06);
	%[y t] = lsim(Hxh,y,t);
	[y t] = lsim(Hap,y,t);
	specgram(y,256,Fs,hanning(256),256-32)
	break;
end

%chirp straightening
wxo = pi*(Fc/2)/Nyquist; %crossover frequency (in range [0,1]*pi)
Da = k*M*(1-al^2)/(1+2*al*cos(wxo*k)+al^2);%delay of allpass filter at Xover freq
Dad = Da - floor(Da);%decimal part of Da
astrt = (-Dad*cos(wxo) + sqrt(1-Dad^2+Dad^2*cos(wxo)^2))/(1+Dad); %fractional delay line coeff.
Hstrt = tf([astrt 1],[1 astrt zeros(1,floor(Da)-1)],Ts);%tf([astrt 1],[1 astrt zeros(1,k*M)],Ts);

if(0)
	[y t] = impulse(Haa,.06);
	[yh t] = lsim(Hxh,y,t);
	[yh t] = lsim(Hap,yh,t);
	[yl t] = lsim(Hxl,y,t);
	[yl t] = lsim(Hstrt,yl,t);
	y = yl+yh;
	specgram(y,256,Fs,hanning(256),256-32)
	break;
end

%feedback delay
Dlf = ceil(.056*Fs);%low frequency FB delay in samples (~56ms)
%spring 4,5 will be 74,91ms
glf = -.64;
Hd = tf([glf],[1 zeros(1,Dlf)],Ts);%pure delay

%putting it all together
if(0)
    Gap = Hxh*Hap + Hxl*Hstrt;
    G = Gap/(1+Hd*Gap);
    %bode(G)
    %pause;
    %[y t] = impulse(G,1,.6);
    %[y t] = impulse(1/(1+Hd),.5);
    %specgram(y,256,Fs,hanning(256),256-32)
    %break;
    [y t] = impulse(Haa,.5);
    [y1 t] = lsim(Gap,y,t);
    [y2 t] = lsim(1/(1+Hd*Gap),y1,t);
    specgram(y2,256,Fs,hanning(256),256-32)
    %[y t] = impulse(Gap,1,.5);
    %specgram(y,[],44100);
    %specgram(cf,512,44100,hanning(512),496)
end

%eq the LF chirp/anti-imaging filter
[b a] = ellip(1,1.5,50,[180/Nyquist*4 320/Nyquist*4]);
[b a] = ellip(1,1,50,[200/Nyquist*4 4000/Nyquist*4]);
%900 3400
Hai = tf(b,a,Fs/4);
b2 = [b(1) 0 0 0 b(2) 0 0 0 b(3)];
a2 = [a(1) 0 0 0 a(2) 0 0 0 a(3)];

%freqz(b2,a2,Fs/4);
%bode(Hai)
%y = impulse(Hai);
%specgram(y,64,Fs/4,hanning(64),48)

%I think the AI filter should be another cheby1

%the high frequency side 
%[b a] = ellip(5,3,6,[Nyquist/Fc Nyquist/upB]);a%
al = -.64;
k = 2;
M = 200;
Hap = (tf([al zeros(1,k-1) 1],[1 zeros(1,k-1) al],Ts))^M;%old way 
%[y t] = impulse(Hap,.05);
%specgram(y,256,Fs,hanning(256),256-32);


disp "Starting over"

%new design decimate x4
%5500hz k=2; al=-.7; M=19; D=56ms
%5500hz k=2; al=-.5; M=24; D=88ms
%5500hz k=2; al=-.3; M=21; D=63ms
%3700hz k=3; al=-3.6;M=42; D=63.2ms
%2800hz k=4; al=-.6; M=22; D=63.15ms
nspring = 5;
ks = [2 2 2 3 4];
als = [.7 .5 .3 3.6 .6];

%low side
k=3; al=-.36; M=42; D=.063;
z = roots([al zeros(1,k-1) 1]);
p = roots([1 zeros(1,k-1) al]);
b = poly(repmat(z',1,M));
a = poly(repmat(p',1,M));
Hap = zpk(repmat(z,M,1),repmat(p,M,1),1,Ts*4);
%Hap = (tf(b,a,Ts*4));%*tf([1],[1 zeros(1,D*Fs/4)],Ts*4);%delay
Hap2 = (tf([al zeros(1,k-1) 1],[1 zeros(1,k-1) al],Ts*4))^M;%old way 
[y t] = impulse(Hap,.06);
specgram(y,64,Fs/4,hanning(64),64-8)


k=2; al=-.7; M=19; D=.056;
z = roots([al zeros(1,k-1) 1]);
p = roots([1 zeros(1,k-1) al]);
b = poly(repmat(z',1,M));
a = poly(repmat(p',1,M));
%Hap2 = (tf(b,a,Ts*4))*tf([1],[1 zeros(1,D*Fs/4)],Ts*4);

figure(2)
[y2 t] = impulse(Hap2,.10);
specgram(y2,64,Fs/4,hanning(64),64-8)
figure(1)
%Hap.den{1} - Hap2.den{1}
%max(Hap.den{1} - Hap2.den{1})

%high side

