% ex2_1_1()
% ex2_1_2()ex2_1_3()

ex2_1_3()

function ex2_1_1()
    %ex2_1_1:求傅里叶变换
    % 定义符号变量
    syms t;
    % 按题目要求定义函数
    ft=sym(exp(-t).*heaviside(t));
    % 转为ft的傅里叶变换表达式
    Fw=fourier(ft);
    
    % 定义幅度谱对应的函数
    amplitude=abs(Fw);
    % 划分显示区域
    subplot(2,1,1);
    % 画出图像
    fplot(amplitude);
    % 设置坐标范围
    axis([-8 8 0 1.2]);
    % 坐标线
    grid on
    % 设置标题
    title('Amplitude spectrum');
    % 设置横轴名称
    xlabel('w')

    % 定义相位谱对应的函数
    phase=atan(imag(Fw)/real(Fw));
    % 划分显示区域
    subplot(2,1,2);
    % 画出图像
    fplot(phase);
    % 设置坐标范围
    axis([-5 5 -1.5 1.5]);
    % 坐标线
    grid on
    % 设置标题
    title('Phase spectrum');
    % 设置横轴名称
    xlabel('w')
    
end

function ex2_1_2()
    % ex2_1_2:求傅里叶逆变换
    % 定义符号变量
    syms t;
    % 定义F(w)对应的符号表达式
    Fw=str2sym('1/(1+w^2)');
    % 转为关于t的表达式
    ft=ifourier(Fw,t);
    % 画出图像
    fplot(ft);
    % 设置横纵坐标范围，经过尝试，横坐标[-5, 5]，纵坐标[0, 0.55]较合适
    axis([-5 5 0 0.55])
    % 坐标线
    grid on
    % 设置标题
    title('1+1/(1+w^2)对应的傅里叶逆变换')
    % 设置横轴坐标
    xlabel('w')

end

function test()
    %ex2_1_3:数值计算，将数值解和理论解对比
    %采样点数
    N=10000;
    %s设定时域函数区间
    t=-1:2/N:1;
    %生成时间向量
    dt=-40:2/N:40;
    %设定频谱范围
    w=-40:1:40;
    f=exp(-t).*heaviside(t);
    %进行傅里叶变换
    F=1/N*f*exp(-1i*pi*t'*w);
    subplot(2,1,1);
    %绘制幅度谱
    stem(w,abs(F),'-+');
    axis([-8 8 0 1.2]);
    grid on;
    title('Amplitude spectrum');
    subplot(2,1,2);
    %绘制相位谱
    stem(w,angle(F),'-+');
    axis([-5 5 -1.8 1.8]);
    grid on;
    title('Phase spectrum');
end

function ex2_1_3()
    N = 5000;%采样点数
    Ts=1/N;%设定时域函数区间
    t=-15:1/N:15;%设置时间宽度
    w=-15:0.01:15;%设定频谱范围
    ft=exp(-t).*heaviside(t);%指数信号
    Fw=Ts*ft*exp(-1j*t'*w);%进行傅里叶变换
     
    subplot(2,1,1);
    plot(w,abs(Fw))%利用abs函数求得幅度谱
    % plot(w,amplitude,'r')
    axis([-8 8 0 1.3]) 
    grid on
    title('f(t)幅度谱');
    % 设置横轴坐标
    xlabel('w')
    subplot(2,1,2);
    plot(w,angle(Fw));
    grid on
    title('f(t)相位谱');
    % 设置横轴坐标
    xlabel('w')
    
end

    



