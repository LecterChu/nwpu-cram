
ex2_3_2()

function ex2_3_1()

    B=[1];
    A=[1 1 1];
    % 步长
    N=4000;
    % 设置频谱范围
    w=-4*pi:8*pi/N:4*pi; 
    % 使用freqs函数求频率响应
    H=freqs(B,A,w); 
    % 求幅频响应
    amplitude=abs(H);
    % 划分
    subplot(2,1,1);
    % 显示图像
    plot(w,amplitude);
    % 设置标题
    title('H(jw) Amplitude frequency characteristic');
    % 设置横轴名称
    xlabel('w');
    % 求相频响应
    phase=angle(H);
    % 划分
    subplot(2,1,2);
    % 显示图像
    plot(w,phase);
    % 设置标题
    title('H(jw) Phase frequency characteristic');
    % 设置横轴名称
    xlabel('w');
end

function ex2_3_2()
    % 定义时间范围
    t=0:0.001:30;
    % 激励
    yt=cos(t)+cos(10*t);
    % 滤波器分子
    B=[1];
    % 滤波器分母
    A=[1 1 1];
    % 滤波器
    sys=tf(B,A);
    % 求线性时不变系统的响应
    H=lsim(sys,yt,t);
    % 显示图像
    plot(t,yt)
    % 继续画下一张图像
    hold on
    % 幅值变换为分贝单位
    plot(t,H)  
    % 设置范围
    axis([0 30 -3 3])
    % 打开网格
    grid on
    % 设置标题
    title('Time domain waveform')
    % 设置注释
    legend('input','output')
end