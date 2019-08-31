library(changepoint)
setwd("~/00_reports/3S/experiments/sys_percep")

print("0.25")
err_rate <- read.csv('error_rate_0.25.csv', sep=',')
error_rate <- data.frame(as.numeric(err_rate$error_rate))
x = cpt.mean(error_rate$as.numeric.err_rate.error_rate.)
plot(
  x, type='p', pch=19, ylim=c(-35, 0), xaxt="n", main='0.25 sec',
  xlab="Number of figures", ylab="Median error (%)")
axis(1, at=seq(1, 19, by=2), labels=seq(2, 20, by=2))
print(x)

print('------------------------------')

print("0.5")
err_rate <- read.csv('error_rate_0.5.csv', sep=',')
error_rate <- data.frame(as.numeric(err_rate$error_rate))
x = cpt.mean(error_rate$as.numeric.err_rate.error_rate.)
plot(
  x, type='p', pch=19, ylim=c(-35, 0), xaxt="n", main='0.5 sec',
  xlab="Number of figures", ylab="Median error (%)")
axis(1, at=seq(1, 19, by=2), labels=seq(2, 20, by=2))
print(x)

print('------------------------------')

print("0.75")
err_rate <- read.csv('error_rate_0.75.csv', sep=',')
error_rate <- data.frame(as.numeric(err_rate$error_rate))
x = cpt.mean(error_rate$as.numeric.err_rate.error_rate.)
plot(
  x, type='p', pch=19, ylim=c(-35, 0), xaxt="n", main='0.75 sec',
  xlab="Number of figures", ylab="Median error (%)")
axis(1, at=seq(1, 19, by=2), labels=seq(2, 20, by=2))
print(x)

print('------------------------------')

print("1.0")
err_rate <- read.csv('error_rate_1.0.csv', sep=',')
error_rate <- data.frame(as.numeric(err_rate$error_rate))
x = cpt.mean(error_rate$as.numeric.err_rate.error_rate.)
plot(
  x, type='p', pch=19, ylim=c(-35, 0), xaxt="n", main='1.0 sec',
  xlab="Number of figures", ylab="Median error (%)")
axis(1, at=seq(1, 19, by=2), labels=seq(2, 20, by=2))
print(x)
