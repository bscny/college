function [Q,R] = QR_factorzie(A)

[m, n] = size(A);

R = A;
Q = eye(m);

for i = 1:n
    I = eye(m);
    P_curr = house_hold(R(i:m, i));

    I(i:m, i:m) = P_curr;

    R = I*R;
    Q = I*Q;
end

    Q = Q';

end