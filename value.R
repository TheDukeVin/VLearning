
data <- read.delim("/Users/kevindu/Desktop/Employment/Multiagent Snake Research/V_learning/Classic_V_Learn/exploit.out", sep=',', header = FALSE)

N = length(data[1,])

nums <- integer(N)
for(j in 1:N){
  nums[j] = data[1,j]
}

plot(1:N, nums, type='l')