clear

X = [0;
     0.15;
     0.31;
     0.5;
     0.6;
     0.75];
Y = [1;
    1.004;
    1.031;
    1.117;
    1.223;
    1.422];

%determine A x B
n = size(X, 1);

deg = 1;
pol_deg = 1;
while(deg <= pol_deg)
    A(1:n, deg) = X.^deg;

    deg = deg + 1;
end
A(1:n, deg) = ones(n, 1);

B(1:n, 1) = Y;

%x = (A'*A)\(A'*B);

[Q, R] = QR_factorzie(A);

r = R(1:deg, 1:deg);

q_transpose = Q';
q_transpose = q_transpose(1:deg, :);

x = r\(q_transpose*B);
