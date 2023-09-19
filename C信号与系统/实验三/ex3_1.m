
ex3_1_2_3()

function ex3_1_1()
    t = -pi:0.01:pi;
    f = ((1+cos(t))/2) .* (stepfun(t,-pi)-stepfun(t,pi));
    figure;
    subplot(2,1,1),plot(t,f);
    title('f(t)时域波形');
    grid on;
    xlabel('t');
    xlim([-pi, pi]);
    ylabel('f(t)');
    ylim([0, 1.1]);
    
    omega1=-pi;omega2=pi;K=4000;
    OMEGA=omega2-omega1;
    delta_omega=OMEGA/K;
    omega=omega1:delta_omega:omega2;
    F=0.01*(f*exp(-1i*t'*omega));
    
    subplot(2,1,2);
    plot(omega,abs(F));
    title('f(t)=0.5 * (1+cos(t))幅度谱');
    grid on;
    xlabel('w');
    xlim([-pi,pi]);
    ylabel('F(jw)')
    ylim([0, 3.5]);
end

function ex3_1_2_1()
    % 采样间隔
    Ts=0.5;
    ts=-20:Ts:20;
    fs=((1+cos(ts))/2).*(heaviside(ts+pi)-heaviside(ts-pi));
    figure;
    subplot(2,1,1);
    stem(ts,fs);
    title('f(t)=0.5 * (1+cos(t)) 采样间隔为0.5s时的时域波形');
    grid on;
    xlabel('t');
    xlim([-4, 4]);
    ylabel('f(t)');
    ylim([0, 1.1]);
    
    omega1=-8*pi;omega2=8*pi;K=4000;
    OMEGA=omega2-omega1;
    delta_omega=OMEGA/K;
    omega=omega1:delta_omega:omega2;
    Fs=Ts*(fs*exp(-1i*ts'*omega));
    subplot(2,1,2)
    plot(omega,abs(2 * Fs));
    title('f(t)=0.5 * (1+cos(t))/2 采样间隔为0.5时的幅度谱');
    grid on;
    xlabel('w');
    xlim([-15,15]);
    ylabel('F(jw)');
    ylim([0, 7])
end

function ex3_1_2_2()
    Ts=1;
    ts=-20:Ts:20;
    fs=((1+cos(ts))/2).*(heaviside(ts+pi)-heaviside(ts-pi));
    figure;
    subplot(2,1,1);
    stem(ts,fs);
    title('f(t)=(1+cos(t))/2 采取样间隔为1s时的时域波形');
    grid on;
    xlabel('t');
    xlim([-4, 4]);
    ylabel('f(t)');
    ylim([0, 1.1]);
    
    omega1=-8*pi;omega2=8*pi;K=4000;
    OMEGA=omega2-omega1;
    delta_omega=OMEGA/K;
    omega=omega1:delta_omega:omega2;
    Fs=Ts*(fs*exp(-1i*ts'*omega));
    subplot(2,1,2)
    plot(omega,abs(Fs));
    title('f(t)=(1+cos(t))/2 采样间隔为1s时的幅度谱');
    grid on;
    xlabel('w');
    xlim([-15,15]);
    ylabel('F(jw)');
    ylim([0, 3.5])
end

function ex3_1_2_3()
    Ts=2;
    ts=-20:Ts:20;
    fs=((1+cos(ts))/2).*(heaviside(ts+pi)-heaviside(ts-pi));
    figure;
    subplot(2,1,1);
    stem(ts,fs);
    title('f(t)=(1+cos(t))/2 采样间隔为2s时的时域波形');
    grid on;
    xlabel('t');
    xlim([-10, 10]);
    ylabel('f(t)');
    ylim([0, 1.1]);
    
    omega1=-10*pi;omega2=10*pi;K=4000;
    OMEGA=omega2-omega1;
    delta_omega=OMEGA/K;
    omega=omega1:delta_omega:omega2;
    Fs=Ts*(fs*exp(-1i*ts'*omega));
    subplot(2,1,2)
    plot(omega,abs(Fs / 2));
    title('f(t)=(1+cos(t))/2 采样间隔为2s时的幅度谱');
    grid on;
    xlabel('w');
    xlim([-5,5]);
    ylabel('F(jw)');
    ylim([0, 1.8]);
end

function ex3_1_3_1()
    % 采样间隔
    Ts=0.5;
    ts=-20:Ts:20;
    fs=((1+cos(ts))/2).*(heaviside(ts+pi)-heaviside(ts-pi));;
    figure;
    omega1=-8*pi;omega2=8*pi;K=4000;
    OMEGA=omega2-omega1;
    delta_omega=OMEGA/K;
    omega=omega1:delta_omega:omega2;
    Fs=Ts*(fs*exp(-1i*ts'*omega));
    subplot(3,1,1)
    plot(omega,abs(2 * Fs));
    title('f(t)=(1+cos(t))/2 采样间隔为0.5时的幅度谱'),grid on;
    xlabel('w');
    xlim([-15,15]);
    
    
    Ts=1;ts=-20:Ts:20;
    fs=((1+cos(ts))/2).*(heaviside(ts+pi)-heaviside(ts-pi));;
    omega1=-8*pi;omega2=8*pi;K=4000;
    OMEGA=omega2-omega1;
    delta_omega=OMEGA/K;
    omega=omega1:delta_omega:omega2;
    Fs=Ts*(fs*exp(-1i*ts'*omega));
    subplot(3,1,2)
    plot(omega,abs(Fs));
    title('f(t)=(1+cos(t))/2 采样间隔为1s时的幅度谱'),grid on;
    xlabel('w');
    xlim([-15,15]);

    
    Ts=2;ts=-20:Ts:20;
    fs=((1+cos(ts))/2).*(heaviside(ts+pi)-heaviside(ts-pi));
    omega1=-10*pi;omega2=10*pi;K=4000;
    OMEGA=omega2-omega1;
    delta_omega=OMEGA/K;
    omega=omega1:delta_omega:omega2;
    Fs=Ts*(fs*exp(-1i*ts'*omega));
    subplot(3,1,3)
    plot(omega,abs(Fs / 2));
    title('f(t)=(1+cos(t))/2 采样间隔为2s时的幅度谱'),grid on;
    xlabel('w');
    xlim([-15,15]);
end

function ex3_1_3_2()
    % 采样间隔
    Ts=0.5;
    ts=-20:Ts:20;
    fs=((1+cos(ts))/2).*(heaviside(ts+pi)-heaviside(ts-pi));;
    figure;
    omega1=-8*pi;omega2=8*pi;K=4000;
    OMEGA=omega2-omega1;
    delta_omega=OMEGA/K;
    omega=omega1:delta_omega:omega2;
    Fs=Ts*(fs*exp(-1i*ts'*omega));
    subplot(3,1,1)
    plot(omega,angle(2 * Fs));
    title('f(t)=(1+cos(t))/2 采样间隔为0.5s时的相位谱'),grid on;
    xlabel('w');
    xlim([-15,15]);
    
    
    Ts=1;ts=-20:Ts:20;
    fs=((1+cos(ts))/2).*(heaviside(ts+pi)-heaviside(ts-pi));;
    omega1=-8*pi;omega2=8*pi;K=4000;
    OMEGA=omega2-omega1;
    delta_omega=OMEGA/K;
    omega=omega1:delta_omega:omega2;
    Fs=Ts*(fs*exp(-1i*ts'*omega));
    subplot(3,1,2)
    plot(omega,angle(Fs));
    title('f(t)=(1+cos(t))/2 采样间隔为1s时的相位谱'),grid on;
    xlabel('w');
    xlim([-15,15]);
    

    Ts=2;ts=-20:Ts:20;
    fs=((1+cos(ts))/2).*(heaviside(ts+pi)-heaviside(ts-pi));
    omega1=-10*pi;omega2=10*pi;K=4000;
    OMEGA=omega2-omega1;
    delta_omega=OMEGA/K;
    omega=omega1:delta_omega:omega2;
    Fs=Ts*(fs*exp(-1i*ts'*omega));
    subplot(3,1,3)
    plot(omega,angle(Fs / 2));
    title('f(t)=(1+cos(t))/2 采样间隔为2s时的相位谱'),grid on;
    xlabel('w');
    xlim([-15,15]);
end