# To add a new cell, type '# %%'
# To add a new markdown cell, type '# %% [markdown]'
# %%
# from IPython import get_ipython

# %% [markdown]
# # Introduction to Linear Regression
#
# *Notebook credit: https://github.com/justmarkham/DAT4*
#
# *Adapted from Chapter 3 of [An Introduction to Statistical Learning](http://www-bcf.usc.edu/~gareth/ISL/)*
#
# ||continuous|categorical|
# |---|---|---|
# |**supervised**|**regression**|classification|
# |**unsupervised**|dimension reduction|clustering|
#
# ## Motivation
#
# Why are we learning linear regression?
# - widely used
# - runs fast
# - easy to use (not a lot of tuning required)
# - highly interpretable
# - basis for many other methods
#
# ## Libraries
#
# Will be using [Statsmodels](http://statsmodels.sourceforge.net/) for **teaching purposes** since it has some nice characteristics for linear modeling. However, we recommend that you spend most of your energy on [scikit-learn](http://scikit-learn.org/stable/) since it provides significantly more useful functionality for machine learning in general.

# %%
# imports
import numpy as np
import statsmodels.formula.api as smf
from sklearn.linear_model import LinearRegression
import seaborn as sns
import pandas as pd
import matplotlib.pyplot as plt

# this allows plots to appear directly in the notebook
get_ipython().run_line_magic('matplotlib', 'inline')


# %% [markdown]
# ## Example: Advertising Data
#
# Let's take a look at some data, ask some questions about that data, and then use linear regression to answer those questions!

# %%
# read data into a DataFrame
data = pd.read_csv('Advertising.csv', index_col=0)
display(data.head())

# %% [markdown]
# What are the **samples**?
# - For a given market, number of dollars spent on different advertising media and number of products sold in that market
#
# What are the **features**?
# - TV: advertising dollars spent on TV for a single product in a given market (in thousands of dollars)
# - Radio: advertising dollars spent on Radio
# - Newspaper: advertising dollars spent on Newspaper
#
# What is the **response**?
# - Sales: sales of a single product in a given market (in thousands of widgets)

# %%
# print the shape of the DataFrame
data.shape

# %% [markdown]
# There are 200 **observations**, and thus 200 markets in the dataset.

# %%
# visualize the relationship between the features and the response using scatterplots
fig, axs = plt.subplots(1, 3, sharey=True)
data.plot(kind='scatter', x='TV', y='sales', ax=axs[0], figsize=(16, 8))
data.plot(kind='scatter', x='radio', y='sales', ax=axs[1])
data.plot(kind='scatter', x='newspaper', y='sales', ax=axs[2])

# %% [markdown]
# ## Questions About the Advertising Data
#
# Let's pretend you work for the company that manufactures and markets this widget. The company might ask you the following: On the basis of this data, how should we spend our advertising money in the future?
#
# This general question might lead you to more specific questions:
# 1. Is there a relationship between ads and sales?
# 2. How strong is that relationship?
# 3. Which ad types contribute to sales?
# 4. What is the effect of each ad type of sales?
# 5. Given ad spending in a particular market, can sales be predicted?
#
# We will explore these questions below!
# %% [markdown]
# ## Simple Linear Regression
#
# Simple linear regression is an approach for predicting a **quantitative response** using a **single feature** (or "predictor" or "input variable"). It takes the following form:
#
# $y = \beta_0 + \beta_1x$
#
# What does each term represent?
# - $y$ is the response
# - $x$ is the feature
# - $\beta_0$ is the intercept
# - $\beta_1$ is the coefficient for x
#
# Together, $\beta_0$ and $\beta_1$ are called the **model coefficients**. To create your model, you must "learn" the values of these coefficients. And once we've learned these coefficients, we can use the model to predict Sales!

# %% [markdown]
# ## Estimating ("Learning") Model Coefficients
#
# Generally speaking, coefficients are estimated using the **least squares criterion**, which means we are find the line (mathematically) which minimizes the **sum of squared residuals** (or "sum of squared errors"):

# %% [markdown]
# <img src="08_estimating_coefficients.png">

# %% [markdown]
# What elements are present in the diagram?
# - The black dots are the **observed values** of x and y.
# - The blue line is our **least squares line**.
# - The red lines are the **residuals**, which are the distances between the observed values and the least squares line.
#
# How do the model coefficients relate to the least squares line?
# - $\beta_0$ is the **intercept** (the value of $y$ when $x$=0)
# - $\beta_1$ is the **slope** (the change in $y$ divided by change in $x$)
#
# Here is a graphical depiction of those calculations:

# %% [markdown]
# <img src="08_slope_intercept.png">

# %% [markdown]
# Suppose $\beta_0$ for spending on TV is large. What does this mean?
# - It means that we could spend very little or none on TV and still make a lot of sales.
#
# Suppose $\beta_1$ for spending on TV is small. What does this mean?
# - It means that if we spend a lot more on TV we're not going to get a lot more sales.
#
# Suppose $\beta_1$ for spending on TV is negative. What does this mean?
# - It means that if spending money on TV advertising actually *hurts* our sales.
# %% [markdown]
# Let's use **scikit-learn** to estimate the model coefficients for the advertising data:

# %%
# create X and y
feature_cols = ['TV']
X = data[feature_cols]
y = data.sales

# print(X)
# print(y)

# follow the usual sklearn pattern: import, instantiate, fit
lm = LinearRegression()
lm.fit(X, y)

# print intercept and coefficients
print(lm.intercept_)
print(lm.coef_)

# %% [markdown]
# ## Interpreting Model Coefficients
#
# How do we interpret the TV coefficient ($\beta_1$)?
# - A "unit" increase in TV ad spending is **associated with** a 0.047537 "unit" increase in Sales.
# - Or more clearly: An additional $1,000 spent on TV ads is **associated with** an increase in sales of 47.537 widgets.
#
# Note that if an increase in TV ad spending was associated with a **decrease** in sales, $\beta_1$ would be **negative**.

# 1 more unit of sales
# slope = dy/dx
# dy = 1
# slope = 0.047
# dx = dy/slope = 1/0.047 = 21 = number of dollars more we need spend in advertising to get one unit of sales increase
# %% [markdown]
# ## Using the Model for Prediction
#
# Let's say that there was a new market where the TV advertising spend was **$50,000**. What would we predict for the Sales in that market?
#
# $$y = \beta_0 + \beta_1x$$
# $$y = 7.032594 + 0.047537 \times 50$$

# %%
# manually calculate the prediction
7.032594 + 0.047537*50

# %% [markdown]
# Thus, we would predict Sales of **9,409 widgets** in that market.
#
# Of course, we can also use Statsmodels to make the prediction:

# %%
# you have to create a DataFrame since the Statsmodels formula interface expects it
X_new = pd.DataFrame({'TV': [50, 55, 60]})
display(X_new)


# %%
# use the model to make predictions on a new value
lm.predict(X_new.values)

# %% [markdown]
# ## Plotting the Least Squares Line
#
# Let's make predictions for the **smallest and largest observed values of x**, and then use the predicted values to plot the least squares line:

# %%
# create a DataFrame with the minimum and maximum values of TV
X_new = pd.DataFrame({'TV': [data.TV.min(), data.TV.max()]})
X_new


# %%
# make predictions for those x values and store them
preds = lm.predict(X_new)
preds


# %%
# first, plot the observed data
data.plot(kind='scatter', x='TV', y='sales')

# then, plot the least squares line
plt.plot(X_new, preds, c='red', linewidth=2)


# %%
# ...or just use seaborn
sns.regplot(x='TV', y='sales', data=data)

# %% [markdown]
# ## Confidence in our Model
#
# **Question:** Is linear regression a high bias/low variance model, or a low bias/high variance model?
#
# **Answer:** High bias/low variance. Under repeated sampling, the line will stay roughly in the same place (low variance), but the average of those models won't do a great job capturing the true relationship (high bias). Note that low variance is a useful characteristic when you don't have a lot of training data!
#
# A closely related concept is **confidence intervals**. Statsmodels calculates 95% confidence intervals for our model coefficients, which are interpreted as follows: If the population from which this sample was drawn was **sampled 100 times**, approximately **95 of those samplings** would fall inside the confidence interval.
#
# **statsmodels** is a handy library to compute things like this.

# %%
# this is the standard import if you're using "formula notation" (similar to R)

# create a fitted model in one line
lm = smf.ols(formula='sales ~ TV', data=data).fit()

# print the coefficients
display(lm.params)

# print the confidence intervals for the model coefficients
display(lm.conf_int())

# %% [markdown]
# Keep in mind that we only have a **single sample of data**, and not the **entire population of data**. The "true" coefficient is either within this interval or it isn't, but there's no way to actually know. We estimate the coefficient with the data we do have, and we show uncertainty about that estimate by giving a range that the coefficient is **probably** within.
#
# Note that using 95% confidence intervals is just a convention. You can create 90% confidence intervals (which will be more narrow), 99% confidence intervals (which will be wider), or whatever intervals you like.
# %% [markdown]
# We can plot confidence intervals using **Seaborn**. The confidence intervals are computed a little differently: the data is binned according to the independent variable and then a band containing 95% of the means of the bin is shown.

# %%

plt.figure()
ax = sns.regplot(x='TV', y='sales', data=data)

plt.figure()
ax = sns.regplot(x='newspaper', y='sales', data=data)

# %% [markdown]
# Note that the shaded region shows all possible regression curves within the 95% confidence interval
# %% [markdown]
# ## Hypothesis Testing and p-values
#
# Closely related to confidence intervals is **hypothesis testing**. Generally speaking, you start with a **null hypothesis** and an **alternative hypothesis** (that is opposite the null). Then, you check whether the data supports **rejecting the null hypothesis** or **failing to reject the null hypothesis**.
#
# (Note that "failing to reject" the null is not the same as "accepting" the null hypothesis. The alternative hypothesis may indeed be true, except that you just don't have enough data to show that.)
#
# As it relates to model coefficients, here is the conventional hypothesis test:
# - **null hypothesis:** There is no relationship between TV ads and Sales (and thus $\beta_1$ equals zero)
# - **alternative hypothesis:** There is a relationship between TV ads and Sales (and thus $\beta_1$ is not equal to zero)
#
# How do we test this hypothesis? Intuitively, we reject the null (and thus believe the alternative) if the 95% confidence interval **does not include zero**. Conversely, the **p-value** represents the probability that the coefficient is actually zero:

# %%
lm = smf.ols(formula='sales ~ TV', data=data).fit()
# print the p-values for the model coefficients
lm.pvalues

# %% [markdown]
# If the 95% confidence interval **includes zero**, the p-value for that coefficient will be **greater than 0.05**. If the 95% confidence interval **does not include zero**, the p-value will be **less than 0.05**. Thus, a p-value less than 0.05 is one way to decide whether there is likely a relationship between the feature and the response. (Again, using 0.05 as the cutoff is just a convention.)
#
# In this case, the p-value for TV is far less than 0.05, and so we **believe** that there is a relationship between TV ads and Sales.
#
# Note that we generally ignore the p-value for the intercept.
#
# Note also that **p-values** and **confidence intervals** are not (easily) accessible through scikit-learn.
# %% [markdown]
# ## How Well Does the Model Fit the data? (R-squared)
#
# The most common way to evaluate the overall fit of a linear model is by the **R-squared** value. R-squared is the **proportion of variance explained**, meaning the proportion of variance in the observed data that is explained by the model, or the reduction in error over the **null model**. (The null model just predicts the mean of the observed response, and thus it has an intercept and no slope.)
#
# $R^2 = 1 - \frac{\text{residual}}{\text{total variation}} = \frac{\sum_{i=1}^N (y_i-\hat{y}_i)^2}{\sum_{i=1}^N (y_i-\overline{y})^2}$
#
# where $\overline{y}$ is the average value and $\hat{y}_i$ is the predicted value.
#
# R-squared is between 0 and 1, and higher is better because it means that more variance is explained by the model. This is a way of normalizing the raw residual. Here's an example of what R-squared "looks like":
# %% [markdown]
# <img src="08_r_squared.png">
# %% [markdown]
# You can see that the **blue line** explains some of the variance in the data (R-squared=0.54), the **green line** explains more of the variance (R-squared=0.64), and the **red line** fits the training data even further (R-squared=0.66). (Does the red line look like it's overfitting?)
#
# Let's calculate the R-squared value for our simple linear model:

# %%
# Print the R-squared value for the model using statsmodels
lm = smf.ols(formula='sales ~ TV', data=data).fit()
display(lm.rsquared)

# Print the R-squared value for the model using sklearn
lm = LinearRegression()
lm.fit(data[['TV']], data.sales)
display(lm.score(data[['TV']], data.sales))

# %% [markdown]
# Is that a "good" R-squared value? It's hard to say. The threshold for a good R-squared value depends widely on the domain. Therefore, it's most useful as a tool for **comparing different models**.
# %% [markdown]
# ## Multiple Linear Regression
#
# Simple linear regression can easily be extended to include multiple features. This is called **multiple linear regression**:
#
# $y = \beta_0 + \beta_1x_1 + ... + \beta_nx_n$
#
# Each $x$ represents a different feature, and each feature has its own coefficient. In this case:
#
# $y = \beta_0 + \beta_1 \times TV + \beta_2 \times Radio + \beta_3 \times Newspaper$
#
# Let's use sklearn to estimate these coefficients:

# %%
# create X and y
feature_cols = ['TV', 'radio', 'newspaper']
X = data[feature_cols]
y = data.sales

# follow the usual sklearn pattern: import, instantiate, fit
lm = LinearRegression()
lm.fit(X, y)

# print intercept and coefficients
display(lm.intercept_)
display(list(zip(feature_cols, lm.coef_)))

# %% [markdown]
# How do we interpret these coefficients? For a given amount of Radio and Newspaper ad spending, an **increase of $1000 in TV ad spending** is associated with an **increase in Sales of 45.765 widgets**.
#
# A lot of the information we have been reviewing piece-by-piece is available in the model summary output using statsmodels:

# %%
# create a fitted model with all three features
lm = smf.ols(formula='sales ~ TV + radio + newspaper', data=data).fit()

# print the coefficients
display(lm.params)

# print a summary of the fitted model
lm.summary()

# %% [markdown]
# What are a few key things we learn from this output?
#
# - TV and Radio have significant **p-values**, whereas Newspaper does not. Thus we reject the null hypothesis for TV and Radio (that there is no association between those features and Sales), and fail to reject the null hypothesis for Newspaper.
# - TV and Radio ad spending are both **positively associated** with Sales, whereas Newspaper ad spending is **slightly negatively associated** with Sales. (However, this is irrelevant since we have failed to reject the null hypothesis for Newspaper.)
# - This model has a higher **R-squared** (0.897) than the previous model, which means that this model provides a better fit to the data than a model that only includes TV.
# %% [markdown]
# ## Feature Selection
#
# How do I decide **which features to include** in a linear model? Here's one idea:
# - Try different models, and only keep predictors in the model if they have small p-values.
# - Check whether the R-squared value goes up when you add new predictors.
#
# What are the **drawbacks** to this approach?
# - Linear models rely upon a lot of **assumptions** (such as the features being independent), and if those assumptions are violated (which they usually are), R-squared and p-values are less reliable.
# - Using a p-value cutoff of 0.05 means that if you add 100 predictors to a model that are **pure noise**, 5 of them (on average) will still be counted as significant.
# - R-squared is susceptible to **overfitting**, and thus there is no guarantee that a model with a high R-squared value will generalize. Below is an example:

# %%
# only include TV and Radio in the model
lm = smf.ols(formula='sales ~ TV + radio', data=data).fit()
lm.rsquared


# %%
# add Newspaper to the model (which we believe has no association with Sales)
lm = smf.ols(formula='sales ~ TV + radio + newspaper', data=data).fit()
lm.rsquared

# %% [markdown]
# **R-squared will always increase as you add more features to the model**, even if they are unrelated to the response. Thus, selecting the model with the highest R-squared is not a reliable approach for choosing the best linear model.
#
# There is alternative to R-squared called **adjusted R-squared** that penalizes model complexity (to control for overfitting), but it generally [under-penalizes complexity](http://scott.fortmann-roe.com/docs/MeasuringError.html).
#
# So is there a better approach to feature selection? **Cross-validation.** It provides a more reliable estimate of out-of-sample error, and thus is a better way to choose which of your models will best **generalize** to out-of-sample data. There is extensive functionality for cross-validation in scikit-learn, including automated methods for searching different sets of parameters and different models. Importantly, cross-validation can be applied to any model, whereas the methods described above only apply to linear models.
# %% [markdown]
# ## Linear Regression in scikit-learn
#
# Let's redo some of the Statsmodels code above in scikit-learn:

# %%
data
# %%
# create X and y
feature_cols = ['TV', 'Radio', 'Newspaper']
X = data[feature_cols]
y = data.Sales

# follow the usual sklearn pattern: import, instantiate, fit
lm = LinearRegression()
lm.fit(X, y)

# print intercept and coefficients
print(lm.intercept_)
print(lm.coef_)


# %%
# pair the feature names with the coefficients
zip(feature_cols, lm.coef_)


# %%
# predict for a new observation
lm.predict([100, 25, 25])


# %%
# calculate the R-squared
lm.score(X, y)

# %% [markdown]
# Note that **p-values** and **confidence intervals** are not (easily) accessible through scikit-learn.
# %% [markdown]
# ## Handling Categorical Predictors with Two Categories
#
# Up to now, all of our predictors have been numeric. What if one of our predictors was categorical?
#
# Let's create a new feature called **Size**, and randomly assign observations to be **small or large**:

# %%

# set a seed for reproducibility
np.random.seed(12345)

# create a Series of booleans in which roughly half are True
nums = np.random.rand(len(data))
mask_large = nums > 0.5

# initially set Size to small, then change roughly half to be large
data['Size'] = 'small'
data.loc[mask_large, 'Size'] = 'large'
data.head()

# %% [markdown]
# For scikit-learn, we need to represent all data **numerically**. If the feature only has two categories, we can simply create a **dummy variable** that represents the categories as a binary value:

# %%
# create a new Series called IsLarge
data['IsLarge'] = data.Size.map({'small': 0, 'large': 1})
data.head()

# %% [markdown]
# Let's redo the multiple linear regression and include the **IsLarge** predictor:

# %%
# create X and y
feature_cols = ['TV', 'Radio', 'Newspaper', 'IsLarge']
X = data[feature_cols]
y = data.Sales

# instantiate, fit
lm = LinearRegression()
lm.fit(X, y)

# print coefficients
zip(feature_cols, lm.coef_)

# %% [markdown]
# How do we interpret the **IsLarge coefficient**? For a given amount of TV/Radio/Newspaper ad spending, being a large market is associated with an average **increase** in Sales of 57.42 widgets (as compared to a Small market, which is called the **baseline level**).
#
# What if we had reversed the 0/1 coding and created the feature 'IsSmall' instead? The coefficient would be the same, except it would be **negative instead of positive**. As such, your choice of category for the baseline does not matter, all that changes is your **interpretation** of the coefficient.
# %% [markdown]
# ## Handling Categorical Predictors with More than Two Categories
#
# Let's create a new feature called **Area**, and randomly assign observations to be **rural, suburban, or urban**:

# %%
# set a seed for reproducibility
np.random.seed(123456)

# assign roughly one third of observations to each group
nums = np.random.rand(len(data))
mask_suburban = (nums > 0.33) & (nums < 0.66)
mask_urban = nums > 0.66
data['Area'] = 'rural'
data.loc[mask_suburban, 'Area'] = 'suburban'
data.loc[mask_urban, 'Area'] = 'urban'
data.head()

# %% [markdown]
# We have to represent Area numerically, but we can't simply code it as 0=rural, 1=suburban, 2=urban because that would imply an **ordered relationship** between suburban and urban (and thus urban is somehow "twice" the suburban category).
#
# Instead, we create **another dummy variable**:

# %%
# create three dummy variables using get_dummies, then exclude the first dummy column
area_dummies = pd.get_dummies(data.Area, prefix='Area').iloc[:, 1:]

# concatenate the dummy variable columns onto the original DataFrame (axis=0 means rows, axis=1 means columns)
data = pd.concat([data, area_dummies], axis=1)
data.head()

# %% [markdown]
# Here is how we interpret the coding:
# - **rural** is coded as Area_suburban=0 and Area_urban=0
# - **suburban** is coded as Area_suburban=1 and Area_urban=0
# - **urban** is coded as Area_suburban=0 and Area_urban=1
#
# Why do we only need **two dummy variables, not three?** Because two dummies captures all of the information about the Area feature, and implicitly defines rural as the baseline level. (In general, if you have a categorical feature with k levels, you create k-1 dummy variables.)
#
# If this is confusing, think about why we only needed one dummy variable for Size (IsLarge), not two dummy variables (IsSmall and IsLarge).
#
# Let's include the two new dummy variables in the model:

# %%
# create X and y
feature_cols = ['TV', 'Radio', 'Newspaper',
                'IsLarge', 'Area_suburban', 'Area_urban']
X = data[feature_cols]
y = data.Sales

# instantiate, fit
lm = LinearRegression()
lm.fit(X, y)

# print coefficients
zip(feature_cols, lm.coef_)

# %% [markdown]
# How do we interpret the coefficients?
# - Holding all other variables fixed, being a **suburban** area is associated with an average **decrease** in Sales of 106.56 widgets (as compared to the baseline level, which is rural).
# - Being an **urban** area is associated with an average **increase** in Sales of 268.13 widgets (as compared to rural).
#
# **A final note about dummy encoding:** If you have categories that can be ranked (i.e., strongly disagree, disagree, neutral, agree, strongly agree), you can potentially use a single dummy variable and represent the categories numerically (such as 1, 2, 3, 4, 5).
# %% [markdown]
# ## What Didn't We Cover?
#
# - Detecting collinearity
# - Diagnosing model fit
# - Transforming predictors to fit non-linear relationships
# - Interaction terms
# - Assumptions of linear regression
# - And so much more!
#
# You could certainly go very deep into linear regression, and learn how to apply it really, really well. It's an excellent way to **start your modeling process** when working a regression problem. However, it is limited by the fact that it can only make good predictions if there is a **linear relationship** between the features and the response, which is why more complex methods (with higher variance and lower bias) will often outperform linear regression.
#
# Therefore, we want you to understand linear regression conceptually, understand its strengths and weaknesses, be familiar with the terminology, and know how to apply it. However, we also want to spend time on many other machine learning models, which is why we aren't going deeper here.
# %% [markdown]
# ## Resources
#
# - To go much more in-depth on linear regression, read Chapter 3 of [An Introduction to Statistical Learning](http://www-bcf.usc.edu/~gareth/ISL/), from which this lesson was adapted. Alternatively, watch the [related videos](http://www.dataschool.io/15-hours-of-expert-machine-learning-videos/) or read my [quick reference guide](http://www.dataschool.io/applying-and-interpreting-linear-regression/) to the key points in that chapter.
# - To learn more about Statsmodels and how to interpret the output, DataRobot has some decent posts on [simple linear regression](http://www.datarobot.com/blog/ordinary-least-squares-in-python/) and [multiple linear regression](http://www.datarobot.com/blog/multiple-regression-using-statsmodels/).
# - This [introduction to linear regression](http://people.duke.edu/~rnau/regintro.htm) is much more detailed and mathematically thorough, and includes lots of good advice.
# - This is a relatively quick post on the [assumptions of linear regression](http://pareonline.net/getvn.asp?n=2&v=8).
