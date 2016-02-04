function plotIREQ(file)

[y fs b] = wavread(file);
l = length(y);

%eq curve
figure(1)
plot(1/l:fs/l:fs/2,20*log10(abs(fft(y(:,1)))(1:ceil(l/2))))
title('Frequency response')
xlabel('Hz')
ylabel('dB')

%spectrogram
figure(2)
specgram(y(:,1),256,fs,hanning(256),256-32)
title('Spectrogram')


%waterfall plot
%figure(3)
nfft = 128;
[S, f, t] = specgram (y(:,1), nfft, fs);
ff = f' * ones (1, length (t));
tt = ones (length (f), 1) * t;
%TODO: color not ideal, log y axis, limit to 200hz, better LF resolution
waterfall (tt', ff', 20*log10 (abs (S')),.5*ones(size(S')))


figure(1)


