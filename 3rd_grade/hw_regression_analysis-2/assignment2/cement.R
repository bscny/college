cement_data <- read.table("./cement.txt", header = TRUE)

# str(cement_data)

# (a)
# Fit full model
full_model <- lm(y ~ x1 + x2 + x3 + x4, data = cement_data)
summary(full_model)

# (b)
# Calculate correlation matrix
cor_matrix <- cor(cement_data[, c("x1", "x2", "x3", "x4")])
print(cor_matrix)

# Calculate Variance Inflation Factors (VIF)
library(car)
vif_values <- vif(full_model)
print(vif_values)

# Condition indices
# library(perturb)
# colldiag(full_model)

# Check if sum of percentages ≈ 100% (indicating constraint)
# cement_data$sum_percentages <- rowSums(cement_data[, c("x1", "x2", "x3", "x4")])
# print(cement_data$sum_percentages)

# (c)
# Fit reduced model with only x1 and x2
reduced_model <- lm(y ~ x1 + x2, data = cement_data)
summary(reduced_model)

# Compare with full model
anova(reduced_model, full_model)

# Check VIF for reduced model
vif(reduced_model)

# (d)
# Plot Y vs X1
plot(cement_data$x1, cement_data$y, 
     main = "Y vs X1", xlab = "X1", ylab = "Y")
abline(lm(y ~ x1, cement_data), col = "red")

# Create partial regression plot for X1
# Regress Y on all other predictors except x1
y_residuals <- residuals(lm(y ~ x2, data = cement_data))

# Regress X1 on all other predictors
x1_residuals <- residuals(lm(x1 ~ x2, data = cement_data))

partial_lm <- lm(y_residuals ~ x1_residuals)

# Plot residuals
plot(x1_residuals, y_residuals,
     main = "Partial Regression Plot for X1",
     xlab = "X1 Residuals", ylab = "Y Residuals")
abline(partial_lm, col = "blue")

summary(partial_lm)