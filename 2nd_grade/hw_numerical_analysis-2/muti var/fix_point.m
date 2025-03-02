clear

TOL = 10^-13;
X0 = [0.1;0.1;-0.1];
step = 1;
errors = F(X0);
diff = [step norm(errors, inf)];

while(diff(step, 2) > TOL & step < 80)
    X = G(X0);
    X0 = X;

    step = step + 1;
    errors = F(X0);
    diff = [diff;
            step norm(errors, inf)];
end

find_order_convergence(diff(:, 2));