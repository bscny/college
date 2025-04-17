# (a) Load the data into R
fevdata <- read.table("./fevdata.txt", header = TRUE)

# str(fevdata)

# (b) Plot the data for the response and independent variables
#     Include a smoothed function on the plot
library(ggplot2)
ggplot(fevdata, aes(x = age, y = fev)) +
  geom_point() +
  geom_smooth(method = "loess") +
  labs(title = "FEV vs Age", x = "Age (years)", y = "FEV (liters)")

# (c) Fit a straight line model
model1 <- lm(fev ~ age, data = fevdata)

summary(model1)

# (d) Perform an analysis of variance analysis
anova(model1)

# (g) Compute the sample Pearson correlation coefficient
cor.test(fevdata$age, fevdata$fev)

# (i) Perform the residual analysis
plot(model1)

# (j) Fit a simple linear regression model in which 
#     the response variable is the nature log
#     of the response variable
model2 <- lm(log(fev) ~ age, data = fevdata)

summary(model2)

# (k) Repeat the part (b) and part (i) using the transformed data
# for (b):
ggplot(fevdata, aes(x = age, y = log(fev))) +
  geom_point() +
  geom_smooth(method = "loess") +
  labs(title = "Log(FEV) vs Age", x = "Age", y = "log(FEV)")

# for (i):
plot(model2)

# (l) Plot the estimated regression function,
#     95% confidence intervals for the mean response
#     95% prediction intervals for a range of X values that span the data
age_seq <- data.frame(age = seq(min(fevdata$age), max(fevdata$age), 0.5))
predictions <- predict(model2, newdata = age_seq, interval = "prediction", level = 0.95)
conf <- predict(model2, newdata = age_seq, interval = "confidence", level = 0.95)

# scatter point
plot(fevdata$age, log(fevdata$fev), main = "Log(FEV) with Prediction & Confidence Interval",
     xlab = "Age", ylab = "log(FEV)",
     ylim = c(min(log(fevdata$fev)), max(log(fevdata$fev)) + 0.5))

# mean response line
lines(age_seq$age, predictions[, "fit"], col = "black")

# prediction interval
lines(age_seq$age, predictions[, "lwr"], col = "blue", lty = 2)
lines(age_seq$age, predictions[, "upr"], col = "blue", lty = 2)

# confidence interval
lines(age_seq$age, conf[, "lwr"], col = "red", lty = 2)
lines(age_seq$age, conf[, "upr"], col = "red", lty = 2)

# (n): Fit the model in part (j) without the intercept
model_no_intercept <- lm(log(fev) ~ age + 0, data = fevdata)
sum_resid_with_intercept <- sum(resid(model2))
sum_resid_without_intercept <- sum(resid(model_no_intercept))