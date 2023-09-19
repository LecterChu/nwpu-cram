
ex3_1_1_1()

function ex3_1_1_1()
    t = -pi:0.01:pi;
    f = 0.5 * (1+cos(t));
    subplot(2, 1, 1);
    plot(t, f);
    grid on;
    title('f(t) = 0.5 * (1+cos(t))时域波形')
    xlabel('t');
    xlim([-pi,pi]);
    ylabel('f(t)');
    N = 6000;
    Ts = 1/N;
    w = -10:0.01:10;
    ft = 0.5 * (1+cos(t));
    F = Ts * ft * exp(-1j*t'*w);
    subplot(2, 1, 2);
    plot(w, abs(F));
    grid on;
    title('f(t)对应的幅度谱');
    xlabel('w');
    xlim([-pi,pi]);
    ylabel('F(jw)')
end