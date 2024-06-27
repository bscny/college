function [P] = house_hold(X)
    n = size(X, 1);

    W = X;
    alpha = norm(X);

    %{
    E = zeros([n, 1]);
    E(1,1) = 3/5;
    E(3,1) = 4/5;

    W = X - alpha*E;
    %}

    W(1, 1) = X(1, 1) - alpha;


    r = (2*alpha^2 - 2*alpha*X(1, 1))^(1/2);
    %r = norm(W);
    W = W/r;

    P = eye(n) - 2*W*W';

end