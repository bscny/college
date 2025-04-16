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
# (b):
ggplot(fevdata, aes(x = age, y = log(fev))) +
  geom_point() +
  geom_smooth(method = "loess") +
  labs(title = "Log(FEV) vs Age", x = "Age", y = "log(FEV)")

# (i):
plot(model2)

# (l) Plot the estimated regression function,
#     the 95% confidence intervals for the mean response
#     95% prediction intervals for a range of X values that span the data