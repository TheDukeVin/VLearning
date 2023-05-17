
data <- read.delim("/Users/kevindu/Desktop/Employment/Multiagent Snake Research/V_learning/Classic_V_Learn/probs.out", sep=',', header = FALSE)

N = length(data[,1])

true_val = c(1/111, 10/111, 100/111)

for(i in 1:3){
  
  nums <- integer(N)
  for(j in 1:N){
    nums[j] = data[j,i]
  }
  
  plot(1:N, nums, type='l')
  lines(1:N, cumsum(nums) / (1:N), col='red')
  lines(c(0, N), c(true_val[i], true_val[i]), col='blue')
  print(mean(nums))
  print(var(nums[(N/2):N]))
}

