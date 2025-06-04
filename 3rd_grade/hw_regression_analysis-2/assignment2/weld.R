weld <- read.table("./weld.txt", header = TRUE)
weld$cALLOY <- factor(weld$ALLOY)

# str(weld)

# (a):
# Scatter plot with different symbols by alloy
library(ggplot2)
ggplot(weld, aes(x = Diameter, y = Strength, color = cALLOY, shape = cALLOY)) +
  geom_point(size = 3) +
  geom_smooth(method = "lm", se = FALSE, aes(group = cALLOY)) +
  labs(title = "Strength vs Diameter by Alloy", x = "Diameter", y = "Strength")

# Fit model without interaction
model1 <- lm(Strength ~ Diameter + cALLOY, data = weld)
summary(model1)

# Extract model coefficients
coef <- coef(model1)

# Plot the data: pch and col change with alloy type
plot(Strength ~ Diameter, pch = 15 + ALLOY, col = 2 + ALLOY, data = weld,
     main = "Strength vs Diameter by Alloy",
     xlab = "Diameter", ylab = "Strength")

# Draw regression lines for each alloy (no interaction model)
# Alloy 1 (baseline)
abline(a = coef["(Intercept)"], b = coef["Diameter"], col = 2, lwd = 2)

# Alloy 2
abline(a = coef["(Intercept)"] + coef["cALLOY2"], b = coef["Diameter"], col = 3, lwd = 2)

# Alloy 3
abline(a = coef["(Intercept)"] + coef["cALLOY3"], b = coef["Diameter"], col = 4, lwd = 2)

# Add legend
legend("topleft", legend = c("Alloy 1", "Alloy 2", "Alloy 3"),
       col = c(2, 3, 4), lwd = 2, pch = c(16, 17, 18))

# (c)
# Create residual plot with different symbols for alloys
residuals <- residuals(model1)
fitted_values <- fitted(model1)

plot_data <- data.frame(
  Fitted = fitted_values,
  Residuals = residuals,
  cALLOY = weld$cALLOY
)

# fitted against residual
ggplot(plot_data, aes(x = Fitted, y = Residuals, color = cALLOY, shape = cALLOY)) +
  geom_point(size = 3) +
  geom_hline(yintercept = 0, linetype = "dashed") +
  labs(title = "Residual Plot by Alloy Type",
       x = "Fitted Values", y = "Residuals") +
  theme_minimal()

# (d)

model2 <- lm(Strength ~ Diameter * cALLOY, data = weld)
summary(model2)
