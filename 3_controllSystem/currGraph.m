clc 
clear all
t=2; %ms Tempo campionamento

%% Load Data
[file,path] = uigetfile('.dat');
Curr=dlmread(file,'\t',1,0); %non leggo i titoli
Curr


%% Data plot
times=zeros(size(Curr,1),1);
for i=0:size(Curr,1)-1
    times(i+1)=i*t;
end
figure(1)
clf(1)
grid on
hold on
for i=1:size(Curr,2)
    str_e = sprintf('Mot%d A',i);
    plot(times,Curr(:,i),'DisplayName',str_e)
    hold on
end
grid on
legend();
axis([0 inf 0 inf]);
str_e = sprintf('Sampling time %d ms', t);
xlabel(str_e) 
