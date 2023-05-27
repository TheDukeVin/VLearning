
data <- read.delim("/Users/kevindu/Desktop/Employment/Multiagent Snake Research/V_learning/Classic_V_Learn/probs.out", sep=',', header = FALSE)

N = length(data[,1])

true_val = 0.5

nums <- integer(N)
for(j in 1:N){
  nums[j] = data[j,1]
}

plot(1:N, nums, type='l')
lines(1:N, cumsum(nums) / (1:N), col='red')
lines(c(0, N), c(true_val, true_val), col='blue')
print(mean(nums))
print(var(nums[(N/2):N]))