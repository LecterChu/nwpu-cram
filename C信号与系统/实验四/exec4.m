expr4_1_4_1_1()


function expr4_1_1_1()
    syms t;
    f1 = exp(-2 * t) .* heaviside(t);
    F1 = laplace(f1);
    disp(F1);
end

function expr4_1_1_2()
    syms t;
    f2 = dirac(t) + exp(2 * t) .* heaviside(t) - 4 / 3 * exp(-t) .* heaviside(t);
    F2 = laplace(f2);
    % disp(f2);
    disp(F2);
end

function expr4_1_2_1()
    syms s t;
    F1 = (4 * s + 5) / (s * s + 5 * s + 6);
    f1 = ilaplace(F1);
    f1 = f1 * heaviside(t);
    disp(f1);
end

function expr4_1_2_2()
    syms s t;
    F2 = (3 * s) / ((s + 4) * (s + 2));
    f2 = ilaplace(F2);
    f2 = f2 * heaviside(t);
    disp(f2);
end

function expr4_1_3()
    syms s
    b = [1 4 5];
    a = [1 5 6];
    [r, p, k] = residue(b, a);
    F1 = r(1) / (s - p(1)) + r(2) / (s - p(2)) + k;
    disp(F1);
end

function expr4_1_4_1_1()
    H = tf([1], [1 1.5]);
    pzmap(H);
    grid on;
end

function expr4_1_4_1_2()
    sys = tf(1,[1 1.5]);
    impulse(sys);
    grid on;
end

function expr4_1_4_2_1()
    H = tf([1], [1 0.5]);
    pzmap(H);
    grid on;
end

function expr4_1_4_2_2()
    sys = tf(1, [1 0.5]);
    impulse(sys);
    grid on;
end

function expr4_1_4_3_1()
    H = tf([1], [1 0]);
    pzmap(H);
    grid on;
end

function expr4_1_4_3_2()
    sys = tf(1,[1 0]);
    impulse(sys);
    grid on;
end

function expr4_1_4_4_1()
    H = tf([1], [1 -0.5]);
    pzmap(H);
    grid on;
end

function expr4_1_4_4_2()
    sys = tf(1, [1, -0.5]);
    impulse(sys);
    grid on;
end

function expr4_1_4_5_1()
    H = tf([1], [1 -1.5]);
    pzmap(H);
    grid on;
end

function expr4_1_4_5_2()
    sys = tf(1, [1 -1.5]);
    impulse(sys);
    grid on;
end

function expr4_2_1()
    syms k;
    f = 2 ^ (k - 1) * stepfun(k, 0);
    F = ztrans(f);
    disp(F);
end

function expr4_2_2()
    syms z k;
    F = (2 * z ^ 2 - 0.5 * z) / (z ^ 2 - 0.5 * z -0.5);
    f = iztrans(F);
    f = f * heaviside(k);
    disp(f);
end

function expr4_2_3()
    syms z k;
    F = z / (2 * z ^ 2 - 3 * z + 1);
    [r, p, m] = residuez(1, [2 -3 1]);
    disp("F(z)=");disp(F);
    disp("F(z)apart=");disp("b:" + r);disp("a:"+p);
    f = iztrans(F, z, k) * heaviside(k - 1);
    disp("f(k)=");disp(f);
end

function expr4_2_4_1()
    syms z k;
    zplane(1, [1, -0.8]);
    legend("零点","极点");
    grid on;
    h = impz(1, [1, -0.8], 51);
    k = 0:50;
    figure;
    stem(k, h);
    grid on;
    title("H = z / (z - 0.8)");
    xlabel("k");
    ylabel("h(k)");
end

function expr4_2_4_2()
    syms z k;
    zplane(1, [1, -1]);
    grid on;
    legend("零点", "极点");
    h = impz(1, [1, -1], 51);
    k = 0:50;
    figure;
    stem(k,h);
    grid on;
    title("H =  z / (z-1)");
    xlabel("k");
    ylabel("h(k)");
end

function expr4_2_4_3()
    syms z k ;
    zplane(1, [1, -1.2]);
    legend("零点", "极点");
    grid on;
    h = impz(1, [1, -1.2], 51);
    n = 0:50;
    figure;
    stem(n,h);
    grid on;
    title("H = z / (z-1.2)");
    xlabel("n");
    ylabel("h(n)");
end

function expr4_2_4_4()
    syms z k ;
    zplane(1, [1, 0.8]);
    legend("零点", "极点");
    grid on;
    h = impz(1, [1, 0.8], 51);
    n = 0:50;
    figure;
    stem(n,h);
    grid on;
    title("H = z / (z+0.8)");
    xlabel("n");
    ylabel("h(n)");
end

function expr4_2_4_5()
    syms z k;
    zplane(1, [1, -1.2, 0.72]);
    legend("零点", "极点");
    grid on;
    h = impz(1, [1, -1.2, 0.72], 51);
    n = 0:50;
    figure;
    stem(n,h);
    grid on;
    title("H = z / (z^2-1.2z+0.72)");
    xlabel("n");
    ylabel("h(n)");
end

function expr4_2_4_6()
    syms z k;
    zplane(1, [1, -1.6, 1]);
    legend("零点", "极点");
    grid on;
    h = impz(1, [1, -1.6, 1], 51);
    n = 0:50;
    figure;
    stem(n,h);
    grid on;
    title("H = z / (z^2-1.6z+1)");
    xlabel("n");
    ylabel("h(n)");
end

function expr4_2_4_7()
    syms z k;
    zplane(1, [1, -2, 1.36]);
    legend("零点", "极点");
    grid on;
    h = impz(1, [1, -2, 1.36], 51);
    n = 0:50;
    figure;
    stem(n,h);
    grid on;
    title("H = z / (z^2-2z+1.36)");
    xlabel("n");
    ylabel("h(n)");
end