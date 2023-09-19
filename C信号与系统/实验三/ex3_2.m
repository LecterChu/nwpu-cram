
% ex3_2_1_1()

% ex3_2_1_1()
% 
% function ex3_2_1_1()
%     Ts=0.5;ts=-20:Ts:20;
%     fs=((1+cos(ts))/2).*(heaviside(ts+pi)-heaviside(ts-pi));;
%     figure;
%     subplot(2,1,1),stem(ts,fs);
%     title('fs(t)（取样时间0.5s）幅度谱'),grid on;
%     xlabel('t');
%     axis([-5,5,-0.5,1.5]);
%     omega1=-8*pi;omega2=8*pi;K=4000;
%     OMEGA=omega2-omega1;
%     delta_omega=OMEGA/K;
%     omega=omega1:delta_omega:omega2;
%     Fs=Ts*(fs*exp(-1i*ts'*omega));
%     subplot(2,1,2)
%     plot(omega,abs(Fs * 2));
%     title('fs(t)（取样时间0.5s）幅度谱'),grid on;
%     xlabel('w');
%     xlim([-25,25]);
%     Wc=2.4;
%     t1=-6;t2=6;N=40;T=t2-t1;delta_t=T/N;
%     t=t1:delta_t:t2;
%     fh=(Ts*Wc/pi)*fs*sinc((Wc./pi)*(ones(length(ts),1)*t-ts'*ones(1,length(t))));
%     f=((1+cos(t))/2).*(heaviside(t+pi)-heaviside(t-pi));
%     figure;
%     subplot(2,1,1)
%     plot(t,f,'*');legend('原始信号')
%     hold on
%     plot(t,fh,'r'),grid on; title('同时输出重建与原始信号')
%     subplot(2,1,2)
%     plot(t,f-fh);axis([-6,6,-0.02,0.02]);
% end
% 
% function ex3_2_1_2()
%    Ts=1;ts=-20:Ts:20;
%     fs=((1+cos(ts))/2).*(heaviside(ts+pi)-heaviside(ts-pi));;
%     figure;
%     subplot(2,1,1),stem(ts,fs);
%     title('fs(t)（取样时间1s）幅度谱'),grid on;
%     xlabel('t');
%     axis([-5,5,-0.5,1.5]);
%     omega1=-8*pi;omega2=8*pi;K=4000;
%     OMEGA=omega2-omega1;
%     delta_omega=OMEGA/K;
%     omega=omega1:delta_omega:omega2;
%     Fs=Ts*(fs*exp(-1i*ts'*omega));
%     subplot(2,1,2)
%     plot(omega,abs(Fs));
%     title('fs(t)（取样时间1s）幅度谱'),grid on;
%     xlabel('w');
%     xlim([-10,10]);
%     Wc=2.4;
%     t1=-6;t2=6;N=40;T=t2-t1;delta_t=T/N;
%     t=t1:delta_t:t2;
%     fh=(Ts*Wc/pi)*fs*sinc((Wc./pi)*(ones(length(ts),1)*t-ts'*ones(1,length(t))));
%     f=((1+cos(t))/2).*(heaviside(t+pi)-heaviside(t-pi));
%     figure;
%     subplot(2,1,1)
%     plot(t,f,'*');legend('原始信号')
%     hold on
%     plot(t,fh,'r'),grid on; title('同时输出重建与原始信号')
%     subplot(2,1,2)
%     plot(t,f-fh);axis([-6,6,-0.02,0.02]);
% end
% 
% function ex3_2_1_3()
%     Ts=2;ts=-20:Ts:20;
%     fs=((1+cos(ts))/2).*(heaviside(ts+pi)-heaviside(ts-pi));;
%     figure;
%     subplot(2,1,1),stem(ts,fs);
%     title('fs(t)（取样时间2s）幅度谱'),grid on;
%     xlabel('t');
%     axis([-5,5,-0.5,1.5]);
%     omega1=-8*pi;omega2=8*pi;K=4000;
%     OMEGA=omega2-omega1;
%     delta_omega=OMEGA/K;
%     omega=omega1:delta_omega:omega2;
%     Fs=Ts*(fs*exp(-1i*ts'*omega));
%     subplot(2,1,2)
%     plot(omega,abs(Fs / 2));
%     title('fs(t)（取样时间2s）幅度谱'),grid on;
%     xlabel('w');
%     xlim([-5,5]);
%     Wc=2.4;
%     t1=-6;t2=6;N=40;T=t2-t1;delta_t=T/N;
%     t=t1:delta_t:t2;
%     fh=(Ts*Wc/pi)*fs*sinc((Wc./pi)*(ones(length(ts),1)*t-ts'*ones(1,length(t))));
%     f=((1+cos(t))/2).*(heaviside(t+pi)-heaviside(t-pi));
%     figure;
%     subplot(2,1,1)
%     plot(t,f,'*');legend('原始信号')
%     hold on
%     plot(t,fh,'r'),grid on; title('同时输出重建与原始信号')
%     subplot(2,1,2)
%     plot(t,f-fh);axis([-6,6,-0.5,0.5]);
% end
% 
% function ex3_2_2()
%     clc
%     clear
%     close all
%     Dt = 0.00005;
%     t = -6:Dt:6;
%     xa = ((1+cos(t))/2).*(heaviside(t+pi)-heaviside(t-pi)); 
%     subplot(2,1,1);
%     plot(t,xa);
%     title('原始信号f(t)');
%     xlabel('t');
%     Ts = 1;
%     Fs = 1/Ts;
%     t = -6:1:6;
%     x = ((1+cos(t))/2).*(heaviside(t+pi)-heaviside(t-pi));
%     subplot(2,1,2);
%     plot(t,x);
%     title('重建信号时域图和离散时域图');
%     xlabel('t');
%     hold on 
%     stem(t,x);
% end

% ex3_1_4()
ex3_2_2()
% ex3_2_1_3()
% ex3_2_1_4()

function ex3_2_1_1()
    T1 = 0.5; % 抽样间隔
    t1 = -pi:T1:pi;
    t = -pi:0.01:pi;
    Wc = 2.4;
    f = 0.5 * (1 + cos(t1));
    F1 = T1 * (Wc / pi) * f * sinc(Wc / pi * (ones(length(t1), 1) * t - t1' * ones(1, length(t))));
    figure;
    stem(t1, f);
    hold on
    plot(t, F1);
    hold off
    xlabel('t');
    ylabel('f(t)');
    ylim([0, 1.05])
    title('f(t) = 0.5*(1+cos(t)) 在抽样间隔为0.5s时的ILPF时域波形');
    legend('时域波形','ILPF时域波形');
    grid on;
end

function ex3_2_1_2()
    T2 = 1.0; % 抽样间隔
    t2 = -pi:T2:pi;
    t = -pi:0.01:pi;
    Wc = 2.4;
    f = 0.5 * (1 + cos(t2));
    F2 = T2*(Wc/pi) * f * sinc(Wc/pi*(ones(length(t2),1) * t - t2'*ones(1,length(t))));
    figure;
    stem(t2, f);
    hold on
    plot(t, F2);
    hold off
    xlabel('t');
    ylabel('f(t)');
    ylim([0, 1.05])
    title('f(t) = 0.5 * (1+cos(t)) 在抽样间隔为1s时的ILPF时域波形');
    legend('时域波形','ILPF时域波形');
    grid on;
end

function ex3_2_1_3()
    T3 = 2.0; % 抽样间隔
    t3 = -pi:T3:pi;
    t = -pi:0.01:pi;
    Wc = 2.4;
    f = 0.5 * (1 + cos(t3));
    F3 = T3*(Wc/pi) * f * sinc(Wc/pi*(ones(length(t3),1) * t - t3'*ones(1,length(t))));
    figure;
    stem(t3, f);
    hold on
    plot(t, F3);
    hold off
    xlabel('t');
    ylabel('f(t)');
    title('f(t) = 0.5 * (1+cos(t)) 在抽样间隔为2s时的ILPF时域波形');
    legend('时域波形','ILPF时域波形');
    grid on;
end

function ex3_2_1_4()
    % 0.5s 1s 2s 三种抽样间隔
    T1 = 0.5;
    T2 = 1.0;
    T3 = 2.0;
    
    % 采样范围
    t1 = -pi:T1:pi;
    t2 = -pi:T2:pi;
    t3 = -pi:T3:pi;
    t = -pi:0.01:pi;
    Wc = 2.4;
    
    %原信号
    f = 0.5*(1+cos(t));
    
    %抽样间隔为 0.5s
    f1 = 0.5 * (1+cos(t1));
    F1 = T1 * (Wc/pi) * f1 * sinc(Wc/pi*(ones(length(t1),1) * t - t1' * ones(1,length(t))));%恢复信号
    subplot(3,1,1);
    plot(t,abs(F1-f));
    title('抽样间隔为 0.5s 的绝对误差图');
    xlabel('t');
    xlim([-3.5, 3.5]);
    ylabel('f(t)');
    ylim([0, 0.015]);
    grid on;
    
    %抽样间隔为 1s
    f2 = 0.5 * (1+cos(t2));
    F2 = T2 * (Wc/pi) * f2 * sinc(Wc/pi*(ones(length(t2),1) * t - t2' * ones(1,length(t))));%恢复信号
    subplot(3,1,2);
    plot(t,abs(F2-f));
    title('抽样间隔为 1s 的绝对误差图');
    xlabel('t');
    xlim([-3.5, 3.5]);
    ylabel('f(t)');
    ylim([0, 0.015]);
    grid on;
    
    %抽样间隔为 2s
    f3 = 0.5 * (1+cos(t3));
    F3 = T3 * (Wc/pi) * f3 * sinc(Wc/pi*(ones(length(t3),1) * t - t3' * ones(1,length(t))));%恢复信号
    subplot(3,1,3);
    plot(t,abs(F3-f));
    title('抽样间隔为 2s 的绝对误差图');
    xlabel('t');
    xlim([-3.5, 3.5]);
    ylabel('f(t)');
    ylim([0, 0.35]);
    grid on;
end

function ex3_2_2()
    %抽样间隔为1s
    T = 1;
    n = -pi:pi;
    t = n*T;
    f = 0.5 * (1 + cos(t));
    plot(t,f);
    title('抽样间隔为 1s 的抽样信号经过 DAC 一阶保持器后的恢复信号时域波形');
    xlabel('t');
    xlim([-3.5, 3.5])
    ylabel('f(t)');
    hold on
    stem(t,f)
    hold off
    grid on;
    legend('抽样信号','恢复信号')
end

function ex3_1_1()
    
    T1=0.5;%抽样间隔
    T2=1;%抽样间隔
    T3=2;%抽样间隔
    
    t1=-pi:T1:pi;%设置题目要求的时间范围
    t=-pi:0.01:pi;
    W=2.4;
    f1=0.5*(1+cos(t1));%表达式
    F1=T1*(W/pi)*f1*sinc(W/pi*(ones(length(t1),1)*t-t1'*ones(1,length(t))));
    subplot(3,1,1);
    stem(t1,f1);
    title('抽样间隔为 0.5s 的时域波形:f(t)=0.5(1+cost)');
    xlabel('t');
    ylabel('f(t)');
    hold on
    subplot(3,1,1);
    plot(t,F1);
    title('抽样间隔为 0.5s 的 ILPF 信号时域波形:f(t)=0.5(1+cost)');
    xlabel('t');
    ylabel('f(t)');
    hold off
    legend('时域波形','ILPF 信号时域波形')
    t2=-pi:T2:pi;%设置题目要求的时间范围
    t=-pi:0.01:pi;
    W=2.4;
    f2=0.5*(1+cos(t2));%表达式
    F2=T2*(W/pi)*f2*sinc(W/pi*(ones(length(t2),1)*t-t2'*ones(1,length(t))));
    subplot(3,1,2);
    stem(t2,f2);
    title('抽样间隔为 1s 的时域波形:f(t)=0.5(1+cost)');
    xlabel('t');
    ylabel('f(t)');
    hold on
    subplot(3,1,2);
    plot(t,F2);
    title('抽样间隔为 1s 的 ILPF 信号时域波形:f(t)=0.5(1+cost)');
    xlabel('t');
    ylabel('f(t)');
    hold off
    legend('时域波形','ILPF 信号时域波形')
    t3=-pi:T3:pi;%设置题目要求的时间范围
    t=-pi:0.01:pi;
    W=2.4;
    f3=0.5*(1+cos(t3));%表达式
    F3=T3*(W/pi)*f3*sinc(W/pi*(ones(length(t3),1)*t-t3'*ones(1,length(t))));
    subplot(3,1,3);
    stem(t3,f3);
    title('抽样间隔为 2s 的时域波形:f(t)=0.5(1+cost)');
    xlabel('t');
    ylabel('f(t)');
    hold on
    subplot(3,1,3);
    plot(t,F3);
    title('抽样间隔为 2s 的 ILPF 信号时域波形:f(t)=0.5(1+cost)');
    xlabel('t');
    ylabel('f(t)');
    hold off
    legend('时域波形','ILPF 信号时域波形')
end
