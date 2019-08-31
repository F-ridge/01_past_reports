# install.packages("data.table")

# covariance_selection.Rとcatsvdogs.csvを同ディレクトリに置き，その場所をsetwdで指定してください
# setwd('path')

library(ggm)
library(data.table)
source('covariance_selection.R')

catsvdogs <- read.csv('catsvdogs.csv', sep=',')
keeps <- c(
  'Density', 'Pop_2019', 'Area',
  'Dog.Owners.percentage', 'Mean.Dogs.per.household',
  'Cat.Owners.percentage', 'Mean.Cats.per.household')
catsvdogs <- catsvdogs[keeps]

col_map = c('S1', 'S2', 'S3', 'S4', 'S5', 'S6', 'S7')
setnames(catsvdogs, keeps, col_map) # data.tableが使えない場合はコメントアウトしてください
pairs(catsvdogs)
setnames(catsvdogs, col_map, keeps) # data.tableが使えない場合はコメントアウトしてください

catsvdogs.summary <- summary(catsvdogs)
catsvdogs.summary <- apply(catsvdogs, 2, summary)
catsvdogs.summary

cor(catsvdogs)

col2par(cor(catsvdogs))

options(digits=3)
result <- covselection(catsvdogs)
drawGraph(result[[5]], adjust=TRUE)

result
