function [final_ans] = C_M(const_X0)
% for my own use for question 4
TOL = 10^-12;

if(abs(det(J(const_X0))) < TOL) % J is likely to be singular
    final_ans = [-1;-1;-1];
    return;
end

n = 10;       % num of segments for lamda
has_solution = 1;    % indicator of if there's a singular J

X_prev = const_X0;

Curve_vectors = const_X0;

for i = 1:n
    % asking for the solution at lamda = i/n
    X_predict = X_prev + 1/n * dX_dlamda(X_prev, const_X0);

    if(abs(det(J(X_predict))) < TOL)  % J is likely to be singular
        final_ans = [-1;-1;-1];
        has_solution = 0;
        break;
    end

    [Curve_vectors(:, i + 1), records{i}] = Newton_on_H(i/n, X_predict, const_X0);

    if(size(records{i}, 1) == 16)  % converges to another point
        final_ans = [-1;-1;-1];
        has_solution = 0;
        break;
    end

    X_prev = Curve_vectors(:, i + 1);
end

if(has_solution == 1)
    final_ans = X_prev;
end

end