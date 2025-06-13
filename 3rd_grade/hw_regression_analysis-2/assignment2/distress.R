distress_data <- read.table("./distress.txt", header = TRUE)

# str(distress_data)
# head(distress_data)

# (a)
# Fit full model with DISTRESS.2 as response
full_model <- lm(DISTRESS.2 ~ DISTRESS.1 + BLACK + NBHISP + GRADE + SLFHLTH + 
                   SLFWGHT + WORKHARD + GOODQUAL + PHYSFIT + PROUD + LIKESLF + 
                   ACCEPTED + FEELLOVD + DIET, data = distress_data)

summary(full_model)

# (b)

library(ALSM)

# Prepare data in the format expected by BestSub()
# X variables: all predictors except DISTRESS.2
X_vars <- distress_data[, !names(distress_data) %in% "DISTRESS.2"]
Y_var <- distress_data$DISTRESS.2

# Use BestSub function to fit all 2^14 = 16384 possible regression models
# This matches the teacher's example structure
best_subsets_results <- BestSub(X_vars, Y_var,
                                method = c('r2', 'r2adj', 'sse', 'cp', 'press', 'aic', 'sbc'),
                                num = 1)

# (c)
# Backward stepwise selection  
backward_model <- step(full_model, direction = "backward", trace = FALSE)

cat("Backward Selection Variables:", names(coef(backward_model))[-1], "\n")

# (d)
# I use the 10th model
final_model <- lm(DISTRESS.2 ~ DISTRESS.1 + BLACK + NBHISP + SLFHLTH + 
                   WORKHARD + GOODQUAL + PROUD + LIKESLF + 
                   ACCEPTED + FEELLOVD, data = distress_data)

summary(final_model)

plot(final_model)

# (e)
# Outlying X observations (leverage)
leverage <- hatvalues(final_model)
n <- nrow(distress_data)
p <- length(coef(final_model))
leverage_threshold <- 2 * p / n

high_leverage <- which(leverage > leverage_threshold)
cat("High Leverage Points (Outlying X):", high_leverage, "\n")
cat("Leverage threshold:", leverage_threshold, "\n")

# Outlying Y observations (standardized residuals)
std_residuals <- rstandard(final_model)
outlying_y <- which(abs(std_residuals) > 3)
cat("Outlying Y observations (|std residual| > 3):", outlying_y, "\n")

# Influence point
cook_dist <- cooks.distance(final_model)
influential_cook <- which(cook_dist > 4/(n-p))
cat("Influential by Cook's Distance:", influential_cook, "\n")