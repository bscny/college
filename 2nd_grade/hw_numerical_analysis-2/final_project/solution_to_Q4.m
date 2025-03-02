clear

X0 = [0;0;0];
TOL = 10^-12;

num_diff_solutions = 0;
set_of_X0 = cell(1, 3);

is_new = 1;

for i = -2:2
    for k = -2:2
        for j = -2:2
            X = X0;
            X(1, 1) = X(1, 1) + i;
            X(2, 1) = X(2, 1) + k;
            X(3, 1) = X(3, 1) + j;
            temp = C_M(X);

            if(temp == [-1;-1;-1])    % no solutions for x0
                set_of_X0{3}(:, size(set_of_X0{3}, 2) + 1) = X;
                continue;
            end

            is_new = 1;
            for cur = 1:num_diff_solutions
                if(abs(norm(temp - diff_solutions(:, cur), inf)) < TOL)  % already finded
                    is_new = 0;

                    set_of_X0{cur}(:, size(set_of_X0{cur}, 2) + 1) = X;
                    break;
                end
            end

            if(is_new == 1)
                num_diff_solutions = num_diff_solutions + 1;
                diff_solutions(:, num_diff_solutions) = temp;

                set_of_X0{num_diff_solutions}(:, size(set_of_X0{num_diff_solutions}, 2) + 1) = X;
            end

        end
    end
end