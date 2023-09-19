% 奇偶特性


ex2_2_2_3()

% ex2_2_1_4()
% ex2_2_1_4()

function ex2_2_1_1()
    % 矩形脉冲信号G4
    
    % 设置时间范围与步长
    t = -10:0.01:10;
    % 划分显示范围
    subplot(3,1,1);
    % 显示图像
    plot(t,rectpuls(0.25*t));
    % 设置坐标范围
    axis([-5,5,-0.2,1.2])
    % 设置标题
    title('Rectangular pulse signal G4(t)')
    % 设置横轴名称
    xlabel('t')
    
    % 求矩形脉冲幅度谱和相位谱
    % 采样点数，即dt在数值上的倒数
    N = 5000;
    % 抽样间隔
    Ts=1/N;
    % 设置时间尺度上的取值区间[-10,10]
    t=-10:1/N:10;
    % 设定频谱范围
    w=-10:0.01:10;
    % 矩形脉冲信号
    ft=rectpuls(t,4);
    % 进行傅里叶变换
    Fw=Ts*ft*exp(-1j*t'*w);
    
    % 划分显示范围
    subplot(3,1,2);
    % 求幅度谱
    amplitude=abs(Fw);
    % 显示图像
    plot(w,amplitude);
    % 设置坐标范围
    axis([-10,10,0,5])
    % 设置标题
    title('G4(t) Amplitude spectrum');
    % 设置横轴名称
    xlabel('w')
     % 划分显示范围
    subplot(3,1,3);
    % 求相位谱
    phase=angle(Fw);
    % 显示图像
    plot(w,phase);
    % 设置坐标范围
    axis([-10,10,-4,4])
    % 设置标题
    title('G4(t) Phase spectrum');
    % 设置横轴名称
    xlabel('w')
    
end

function ex2_2_1_2()
    %三角波脉冲信号A4
    
    % 设置时间范围与步长
    t = -10:0.01:10;
    % 划分显示范围
    subplot(3,1,1);
    % 加载图像
    plot(t,tripuls(0.25*t,1));
    % 设置坐标范围
    axis([-6,6,-0.2,1.2])
    % 设置标题
    title('三角波脉冲信号(宽度为4)')
    % 设置横轴名称
    xlabel('t')
    
    % 求三角脉冲幅度谱和相位谱
    % 采样点数，dt在数值上的倒数
    N = 5000;
    % 抽样间隔
    Ts=1/N;
    % 设置时间尺度上的取值区间[-10,10]
    t=-10:1/N:10;
    %设定频谱范围
    w=-10:0.01:10;
    %三角脉冲信号A4
    ft=tripuls(t/4,1);
    %进行傅里叶变换
    Fw=Ts*ft*exp(-1j*t'*w);
    % 划分显示范围
    subplot(3,1,2);
    %求幅度谱
    amplitude=abs(Fw);
    % 显示图像
    plot(w,amplitude)
    % 设置坐标范围
    axis([-10,10,-0.2,2.2])
    % 设置标题
    title('A4(t) Amplitude spectrum');
    % 设置横轴名称
    xlabel('w')
    % 划分显示范围
    subplot(3,1,3);
    % 显示图像
    plot(w,angle(Fw));
    % 设置标题
    title('A4(t) Phase spectrum');
    % 设置横轴名称
    xlabel('w')
end

function ex2_2_1_3()
    %单指数信号
    
%     % 符号
%     syms t;
%     % 函数定义
%     f=exp(-t).*heaviside(t);
%     % 划分显示范围
%     subplot(3,1,1);
%     % 显示图像
%     fplot(f);
%     % 设置坐标范围
%     axis([-0.5,4,-0.1,1.2])
%     % 设置标题
%     title('exp(-t)*u(t)单指数信号')
%     % 设置横轴名称
%     xlabel('t')
    
    % 求指数信号幅度谱和相位谱，数值解法
    % 采样点数
    N = 5000;
    % 采样步长
    Ts=1/N;
    % 设置时间宽度
    t=-10:1/N:10;
    % 设定频谱范围
    w=-10:0.01:10;
    % 指数信号
    ft=exp(-t).*heaviside(t);
    % 划分
    subplot(3,1,1);
    % 显示
    plot(t,ft);
    % 设置标题
    title('exp(-t)*u(t)单指数信号')
    % 设置横轴名称
    xlabel('t')
    
    % 进行傅里叶变换
    Fw=Ts*ft*exp(-1j*t'*w);
    % 划分显示范围
    subplot(3,1,2);
    % 求幅度谱
    amplitude=abs(Fw);
    % 显示图像
    plot(w,amplitude)
    % 设置坐标范围
    axis([-10,10,0,1.2])
    % 设置标题
    title('Amplitude spectrum');
    % 设置横轴名称
    xlabel('w')
    subplot(3,1,3);
    % 求相位谱
    phase=angle(Fw);
    % 显示图像
    plot(w,phase);
    % 设置标题
    title('Phase spectrum');
    % 设置横轴名称
    xlabel('w')
    
end

function ex2_2_1_4()
    % 两指数相减信号
    
%     % 定义一个符号变量
%     syms t_sym;
%     % 函数定义
%     f=(exp(-t_sym).*heaviside(t_sym))-(exp(t_sym).*heaviside(-t_sym));
%     % 划分显示范围
%     subplot(3,1,1);
%     % 显示图像
%     fplot(f);
%     % 设置坐标范围
%     axis([-4,4,-1.2,1.2])
%     % 设置标题
%     title('exp(-t_sym)*u(t_sym)-exp(t_sym)*u(-t_sym)')
%     % 设置横坐标名称
%     xlabel('t_sym')
    
    % 求幅度谱和相位谱
    % 采样点数
    N = 5000;
    % 设置采样步长
    Ts=1/N;
    % 设置时间宽度
    t=-10:1/N:10;
    % 设定频谱范围
    w=-10:0.01:10;
    % 指数差信号
    ft=exp(-t).*heaviside(t)-exp(t).*heaviside(-t);
    subplot(3,1,1)
    plot(t,ft)
    axis([-4,4,-1.2,1.2])
    title('exp(-t_sym)*u(t_sym)-exp(t_sym)*u(-t_sym)')
    xlabel('t_sym')
    % 进行傅里叶变换
    Fw=Ts*ft*exp(-1j*t'*w);
    % 划分显示范围
    subplot(3,1,2);
    % 求幅度谱
    amplitude=abs(Fw);
    % 显示图像
    plot(w,amplitude)
    % 设置标题
    title('Amplitude spectrum');
    % 设置横轴名称
    xlabel('w')
    % 划分显示范围
    subplot(3,1,3);
    % 求相位谱
    phase=angle(Fw);
    % 显示图像
    plot(w,phase);
    % 设置标题
    title('Phase spectrum');
    % 设置横轴名称
    xlabel('w')
end


% 展缩特性
function ex2_2_2_1()
    %x(t)=G4(t)
    
    %设置时间宽度
    t = -10:0.01:10;
    % 划分显示范围
    subplot(3,1,1);
    % 显示图像
    plot(t,rectpuls((1/4)*t));
    % 设置坐标范围
    axis([-10,10,-0.2,1.2])
    % 设置标题
    title('x(t) Rectangular pulse signal')
    % 设置横坐标名称
    xlabel('t')
    
    % 求x(t)矩形脉冲幅度谱和相位谱
    % 采样点数
    N = 10000;
    % 设定采样步长
    Ts=1/N;
    % 设置时间宽度
    t=-10:1/N:10;
    % 设定频谱范围
    w=-10:0.01:10;
    % ft函数
    ft=rectpuls(t,4);
    % 进行傅里叶变换
    Fw=Ts*ft*exp(-1j*t'*w);
    % 划分显示范围
    subplot(3,1,2);
    % 求幅度谱
    amplitude=abs(Fw);
    plot(w,amplitude)
    % 设置标题
    title('x(t) Amplitude spectrum');
    % 设置横轴名称
    xlabel('w')
    % 划分显示范围
    subplot(3,1,3);
    % 求相位谱
    phase=angle(Fw);
    plot(w,phase);
    % 设置标题
    title('x(t) Phase spectrum');
    % 设置横轴名称
    xlabel('w')
             
end

function ex2_2_2_2()
    % x(t/2)
    % 设置时间宽度
    t = -10:0.01:10;
    % 划分显示范围
    subplot(3,1,1);
    % 显示图像
    plot(t,rectpuls((1/8)*t));
    % 设置坐标范围
    axis([-10,10,-0.2,1.2])
    % 设置标题
    title('x(t/2) Rectangular pulse signal')
    % 设置横坐标名称
    xlabel('t')
    %采样点数
    N = 10000;
    %设定采样步长
    Ts=1/N;
    %设置时间宽度
    t=-10:1/N:10;
    %设定频谱范围
    w=-10:0.01:10;
    %ft函数
    ft=rectpuls(t,8);
    %傅里叶变换
    Fw=Ts*ft*exp(-1j*t'*w);
    % 划分显示范围
    subplot(3,1,2);
    % 求幅度谱
    amplitude=abs(Fw);
    % 显示图像
    plot(w,amplitude);
    % 设置标题
    title('x(t/2) Amplitude spectrum ');
    % 设置横轴名称
    xlabel('w')
    % 划分显示范围
    subplot(3,1,3);
    % 求相位谱
    phase=angle(Fw);
    % 显示图像
    plot(w,phase);
    % 设置标题
    title('x(t/2) Phase spectrum');
    % 设置横轴名称
    xlabel('w')
    
end

function ex2_2_2_3()
    % x(2t)
    % 设置时间宽度
    t = -10:0.01:10;
    % 划分显示范围
    subplot(3,1,1);
    % 显示图像
    plot(t,rectpuls((1/2)*t));
    % 设置坐标范围
    axis([-10,10,-0.2,1.2])
    % 设置标题
    title('x(2t) Rectangular pulse signal')
    % 设置横坐标名称
    xlabel('t')
    % 采样点数
    N = 10000;
    % 设定采样步长
    Ts=1/N;
    % 设置时间宽度
    t=-10:1/N:10;
    % 设定频谱范围
    w=-10:0.01:10;
    % ft函数
    ft=rectpuls(t,2);
    % 傅里叶变换
    Fw=Ts*ft*exp(-1j*t'*w);
    % 划分显示范围
    subplot(3,1,2);
    % 求幅度谱
    amplitude=abs(Fw);
    % 显示图像
    plot(w,amplitude);
    % 设置标题
    title('x(2t) Amplitude spectrum ');
    % 设置横轴名称
    xlabel('w')
    % 划分显示范围
    subplot(3,1,3);
    % 求相位谱
    phase=angle(Fw);
    % 显示图像
    plot(w,phase);
    % 设置标题
    title('x(2t) Phase spectrum');
    % 设置横轴名称
    xlabel('w')
    
end

function ex2_2_3_1()
    % x(t)=A4(t)
    % 设置时间宽度
    t = -10:0.01:10;
    % 划分显示范围
    subplot(3,1,1);
    %  显示图像
    plot(t,tripuls(0.25*t,1));
    % 设置坐标范围
    axis([-10,10,-0.2,1.2])
    % 设置标题
    title('x(t) Triangular pulse signal')
    % 设置横坐标名称
    xlabel('t')
    %采样点数
    N = 10000;
    % 设定采样步长
    Ts=1/N;
    % 设置时间宽度
    t=-10:1/N:10;
    % 设定频谱范围
    w=-10:0.01:10;
    % ft函数
    ft=tripuls(0.25*t,1);
    % 傅里叶变换
    Fw=Ts*ft*exp(-1j*t'*w);
    % 划分显示范围
    subplot(3,1,2);
    % 求幅度谱
    amplitude=abs(Fw);
    % 显示图像
    plot(w,amplitude);
    % 设置标题
    title('x(t) Amplitude spectrum');
    % 设置横坐标名称
    xlabel('w')
    % 划分显示范围
    subplot(3,1,3);
    % 求相位谱
    phase=angle(Fw);
    % 显示图像
    plot(w,phase);
    % 设置标题
    title('x(t) Phase spectrum');
    % 设置横坐标名称
    xlabel('w')
    
end

function ex2_2_3_2()
    % x(t-0.1)
    % 设置时间宽度
    t = -10:0.01:10;
    % 划分显示范围
    subplot(3,1,1);
    %  显示图像
    plot(t,tripuls(0.25*(t-0.1),1));
    % 设置坐标范围
    axis([-10,10,-0.2,1.2])
    % 设置标题
    title('x(t-0.1) Triangular pulse signal')
    % 设置横坐标名称
    xlabel('t')
    %采样点数
    N = 10000;
    % 设定采样步长
    Ts=1/N;
    % 设置时间宽度
    t=-10:1/N:10;
    % 设定频谱范围
    w=-10:0.01:10;
    % ft函数
    ft=tripuls(0.25*(t-0.1),1);
    % 傅里叶变换
    Fw=Ts*ft*exp(-1j*t'*w);
    % 划分显示范围
    subplot(3,1,2);
    % 求幅度谱
    amplitude=abs(Fw);
    % 显示图像
    plot(w,amplitude);
    % 设置标题
    title('x(t-0.1) Amplitude spectrum');
    % 设置横坐标名称
    xlabel('w')
    % 划分显示范围
    subplot(3,1,3);
    % 求相位谱
    phase=angle(Fw);
    % 显示图像
    plot(w,phase);
    % 设置标题
    title('x(t-0.1) Phase spectrum');
    % 设置横坐标名称
    xlabel('w')

end

function ex2_2_3_3()
    % x(t-1)
    % 设置时间宽度
    t = -10:0.01:10;
    % 划分显示范围
    subplot(3,1,1);
    %  显示图像
    plot(t,tripuls(0.25*(t-1),1));
    % 设置坐标范围
    axis([-10,10,-0.2,1.2])
    % 设置标题
    title('x(t-1) Triangular pulse signal')
    % 设置横坐标名称
    xlabel('t')
    %采样点数
    N = 10000;
    % 设定采样步长
    Ts=1/N;
    % 设置时间宽度
    t=-10:1/N:10;
    % 设定频谱范围
    w=-10:0.01:10;
    % ft函数
    ft=tripuls(0.25*(t-1),1);
    % 傅里叶变换
    Fw=Ts*ft*exp(-1j*t'*w);
    % 划分显示范围
    subplot(3,1,2);
    % 求幅度谱
    amplitude=abs(Fw);
    % 显示图像
    plot(w,amplitude);
    % 设置标题
    title('x(t-1) Amplitude spectrum');
    % 设置横坐标名称
    xlabel('w')
    % 划分显示范围
    subplot(3,1,3);
    % 求相位谱
    phase=angle(Fw);
    % 显示图像
    plot(w,phase);
    % 设置标题
    title('x(t-1) Phase spectrum');
    % 设置横坐标名称
    xlabel('w')

end

function ex2_2_4_1()
    % x(t)=G4(t)
    
    % 设置时间宽度
    t = -10:0.01:10;
    % 划分显示范围
    subplot(3,1,1);
    % 显示图像
    plot(t,rectpuls((1/4)*t));
    % 设置坐标范围
    axis([-10,10,-0.2,1.2])
    % 设置标题
    title('x(t) Rectangular pulse signal')
    % 设置横坐标名称号
    xlabel('t')

    % 采样点数
    N = 10000;
    % 设定采样步长
    Ts=1/N;
    % 设置时间宽度
    t=-10:1/N:10;
    % 设定频谱范围
    w=-10:0.01:10;
    %ft=G4(t)
    ft=rectpuls(t,4);
    % 傅里叶变换
    Fw=Ts*ft*exp(-1j*t'*w);
    % 划分显示范围
    subplot(3,1,2);
    % 求幅度谱
    amplitude=abs(Fw);
    % 显示图像
    plot(w,amplitude);
    % 设置标题
    title('x(t) Amplitude spectrum');
    % 设置横坐标名称号
    xlabel('w')
    % 划分显示范围
    subplot(3,1,3);
    % 求相位图
    phase=angle(Fw);
    % 显示图像
    plot(w,phase);
    % 设置标题
    title('x(t) Amplitude spectrum');
    % 设置横坐标名称号
    xlabel('w')
    
end

function ex2_2_4_2()
    %x(t)cos(20t)
    
%     %定义一个符号变量
%     syms t;
%     % ft函数
%     ft=cos(20*t).*(heaviside(t+2)-heaviside(t-2));
%     % 划分显示范围
%     subplot(3,1,1);
%     % 显示图像
%     fplot(ft);
%     % 设置坐标范围
%     axis([-10,10,-1.2,1.2])
%     % 设置标题
%     title('x(t)cos(20t) Rectangular pulse signal')
%     % 设置横坐标名称
%     xlabel('t')
    
    % 采样点数
    N = 10000;
    % 设定采样步长
    Ts=1/N;
    % 设置时间宽度
    t=-10:1/N:10;
    % 设定频谱范围
    w=-10:0.01:10;
    % G4(t)cos(20t)
    ft=rectpuls(t,4).*cos(20*t);
    % 划分
    subplot(3,1,1)
    % 显示
    plot(t,ft)
    % 标题
    title('x(t)cos(20t) Rectangular pulse signal')
    % 设置横坐标名称
    xlabel('t')
    % 傅里叶变换
    Fw=Ts*ft*exp(-1j*t'*w);
    % 划分显示范围
    subplot(3,1,2);
    % 求幅度谱
    amplitude=abs(Fw);
    % 显示图像
    plot(w,amplitude)
    % 设置标题
    title('x(t)cos(20t) Amplitude spectrum');
    % 设置横轴名称
    xlabel('w')
    % 划分显示范围
    subplot(3,1,3);
    % 求相位谱
    phase=angle(Fw);
    % 显示图像
    plot(w,phase);
    % 设置标题
    title('x(t)cos(20t) Amplitude spectrum');
    % 设置横轴名称
    xlabel('w')

end

