clear

TOL = 10^-13;
step = 1;
X0 = [0.1;0.1;-0.1];
errors = F(X0);
diff = [step norm(errors, inf)];

while(step < 10 & diff(step, 2) > TOL)
    A = DF(X0);
    X = X0 - A\errors;
    X0 = X;

    step = step + 1;
    errors = F(X0);
    diff = [diff;
            step norm(errors, inf)];
end

find_order_convergence(diff(:, 2));