function plotIREQ(file)

[y fs b] = wavread(file);
l = length(y);

%eq curve
figure(1)
%TODO: add smoothed line
semilogx(1/l:fs/l:fs/2,20*log10(abs(fft(y(:,1)))(1:ceil(l/2))))
xlim([20 20000])
title('Frequency response')
xlabel('Hz')
ylabel('dB')
grid('on')

%spectrogram
figure(2)
clf
specgram(y(:,1),256,fs,hanning(256),256-32)
title('Spectrogram')


%waterfall plot
%this plot is tuned for looking at room responses for resonances
%figure(3)
windowlen = 500;%ms
rise = 100;%ms
slices = 51;

nfft = 2^ceil(log2(windowlen/1000*fs));
lhs = rise/1000*fs;%samples of hanning rise time
win = [hanning(2*lhs)(1:lhs); tukeywin(nfft,.25)(lhs+1:end)];%window has hanning rise and rest is .25 tukey
step = 2^floor(log2(length(y)/slices));%time size of each slice of spectra
overlap = nfft - step;
[S, f, t] = specgram (y(:,1), nfft, fs, win,  overlap);%nfft - nfft/8);
ff = f' * ones (1, length (t));
tt = ones (length (f), 1) * t;
Sdb = 20*log10(abs(S'));
%TODO: may want to smooth it a bit 
srf = waterfall (tt', ff'+.1, Sdb);%a minor offset is added to avoid 0 values on the log scale
ax = get(srf,'parent');
set(ax,'yscale','log');
view([100,15,15])
grid('on')
shading('faceted')
ylim([10 200])
zmx = max(Sdb);
zlim([-50 zmx+10])
xlabel('sec')
ylabel('Hz')
zlabel('dB')
colormap('jet')


figure(1)


