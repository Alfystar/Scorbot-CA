clc 
clear all
t=3; %ms Tempo campionamento

%% Load Data
[file,path] = uigetfile('.dat');
sample=dlmread(file,'\t',1,0); %non leggo i titoli
sample


%% Data plot
times=zeros(size(sample,1),1);
for i=0:size(sample,1)-1
    times(i+1)=i*t/1000;
end
figure(1)
clf(1)
grid on
hold on
for i=1:size(sample,2)
    str_e = sprintf('Mot%d',i);
    plot(times,sample(:,i),'DisplayName',str_e)
    hold on
end
grid on
legend();
axis([0 inf -inf inf]);
str_e = sprintf('Unit: 1s; Sampling time %d ms', t);
xlabel(str_e) 
