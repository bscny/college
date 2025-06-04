distress_data <- read.table("./distress.txt", header = TRUE)

# str(distress_data)
# head(distress_data)

# (a)
# Fit full model with DISTRESS.2 as response
full_model <- lm(DISTRESS.2 ~ DISTRESS.1 + BLACK + NBHISP + GRADE + SLFHLTH + 
                   SLFWGHT + WORKHARD + GOODQUAL + PHYSFIT + PROUD + LIKESLF + 
                   ACCEPTED + FEELLOVD + DIET, data = distress_data)

summary(full_model)
