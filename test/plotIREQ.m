function plotIREQ(file)

[y fs b] = wavread(file);
l = length(y);
figure(1)
plot(1/l:fs/l:fs/2,20*log10(abs(fft(y(:,1)))(1:ceil(l/2))))
figure(2)
specgram(y(:,1),256,fs,hanning(256),256-32)
figure(1)


