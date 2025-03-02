function [convergence_speed] = find_order_convergence(seq)
    n = size(seq, 1);
    x_star = seq(n, 1);
    x1 = seq(n-1, 1);
    x2 = seq(n-2, 1);
    x3 = seq(n-3, 1);

    convergence_speed = log(abs(x1 - x_star) / abs(x2 - x_star)) / log(abs(x2 - x_star) / abs(x3 - x_star))
end