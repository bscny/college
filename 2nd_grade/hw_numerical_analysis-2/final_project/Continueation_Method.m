clear
% the following is the describtion of all the varibles i use in this code
% Curve_vectors : every set of (x1, x2, x3) corresponding to each lamda
% n : how many segements we want
% records : the desire datas through calculation. For example, num of
% newton iterations with each lamda, all risiduals with each lamda
% final_ans : final answer

% hints how to use records: records{1} to get the record we want
% corresponding to lamda1, records{i} to get the record we want
% corresponding to lamdai

const_X0 = [-2;0;0];  % the init vector
n = 10;              % num of segments for lamda
has_solution = 1;    % indicator of if there's a singular J
TOL = 10^-12;

if(abs(det(J(const_X0))) < TOL) % J is likely to be singular
    final_ans = [-1;-1;-1];
    return;
end

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
